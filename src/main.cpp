#include <iostream>
#include "Eigen/Dense" 
#include "image.h"
#include "filepaths.h"
#include "harrisCorner.h"
#include "rgb.h"
#include "grayscale.h"

//TODO make filter work with rgb images, not urgent can be done later but will make overall code structure and moduarity better
// Only allows images with no transparency channel
int main(){

    Rgb img("leftTest.png");

    Grayscale grayImg = img.convertToGrayscale();

    grayImg.filter(Image::FilterType::gaussian);

    grayImg.outputImage("filter.png");
    
    return 0;

}