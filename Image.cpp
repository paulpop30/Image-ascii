#include <iostream>
#include <fstream>
#include <exception>
#include "Image.h"
Image::Image() : m_data{ nullptr }, m_width{ 0 }, m_height{ 0 } {}
Image::Image(unsigned int w, unsigned int h)
{
    this->m_width = w;
    this->m_height = h;
    this->m_data = new unsigned char* [h];
    for (int i = 0; i < h; ++i)
    {
        m_data[i] = new unsigned char[w];
        for (int j = 0; j < w; ++j)
            m_data[i][j] = 0;
    }
}

unsigned int Image::getWidth() const
{
    return this->m_width;
}

unsigned int Image::getHeight() const
{
    return this->m_height;
}

unsigned char** Image::getData() const
{
    return this->m_data;
}

unsigned int Image::maxPixelValue() const
{
    unsigned int maxx = 0;
    for (int i = 0; i < this->m_height; ++i)
        for (int j = 0; j < this->m_width; ++j)
            if (this->m_data[i][j] > maxx)
                maxx = this->m_data[i][j];
    return maxx;
}

void Image::setWidth(unsigned int newWidth)
{
    unsigned char** newData = new unsigned char* [this->m_height];
    for (int i = 0; i < this->m_height; ++i)
    {
        newData[i] = new unsigned char[newWidth];
        if (newWidth < this->m_width)
        {
            for (int j = 0; j < newWidth; ++j)
                newData[i][j] = this->m_data[i][j];
        }
        else
        {
            for (int j = 0; j < this->m_width; ++j)
                newData[i][j] = this->m_data[i][j];
            for (int j = this->m_width; j < newWidth; ++j)
                newData[i][j] = 0;
        }
    }
    for (int i = 0; i < this->m_height; ++i)
        delete[] this->m_data[i];
    delete[] this->m_data;
    this->m_width = newWidth;
    this->m_data = newData;
}

void Image::setPixel(int x, int y, int newValue)
{
    if (newValue > 255)
        newValue = 255;
    else if (newValue < 0)
        newValue = 0;
    this->m_data[x][y] = static_cast<unsigned char>(newValue);
}


void Image::setHeight(unsigned int newHeight)
{
    if (newHeight < this->m_height)
    {
        for (int i = newHeight; i < this->m_height; ++i)
            delete[] this->m_data[i];
        this->m_height = newHeight;
    }
    else
    {
        unsigned char** newData = new unsigned char* [newHeight];
        for (int i = 0; i < newHeight; ++i)
        {
            newData[i] = new unsigned char[this->m_width];
            if (i < this->m_height)
            {
                for (int j = 0; j < this->m_width; ++j)
                    newData[i][j] = this->m_data[i][j];
            }
            else
            {
                for (int j = 0; j < this->m_width; ++j)
                    newData[i][j] = 0;
            }
        }
        delete[] this->m_data;
        this->m_height = newHeight;
        this->m_data = newData;
    }
}

void Image::setPixel(Point point, unsigned int newValue)
{
    this->m_data[point.getX()][point.getY()] = newValue;
}

unsigned char& Image::at(int x, int y) const
{
    return this->m_data[x][y];
}

unsigned char& Image::at(Point point)
{
    return this->m_data[point.getX()][point.getY()];
}

unsigned char* Image::row(int y)
{
    return this->m_data[y];
}

bool Image::getROI(Image& roiImg, Rectangle roiRect)
{

    if (roiRect.getX() + roiRect.getWidth() > roiImg.getWidth() || roiRect.getY() + roiRect.getHeight() > roiImg.getHeight())
        return false;

    Image cropped(roiRect.getWidth(), roiRect.getHeight());
    for (int i = 0; i < cropped.getHeight(); ++i)
    {
        for (int j = 0; j < cropped.getWidth(); ++j)
            cropped.setPixel(i, j, roiImg.at(i + roiRect.getY(), j + roiRect.getX()));
    }
    roiImg = cropped;
    return true;
}

bool Image::getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{

    if (x + width > roiImg.getWidth() || y + height > roiImg.getHeight())
        return false;

    Image cropped(width, height);
    for (int i = 0; i < cropped.getHeight(); ++i)
    {
        for (int j = 0; j < cropped.getWidth(); ++j)
            cropped.setPixel(i, j, roiImg.at(i + y, j + x));
    }
    roiImg = cropped;
    return true;
}

void Image::release()
{
    for (int i = 0; i < this->m_height; ++i)
    {
        delete[] this->m_data[i];
        this->m_data[i] = nullptr;
    }
    delete[] this->m_data;
    this->m_data = nullptr;
}

Image::~Image()
{
    release();
}

Image::Image(const Image& other)
{
    this->m_width = other.getWidth();
    this->m_height = other.getHeight();
    this->m_data = new unsigned char* [this->m_height];
    for (int i = 0; i < this->m_height; ++i)
    {
        this->m_data[i] = new unsigned char[this->m_width];
        for (int j = 0; j < this->m_width; ++j)
            m_data[i][j] = other.m_data[i][j];
    }
}

Image& Image::operator=(const Image& other)
{
    if (this != &other)
    {
        release();
        m_width = other.getWidth();
        m_height = other.getHeight();
        m_data = new unsigned char* [m_height];
        for (int i = 0; i < m_height; ++i)
        {
            m_data[i] = new unsigned char[m_width];
            for (int j = 0; j < m_width; ++j)
                m_data[i][j] = other.m_data[i][j];
        }
    }
    return *this;
}

Image Image::operator+(const Image& i)
{
    try
    {
        if (this->m_width != i.getWidth() || this->m_height != i.getHeight())
            throw std::invalid_argument("Not the same size!");
        Image result(this->m_width, this->m_height);
        for (int k = 0; k < this->m_height; ++k)
            for (int j = 0; j < this->m_width; ++j)
                result.setPixel(k, j, static_cast<unsigned int>(this->m_data[k][j] + i.at(k, j)));
        return result;
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        throw;
    }
}

Image Image::operator-(const Image& i)
{
    try
    {
        if (this->m_width != i.getWidth() || this->m_height != i.getHeight())
            throw std::invalid_argument("Not the same size!");
        Image result(this->m_width, this->m_height);
        for (int k = 0; k < this->m_height; ++k)
            for (int j = 0; j < this->m_width; ++j)
                result.setPixel(k, j, static_cast<unsigned int>(this->m_data[k][j] - i.at(k, j)));
        return result;
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        throw;
    }
}

Image Image::operator*(double s)
{
    Image result(this->m_width, this->m_height);
    for (int i = 0; i < this->m_height; ++i)
        for (int j = 0; j < this->m_width; ++j)
            result.setPixel(i, j, static_cast<int>(this->m_data[i][j] * s));
    return result;
}

Size Image::size() const
{
    return Size(this->m_width, this->m_height);
}

bool Image::isEmpty() const
{
    return m_data == nullptr && m_width == 0 && m_height == 0;
}

std::ostream& operator<<(std::ostream& os, const Image& dt)
{
    os << "P2" << std::endl;
    os << "# This is a pgm format" << std::endl;
    os << dt.getWidth() << " " << dt.getHeight() << std::endl;
    os << dt.maxPixelValue() << std::endl;
    for (int i = 0; i < dt.getHeight(); ++i)
    {
        for (int j = 0; j < dt.getWidth(); ++j)
        {
            os << static_cast<int>(dt.m_data[i][j]) << "  ";
        }
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Image& dt)
{
    std::string format, comment;
    unsigned int width, height, maxPixelValue, value;

    is >> format;
    std::getline(is >> std::ws, comment);
    is >> width;
    is >> height;
    is >> maxPixelValue;
    Image img(width, height);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            is >> value;
            img.setPixel(i, j, value);
        }
    }
    dt = img;
    return is;
}

bool Image::load(const std::string imagePath)
{
    std::ifstream file(imagePath);
    if (!file.is_open())
        return false;

    file >> *this;
    file.close();
    return true;
}

bool Image::save(const std::string imagePath) const
{
    std::ofstream file(imagePath);
    if (!file.is_open())
        return false;
    file << *this;
    file.close();
    return true;
}

Image Image::zeros(unsigned int width, unsigned int height)
{
    Image img(width, height);
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
            img.setPixel(i, j, 0);
    }
    return img;
}

Image Image::ones(unsigned int width, unsigned int height)
{
    Image img(width, height);
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
            img.setPixel(i, j, 1);
    }
    return img;
}