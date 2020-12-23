#include "Model.h"

#include <cstdio>

Model::Model()
{
}

void Model::AddLayer(Layer* layer)
{
	if (layer != nullptr)
	{
		mLayers.push_back(layer);
	}
}

Model::~Model()
{
	for (Layer* layer : mLayers)
	{
		delete layer;
	}

	for (Tensor3D* tensor : mTensors)
	{
		delete tensor;
	}
}

void Model::Test(string filename_input, string filename_output)
{
	size_t nH = 0;
	size_t nW = 0;
	double** input_img_Y;
	double** input_img_U;
	double** input_img_V;
	BYTE* pLoadImage;

	ReadImage(filename_input, pLoadImage, input_img_Y, input_img_U, input_img_V, nH, nW);
	cout << "Reading (" << filename_input << ") is complete..." << endl;

	double** zero_img = dmatrix2D_malloc(nH, nW);

	Tensor3D* prevTensor = nullptr;
	Tensor3D* curTensor = mTensors[0];
	for (size_t l = 0; l < mLayers.size(); ++l)
	{
		// std::cout << "layer[" << l << "]" << std::endl;
		// prevTensor = curTensor;
		// curTensor = mLayers[l]->Forward(curTensor);
		// delete prevTensor;
		mTensors.push_back(mLayers[l]->Forward(mTensors[l]));
		// for (size_t imageIndex = 0; imageIndex < (mTensors[l + 1])->GetChannelCount(); ++imageIndex)
		// {
		// 	char* tempFilename = new char[100];
		// 	sprintf(tempFilename, "image/%s_%lu_%lu", filename_output.c_str(), l, imageIndex);
		// 	double** img = dmatrix2D_malloc(nH, nW);
		// 	convert3Dto2D(mTensors[mTensors.size() - 1]->GetTensor(), img, imageIndex, nH, nW);
		// 	SaveImage(tempFilename, pLoadImage, img, nH, nW);
		// 	delete[] tempFilename;
		// }
	}

	cout << "Super-resolution is complete..." << endl;

	Tensor3D* output_tensor_Y = mTensors.at(mTensors.size() - 1);

	// for (size_t w = 0; w < 512; ++w)
	// {
	// 	for (size_t h = 0; h < 512; ++h)
	// 	{
	// 		if (output_tensor_Y->GetElem(h, w, 0) > 1.0)
	// 		{
	// 			output_tensor_Y->SetElem(h, w, 0, 1.0);
	// 		}
	// 		if (output_tensor_Y->GetElem(h, w, 0) > 1.0)
	// 		{
	// 			printf("%lf\n", output_tensor_Y->GetElem(h, w, 0));
	// 		}
	// 	}
	// }

	SaveImage(filename_output, pLoadImage, output_tensor_Y, input_img_U, input_img_V, nH, nW);
	cout << "Saving (" << filename_output << ") is complete..." << endl;

	free(pLoadImage);
	free_dmatrix2D(input_img_Y, nH, nW);
	free_dmatrix2D(input_img_U, nH, nW);
	free_dmatrix2D(input_img_V, nH, nW);
}

void Model::ReadImage(const string filename, BYTE*& pLoadImage, double**& img_Y, double**& img_U, double**& img_V, size_t& nH, size_t& nW)
{

	LoadBmp(filename.c_str(), &pLoadImage, nH, nW);

	img_Y = dmatrix2D_malloc(nH, nW);
	img_U = dmatrix2D_malloc(nH, nW);
	img_V = dmatrix2D_malloc(nH, nW);

	convert1Dto2D(pLoadImage, img_Y, img_U, img_V, nH, nW);

	double*** inImage3D = dmatrix3D_malloc(nH, nW, 1);
	convert2Dto3D(img_Y, inImage3D, nH, nW);

	Tensor3D* temp = new Tensor3D(nH, nW, 1);
	temp->SetTensor(inImage3D);
	mTensors.push_back(temp);
}

void Model::SaveImage(string filename, BYTE*& pLoadImage, Tensor3D*& tensor_Y, double** img_U, double** img_V, size_t nH, size_t nW)
{
	double** img_Y = dmatrix2D_malloc(nH, nW);
	convert3Dto2D(tensor_Y->GetTensor(), img_Y, nH, nW);
	convert2Dto1D(img_Y, img_U, img_V, pLoadImage, nH, nW);
	SaveBmp(filename.c_str(), pLoadImage, nH, nW);
	free_dmatrix2D(img_Y, nH, nW);
}

void Model::SaveImage(string filename, BYTE*& pLoadImage, double** img, size_t nH, size_t nW)
{
	convert2Dto1D(img, img, img, pLoadImage, nH, nW);
	SaveBmp(filename.c_str(), pLoadImage, nH, nW);
	free_dmatrix2D(img, nH, nW);
}

void Model::PrintLayerInfo() const
{
	cout << endl << "(Layer information)_____________" << endl;
	for (unsigned i = 0; i < mLayers.size(); i++)
	{
		cout << i + 1 << "-th layer: ";
		mLayers.at(i)->Print();
	}
}

void Model::PrintTensorInfo() const
{
	cout << endl << "(Tensor information)_____________" << endl;
	for (unsigned i = 0; i < mTensors.size(); i++)
	{
		cout << i + 1 << "-th tensor: ";
		mTensors.at(i)->Print();
	}
}

//	void Train() {}