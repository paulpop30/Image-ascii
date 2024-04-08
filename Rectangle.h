#pragma once
#include "Point.h"
class Rectangle {
public:
	Rectangle();
	Rectangle(int x, int y, unsigned int width, unsigned int height);
	int getX() const;
	int getY() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	void setX(int newX);
	void setY(int newY);
	void setWidth(unsigned int newWidth);
	void setHeight(unsigned int newHeight);
	void operator+(const Point& point);
	void operator-(const Point& point);
	Rectangle operator&(const Rectangle& rtg);
	Rectangle operator|(const Rectangle& rtg);
private:
	int x;
	int y;
	unsigned int height;
	unsigned int width;

};