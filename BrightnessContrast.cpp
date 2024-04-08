#include "BrightnessContrast.h"
#include "Image.h"
#include <iostream>


BrightnessContrast::BrightnessContrast() : gain{ 1 }, bias{ 0 } {}

BrightnessContrast::BrightnessContrast(double gain, double bias)
{
    this->gain = gain;
    this->bias = bias;
}

void BrightnessContrast::setGain(double gain)
{
    if (gain > 0)
        this->gain = gain;
    else
        std::cerr << "Gain should be positive!";
}


double BrightnessContrast::getGain() const
{
    return this->gain;
}

void BrightnessContrast::setBias(double bias)
{
    this->bias = bias;
}


double BrightnessContrast::getBias() const
{
    return this->bias;
}


void BrightnessContrast::process(const Image& src, Image& dst)
{
    dst = src;
    dst = dst * gain;
    for (int i = 0; i < dst.getHeight(); ++i)
    {
        for (int j = 0; j < dst.getWidth(); ++j)
        {
            dst.setPixel(i, j, dst.at(i, j) + bias);
        }
    }
}