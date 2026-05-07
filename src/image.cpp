#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <iostream>
#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


// Constructor
Image::Image(const char* imagePath)
    : m_imageData{nullptr}
    , m_height{} 
    , m_width{} 
    , m_channels{3}
    , m_grayImageMatrix{} 
    , m_cornerList{}
{
    int originalChannels{};

    m_imageData = stbi_load(imagePath, &m_width, &m_height, &originalChannels, m_channels);

    if (!m_imageData) {
        std::cout << "Could not load image" << stbi_failure_reason() << std::endl;


    } // have to load image for this program to work

    int imageSize{m_width * m_height * m_channels};

    std::cout << "loaded image with height, width, channels: " << m_height << " , " << m_width << " , " << m_channels << std::endl;

}

// Destructor
Image::~Image()
{
    stbi_image_free(m_imageData);
}

// Copy constructor
Image::Image(const Image& image)
{
    int imageSize{m_width * m_height * m_channels};

    m_imageData = (unsigned char*)malloc(imageSize * sizeof(unsigned char*));

    // std::copy(m_imageData, m_imageData + imageSize, &image.m_imageData);

    memcpy(m_imageData, &image.m_imageData, imageSize * sizeof(unsigned char*));

    m_height = image.m_height;
    m_width = image.m_width;
    m_channels = image.m_channels;
    m_grayImageMatrix = image.m_grayImageMatrix;
    m_cornerList = image.m_cornerList;

}

Image& Image::operator=(const Image& image)
{
    if (this != &image) {

        // make sure to always delete/free heap variables before copying again
        stbi_image_free(m_imageData);

        int imageSize{m_width * m_height * m_channels};

        m_imageData = (unsigned char*)malloc(imageSize * sizeof(unsigned char*));

        // std::copy(m_imageData, m_imageData + imageSize, &image.m_imageData);

        memcpy(m_imageData, &image.m_imageData, imageSize * sizeof(unsigned char*));

        m_height = image.m_height;
        m_width = image.m_width;
        m_channels = image.m_channels;
        m_grayImageMatrix = image.m_grayImageMatrix;
        m_cornerList = image.m_cornerList;

    }

    return *this;
}

Image::Image(Image&& image) noexcept
    : m_imageData{std::move(image.m_imageData)}
    , m_height{std::move(image.m_height)}
    , m_width{std::move(image.m_width)}
    , m_channels{std::move(image.m_channels)}
    , m_grayImageMatrix{std::move(image.m_grayImageMatrix)}
    , m_cornerList{std::move(image.m_cornerList)}
{
    image.m_imageData = nullptr;
    image.m_height = 0;
    image.m_width = 0;
    image.m_channels = 3;
    image.m_grayImageMatrix.setZero();
    image.m_cornerList.clear();
}

Image& Image::operator=(Image&& image)
{
    if (this != &image){
        stbi_image_free(m_imageData);

        m_imageData = std::move(image.m_imageData);
        m_height = std::move(image.m_height);
        m_width = std::move(image.m_width);
        m_channels = std::move(image.m_channels);
        m_grayImageMatrix = std::move(image.m_grayImageMatrix);
        m_cornerList = std::move(image.m_cornerList);
    }

    return *this;
}

void Image::checkImage(const char* outputPath)
{
    stbi_write_png(outputPath, m_width, m_height, m_channels, m_imageData, m_width * m_channels);
}

/*
Filter the image based on input enum of filter types (mean, median, gaussian)
and allowing member function chaining to filter many times.
*/
Image& Image::filter(FilterType filterToUse)
{
    return *this;
}





