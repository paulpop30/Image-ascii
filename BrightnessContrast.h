#pragma once
#include "ImageProcessing.h"


class BrightnessContrast : public ImageProcessing
{

private:
    double gain; 
    double bias;

public:
    
    BrightnessContrast();
    BrightnessContrast(double gain, double bias);
    double getGain() const;
    double getBias() const;
    void setGain(double gain);
    void setBias(double bias);
    void process(const Image& src, Image& dst) override;
};