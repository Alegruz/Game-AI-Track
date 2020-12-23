#include "LayerConv.h"

#include <bitset>
#include <iomanip>

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
		ifstream inBiasFile;
		ifstream inWeightFile;

		inBiasFile.open(mBiasFilename);
		inWeightFile.open(mWeightFilename);

		for (size_t f = 0; f < mFilterCount; ++f)
		{
			for (size_t ch = 0; ch < mChannelCount; ++ch)
			{
				for (size_t h = 0; h < mKernelSize; ++h)
				{
					for (size_t w = 0; w < mKernelSize && !inWeightFile.fail() && !inWeightFile.eof(); ++w)
					{
						inWeightFile >> std::setprecision(18) >> mWeightTensor[h][w][ch][f];
					}
				}
			}
			if (!inBiasFile.eof() && !inBiasFile.fail())
			{
				inBiasFile >> mBiasTensor[f];
				std::cout << std::fixed << std::setprecision(18) << mBiasTensor[f] << std::endl;
			}
		}

		std::cout << mBiasFilename << std::endl;
		// for (size_t i = 0; i < mFilterCount; ++i)
		// {
		// 	std::cout << mBiasTensor[i] << "\t" << std::endl;
		// }
		inBiasFile.close();
		inWeightFile.close();
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

	for (size_t f = 0; f < mFilterCount; ++f)
	{
		for (size_t ch = 0; ch < channelCount; ++ch)
		{
			for (size_t w = offset; w < width - offset; ++w)
			{
				for (size_t h = offset; h < height - offset; ++h)
				{
					for (size_t kW = 0; kW < mKernelSize; ++kW)
					{
						for (size_t kH = 0; kH < mKernelSize; ++kH)
						{
							// if (h == offset && w == offset)
							// {
							// 	std::cout << "output[" << std::setw(2) << h << ", " << std::setw(2) << w << ", " << std::setw(2) << f << "]: " << std::setw(12) << output->GetElem(h, w, f);
							// 	std::cout << " + "
							// 	          << "input[" << std::setw(2) << h + kH - offset << ", " << std::setw(2) << w + kW - offset << ", " << std::setw(2) << ch << "]: " << std::setw(10) << input->GetElem(h + kH - offset, w + kW - offset, ch);
							// 	std::cout << " * "
							// 	          << "mWeightTensor[" << std::setw(2) << kH << ", " << std::setw(2) << kW << ", " << std::setw(2) << ch << ", " << std::setw(2) << f << "]: " << std::setw(10) << mWeightTensor[kH][kW][ch][f] << std::endl;
							// }
							output->SetElem(h, w, f, output->GetElem(h, w, f) + input->GetElem(h + kH - offset, w + kW - offset, ch) * mWeightTensor[kH][kW][ch][f]);
						}
					}

					// if (output->GetElem(h, w, f) >= 1.0)
					// {
					// 	std::cout << "input[" << h << ", " << w << ", " << ch << "] = " << input->GetElem(h, w, ch) << " ~ "
					// 	          << "output[" << h << ", " << w << ", " << f << "] = " << output->GetElem(h, w, f) << std::endl;
					// }

					output->SetElem(h, w, f, output->GetElem(h, w, f) + mBiasTensor[f]);

					if (h == offset && w == offset)
					{
						// std::cout << "output[" << h << ", " << w << ", " << f << "] = " << output->GetElem(h, w, f) << " bias: " << mBiasTensor[f] << std::endl;
					}
				}
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
