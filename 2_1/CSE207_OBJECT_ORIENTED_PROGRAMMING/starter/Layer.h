#pragma once
#include "Imagelib.h"
#include "Tensor3D.h"

class Layer {
public:
	Layer(string name, size_t kernelSize, size_t channelCount, size_t filterCount);
	virtual ~Layer();
	virtual Tensor3D* Forward(const Tensor3D* input) = 0;
	//	virtual bool backward() = 0;
	virtual void Print() const = 0;
	virtual void GetInfo(string& name, size_t& kernelSize, size_t& channelCount, size_t& filterCount) const = 0;
protected:
	size_t mKernelSize; // kernel size in K*K kernel
	size_t mChannelCount; // number of channels
	size_t mFilterCount; //number of filters
	string mName;
};