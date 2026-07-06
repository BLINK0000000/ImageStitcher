#ifndef HARRIS_CORNER_H
#define HARRIS_CORNER_H

#include "Eigen/Core"
#include "image.h"

namespace HarrisCorner
{
    struct ImageDerivatives{
        Eigen::MatrixXf ix;
        Eigen::MatrixXf iy;
    };

    /*
        Computing the corner scores for a grayscale image matrix
    */
    ImageDerivatives computeImageDerivatives(Image img);
    Eigen::MatrixXf computeCornerScores(ImageDerivatives& imageDerivate);
}


#endif