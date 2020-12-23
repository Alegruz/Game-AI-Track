#include "LayerReLU.h"

LayerReLU::LayerReLU(string name, size_t kernelSize, size_t channelCount, size_t filterCount)
    : Layer(name, kernelSize, channelCount, filterCount)
{
}

LayerReLU::~LayerReLU()
{
}

Tensor3D* LayerReLU::Forward(const Tensor3D* input)
{
	size_t height = 0;
	size_t width = 0;
	size_t channelCount = 0;

	input->GetInfo(height, width, channelCount);

	assert(channelCount == mFilterCount);

	Tensor3D* output = new Tensor3D(height, width, mFilterCount);

	size_t offset = (mKernelSize - 1) / 2;
	for (size_t h = offset; h < height - offset; ++h)
	{
		for (size_t w = offset; w < width - offset; ++w)
		{
			for (size_t f = 0; f < mFilterCount; ++f)
			{
				output->SetElem(h, w, f, input->GetElem(h, w, f) > 0.0 ? input->GetElem(h, w, f) : 0.0);
			}
		}
	}

	cout << mName << " is finished" << endl;
	return output;
}

void LayerReLU::GetInfo(string& name, size_t& kernelSize, size_t& channelCount, size_t& filterCount) const
{
	name = mName;
	kernelSize = mKernelSize;
	channelCount = mChannelCount;
	filterCount = mFilterCount;
}

void LayerReLU::Print() const
{
	std::cout << mKernelSize << "*" << mKernelSize << "*" << mChannelCount << "*" << mFilterCount << std::endl;
}