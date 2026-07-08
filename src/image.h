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

class Image{
    public:
        // Type defs, make this it's own header
        typedef Eigen::Matrix<uint8_t,Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> ImageMatrix;

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


        ImageMatrix boundaryPad();

        Image filter(FilterType filterToUse);
        
        // maybe compute corners as a non member function and instead change this to getCorners which calls the corner calcs function     
        bool findCorners();

        // Getters, Setters
        

        /*Testing Methods*/
        void checkImage(const char* output);
        void checkGrayImage(const char* output);
        
    private:
        unsigned char* m_imageData;
        int m_height;
        int m_width;
        int m_channels;

        ImageMatrix m_grayImageMatrix;
        // use reserve with the total number of pixels
        // then use push to add corners and shrink to fit after
        // ^^ do this on the pi, no need to do it here

        std::vector<HarrisCorner::Corner> m_cornerList;

};

#endif