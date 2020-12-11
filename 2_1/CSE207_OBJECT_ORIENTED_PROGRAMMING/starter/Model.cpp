#include "Model.h"

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

	for (size_t l = 0; l < mLayers.size(); ++l)
	{
		mTensors.push_back(mLayers[l]->Forward(mTensors[l]));
	}

	cout << "Super-resolution is complete..." << endl;

	Tensor3D* output_tensor_Y = mTensors.at(mTensors.size() - 1);
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