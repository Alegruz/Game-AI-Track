#pragma once
#include "Layer.h"

class LayerReLU : public Layer {
public:
	LayerReLU(string name, size_t kernelSize, size_t channelCount, size_t filterOut);
	virtual ~LayerReLU();
	Tensor3D* Forward(const Tensor3D* input) override;
	void GetInfo(string& name, size_t& kernelSize, size_t& channelCount, size_t& filterOut) const override;
	void Print() const override;
};


