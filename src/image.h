#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include "Eigen/Core"
#include "stb_image.h"

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
        std::vector<int> m_cornerList;
        // std::vector<int> m_matchingCorners;
        // std::vector<int> m_bestMatchingCorners;
        // std::vector<int> m_secondBestMatchingCorners;

};

#endif