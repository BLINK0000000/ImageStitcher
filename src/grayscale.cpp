#include <iostream>
#include "grayscale.h"
#include "rgb.h"

Grayscale::Grayscale(const char* imageName)
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

// Grayscale::Grayscale(Image&& image)
//     : Grayscale(std::move(image))
// {

// }


