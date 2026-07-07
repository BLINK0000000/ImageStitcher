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
    ImageDerivatives computeImageDerivatives(Image& img);
    std::vector<Corner> computeCornerScores(ImageDerivatives& imageDerivate);
    void nonMaxSuppression(std::vector<int>& corners);
}


#endif