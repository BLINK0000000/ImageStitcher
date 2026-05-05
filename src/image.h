#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include "Eigen/Core"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Image{
    public:
        Image(const char* imagePath); // constructor
        ~Image(); //destructor
        Image(const Image& image); //copy constructor
        bool filter();
        bool imageDerivatives();
        // maybe compute corners as a non member function and instead change this to getCorners which calls the corner calcs function
        
        bool getCorners();

        // get corners function
        // nms
        



    private:
        unsigned char* m_imageData;
        int m_height;
        int m_width;
        int m_imageChannels;

        Eigen::MatrixXd m_grayImageMatrix;
        // use reserve with the total number of pixels
        // then use push to add corners and shrink to fit after 
        std::vector<int> m_cornerList;
        // std::vector<int> m_matchingCorners;
        // std::vector<int> m_bestMatchingCorners;
        // std::vector<int> m_secondBestMatchingCorners;

        // maybe do inheritance cause i need filter function
        struct m_imageDerivative {
            Eigen::MatrixXd ix;
            Eigen::MatrixXd iy;
        };

          
        



};

#endif