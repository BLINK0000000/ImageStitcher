#include "Eigen/Core"

namespace HarrisCorner
{
    struct ImageDerivatives{
        Eigen::MatrixXd ix;
        Eigen::MatrixXd iy;
    };

/*
    Computing the corner scores for a grayscale image matrix
*/ 

    Eigen::MatrixXd computeCornerScores(ImageDerivatives& imageDerivate);
}
