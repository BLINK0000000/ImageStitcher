#include <iostream>
#include "rgb.h"


Rgb::Rgb(const char* imageName)
    : Image(imageName),
      m_imgTensor{}
{
    m_imgTensor.resize(m_height, m_width, 3);
    m_imgTensor = Eigen::TensorMap<rgbImageTensor, 0>(m_imageData, m_channels, m_height, m_width);
}

Grayscale Rgb::convertToGrayscale()
{
    size_t imageSize{static_cast<size_t>(m_width * m_height * m_channels)};

    int grayChannels{m_channels == 4 ? 2 : 1};
    size_t grayImageSize{static_cast<size_t>(m_width * m_height * grayChannels)};

    unsigned char* grayImageData = new unsigned char[grayImageSize];

    if (!grayImageData){
        
        std::cout << "Could not allocate memory for gray image" << std::endl;

        Grayscale grayImg(m_imgName.c_str());

        return grayImg;
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

        Grayscale grayImg(*this, grayChannels, grayImageData);

        delete[] grayImageData;

        return grayImg;
    } 
}