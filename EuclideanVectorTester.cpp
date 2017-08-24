#include <iostream>
#include <vector>
#include <list>

#include "EuclideanVector.h"




int main() {
    evec::EuclideanVector a {3,6};
    evec::EuclideanVector b = std::move(a);
    std::cout << a << '\n';
    std::cout << b << '\n';
}