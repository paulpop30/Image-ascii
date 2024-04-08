#pragma once

class Size {
private: 
	unsigned int height;
	unsigned int width;
public:
	Size();
	Size(unsigned int width, unsigned int height);
	unsigned int getHeight() const;
	unsigned int getWidth() const;
	void setHeight(unsigned int newHeight);
	void setWidth(unsigned int newWidth);
	bool operator==(const Size& other) const;
	bool operator<(const Size& other) const;
	bool operator<=(const Size& other) const;
	bool operator>(const Size& other) const;
	bool operator>=(const Size& other) const;
};