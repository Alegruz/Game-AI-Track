#include "loadbmp.h"
#include "Imagelib.h"

#include <cstdio>
#include <cstring>

#define IS_WINDOWS (0)

bool LoadBmp(const char* filename, BYTE** pImage, size_t& height, size_t& width)
{
#if IS_WINDOWS
	FILE* fp;

	BITMAPFILEHEADER BMFH;					///< BitMap File Header.
	BITMAPINFOHEADER BMIH;					///< BitMap Info Header.

	fopen_s(&fp, filename, "rb");
	if (nullptr == fp)
	{
		LOG_OUT_A("fopen() error");
		return false;
	}

	fread(&BMFH, sizeof(BITMAPFILEHEADER), 1, fp);
	if (BMFH.bfType != 0x4d42)
	{
		fclose(fp);
		LOG_OUT_A("not '.bmp' file !!!");
		return false;
	}

	fread(&BMIH, sizeof(BITMAPINFOHEADER), 1, fp);
	if (BMIH.biBitCount != 24 || BMIH.biCompression != BI_RGB)
	{
		fclose(fp);
		return false;
	}

	INT Width = BMIH.biWidth;
	INT Height = BMIH.biHeight - 1;
	INT BytePerScanline = (Width * 3 + 3) & ~3;  // �е�
	INT size = BMFH.bfSize;
	height = BMIH.biHeight;
	width = BMIH.biWidth;

	*pImage = (std::BYTE*) (BYTE*) malloc(size);

	fread(*pImage, size, 1, fp);  // ������ ������ ���� �о�´�.
								  //*pImage += BytePerScanline * Height;

								  // FILE*�� ����.
	fclose(fp);
#endif
	unsigned int uiHeight = static_cast<unsigned int>(height);
	unsigned int uiWidth = static_cast<unsigned int>(width);
	loadbmp_decode_file(filename, pImage, &uiHeight, &uiWidth, LOADBMP_RGB);
	height = static_cast<size_t>(uiHeight);
	width = static_cast<size_t>(uiWidth);

    return true;
}

bool SaveBmp(const char* filename, BYTE* pImage, size_t height, size_t width)
{
#if IS_WINDOWS
	// DIB�� ������ �����Ѵ�.
	BITMAPINFO dib_define;
	dib_define.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	dib_define.bmiHeader.biWidth = width;
	dib_define.bmiHeader.biHeight = height;
	dib_define.bmiHeader.biPlanes = 1;
	dib_define.bmiHeader.biBitCount = 24;
	dib_define.bmiHeader.biCompression = BI_RGB;
	dib_define.bmiHeader.biSizeImage = (((width * 24 + 31) & ~31) >> 3) * height;
	dib_define.bmiHeader.biXPelsPerMeter = 0;
	dib_define.bmiHeader.biYPelsPerMeter = 0;
	dib_define.bmiHeader.biClrImportant = 0;
	dib_define.bmiHeader.biClrUsed = 0;

	// DIB ������ ��� ������ �����Ѵ�.
	BITMAPFILEHEADER dib_format_layout;
	ZeroMemory(&dib_format_layout, sizeof(BITMAPFILEHEADER));
	memset(dib_format_layout, 0, sizeof(BITMAPFILEHEADER));
	dib_format_layout.bfType = *(WORD*)"BM";
	dib_format_layout.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);// +dib_define.bmiHeader.biSizeImage;
	dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// ���� ����.
	FILE* fp = nullptr;
	fopen_s(&fp, filename, "wb");
	if (nullptr == fp)
	{
		LOG_OUT_A("fopen() error");
		return false;
	}

	// ���� �� ��� �� ������ ����.
	fwrite(&dib_format_layout, 1, sizeof(BITMAPFILEHEADER), fp);
	fwrite(&dib_define, 1, sizeof(BITMAPINFOHEADER), fp);
	fwrite(pImage, 1, dib_define.bmiHeader.biSizeImage, fp);
	fclose(fp);
#endif
	loadbmp_encode_file(filename, pImage, width, height, LOADBMP_RGB);

    return true;
}
bool convert1Dto2D(BYTE* src, double** dst_Y, double** dst_U, double** dst_V, size_t height, size_t width)
{
    int iR, iG, iB;
    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            iB = static_cast<int>(src[3 * width * y + 3 * x + 0]);
            iG = static_cast<int>(src[3 * width * y + 3 * x + 1]);
            iR = static_cast<int>(src[3 * width * y + 3 * x + 2]);

            dst_Y[y][x] = iR * 0.299 + iG * 0.587 + iB * 0.114;
            dst_U[y][x] = (iB - dst_Y[y][x]) * 0.565;
            dst_V[y][x] = (iR - dst_Y[y][x]) * 0.713;

            dst_Y[y][x] = dst_Y[y][x] / 255.0; // in the range from [0, 255] to [0, 1]
        }
    }
    return true;
}

bool convert2Dto1D(double** src_Y, double** src_U, double** src_V, BYTE* dst, size_t height, size_t width)
{
    int iCount = 0;
    int iR, iG, iB;
    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
			if (src_Y[y][x] < 0.0 || src_Y[y][x] > 1.0)
			{
				std::cout << x << ", " << y << ": " << src_Y[y][x] << std::endl;
			}
            src_Y[y][x] = src_Y[y][x] * 255.0; // in the range from [0, 1] to [0, 255]
            iR = static_cast<int>(BYTE(clip(src_Y[y][x] + 1.403 * src_V[y][x], 0, 255)));
            iG = static_cast<int>(BYTE(clip(src_Y[y][x] - 0.344 * src_U[y][x] - 0.714 * src_V[y][x], 0, 255)));
            iB = static_cast<int>(BYTE(clip(src_Y[y][x] + 1.770 * src_U[y][x], 0, 255)));

            dst[iCount + 0] = static_cast<BYTE>(iB);
            dst[iCount + 1] = static_cast<BYTE>(iG);
            dst[iCount + 2] = static_cast<BYTE>(iR);
            iCount = iCount + 3;
        }
    }

    return true;
}

double clip(double x, double minVal, double maxVal)
{
    if (x < minVal)
        x = minVal;
    if (x > maxVal)
        x = maxVal;

    return x;
}

double** simpleUpsampling2x(double** Image, size_t height, size_t width)
{
    double** outImg = dmatrix2D_malloc(height * 2, width * 2);

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            outImg[2 * y + 0][2 * x + 0] = Image[y][x];
            outImg[2 * y + 0][2 * x + 1] = Image[y][x];
            outImg[2 * y + 1][2 * x + 0] = Image[y][x];
            outImg[2 * y + 1][2 * x + 1] = Image[y][x];
        }
    }
    return outImg;
}

double* dmatrix1D_malloc(size_t height)
{
    double* tmp = new double[height];
    return tmp;
}

double** dmatrix2D_malloc(size_t height, size_t width)
{
    double** Temp;

    Temp = new double*[height];
    for (int y = 0; y < height; y++)
        Temp[y] = new double[width];

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Temp[y][x] = 0;
        }
    }

    return Temp;
}

double*** dmatrix3D_malloc(size_t height, size_t width, size_t channelCount)
{
    double*** Temp;

    Temp = new double**[height];
    for (size_t y = 0; y < height; y++)
	{
        Temp[y] = new double*[width];
	}

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            Temp[y][x] = new double[channelCount];
        }
    }

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            for (size_t c = 0; c < channelCount; c++)
            {
                Temp[y][x][c] = 0;
            }
        }
    }

    return Temp;
}

double**** dmatrix4D_malloc(size_t height, size_t width, size_t channelCount, size_t filterCount)
{
    double**** Temp;

    Temp = new double***[height];
    for (int y = 0; y < height; y++)
        Temp[y] = new double**[width];

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Temp[y][x] = new double*[channelCount];
        }
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < channelCount; c++)
            {
                Temp[y][x][c] = new double[filterCount];
            }
        }
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < channelCount; c++)
            {
                for (int n = 0; n < filterCount; n++)
                    Temp[y][x][c][n] = 0;
            }
        }
    }

    return Temp;
}

void free_dmatrix1D(double* Image, size_t height)
{
    delete[] Image;
}

void free_dmatrix2D(double** Image, size_t height, size_t width)
{
    for (int y = 0; y < height; y++)
        delete[] Image[y];

    delete[] Image;
}

void free_dmatrix3D(double*** Image, size_t height, size_t width, size_t channelCount)
{
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            delete[] Image[y][x];
        }

    for (int y = 0; y < height; y++)
        delete[] Image[y];

    delete[] Image;
}

void free_dmatrix4D(double**** Image, size_t height, size_t width, size_t channelCount, size_t filterCount)
{
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < channelCount; c++)
            {
                delete[] Image[y][x][c];
            }
        }
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            delete[] Image[y][x];
        }

    for (int y = 0; y < height; y++)
        delete[] Image[y];

    delete[] Image;
}

void convert2Dto3D(double** src2D, double*** dst3D, size_t height, size_t width)
{
    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            dst3D[y][x][0] = src2D[y][x];
        }
    }
}

void convert3Dto2D(double*** src3D, double** dst2D, size_t height, size_t width)
{
    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            dst2D[y][x] = src3D[y][x][0];
        }
    }
}

void convert3Dto2D(double*** src3D, double** dst2D, size_t filter, size_t height, size_t width)
{
    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            dst2D[y][x] = src3D[y][x][filter] / 3.0;
        }
    }
}