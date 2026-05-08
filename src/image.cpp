#include <cassert>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <filesystem>
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

    try {
        m_imageData = stbi_load(imagePath, &m_width, &m_height, &originalChannels, m_channels);
    
        if (m_imageData) {

            std::cout << "loaded image with width, height, channels: " << m_width << " , " << m_height << " , " << m_channels << std::endl;
            
        } else {
            throw std::invalid_argument("Could not load image: ");
        }
    }
    catch (std::invalid_argument e) {
        std::cout << "Exception: " << e.what() << stbi_failure_reason() << std::endl;
    }
    
    size_t imageSize{static_cast<size_t>(m_width * m_height * m_channels)};

    int grayChannels{m_channels == 4 ? 2 : 1};
    size_t grayImageSize{static_cast<size_t>(m_width * m_height * grayChannels)};

    unsigned char* grayImageData = new unsigned char[grayImageSize];

    if (!grayImageData){
        
        std::cout << "Could not allocate memory for gray image" << std::endl;
    }
    else{
        /*
            Image data is stored in memory like: row,col where col is r,g,b so row0: r0, g0, b0, row0: r1, g1, b1. (row major order)
            Here we get grayscale image
        */
        for (unsigned char* p{m_imageData}, *pg{grayImageData}; p != m_imageData + imageSize; p += m_channels, pg += grayChannels) {
            *pg = static_cast<uint8_t>((*p + *(p + 1) + *(p + 2)) / 3.0);
            
            if(m_channels == 4){
                *(pg + 1) = *(p + 3); // copy transparancy channel over 
            }
        }

        // Testing output, in reality, gray pixels will be mapped to matrix
        this->checkImage((std::filesystem::current_path().parent_path() /= "tests/images/grayLeftTest.png").c_str(), grayImageData);
    }

    delete[] grayImageData;


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

void Image::checkImage(const char* outputPath, unsigned char* data)
{
    stbi_write_png(outputPath, m_width, m_height, 1, data, m_width);
}

/*
Filter the image based on input enum of filter types (mean, median, gaussian)
and allowing member function chaining to filter many times.
*/
Image& Image::filter(FilterType filterToUse)
{
    return *this;
}

/*
    Helper Functions
*/

// Loop through image data memory and copy to matrix format
static void transferToGrayMatrix()
{

}





