#pragma once
#include "Layer.h"

class Model
{
public:
	Model();
	void AddLayer(Layer* layer);
	~Model();
	void Test(string filename_input, string filename_output);

	void ReadImage(const string filename, BYTE*& pLoadImage, double**& img_Y, double**& img_U, double**& img_V, size_t& nH, size_t& nW);
	void SaveImage(string filename, BYTE*& pLoadImage, Tensor3D*& tensor_Y, double** img_U, double** img_V, size_t nH, size_t nW);
	void SaveImage(string filename, BYTE*& pLoadImage, double** img, size_t nH, size_t nW);
	void PrintLayerInfo() const;
	void PrintTensorInfo() const;

	//	void train();
private:
	vector<Layer*> mLayers;
	vector<Tensor3D*> mTensors;
};