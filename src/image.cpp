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
#include "grayscale.h"
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
    , m_channels{}
    , m_imgName{imageName}
{
    const fp::path imagePath = fp::assetsDir / imageName;

    try {
        m_imageData = stbi_load(imagePath.c_str(), &m_width, &m_height, &m_channels, 0);
    
        if (m_imageData) {

            std::cout << "loaded image with width, height, channels: " << m_width << " , " << m_height << " , " << m_channels << std::endl;
            
        } else {
            throw std::invalid_argument("Could not load image: ");
        }
    }
    catch (std::invalid_argument e) {
        std::cout << "Exception: " << e.what() << stbi_failure_reason() << std::endl;
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

    memcpy(m_imageData, image.m_imageData, imageSize * sizeof(unsigned char));

    m_height = image.m_height;
    m_width = image.m_width;
    m_channels = image.m_channels;
}

Image::Image(const Image& image, const int channels, const unsigned char* imgData)
{   
    m_channels = channels;
    size_t imageSize{static_cast<size_t>(image.m_width * image.m_height * image.m_channels)};

    m_imageData = (unsigned char*)malloc(imageSize * sizeof(unsigned char));

    memcpy(m_imageData, image.m_imageData, imageSize * sizeof(unsigned char));

    m_height = image.m_height;
    m_width = image.m_width;
    m_channels = image.m_channels;
}

Image& Image::operator=(const Image& image)
{
    if (this != &image) {

        // make sure to always delete/free heap variables before copying again
        stbi_image_free(m_imageData);

        int imageSize{m_width * m_height * m_channels};

        m_imageData = (unsigned char*)malloc(imageSize * sizeof(unsigned char));

        memcpy(m_imageData, &image.m_imageData, imageSize * sizeof(unsigned char));

        m_height = image.m_height;
        m_width = image.m_width;
        m_channels = image.m_channels;
    }

    return *this;
}

Image::Image(Image&& image) noexcept
    : m_imageData{std::move(image.m_imageData)}
    , m_height{std::move(image.m_height)}
    , m_width{std::move(image.m_width)}
    , m_channels{std::move(image.m_channels)}
{
    image.m_imageData = nullptr;
    image.m_height = 0;
    image.m_width = 0;
    image.m_channels = 0;
}

Image& Image::operator=(Image&& image)
{
    if (this != &image){
        stbi_image_free(m_imageData);

        m_imageData = std::move(image.m_imageData);
        m_height = std::move(image.m_height);
        m_width = std::move(image.m_width);
        m_channels = std::move(image.m_channels);
    }

    return *this;
}

void Image::outputImage(const char* output)
{   
    const fp::path outputPath = fp::imageTestsDir / output;
    stbi_write_png(outputPath.c_str(), m_width, m_height, m_channels, m_imageData, m_width * m_channels);
}

// void Image::checkGrayImage(const char* output)
// {
//     const fp::path outputPath = fp::imageTestsDir / output;

//     // Testing output, in reality, gray pixels will be mapped to matrix
//     uint8_t* grayImageData = m_imgMatrix.data();

//     stbi_write_png(outputPath.c_str(), m_width, m_height, 1, grayImageData, m_width);
// }

/*
    Create a padded image matrix from this image object
*/
// Image::ImageMatrix Image::boundaryPad()
// {
//     Image::ImageMatrix paddedImg{}; // make it so the boundary padding function returns this, makes no sense it's created here
    
//     paddedImg.resize(m_imgMatrix.rows() + 2 , m_imgMatrix.cols() + 2);
//     paddedImg.setZero();

//     paddedImg.block<1, Eigen::Dynamic>(0, 1, 1, m_imgMatrix.cols()) = m_imgMatrix.topRows(1);
//     paddedImg.block<Eigen::Dynamic, 1>(1, 0, m_imgMatrix.rows(), 1) = m_imgMatrix.leftCols(1); 
//     paddedImg.block<1, Eigen::Dynamic>(paddedImg.rows() - 1, 1, 1, m_imgMatrix.cols()) = m_imgMatrix.bottomRows(1); 
//     paddedImg.block<Eigen::Dynamic, 1>(1, paddedImg.cols() - 1, m_imgMatrix.rows(), 1) = m_imgMatrix.rightCols(1);
    
//     paddedImg(0, 0) = m_imgMatrix(0, 0);
//     paddedImg(0, paddedImg.cols() - 1) = m_imgMatrix(0, m_imgMatrix.cols() - 1);
//     paddedImg(paddedImg.rows() - 1, 0) = m_imgMatrix(m_imgMatrix.rows() - 1, 0);
//     paddedImg(paddedImg.rows() - 1, paddedImg.cols() - 1) = m_imgMatrix(m_imgMatrix.rows() - 1, m_imgMatrix.cols() - 1);

//     paddedImg.block<Eigen::Dynamic, Eigen::Dynamic>(1, 1, m_imgMatrix.rows(), m_imgMatrix.cols()) = m_imgMatrix;

//     return paddedImg;
// }

// /*
//     Filter the image based on input enum of filter types (mean, median, gaussian)
//     and allowing member function chaining to filter many times.
// */
// Image Image::filter(FilterType filterToUse) // in future make filter also work on rgb
// {
//     Image filteredImg(*this); 
//     ImageMatrix filteredGrayMatrix{};
    
//     Eigen::Matrix3f kernal; // 3x3 kernal
//     float meanConstant{1.0f / 9.0f};
//     float gaussianConst{16.0f};

//     switch(filterToUse){

//         case FilterType::mean:

//             kernal.setConstant(meanConstant);
//             break;

//         case FilterType::gaussian:
            
//             kernal << 1, 2, 1, 2, 4, 2, 1, 2, 1; // gaussian kernal
//             kernal /= gaussianConst;
//             break;

//         case FilterType::median: // do this later
//             break;
//     }
    
    
//     ImageMatrix paddedImg = filteredImg.boundaryPad();

//     size_t ri{}; // row index for resulting matrix
//     size_t rj{};
//     size_t ki{}; // row index for kernal matrix
//     size_t kj{};

//     float sum{};

//     filteredGrayMatrix.resize(m_height, m_width);
//     filteredGrayMatrix.setZero();

//     ri = 0;
//     for (size_t i{1}; i < paddedImg.rows() - 1; ++i)
//     {
//         rj = 0;

//         for (size_t j{1}; j < paddedImg.cols() - 1; ++j)
//         {
//             sum = 0;
//             ki = 0;

//             for (size_t k{i - 1}; k <= i + 1; ++k)
//             {
//                 kj = 0;

//                 for (size_t m{j - 1}; m <= j + 1; ++m)
//                 {
//                     sum = sum + paddedImg(k, m) * kernal(ki, kj);
//                     ++kj;
//                 }
//                 ++ki;
//             }
//             filteredGrayMatrix(ri, rj) = sum;

//             ++rj;
//         }
//         ++ri;
//     }

//     filteredImg.m_imgMatrix = filteredGrayMatrix;

//     return filteredImg;
// }

/*
    Find corners using harris corner
*/

// bool Image::findCorners()
// {
//     HarrisCorner::ImageDerivatives derivatives{};

//     Image::ImageMatrix paddedImg = this->boundaryPad();

//     derivatives.ix.resize(paddedImg.rows() - 2, paddedImg.cols() - 2); // padding is always 1 on each side
//     derivatives.iy.resize(paddedImg.rows() - 2, paddedImg.cols() - 2);

//     derivatives.ix.setZero();
//     derivatives.iy.setZero();

//     HarrisCorner::computeImageDerivatives(paddedImg, derivatives);


// }









