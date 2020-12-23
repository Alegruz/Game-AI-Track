#pragma once
#include "Imagelib.h"

class Tensor3D
{
public:
	Tensor3D(size_t height, size_t width, size_t channelCount);
	virtual ~Tensor3D();
	void SetElem(size_t height, size_t width, size_t channelCount, double value);
	double GetElem(size_t height, size_t width, size_t channelCount) const;
	void GetInfo(size_t& height, size_t& width, size_t& channelCount) const;
	void SetTensor(double*** tensor);
	double*** GetTensor() const;
	size_t GetHeight() const;
	size_t GetWidth() const;
	size_t GetChannelCount() const;
	void Print() const;
private:
	double*** mTensor;
	size_t mHeight; // height
	size_t mWidth; // width
	size_t mChannelCount; // channel
};