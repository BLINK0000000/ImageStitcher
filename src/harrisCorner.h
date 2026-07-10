// #ifndef HARRIS_CORNER_H
// #define HARRIS_CORNER_H

// #include "Eigen/Core"
// #include "image.h"
// #include <vector>

// namespace HarrisCorner
// {
//     struct ImageDerivatives{
//         Eigen::MatrixXf ix;
//         Eigen::MatrixXf iy;
//     };

//     struct CornerInfo{
//         size_t i;
//         size_t j;
//         float score;
//     };

//     /*
//         Computing the corner scores for a grayscale image matrix
//     */
//     void computeImageDerivatives(Image& img, ImageDerivatives& derivatives);
//     void computeCornerScores(ImageDerivatives& imageDerivate, std::vector<CornerInfo>& corners);
//     void nonMaxSuppression(std::vector<int>& corners);

//     // use reserve with the total number of pixels
//         // then use push to add corners and shrink to fit after
//         // ^^ do this on the pi, no need to do it here
//     std::vector<HarrisCorner::CornerInfo> m_cornerList;
// }


// #endif