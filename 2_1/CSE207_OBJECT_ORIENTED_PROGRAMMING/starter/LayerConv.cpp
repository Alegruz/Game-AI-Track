#include "LayerConv.h"

LayerConv::LayerConv(string name, size_t kernelSize, size_t channelCount, size_t filterCount, int initType)
    : LayerConv(name, kernelSize, channelCount, filterCount, initType, "", "")
{
}

LayerConv::LayerConv(string name, size_t kernelSize, size_t channelCount, size_t filterCount, int initType, string weightFilename, string biasFilename)
    : Layer(name, kernelSize, channelCount, filterCount)
    , mWeightFilename(weightFilename)
    , mBiasFilename(biasFilename)
    , mWeightTensor(nullptr)
    , mBiasTensor(nullptr)
{
	mWeightTensor = dmatrix4D_malloc(mKernelSize, mKernelSize, mChannelCount, mFilterCount);
	mBiasTensor = dmatrix1D_malloc(mFilterCount);

	init(initType);
}

void LayerConv::init(int initType)
{
	if (initType == LOAD_INIT)
	{
		ifstream inWeightFile;
		inWeightFile.open(mWeightFilename);
		for (size_t h = 0; h < mKernelSize; ++h)
		{
			for (size_t w = 0; w < mKernelSize; ++w)
			{
				for (size_t ch = 0; ch < mChannelCount; ++ch)
				{
					for (size_t f = 0; f < mFilterCount; ++f)
					{
						inWeightFile >> mWeightTensor[h][w][ch][f];
					}
				}
			}
		}
		inWeightFile.close();

		ifstream inBiasFile;
		inBiasFile.open(mBiasFilename);
		for (size_t f = 0; f < mFilterCount; ++f)
		{
			inBiasFile >> mBiasTensor[f];
		}
		inBiasFile.close();
	}
	else if (initType == MEAN_INIT)
	{
		for (size_t h = 0; h < mKernelSize; ++h)
		{
			for (size_t w = 0; w < mKernelSize; ++w)
			{
				for (size_t f = 0; f < mFilterCount; ++f)
				{
					for (size_t ch = 0; ch < mChannelCount; ++ch)
					{
						mWeightTensor[h][w][ch][f] = 1.0 / (static_cast<double>(mKernelSize) * static_cast<double>(mKernelSize) * static_cast<double>(mChannelCount));
					}
				}
			}
		}
	}
	else
	{
		assert(false);
		return;
	}
}

LayerConv::~LayerConv()
{
	free_dmatrix4D(mWeightTensor, mKernelSize, mKernelSize, mChannelCount, mFilterCount);
	free_dmatrix1D(mBiasTensor, mFilterCount);
}

Tensor3D* LayerConv::Forward(const Tensor3D* input)
{
	size_t height = 0;
	size_t width = 0;
	size_t channelCount = 0;

	input->GetInfo(height, width, channelCount);

	Tensor3D* output = new Tensor3D(height, width, mFilterCount);

	size_t offset = (mKernelSize - 1) / 2;
	for (size_t h = offset; h < height - offset; ++h)
	{
		for (size_t w = offset; w < width - offset; ++w)
		{
			for (size_t f = 0; f < mFilterCount; ++f)
			{
				for (size_t ch = 0; ch < channelCount; ++ch)
				{
					for (size_t kH = 0; kH < mKernelSize; ++kH)
					{
						for (size_t kW = 0; kW < mKernelSize; ++kW)
						{
							output->SetElem(h, w, f, output->GetElem(h, w, f) + input->GetElem(h + kH - offset, w + kW - offset, ch) * mWeightTensor[kH][kW][ch][f]);
						}
					}
				}

				output->SetElem(h, w, f, output->GetElem(h, w, f) + mBiasTensor[f]);
			}
		}
	}

	cout << mName << " is finished" << endl;
	return output;
}

void LayerConv::GetInfo(string& name, size_t& kernelSize, size_t& channelCount, size_t& filterCount) const
{
	name = mName;
	kernelSize = mKernelSize;
	channelCount = mChannelCount;
	filterCount = mFilterCount;
}

void LayerConv::Print() const
{
	std::cout << mKernelSize << "*" << mKernelSize << "*" << mChannelCount << "*" << mFilterCount << std::endl;
}
