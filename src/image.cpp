#include <iostream>
#include "image.hpp"
#include "stb_image.h"

Image::Image(const char* imagePath)
: m_imageData{},
  m_height{}, 
  m_width{}, 
  m_imageChannels{}, 
  m_cornerList{}, 
  m_matchingCorners{},
  m_bestMatchingCorners{},
  m_secondBestMatchingCorners{}
{
    m_imageData = stbi_load(imagePath, &m_width, &m_height, &m_imageChannels, 0);

    if (!m_imageData)
    {
        std::cout << "Couldnt load image" << std::endl;
    }
}


