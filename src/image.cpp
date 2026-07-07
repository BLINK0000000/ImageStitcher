#include <cassert>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <filesystem>
#include "image.h"
#include "filepaths.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

/*
    Helper Functions
*/

/*
    Class Definitions
*/

// Constructor
Image::Image(const char* imageName)
    : m_imageData{nullptr}
    , m_height{} 
    , m_width{} 
    , m_channels{3}
    , m_grayImageMatrix{} 
    , m_cornerList{}
{
    int originalChannels{};

    const fp::path imagePath = fp::assetsDir / imageName;

    try {
        m_imageData = stbi_load(imagePath.c_str(), &m_width, &m_height, &originalChannels, m_channels);
    
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

        m_grayImageMatrix.resize(m_height, m_width);
        m_grayImageMatrix = Eigen::Map<Eigen::Matrix<uint8_t, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>, 0>(grayImageData, m_height, m_width);

        delete[] grayImageData;
    } 
}

// Destructor
Image::~Image()
{
    stbi_image_free(m_imageData);
}

// Copy constructor
Image::Image(const Image& image)
{
    size_t imageSize{static_cast<size_t>(image.m_width * image.m_height * image.m_channels)};

    m_imageData = (unsigned char*)malloc(imageSize * sizeof(unsigned char));

    // std::copy(m_imageData, m_imageData + imageSize, &image.m_imageData);

    memcpy(m_imageData, image.m_imageData, imageSize * sizeof(unsigned char));

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

        m_imageData = (unsigned char*)malloc(imageSize * sizeof(unsigned char));

        // std::copy(m_imageData, m_imageData + imageSize, &image.m_imageData);

        memcpy(m_imageData, &image.m_imageData, imageSize * sizeof(unsigned char));

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

void Image::checkImage(const char* output)
{   
    const fp::path outputPath = fp::imageTestsDir / output;
    stbi_write_png(outputPath.c_str(), m_width, m_height, m_channels, m_imageData, m_width * m_channels);
    
}

void Image::checkGrayImage(const char* output)
{
    const fp::path outputPath = fp::imageTestsDir / output;

    // Testing output, in reality, gray pixels will be mapped to matrix
    uint8_t* grayImageData = m_grayImageMatrix.data();

    stbi_write_png(outputPath.c_str(), m_width, m_height, 1, grayImageData, m_width);
}

/*
    Create a padded image matrix from this image object
*/
Image::ImageMatrix Image::boundaryPad()
{
    Image::ImageMatrix paddedImg{}; // make it so the boundary padding function returns this, makes no sense it's created here
    
    paddedImg.resize(m_grayImageMatrix.rows() + 2 , m_grayImageMatrix.cols() + 2);
    paddedImg.setZero();

    paddedImg.block<1, Eigen::Dynamic>(0, 1, 1, m_grayImageMatrix.cols()) = m_grayImageMatrix.topRows(1);
    paddedImg.block<Eigen::Dynamic, 1>(1, 0, m_grayImageMatrix.rows(), 1) = m_grayImageMatrix.leftCols(1); 
    paddedImg.block<1, Eigen::Dynamic>(paddedImg.rows() - 1, 1, 1, m_grayImageMatrix.cols()) = m_grayImageMatrix.bottomRows(1); 
    paddedImg.block<Eigen::Dynamic, 1>(1, paddedImg.cols() - 1, m_grayImageMatrix.rows(), 1) = m_grayImageMatrix.rightCols(1);
    
    paddedImg(0, 0) = m_grayImageMatrix(0, 0);
    paddedImg(0, paddedImg.cols() - 1) = m_grayImageMatrix(0, m_grayImageMatrix.cols() - 1);
    paddedImg(paddedImg.rows() - 1, 0) = m_grayImageMatrix(m_grayImageMatrix.rows() - 1, 0);
    paddedImg(paddedImg.rows() - 1, paddedImg.cols() - 1) = m_grayImageMatrix(m_grayImageMatrix.rows() - 1, m_grayImageMatrix.cols() - 1);

    paddedImg.block<Eigen::Dynamic, Eigen::Dynamic>(1, 1, m_grayImageMatrix.rows(), m_grayImageMatrix.cols()) = m_grayImageMatrix;

    return paddedImg;
}

/*
    Filter the image based on input enum of filter types (mean, median, gaussian)
    and allowing member function chaining to filter many times.
*/
Image Image::filter(FilterType filterToUse) // in future make filter also work on rgb
{
    Image filteredImg(*this); 
    ImageMatrix filteredGrayMatrix{};
    
    Eigen::Matrix3f kernal; // 3x3 kernal
    float meanConstant{1.0f / 9.0f};
    float gaussianConst{16.0f};

    switch(filterToUse){

        case FilterType::mean:

            kernal.setConstant(meanConstant);
            break;

        case FilterType::gaussian:
            
            kernal << 1, 2, 1, 2, 4, 2, 1, 2, 1; // gaussian kernal
            kernal /= gaussianConst;
            break;

        case FilterType::median: // do this later
            break;
    }
    
    
    ImageMatrix paddedImg = filteredImg.boundaryPad();

    size_t ri{}; // row index for resulting matrix
    size_t rj{};
    size_t ki{}; // row index for kernal matrix
    size_t kj{};

    float sum{};

    filteredGrayMatrix.resize(m_height, m_width);
    filteredGrayMatrix.setZero();

    ri = 0;
    for (size_t i{1}; i < paddedImg.rows() - 1; ++i)
    {
        rj = 0;

        for (size_t j{1}; j < paddedImg.cols() - 1; ++j)
        {
            sum = 0;
            ki = 0;

            for (size_t k{i - 1}; k <= i + 1; ++k)
            {
                kj = 0;

                for (size_t m{j - 1}; m <= j + 1; ++m)
                {
                    sum = sum + paddedImg(k, m) * kernal(ki, kj);
                    ++kj;
                }
                ++ki;
            }
            filteredGrayMatrix(ri, rj) = sum;

            ++rj;
        }
        ++ri;
    }

    filteredImg.m_grayImageMatrix = filteredGrayMatrix;

    return filteredImg;
}









