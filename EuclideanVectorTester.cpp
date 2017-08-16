#include <iostream>
#include "EuclideanVector.h"

int main() {
    unsigned int x {3};
    double y {3.24};

    EuclideanVector a{x, y};
    EuclideanVector b(1);
    EuclideanVector c{};

    return 0;
}