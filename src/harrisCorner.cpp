#include "Eigen/Core"
#include "Eigen/LU"
#include "harrisCorner.h"
#include <vector>
#include <cmath>

/*
    Helpers
*/

static void boundaryPad(Eigen::MatrixXf& derivative)
{
    Eigen::MatrixXf padded{}; // make it so the boundary padding function returns this, makes no sense it's created here
    
    padded.resize(derivative.rows() + 2 , derivative.cols() + 2);
    padded.setZero();

    padded.block<1, Eigen::Dynamic>(0, 1, 1, derivative.cols()) = derivative.topRows(1);
    padded.block<Eigen::Dynamic, 1>(1, 0, derivative.rows(), 1) = derivative.leftCols(1); 
    padded.block<1, Eigen::Dynamic>(padded.rows() - 1, 1, 1, derivative.cols()) = derivative.bottomRows(1); 
    padded.block<Eigen::Dynamic, 1>(1, padded.cols() - 1, derivative.rows(), 1) = derivative.rightCols(1);
    
    padded(0, 0) = derivative(0, 0);
    padded(0, padded.cols() - 1) = derivative(0, derivative.cols() - 1);
    padded(padded.rows() - 1, 0) = derivative(derivative.rows() - 1, 0);
    padded(padded.rows() - 1, padded.cols() - 1) = derivative(derivative.rows() - 1, derivative.cols() - 1);

    padded.block<Eigen::Dynamic, Eigen::Dynamic>(1, 1, derivative.rows(), derivative.cols()) = derivative;

    derivative = padded;
}


void HarrisCorner::computeImageDerivatives(Image::ImageMatrix& paddedImg, ImageDerivatives& derivatives)
{

    Eigen::Matrix3f vertSobelKernal{};
    Eigen::Matrix3f horzSobelKernal{};

    vertSobelKernal << 1.0, 0.0, -1.0, 2.0, 0.0, -2.0, 1.0, 0.0, -1.0;
    vertSobelKernal /= 8.0f;

    horzSobelKernal << 1.0, 2.0, 1.0, 0.0, 0.0, 0.0, -1.0, -2.0, -1.0;
    horzSobelKernal /= 8.0f;

    size_t ri{};
    size_t rj{};
    size_t ki{};
    size_t kj{};

    float sumVertSobel{};
    float sumHorzSobel{};

    ri = 0;
    for (size_t i{1}; i < paddedImg.rows() - 1; ++i)
    {
        rj = 0;

        for (size_t j{1}; j < paddedImg.cols() - 1; ++j)
        {
            sumVertSobel = 0;
            sumHorzSobel = 0;
            ki = 0;

            for (size_t k{i - 1}; k <= i + 1; ++k)
            {
                kj = 0;

                for (size_t m{j - 1}; m <= j + 1; ++m)
                {
                    sumVertSobel = sumVertSobel + paddedImg(k, m) * vertSobelKernal(ki, kj);
                    sumHorzSobel = sumHorzSobel + paddedImg(k, m) * horzSobelKernal(ki, kj);
                    ++kj;
                }
                ++ki;
            }
            derivatives.ix(ri, rj) = sumVertSobel;
            derivatives.iy(ri, rj) = sumHorzSobel;

            ++rj;
        }
        ++ri;
    }
}

void HarrisCorner::computeCornerScores(HarrisCorner::ImageDerivatives& derivatives, std::vector<Corner>& corners)
{
    Eigen::Matrix2f Hmat{};
    float alpha{0.04};
    float threshold{pow(10, 6)};

    Corner cornerInfo {};
    float cornerScore{};

    Eigen::MatrixXf ixSq{};
    Eigen::MatrixXf iySq{};
    Eigen::MatrixXf ixiy{};

    ixSq = derivatives.ix.array().pow(2);
    iySq = derivatives.iy.array().pow(2);
    ixiy = derivatives.ix.cwiseProduct(derivatives.iy);

    float sumIxIy{};
    float sumIxSq{};
    float sumIySq{};

    boundaryPad(ixSq);
    boundaryPad(iySq);
    boundaryPad(ixiy);

    size_t ri{};
    size_t rj{};

    ri = 0;
    for (size_t i{1}; i < ixiy.rows() - 1; ++i)
    {
        rj = 0;

        for (size_t j{1}; j < ixiy.cols() - 1; ++j)
        {
            sumIxIy = 0;
            sumIxSq = 0;
            sumIySq = 0;

            for (size_t k{i - 1}; k <= i + 1; ++k)
            {
                for (size_t m{j - 1}; m <= j + 1; ++m)
                {
                    sumIxIy = sumIxIy + ixiy(k, m);
                    sumIxSq = sumIxSq + ixSq(k, m);
                    sumIySq = sumIySq + iySq(k, m);
                }
            }
            
            Hmat << sumIxSq, sumIxIy, sumIxIy, sumIySq;

            float Htrace{Hmat.trace()};
            float Hdeterm{Hmat.determinant()};
                
            cornerScore = Hmat.determinant() - (alpha * (pow(Hmat.trace(), 2)));

            if (cornerScore > threshold)
            {
                cornerInfo.i = ri;
                cornerInfo.j = rj;
                cornerInfo.score = cornerScore;

                corners.push_back(cornerInfo);
            }

            ++rj;
        }
        ++ri;
    }
}

