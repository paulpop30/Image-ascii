#pragma once
#include "ImageProcessing.h"
class Gamma : public ImageProcessing
{
private:
    double gamma; 

public:
   
    Gamma();
    Gamma(double gamma);
    double getGamma();
    void setGamma(double newGamma);
    void process(const Image& src, Image& dst) override;
};