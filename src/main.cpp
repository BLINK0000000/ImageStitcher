#include <iostream>
#include "Eigen/Dense" 
#include "image.h"
#include "filepaths.h"
#include "harrisCorner.h"
#include "rgb.h"
#include "grayscale.h"

//TODO make filter work with rgb images, not urgent can be done later but will make overall code structure and moduarity better
int main(){

    // Image leftImage("leftTest.png");

    Rgb img("leftTest.png");

    img.outputImage("outputTest.png");

    Grayscale grayImg = img.convertToGrayscale();

    grayImg.outputImage("grayTest.png");

    return 0;

}