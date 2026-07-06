#include <iostream>
#include "Eigen/Dense" 
#include "image.h"
#include "filepaths.h"


int main(){
    
    Image leftImage("leftTest.png");

    Image testImage(leftImage);

    // Change this so image name path can be specified here and function will automatically join them
    testImage.checkImage("testImage.png");
    leftImage.checkImage("leftTest.png");

    // leftImage.checkImage(fp::leftImageOutTestPath.c_str());

    // Image filteredImage = leftImage.filter(Image::FilterType::gaussian);

    // filteredImage.checkImage(fp::leftImageOutTestPath.c_str());
    
    return 0;

}