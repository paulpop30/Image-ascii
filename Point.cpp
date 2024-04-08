#include "Point.h"
#include<iostream>
Point::Point() : x{0}, y{0} {}

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Point::getX() const
{
    return this->x;
}

int Point::getY() const
{
    return this->y;
}

void Point::setX(int newX)
{
    this->x = newX;
}

void Point::setY(int newY)
{
    this->y = newY;
}