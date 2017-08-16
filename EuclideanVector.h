#ifndef A2_EUCLIDEANVECTOR_H
#define A2_EUCLIDEANVECTOR_H

#include "vector"

class EuclideanVector {
public:
    EuclideanVector(const unsigned n, const double m): numberOfDimension{n}, magnitudeInEachDimension(n, m) {};
    EuclideanVector(const unsigned n): EuclideanVector(n, 0.0) {};
    EuclideanVector(): EuclideanVector(1) {};

    void printMagnitudes() const;
    void printNumberOfDimension() const;
private:
    unsigned numberOfDimension;
    std::vector<double> magnitudeInEachDimension;
};

#endif
