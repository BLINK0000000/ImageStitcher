#ifndef RGB_H
#define RGB_H

#include "image.h"
#include "grayscale.h"
#include "unsupported/Eigen/CXX11/Tensor"

// eigen matrix is different here, needs a tensor
class Rgb : public Image{ 
    public:
        typedef Eigen::Tensor<uint8_t, 3> rgbImageTensor;

        Rgb(const char* imagePath); // constructor
        Rgb(const Rgb& image); //copy constructor
        Rgb& operator=(const Rgb& image); // copy assignment operator
        
        Rgb(Rgb&& image) noexcept; // move constructor
        Rgb& operator=(Rgb&& image); // move assignment operator

        
        Grayscale convertToGrayscale();
        // rgbImageTensor boundaryPad();
        // void filter(FilterType filterToUse) override;

    private:
        rgbImageTensor m_imgTensor;
};

#endif