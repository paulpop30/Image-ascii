#include "Gamma.h"
#include <math.h>
Gamma::Gamma() : gamma{ 0 } {}
Gamma::Gamma(double gamma)
{
    this->gamma = gamma;
}

double Gamma::getGamma()
{
    return this->gamma;
}

void Gamma::setGamma(double newGamma)
{
    this->gamma = newGamma;
}

void Gamma::process(const Image& src, Image& dst)
{
    dst = src;
    for (int i = 0; i < dst.getHeight(); ++i)
    {
        for (int j = 0; j < dst.getWidth(); ++j)
        {
            int newValue = pow(dst.at(i, j), this->gamma);
            if (newValue > 255)
                newValue = 255;
            else if (newValue < 0)
                newValue = 0;
            dst.setPixel(i, j, newValue);
        }
    }
}