#include "Image.h"
#include "BrightnessContrast.h"
#include "Gamma.h"
#include "ImageConvolution.h"
#include "Draw.h"
#include <iostream>

int main()
{
    // Load an image
    Image img;
    std::cout << img.load("gator.ascii.pgm") << ' ';
    Image dst;

    // Test Brightness
    BrightnessContrast bc(1.5, 0);
    bc.process(img, dst); //brightens the image
    std::cout << dst.save("contrast_output.ascii.pgm");

    bc.setGain(1);
    bc.setBias(-40); //darkens the image
    bc.process(img, dst);

    std::cout << dst.save("brightness_output.ascii.pgm");

    // Test Gamma correction
    Gamma gamma(1.2); // brightens the image
    gamma.process(img, dst);
    std::cout << dst.save("gamma_correction_output.ascii.pgm");

    // Test ImageConvolution(Mean Blur)
    int** meanKernel;
    meanKernel = new int* [3];
    for (int i = 0; i < 3; ++i)
    {
        meanKernel[i] = new int[3];
        for (int j = 0; j < 3; ++j)
            meanKernel[i][j] = 1;
    }
    ImageConvolution ic(meanKernel, 3, 3, ImageConvolution::meanBlurScaling);
    ic.process(img, dst);
    std::cout << dst.save("convolution_meanBlur.ascii.pgm");

    // Test ImageConvolution(Gaussian Blur)
    int** gaussianKernel = new int* [3] {
        new int[3] {1, 2, 1},
            new int[3] {2, 4, 2},
            new int[3] {1, 2, 1}};
    ImageConvolution ic2(gaussianKernel, 3, 3, ImageConvolution::gaussianBlurScaling);
    ic2.process(img, dst);
    std::cout << dst.save("convolution_gaussianBlur.ascii.pgm");

    // Test ImageConvolution(Horizontal Sobel)
    int** horizontalSobelKernel = new int* [3] {
        new int[3] {1, 2, 1},
            new int[3] {0, 0, 0},
            new int[3] {-1, -2, -1}};
    ImageConvolution ic3(horizontalSobelKernel, 3, 3, ImageConvolution::horizontalSobelScaling);
    ic3.process(img, dst);
    std::cout << dst.save("convolution_horizontalSobel.ascii.pgm");

    // Test ImageConvolution(Vertical Sobel)
    int** verticalSobelKernel = new int* [3] {
        new int[3] {-1, 0, 1},
            new int[3] {-2, 0, 2},
            new int[3] {-1, 0, 1}};
    ImageConvolution ic4(verticalSobelKernel, 3, 3, ImageConvolution::verticalSobelScaling);
    ic4.process(img, dst);
    std::cout << dst.save("convolution_verticalSobel.ascii.pgm");

    // Test drawing functions
    Draw draw;
    Point p1(456, 235);
    Point p2(189, 220);
    draw.drawLine(img, p1, p2, 255); // Draw a line
    draw.drawCircle(img, Point(271, 119), 50, 255); // Draw a circle
    draw.drawRectangle(img, p1, Point(615, 343), 255); // Draw a rectangle
    std::cout << img.save("drawing_output.ascii.pgm"); // Save the result

    return 0;
}