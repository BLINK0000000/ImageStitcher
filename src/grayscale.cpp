#include <iostream>
#include "grayscale.h"
#include "rgb.h"
#include "helpers.h"

Grayscale::Grayscale(const char* imageName) // implicitly convert rgb to grayscale here
    : Image(imageName),
      m_imgMatrix{}
{
    m_imgMatrix.resize(m_height, m_width);
    m_imgMatrix = Eigen::Map<GrayImageMatrix, 0>(m_imageData, m_height, m_width);
}

Grayscale::Grayscale(const Image& image, const int& channels, unsigned char* imgData)
    : Image(image, channels, imgData),
      m_imgMatrix{}
{
    m_imgMatrix.resize(m_height, m_width);
    m_imgMatrix = Eigen::Map<GrayImageMatrix, 0>(m_imageData, m_height, m_width);
}

Grayscale::Grayscale(const Grayscale& image)
    : Image(image),
      m_imgMatrix{image.m_imgMatrix}
{
}

Grayscale& Grayscale::operator=(const Grayscale& image)
{
    if (this != &image) {

        Image::operator=(image);

        m_imgMatrix = image.m_imgMatrix;
    }

    return *this;
}

Grayscale::Grayscale(Grayscale&& image) noexcept
    : Image(std::move(image)),
      m_imgMatrix{std::move(image.m_imgMatrix)}
{
    image.m_imgMatrix.setZero();
}

Grayscale& Grayscale::operator=(Grayscale&& image)
{
    if (this != &image){
        Image::operator=(std::move(image));

        m_imgMatrix = std::move(image.m_imgMatrix);
    }

    return *this;
}

void Grayscale::filter(FilterType filterToUse) // in future make filter also work on rgb
{
    GrayImageMatrix paddedMatrix{};

    Eigen::Matrix3f kernal{}; // 3x3 kernal
    constexpr float meanConstant{1.0f / 9.0f};
    constexpr float gaussianConst{16.0f};

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
    
    
    ImageModify::boundaryPad(paddedMatrix, this->m_imgMatrix);

    size_t ri{}; // row index for resulting matrix
    size_t rj{};
    size_t ki{}; // row index for kernal matrix
    size_t kj{};

    float sum{};

    ri = 0;
    for (size_t i{1}; i < paddedMatrix.rows() - 1; ++i)
    {
        rj = 0;

        for (size_t j{1}; j < paddedMatrix.cols() - 1; ++j)
        {
            sum = 0;
            ki = 0;

            for (size_t k{i - 1}; k <= i + 1; ++k)
            {
                kj = 0;

                for (size_t m{j - 1}; m <= j + 1; ++m)
                {
                    sum = sum + paddedMatrix(k, m) * kernal(ki, kj);
                    ++kj;
                }
                ++ki;
            }
            m_imgMatrix(ri, rj) = sum;

            ++rj;
        }
        ++ri;
    }

    size_t imageSize{static_cast<size_t>(m_width * m_height * m_channels)};

    m_imageData = (unsigned char*)malloc(imageSize * sizeof(unsigned char));

    memcpy(m_imageData, m_imgMatrix.data(), imageSize * sizeof(unsigned char));
    
}

