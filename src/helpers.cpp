#include "helpers.h"

void ImageModify::boundaryPad(Grayscale::GrayImageMatrix& paddedMatrix, Grayscale::GrayImageMatrix& originalMatrix)
{
    
    paddedMatrix.resize(originalMatrix.rows() + 2 , originalMatrix.cols() + 2);
    paddedMatrix.setZero();

    paddedMatrix.block<1, Eigen::Dynamic>(0, 1, 1, originalMatrix.cols()) = originalMatrix.topRows(1);
    paddedMatrix.block<Eigen::Dynamic, 1>(1, 0, originalMatrix.rows(), 1) = originalMatrix.leftCols(1); 
    paddedMatrix.block<1, Eigen::Dynamic>(paddedMatrix.rows() - 1, 1, 1, originalMatrix.cols()) = originalMatrix.bottomRows(1); 
    paddedMatrix.block<Eigen::Dynamic, 1>(1, paddedMatrix.cols() - 1, originalMatrix.rows(), 1) = originalMatrix.rightCols(1);
    
    paddedMatrix(0, 0) = originalMatrix(0, 0);
    paddedMatrix(0, paddedMatrix.cols() - 1) = originalMatrix(0, originalMatrix.cols() - 1);
    paddedMatrix(paddedMatrix.rows() - 1, 0) = originalMatrix(originalMatrix.rows() - 1, 0);
    paddedMatrix(paddedMatrix.rows() - 1, paddedMatrix.cols() - 1) = originalMatrix(originalMatrix.rows() - 1, originalMatrix.cols() - 1);

    paddedMatrix.block<Eigen::Dynamic, Eigen::Dynamic>(1, 1, originalMatrix.rows(), originalMatrix.cols()) = originalMatrix;
}