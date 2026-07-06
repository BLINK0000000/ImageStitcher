#include <iostream>
#include "Eigen/Dense" 
#include "image.h"
#include "filepaths.h"


int main(){
    
    Image leftImage("leftTest.png");

    // Change this so image name path can be specified here and function will automatically join them
    leftImage.checkImage("leftTest.png");

    Image filteredImage = leftImage.filter(Image::FilterType::gaussian);

    filteredImage.checkGrayImage("filteredImage.png");
    
    return 0;

}