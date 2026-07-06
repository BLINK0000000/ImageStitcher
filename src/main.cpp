#include <iostream>
#include "Eigen/Dense" 
#include "image.h"
#include "filepaths.h"


int main(){
    
    Image leftImage(fp::leftImagePath.c_str());

    Image testImage(leftImage);

    // Change this so image name path can be specified here and function will automatically join them
    testImage.checkImage(fp::leftImageOutTestPath.c_str());
    leftImage.checkImage(fp::rightImageOutTestPath.c_str());

    // leftImage.checkImage(fp::leftImageOutTestPath.c_str());

    // Image filteredImage = leftImage.filter(Image::FilterType::gaussian);

    // filteredImage.checkImage(fp::leftImageOutTestPath.c_str());
    
    return 0;

}