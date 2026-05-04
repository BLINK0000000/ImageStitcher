#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Image{
    public:
        void filter();
        Image imageDerivatives();
        // get corners function
        // nms




    private:
        const int m_height{};
        const int m_width{};
        // use reserve with the total number of pixels
        // then use push to add corners and shrink to fit after 
        std::vector<int> m_cornerList;
        std::vector<int> m_bestMatchingCorners;
        std::vector<int> m_secondBestMatchingCorners;

          
        



};