#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "image.h"

class Grayscale : public Image{
    public:
        typedef Eigen::Matrix<uint8_t,Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> GrayImageMatrix;
        
        Grayscale(const char* imagePath); // constructor
        ~Grayscale(); //destructor
        Grayscale(const Grayscale& image); //copy constructor
        Grayscale& operator=(const Grayscale& image); // copy assignment operator
        
        Grayscale(Grayscale&& image) noexcept; // move constructor
        Grayscale& operator=(Grayscale&& image); // move assignment operator

        GrayImageMatrix boundaryPad();
        void filter(FilterType filterToUse) override;
        bool findCorners();

    private:
         // use reserve with the total number of pixels
        // then use push to add corners and shrink to fit after
        // ^^ do this on the pi, no need to do it here
        std::vector<HarrisCorner::CornerInfo> m_cornerList;

};
#endif