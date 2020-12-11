#include "Layer.h"

Layer::Layer(string name, size_t kernelSize, size_t channelCount, size_t filterCount)
    : mKernelSize(kernelSize)
    , mChannelCount(channelCount)
    , mFilterCount(filterCount)
	, mName(name)
{
}

Layer::~Layer()
{
}