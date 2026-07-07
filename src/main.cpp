#include <iostream>
#include "Eigen/Dense" 
#include "image.h"
#include "filepaths.h"
#include "harrisCorner.h"

//TODO make filter work with rgb images, not urgent can be done later but will make overall code structure and moduarity better
int main(){
    Image leftImage("leftTest.png");

    // Change this so image name path can be specified here and function will automatically join them
    leftImage.checkImage("leftTest.png");

    Image filteredImage = leftImage.filter(Image::FilterType::gaussian);

    filteredImage.checkGrayImage("filteredImage.png");

    Image derivativeTest(filteredImage);

    HarrisCorner::ImageDerivatives derv = HarrisCorner::computeImageDerivatives(derivativeTest);
    std::vector<HarrisCorner::Corner> corners = HarrisCorner::computeCornerScores(derv);

    return 0;

}