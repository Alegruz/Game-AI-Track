#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define LOG_OUT(_x_) OutputDebugString(_x_)
#define LOG_OUT_W(_x_) OutputDebugStringW(_x_)
#define LOG_OUT_A(_x_) OutputDebugStringA(_x_)

typedef unsigned char BYTE;

bool LoadBmp(const char* filename, BYTE** pImage, size_t& height, size_t& width);
bool SaveBmp(const char* filename, BYTE* pImage, size_t height, size_t width);
bool convert1Dto2D(BYTE* src, double** dst_Y, double** dst_U, double** dst_V, size_t height, size_t width);
bool convert2Dto1D(double** src_Y, double** src_U, double** src_V, BYTE* dst, size_t height, size_t width);

void convert2Dto3D(double** src2D, double*** dst3D, size_t height, size_t width);
void convert3Dto2D(double*** src3D, double** dst2D, size_t height, size_t width);

double* dmatrix1D_malloc(size_t height);
double** dmatrix2D_malloc(size_t height, size_t width);
double*** dmatrix3D_malloc(size_t height, size_t width, size_t channelCount);
double**** dmatrix4D_malloc(size_t height, size_t width, size_t channelCount, size_t filterCount);

void free_dmatrix1D(double* Image, size_t height);
void free_dmatrix2D(double** Image, size_t height, size_t width);
void free_dmatrix3D(double*** Image, size_t height, size_t width, size_t channelCount);
void free_dmatrix4D(double**** Image, size_t height, size_t width, size_t channelCount, size_t filterCount);

double clip(double x, double minVal, double maxVal);
double** simpleUpsampling2x(double** Image, size_t height, size_t width);