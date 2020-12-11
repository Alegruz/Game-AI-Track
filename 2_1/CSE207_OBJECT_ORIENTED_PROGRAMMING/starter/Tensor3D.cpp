#include "Tensor3D.h"

Tensor3D::Tensor3D(size_t height, size_t width, size_t channelCount)
    : mTensor(nullptr)
	, mHeight(height)
    , mWidth(width)
    , mChannelCount(channelCount)
{
	mTensor = dmatrix3D_malloc(mHeight, mWidth, mChannelCount);
}
Tensor3D::~Tensor3D()
{
	if (mTensor != nullptr)
	{
		free_dmatrix3D(mTensor, mHeight, mWidth, mChannelCount);
	}
}

void Tensor3D::SetElem(size_t height, size_t width, size_t channelCount, double value)
{
	assert(height >= 0 && height < mHeight);
	assert(width >= 0 && width < mWidth);
	assert(channelCount >= 0 && channelCount < mChannelCount);

    mTensor[height][width][channelCount] = value;
}

double Tensor3D::GetElem(size_t height, size_t width, size_t channelCount) const
{
	if (!(height >= 0 && height < mHeight))
	{
		std::cout << "height: " << height << " mHeight: " << mHeight << std::endl;
	}
	assert(height >= 0 && height < mHeight);
	if (!(width >= 0 && width < mWidth))
	{
		std::cout << "width: " << width << " mWidth: " << mWidth << std::endl;
	}
	assert(width >= 0 && width < mWidth);
	if (!(channelCount >= 0 && channelCount < mChannelCount))
	{
		std::cout << "channelCount: " << channelCount << " mChannelCount: " << mChannelCount << std::endl;
	}
	assert(channelCount >= 0 && channelCount < mChannelCount);

	return mTensor[height][width][channelCount];
}

void Tensor3D::GetInfo(size_t& height, size_t& width, size_t& channelCount) const
{
	height = mHeight;
	width = mWidth;
	channelCount = mChannelCount;
}

void Tensor3D::SetTensor(double*** tensor)
{
	assert(tensor != nullptr);

	if (tensor != mTensor)
	{
		free_dmatrix3D(mTensor, mHeight, mWidth, mChannelCount);
		mTensor = tensor;
	}
}

double*** Tensor3D::GetTensor() const
{
    return mTensor;
}

void Tensor3D::Print() const
{
	std::cout << mHeight << "*" << mWidth << "*" << mChannelCount << std::endl;
}