#include <cassert>
#include <cstdlib>

#include "Imagelib.h"
#include "Layer.h"
#include "LayerConv.h"
#include "LayerReLU.h"
#include "Model.h"
#include "Tensor3D.h"

using namespace std;

void Test1();
void Test2();
void Test3();
void Test4();
void PrintAllElements(const Tensor3D& tensor);
Tensor3D* ReadTensor(string filename);

int main(int argc, char* argv[])
{
	size_t nH = 0;
	size_t nW = 0;
	double** input_img_Y;
	double** input_img_U;
	double** input_img_V;
	BYTE* pLoadImage0;

	LoadBmp("baby_512x512_output_srcnn_3.bmp", &pLoadImage0, nH, nW);

	input_img_Y = dmatrix2D_malloc(nH, nW);
	input_img_U = dmatrix2D_malloc(nH, nW);
	input_img_V = dmatrix2D_malloc(nH, nW);

	convert1Dto2D(pLoadImage0, input_img_Y, input_img_U, input_img_V, nH, nW);

	double** img_Y;
	double** img_U;
	double** img_V;

	BYTE* pLoadImage1;
	LoadBmp("baby_512x512_output_srcnn_result.bmp", &pLoadImage1, nH, nW);

	img_Y = dmatrix2D_malloc(nH, nW);
	img_U = dmatrix2D_malloc(nH, nW);
	img_V = dmatrix2D_malloc(nH, nW);

	convert1Dto2D(pLoadImage1, img_Y, img_U, img_V, nH, nW);

	for (size_t i = 0; i < nH; ++i)
	{
		for (size_t j = 0; j < 1; ++j)
		{
			std::cout << i << ", " << j << ": " << input_img_U[i][j] << " " << img_U[i][j] << std::endl;
		}
	}

	free_dmatrix2D(input_img_Y, nH, nW);
	free_dmatrix2D(input_img_U, nH, nW);
	free_dmatrix2D(input_img_V, nH, nW);
	free_dmatrix2D(img_Y, nH, nW);
	free_dmatrix2D(img_U, nH, nW);
	free_dmatrix2D(img_V, nH, nW);


	size_t args = 1;

	if (argc > 5)
	{
		return -1;
	}

	if (argc == 1)
	{
		Test1();
		Test2();
		Test3();
		Test4();
	}

	while (args < static_cast<size_t>(argc))
	{
		switch (atoi(argv[args]))
		{
		case 1:
			Test1();
			break;
		case 2:
			Test2();
			break;
		case 3:
			Test3();
			break;
		case 4:
			Test4();
			break;
		default:
			assert(false);
			break;
		}
		++args;
	}
	/* TEST 1 */
	// Test1();
	/* TEST 2 */
	// Test2();
	/* TEST 3 */
	// Test3();
	/* TEST 4 */
	// Test4();

	return 0;
}

void Test1()
{
	size_t height = 2;
	size_t width = 3;
	size_t channelCount = 2;
	Tensor3D tensor(height, width, channelCount);

	//
	tensor.SetElem(0, 0, 0, 1);
	tensor.SetElem(1, 1, 0, 2);
	tensor.SetElem(0, 0, 1, 3);
	tensor.SetElem(1, 2, 1, 4);

	PrintAllElements(tensor);

	tensor.Print();

	int pause = getchar();
}

void Test2()
{
	Layer* layer1 = new LayerConv("Conv1", 3, 3, 1, MEAN_INIT);
	Layer* layer2 = new LayerReLU("Relu1", 1, 1, 1);

	cout << "(Layer information)________________" << endl;
	layer1->Print();
	layer2->Print();
	cout << endl
	     << endl;

	// tensor1 ->(layer1)-> tensor2 -> (layer2) -> tensor3
	Tensor3D* tensor1 = ReadTensor("tensor_5x5x2.txt");
	Tensor3D* tensor2 = layer1->Forward(tensor1);
	Tensor3D* tensor3 = layer2->Forward(tensor2);
	cout << endl
	     << endl;

	cout << "(Tensor information)________________" << endl;
	cout << "[tensor1]:" << endl;
	tensor1->Print();
	PrintAllElements((*tensor1));
	cout << endl;

	cout << "[tensor2]:" << endl;
	tensor2->Print();
	PrintAllElements((*tensor2));
	cout << endl;

	cout << "[tensor3]:" << endl;
	tensor3->Print();
	PrintAllElements((*tensor3));
	cout << endl;

	int pause = getchar();
}

void Test3()
{
	Model model;

	// build model
	model.AddLayer(new LayerConv("Conv1", 3, 1, 1, MEAN_INIT));
	model.AddLayer(new LayerReLU("Relu1", 1, 1, 1));
	model.AddLayer(new LayerConv("Conv2", 3, 1, 1, MEAN_INIT));
	model.AddLayer(new LayerReLU("Relu2", 1, 1, 1));
	model.AddLayer(new LayerConv("Conv3", 3, 1, 1, MEAN_INIT));

	model.Test("baby_512x512_input.bmp", "baby_512x512_output_mean.bmp");

	model.PrintLayerInfo();
	model.PrintTensorInfo();

	int pause = getchar();
}

void Test4()
{
	Model model;

	// build model
	model.AddLayer(new LayerConv("Conv1", 9, 1, 64, LOAD_INIT, "model/weights_conv1_9x9x1x64.txt", "model/biases_conv1_64.txt"));
	model.AddLayer(new LayerReLU("Relu1", 1, 64, 64));
	model.AddLayer(new LayerConv("Conv2", 5, 64, 32, LOAD_INIT, "model/weights_conv2_5x5x64x32.txt", "model/biases_conv2_32.txt"));
	model.AddLayer(new LayerReLU("Relu2", 1, 32, 32));
	model.AddLayer(new LayerConv("Conv3", 5, 32, 1, LOAD_INIT, "model/weights_conv3_5x5x32x1.txt", "model/biases_conv3_1.txt"));

	model.Test("baby_512x512_input.bmp", "baby_512x512_output_srcnn.bmp");

	model.PrintLayerInfo();
	model.PrintTensorInfo();

	int pause = getchar();
}

Tensor3D* ReadTensor(string filename)
{
	ifstream fin(filename);
	size_t kernelSize = 5;
	size_t channelCount = 2;
	Tensor3D* temp = new Tensor3D(kernelSize, kernelSize, channelCount);

	for (size_t c = 0; c < channelCount; c++)
	{
		for (size_t w = 0; w < kernelSize; w++)
		{
			for (size_t h = 0; h < kernelSize; h++)
			{
				double value;
				fin >> value;
				temp->SetElem(h, w, c, value);
			}
		}
	}
	fin.close();
	return temp;
}

void PrintAllElements(const Tensor3D& tensor)
{
	size_t height = 0;
	size_t width = 0;
	size_t channelCount = 0;
	tensor.GetInfo(height, width, channelCount);
	cout.precision(3);
	for (size_t c = 0; c < channelCount; ++c)
	{
		cout << c << "-th channel:" << endl;
		for (size_t h = 0; h < height; h++)
		{
			for (size_t w = 0; w < width; w++)
			{
				cout << setw(8) << tensor.GetElem(h, w, c);
			}
			cout << endl;
		}
	}
}