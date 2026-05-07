#ifndef HARRIS_CORNER_H
#define HARRIS_CORNER_H

#include "Eigen/Core"

namespace HarrisCorner
{
    struct ImageDerivatives{
        Eigen::MatrixXf ix;
        Eigen::MatrixXf iy;
    };

    /*
        Computing the corner scores for a grayscale image matrix
    */ 
    Eigen::MatrixXd computeCornerScores(ImageDerivatives& imageDerivate);
}


#endif