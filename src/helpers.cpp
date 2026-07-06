#include "helpers.h"

void Helpers::boundaryPad(Image::ImageMatrix& imgMat, Image::ImageMatrix& paddedImg)
{

    paddedImg.resize(imgMat.rows() + 2 , imgMat.cols() + 2);
    paddedImg.setZero();


    paddedImg.block<1, Eigen::Dynamic>(0, 1, 1, imgMat.cols()) = imgMat.topRows(1);
    paddedImg.block<Eigen::Dynamic, 1>(1, 0, imgMat.rows(), 1) = imgMat.leftCols(1); 
    paddedImg.block<1, Eigen::Dynamic>(paddedImg.rows() - 1, 1, 1, imgMat.cols()) = imgMat.bottomRows(1); 
    paddedImg.block<Eigen::Dynamic, 1>(1, paddedImg.cols() - 1, imgMat.rows(), 1) = imgMat.rightCols(1);
    
    paddedImg(0, 0) = imgMat(0, 0);
    paddedImg(0, paddedImg.cols() - 1) = imgMat(0, imgMat.cols() - 1);
    paddedImg(paddedImg.rows() - 1, 0) = imgMat(imgMat.rows() - 1, 0);
    paddedImg(paddedImg.rows() - 1, paddedImg.cols() - 1) = imgMat(imgMat.rows() - 1, imgMat.cols() - 1);

    paddedImg.block<Eigen::Dynamic, Eigen::Dynamic>(1, 1, imgMat.rows(), imgMat.cols()) = imgMat;

}