#ifndef HARRIS_CORNER_H
#define HARRIS_CORNER_H

#include "Eigen/Core"
#include "image.h"
#include <vector>

namespace HarrisCorner
{
    struct ImageDerivatives{
        Eigen::MatrixXf ix;
        Eigen::MatrixXf iy;
    };

    struct Corner{
        size_t i;
        size_t j;
        float score;
    };

    /*
        Computing the corner scores for a grayscale image matrix
    */
    void computeImageDerivatives(Image& img, ImageDerivatives& derivatives);
    void computeCornerScores(ImageDerivatives& imageDerivate, std::vector<Corner>& corners);
    void nonMaxSuppression(std::vector<int>& corners);
}


#endif