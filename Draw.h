#pragma once
#include "Image.h"
#include "Point.h"
#include "Rectangle.h"

class Draw
{
public:

    static void drawCircle(Image& img, Point center, int radius, unsigned char color);
    static void drawLine(Image& img, Point p1, Point p2, unsigned char color);
    static void drawRectangle(Image& img, Rectangle r, unsigned char color);
    static void drawRectangle(Image& img, Point tl, Point br, unsigned char color);
};