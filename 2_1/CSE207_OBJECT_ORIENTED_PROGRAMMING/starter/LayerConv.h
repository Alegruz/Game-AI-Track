#pragma once
#include "Layer.h"

#define MEAN_INIT (0)
#define LOAD_INIT (1)

class LayerConv : public Layer {
public:
	LayerConv(string name, size_t kernelSize, size_t channelCount, size_t filterCount, int initType);
	LayerConv(string name, size_t kernelSize, size_t channelCount, size_t filterCount, int initType, string weightFilename, string biasFilename);

	void init(int initType);
	virtual ~LayerConv() override;
	Tensor3D* Forward(const Tensor3D* input) override;
	void GetInfo(string& name, size_t& kernelSize, size_t& channelCount, size_t& filterCount) const override;
	void Print() const override;
private:
	string mWeightFilename;
	string mBiasFilename;
	double**** mWeightTensor;
	double*  mBiasTensor;
};



