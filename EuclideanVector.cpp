#include "EuclideanVector.h"
#include <iostream>

void EuclideanVector::printMagnitudes() const {
    for (auto i : magnitudeInEachDimension)
        std::cout << i << '\n';
}

void EuclideanVector::printNumberOfDimension() const {
    std::cout << numberOfDimension << '\n';
}