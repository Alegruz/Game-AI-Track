
#define _USE_MATH_DEFINES
#include <math.h>

#include <array>
#include <cstdint>
#include <string>
#include <thread>

// 1.1.4 visualization
constexpr const size_t gBufferSize = 80;
const char* gGrayScaleTable = " .:-=+*#%@";
const size_t gGrayScaleTableSize = sizeof(gGrayScaleTable)/sizeof(char);

// 1.1.4 visualization
void AccumulateWaveToHeightField(const double x, 
								 const double waveLength, 
								 const double maxHeight, 
								 std::array<double, gBufferSize>& heightField);
void Draw(const std::array<double, gBufferSize>& heightField);
// 1.1.2 computing motion
void UpdateWave(const double timeInterval, double& x, double& speed);

int main()
{
	// 1.1.4 visualization
	const double waveLengthX = 0.8;
	const double waveLengthY = 1.2;

	const double maxHeightX = 0.5;
	const double maxHeightY = 0.4;

	// 1.1.1 defining state
	double x = 0.0;
	double y = 1.0;

	double speedX = 1.0;
	double speedY = -0.5;

	// 1.1.2 computing motion
	const uint32_t fps = 100;
	const double timeInterval = 1.0 / static_cast<double>(fps);

	// 1.1.4 visualization
	std::array<double, gBufferSize> heightField;

	for (int i = 0; i < 1000; ++i)
	{
		// update waves
		// 1.1.3 boundary handling
		UpdateWave(timeInterval, x, speedX);
		UpdateWave(timeInterval, y, speedY);

		// 1.1.4 visualization
		// clear height field
		for (double& height : heightField)
		{
			height = 0.0;
		}

		// accumulate waves for each center point
		AccumulateWaveToHeightField(x, waveLengthX, maxHeightX, heightField);
		AccumulateWaveToHeightField(y, waveLengthY, maxHeightY, heightField);

		// draw height field
		Draw(heightField);

		// wait
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / fps));
	}

	printf("\n");
	fflush(stdout);

	return 0;
}

// 1.1.4 visualization
void AccumulateWaveToHeightField(const double x, 
								 const double waveLength, 
								 const double maxHeight, 
								 std::array<double, gBufferSize>& heightField)
{
	const double quarterWaveLength = 0.25 * waveLength;
	const int64_t start = static_cast<int64_t>((x - quarterWaveLength) * static_cast<double>(gBufferSize));
	const int64_t end = static_cast<int64_t>((x + quarterWaveLength) * static_cast<double>(gBufferSize));

	for (int64_t i = start; i < end; ++i)
	{
		int64_t newI = i;
		if (i < 0)
		{
			newI = -i - 1;
		}
		else if (i >= static_cast<int64_t>(gBufferSize))
		{
			newI = 2 * gBufferSize - i - 1;
		}

		double distance = fabs((static_cast<double>(i) + 0.5) / static_cast<double>(gBufferSize) - x);
		double height = maxHeight * 0.5 * (cos(fmin(distance * M_PI / quarterWaveLength, M_PI)) + 1.0);
		heightField[newI] += height;
	}
}

void Draw(const std::array<double, gBufferSize>& heightField)
{
	std::string buffer(gBufferSize, ' ');

	// convert height field to grayscale
	for (size_t i = 0; i < gBufferSize; ++i)
	{
		double height = heightField[i];
		size_t tableIndex = static_cast<size_t>(fmin(static_cast<size_t>(floor(gGrayScaleTableSize * height)), gGrayScaleTableSize - 1));
		buffer[i] = gGrayScaleTable[tableIndex];
	}

	// clear old prints
	for (size_t i = 0; i < gBufferSize; ++i)
	{
		printf("\b");
	}

	// draw new buffer
	printf("%s", buffer.c_str);
	fflush(stdout);
}

// 1.1.2 computing motion
void UpdateWave(const double timeInterval, double& x, double& speed)
{
	x += timeInterval * speed;

	// 1.1.3 boundary handling
	// boundary reflection
	if (x > 1.0)
	{
		speed *= -1.0;
		x = 1.0 + timeInterval * speed;
	}
	else if (x < 0.0)
	{
		speed *= -1.0;
		x = timeInterval * speed;
	}
}