#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include "Eigen/Core"
#include "stb_image.h"

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

        void checkImage(const char* output);
        void checkGrayImage(const char* output);

        Image filter(FilterType filterToUse);
        
        bool imageDerivatives();
        // maybe compute corners as a non member function and instead change this to getCorners which calls the corner calcs function     
        bool getCorners();


        // get corners function
        // nms


        /*Testing Methods*/
        void checkImage(const char* outputPath, unsigned char* data); // this is for outputting gray image for testing, probably bad practice but this is easiest for now
        



    private:
        unsigned char* m_imageData;
        int m_height;
        int m_width;
        int m_channels;

        Eigen::Matrix<uint8_t, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> m_grayImageMatrix;
        // use reserve with the total number of pixels
        // then use push to add corners and shrink to fit after 
        std::vector<int> m_cornerList;
        // std::vector<int> m_matchingCorners;
        // std::vector<int> m_bestMatchingCorners;
        // std::vector<int> m_secondBestMatchingCorners;

};

#endif