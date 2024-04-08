#pragma once
#include "ImageProcessing.h"
class ImageConvolution : public ImageProcessing {
private:
	int** kernel;
	int w;
	int h;
	int (*scalingFunction)(int filteredValue);
public:
	ImageConvolution(int** kernel, int w, int h, int(&scalingFunction)(int filteredValue));
	~ImageConvolution();
	int applyKernel(const Image& src, int row, int col) const;
	void process(const Image& src, Image& dst) override;
	static int meanBlurScaling(int filteredValue);
	static int gaussianBlurScaling(int filteredValue);
	static int horizontalSobelScaling(int filteredValue);
	static int verticalSobelScaling(int filteredValue);
};