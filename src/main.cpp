#include <iostream>
#include "Eigen/Dense" 
#include "image.h"
#include "filepaths.h"


int main(){
    
    Image leftImage(fp::leftImagePath.c_str());

    leftImage.checkImage(fp::leftImageOutTestPath.c_str());

    leftImage.filter(Image::FilterType::mean);
    
    return 0;

}