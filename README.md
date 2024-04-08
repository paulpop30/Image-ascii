# Image-ascii
Image Processing Library C++
Abstract:
This project aims to provide a comprehensive image processing library implemented in C++. The library offers functionalities for manipulating grayscale images(PGM format), including image convolution, brightness and contrast adjustment, gamma correction, drawing shapes, loading and saving images into PGM format, image arithmetic operations, region of interest extraction. Additionally, the library includes helper classes such as Size, Point, and Rectangle for managing image dimensions, pixel coordinates, and ROIs.

Introduction:
Image processing is a fundamental field in computer science, with applications ranging from medical imaging to computer vision, machine learning and beyond. This library seeks to provide a robust and efficient toolset for performing various image processing tasks using C++.

Feautures:
Image Class: Implements the image ADT for grayscale images. Supports loading and saving images, pixel-wise arithmetic operations, and region of interest extraction.
Size Class: Manages the dimensions of objects, used extensively in the image processing library.
Point Class: Represents a point in a 2D space, useful for pixel coordinates.
Rectangle Class: Encapsulates a rectangular area, facilitating operations such as translation, intersection, reunion.
Image Processing:
Original Image:

Brightness and Contrast adjustment: This processing type operates at each pixel independently and alters the brightness and contrast of the image, as follows:

dst(x, y) = α⋅src(x, y) + β,

where src(x, y) and dst(x, y) represent the pixels at coordinates (x, y) from the input image and the filtered image respectively. The parameters of this operation α>0 (the gain) and β (the bias) are considered to control the contrast and brightness of the image.

The image below shows the result of appling the brightenss color adjustment operation with the value for β = -40. You can notice that negative β values make the resulting image darker. The lower β is, the darker the image is.

Brightness Image

The image below shows the result of appling the contrast color adjustment operation with the value for α = 1.5. The values of α less than 1 make the image darker, while values of α larger than 1 make the image brighter. As opposed to the previous operation (brightness
alteration), you can notice that the greylevel tones are uniformly scaled.

Contrast Image

Gamma correction: Gamma correction is used to correct the overall brightness of an input image with a non-linear transformation function:

dst(x, y) = src(x, y)^γ,

where dst(x, y) and src(x, y) are the values of the pixels at coordinates (x, y) in the filtered image and input image, respectively, and γ is the gamma encoding factor. This operation is needed because humans perceive light in a non-linear manner; the human eye is more sensitive to changes in dark tones than to changes in lighter ones. So, gamma correction is used to optimize the usage of bytes when encoding an image, by taking into consideration this perception difference between the camera sensor and our eyes.

The image below shows the result of appling gamma correction with the value for γ = 1.2. A value of γ less than 1 will darken the image, while a value larger than 1 will make the image appear brighter.

Gamma Image

Convolution Operations: Convolutions are highly used in image processing and machine learning to extract some features from the input image. They involve the usage of a kernel (or filter) that is convolved over the input image as follows:

F = K * I,

where F is the output (filtered) image, K is the convolutional kernel and I is the input image. The convolutional kernel K has the shape (w, h), where w and h are usually odd numbers: w = 2k + 1. At each image position (x, y), the convolutional filter is applied as follows:

F(x, y) = 

The image below shows the result of applying the 3x3 Mean Blur Convolutional Kernel(+scaling).

MeanBlur Image

The image below shows the result of applying the 3x3 Gaussian Blur Convolutional Kernel(+scaling).

Gaussian Image

The image below shows the result of applying the 3x3 Horizontal Sobel Convolutional Kernel(+scaling).

Horizontal Sobel Image

The image below shows the result of applying the 3x3 Vertical Sobel Convolutional Kernel(+scaling).

Vertical Sobel Image

Drawing : The module for drawing shapes over images aims to provide a simple and intuitive interface for adding basic geometric shapes such as circles, lines, and rectangles onto images. This can be useful for annotations, highlighting areas of interest, or creating simple graphics.

The image below shows the result of drawing a white line from (456, 235) to (189, 220), a circle of center (271, 119) and radius 50, and a rectangle with top left corner (456, 235), bottom right corner (615, 343).

Draw Image
