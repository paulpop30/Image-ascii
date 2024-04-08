#include <iostream>
#include "ImageConvolution.h"

ImageConvolution::ImageConvolution(int** kernel, int w, int h, int(&scalingFunction)(int filteredValue))
{
    this->w = w;
    this->h = h;
    this->kernel = new int* [h];
    for (int i = 0; i < h; ++i)
    {
        this->kernel[i] = new int[w];
        for (int j = 0; j < w; ++j)
            this->kernel[i][j] = kernel[i][j];
    }
    this->scalingFunction = scalingFunction;
}

ImageConvolution::~ImageConvolution()
{
    for (int i = 0; i < this->h; ++i)
    {
        delete[] this->kernel[i];
    }
    delete[] this->kernel;
    this->kernel = nullptr;
}

int ImageConvolution::meanBlurScaling(int filteredValue)
{
    int scaledValue = filteredValue / 9;
    if (scaledValue > 255)
        scaledValue = 255;
    else if (scaledValue < 0)
        scaledValue = 0;
    return scaledValue;
}

int ImageConvolution::gaussianBlurScaling(int filteredValue)
{
    int scaledValue = filteredValue / 16;
    if (scaledValue > 255)
        scaledValue = 255;
    else if (scaledValue < 0)
        scaledValue = 0;
    return scaledValue;
}

int ImageConvolution::horizontalSobelScaling(int filteredValue)
{
    double normalizedValue = (filteredValue + 4 * 255) / (8.0 * 255);
    double scaledValue = normalizedValue * 255;

    if (scaledValue < 0)
    {
        return 0;
    }
    else if (scaledValue > 255)
    {
        return 255;
    }
    else
    {
        return static_cast<int>(scaledValue);
    }
}

int ImageConvolution::verticalSobelScaling(int filteredValue)
{
    double normalizedValue = (filteredValue + 4 * 255) / (8.0 * 255);
    double scaledValue = normalizedValue * 255;

    if (scaledValue < 0)
    {
        return 0;
    }
    else if (scaledValue > 255)
    {
        return 255;
    }
    else
    {
        return static_cast<int>(scaledValue);
    }
}

void ImageConvolution::process(const Image& src, Image& dst)
{
    int outputW = src.getWidth() - (src.getWidth() % this->w);
    int outputH = src.getHeight() - (src.getHeight() % this->h);
    Image output(outputW, outputH);

    int paddingW = this->w / 2;
    int paddingH = this->h / 2;

    for (int i = paddingH; i < outputH - paddingH; ++i)
    {
        for (int j = paddingW; j < outputW - paddingW; ++j)
        {
            int filteredValue = applyKernel(src, i, j);
            output.setPixel(i, j, this->scalingFunction(filteredValue));
        }
    }
    dst = output;
}

int ImageConvolution::applyKernel(const Image& src, int row, int col) const
{
    int filteredValue = 0;
    int paddingW = this->w / 2;
    int paddingH = this->h / 2;

    for (int i = -paddingH; i <= paddingH; ++i)
    {
        for (int j = -paddingW; j <= paddingW; ++j)
        {
            filteredValue += src.at(row + i, col + j) * this->kernel[i + paddingH][j + paddingW];
        }
    }
    return filteredValue;
}