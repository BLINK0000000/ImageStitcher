#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include "Eigen/Core"
#include "stb_image.h"
#include "harrisCorner.h"


// Maybe change this whole design so Image is a base class which has 2 child classes 
// rgb class and grayscale class which inherits from image class
// uses runtime polymorphism to overide functions such as filtering 
// can use a switch statement to determine which derived class to instance
// delcare a base class pointer which points to the address of an instanced derived class
// then call methods based on that
// this makes it way more modular, can input both grayscale and rgb images instead of rgb only
// will let me learn how inheritance and virtual functions work


// on the pi this could be a template class, should be faster too

class Image{
    public:

        Image(const char* imagePath); // constructor
        ~Image(); //destructor
        Image(const Image& image); //copy constructor
        Image& operator=(const Image& image); // copy assignment operator
        
        Image(Image&& image) noexcept; // move constructor
        Image& operator=(Image&& image); // move assignment operator

        enum class FilterType{
            mean,
            median,
            gaussian,
        };

        virtual void filter(FilterType filterToUse) = 0;  

        /*Testing Methods*/
        virtual void checkImage(const char* output);
        void checkGrayImage(const char* output);
        
    private:
        unsigned char* m_imageData;
        int m_height;
        int m_width;
        int m_channels;

};

#endif