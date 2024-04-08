#include <iostream>
#include "Draw.h"
void Draw::drawLine(Image& img, Point p1, Point p2, unsigned char color)
{
    int dx = abs(p2.getX() - p1.getX());
    int dy = abs(p2.getY() - p1.getY());
    int sx = (p1.getX() < p2.getX()) ? 1 : -1;
    int sy = (p1.getY() < p2.getY()) ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        img.setPixel(p1.getY(), p1.getX(), color);

        if (p1.getX() == p2.getX() && p1.getY() == p2.getY())
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            p1.setX(p1.getX() + sx);
        }
        if (e2 < dx)
        {
            err += dx;
            p1.setY(p1.getY() + sy);
        }
    }
}

void Draw::drawCircle(Image& img, Point center, int radius, unsigned char color)
{
    int x = radius;
    int y = 0;
    int radiusError = 1 - x;

    while (x >= y)
    {
        img.setPixel(center.getY() + y, center.getX() + x, color);
        img.setPixel(center.getY() + x, center.getX() + y, color);
        img.setPixel(center.getY() - x, center.getX() + y, color);
        img.setPixel(center.getY() - y, center.getX() + x, color);
        img.setPixel(center.getY() - y, center.getX() - x, color);
        img.setPixel(center.getY() - x, center.getX() - y, color);
        img.setPixel(center.getY() + x, center.getX() - y, color);
        img.setPixel(center.getY() + y, center.getX() - x, color);

        y++;
        if (radiusError < 0)
        {
            radiusError += 2 * y + 1;
        }
        else
        {
            x--;
            radiusError += 2 * (y - x + 1);
        }
    }
}

void Draw::drawRectangle(Image& img, Rectangle r, unsigned char color)
{
    int x = r.getX();
    int y = r.getY();
    drawLine(img, Point(x, y), Point(x + r.getWidth(), y), color);
    drawLine(img, Point(x, y), Point(x, y + r.getHeight()), color);
    drawLine(img, Point(x, y + r.getHeight()), Point(x + r.getWidth(), y + r.getHeight()), color);
    drawLine(img, Point(x + r.getWidth(), y), Point(x + r.getWidth(), y + r.getHeight()), color);
}

void Draw::drawRectangle(Image& img, Point tl, Point br, unsigned char color)
{
    int xTl = tl.getX();
    int yTl = tl.getY();
    int xBr = br.getX();
    int yBr = br.getY();
    int dx = xBr - xTl;
    int dy = yBr - yTl;
    drawLine(img, Point(xTl, yTl), Point(xTl + dx, yTl), color);
    drawLine(img, Point(xTl, yTl), Point(xTl, yTl + dy), color);
    drawLine(img, Point(xTl, yTl + dy), Point(xBr, yBr), color);
    drawLine(img, Point(xBr, yTl), Point(xBr, yBr), color);
}