#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "image.h"

// corners should be separate to adhere to single responsibility. Feature finding should be responsiblity of another function not the image object
class Grayscale : public Image{
    public:
        typedef Eigen::Matrix<uint8_t,Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> GrayImageMatrix;
        
        Grayscale(const char* imageName); // constructor
        Grayscale(Image& image, const int& channels, unsigned char* imgData);

        // destructor uses Image class destructor
        Grayscale(const Grayscale& image); //copy constructor
        Grayscale& operator=(const Grayscale& image); // copy assignment operator
        
        Grayscale(Grayscale&& image) noexcept; // move constructor
        // Grayscale(Image&& image) noexcept; // move contructor from base class

        Grayscale& operator=(Grayscale&& image); // move assignment operator
        // Grayscale& operator=(Image&& image);

        // GrayImageMatrix boundaryPad();
        // void filter(FilterType filterToUse);

    private:
        GrayImageMatrix m_imgMatrix;

};
#endif