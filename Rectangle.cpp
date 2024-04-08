#include <iostream>
#include "Rectangle.h"
Rectangle::Rectangle() : x{ 0 }, y{ 0 }, width{ 0 }, height{ 0 } {}

Rectangle::Rectangle(int x, int y, unsigned int width, unsigned int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

int Rectangle::getX() const
{
    return this->x;
}

int Rectangle::getY() const
{
    return this->y;
}

unsigned int Rectangle::getWidth() const
{
    return this->width;
}

unsigned int Rectangle::getHeight() const
{
    return this->height;
}

void Rectangle::setX(int newX)
{
    this->x = newX;
}

void Rectangle::setY(int newY)
{
    this->y = newY;
}

void Rectangle::setWidth(unsigned int newWidth)
{
    this->width = newWidth;
}

void Rectangle::setHeight(unsigned int newHeight)
{
    this->height = newHeight;
}

void Rectangle::operator+(const Point& point)
{
    this->x += point.getX();
    this->y += point.getY();
}

void Rectangle::operator-(const Point& point)
{
    this->x -= point.getX();
    this->y -= point.getY();
}

Rectangle Rectangle::operator&(const Rectangle& rtg)
{
    if (this->x + this->getWidth() <= rtg.getX() ||
        this->y - this->height >= rtg.getY() ||
        this->x >= rtg.getX() + rtg.getWidth() ||
        this->y <= rtg.getY() - rtg.getHeight())
    {
        return Rectangle(0, 0, 0, 0);
    }
    int xIntersect = std::max(this->x, rtg.getX());
    int yIntersect = std::min(this->y, rtg.getY());
    int widthIntersect = std::min(this->x + this->width, rtg.getX() + rtg.getWidth()) - xIntersect;
    int heightIntersect = yIntersect - std::max(this->y - this->height, rtg.getY() - rtg.getHeight());
    return Rectangle(xIntersect, yIntersect, widthIntersect, heightIntersect);
}

Rectangle Rectangle::operator|(const Rectangle& rtg)
{
    int xReunion = std::min(this->x, rtg.getX());
    int yReunion = std::max(this->y, rtg.getY());
    int widthReunion = std::max(this->x + this->width, rtg.getX() + rtg.getWidth()) - xReunion;
    int heightReunion = yReunion - std::min(this->y - this->height, rtg.getY() - rtg.getHeight());
    return Rectangle(xReunion, yReunion, widthReunion, heightReunion);
}