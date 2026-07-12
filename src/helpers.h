#ifndef HELPERS_H
#define HELPERS_H

#include "grayscale.h"

namespace ImageModify
{
    void boundaryPad(Grayscale::GrayImageMatrix& paddedMatrix, Grayscale::GrayImageMatrix& originalMatrix);
    void copyImageData();
} // namespace ImageModify


#endif