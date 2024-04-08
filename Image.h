#pragma once
#include "Size.h"
#include "Point.h"
#include "Rectangle.h"
#include <string>
class Image
{
public:
	Image();
	Image(unsigned int w, unsigned int h);
	Image(const Image& other);
	Image& operator=(const Image& other);
	~Image();
	bool load(std::string imagePath);
	bool save(std::string imagePath) const;
	Image operator+(const Image& i);
	Image operator-(const Image& i);
	Image operator*(double s);
	bool getROI(Image& roiImg, Rectangle roiRect);
	bool getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	bool isEmpty() const;
	Size size() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	unsigned char** getData() const;
	void setWidth(unsigned int newWidth);
	void setHeight(unsigned int newHeight);
	void setPixel(int x, int y, int newValue);
	void setPixel(Point point, unsigned int newValue);
	unsigned char& at(int x, int y) const;
	unsigned char& at(Point pt);
	unsigned char* row(int y);
	void release();
	friend std::ostream& operator<<(std::ostream& os, const Image& dt);
	friend std::istream& operator>>(std::istream& is, Image& dt);
	static Image zeros(unsigned int width, unsigned int height);
	static Image ones(unsigned int width, unsigned int height);
	unsigned int maxPixelValue() const;
private:
	unsigned char** m_data;
	unsigned int m_width;
	unsigned int m_height;
};