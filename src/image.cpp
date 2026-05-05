#include <iostream>
#include "image.h"
#include "stb_image.h"
#include <cassert>

// Constructor
Image::Image(const char* imagePath)
: m_imageData{nullptr}
, m_height{} 
, m_width{} 
, m_imageChannels{} 
, m_cornerList{}
{
    m_imageData = stbi_load(imagePath, &m_width, &m_height, &m_imageChannels, 0);

    assert (!m_imageData); // have to load image for this program to work
}

// Destructor
Image::~Image()
{
    stbi_image_free(m_imageData);
}

// Copy constructor TODO: finish
Image::Image(const Image& image)
{
    m_imageData = image.m_imageData;

}

/*
Filter the image based on input enum of filter types (mean, median, gaussian)
*/
bool Image::filter()
{

}





