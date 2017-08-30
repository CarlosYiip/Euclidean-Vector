#ifndef A2_EUCLIDEANVECTOR_H
#define A2_EUCLIDEANVECTOR_H

#include <vector>
#include <list>
#include <initializer_list>
#include <iostream>
#include <cmath>
#include <numeric>
#include <algorithm>

namespace evec {
    class EuclideanVector {
    public:
        // Default constructor
        EuclideanVector();

        // Constructor that takes the number of dimensions but no magnitudes
        EuclideanVector(unsigned);

        // Constructor that takes the number of dimensions and initialises the magnitude in each dimension as the second argument
        EuclideanVector(unsigned, double);

        // Constructor that takes iterators from a vector
        EuclideanVector(std::vector<double>::iterator, std::vector<double>::iterator);

        // Constructor that takes iterators from a list
        EuclideanVector(std::list<double>::iterator, std::list<double>::iterator);

        // Constructor that takes a initialiser list of doubles
        EuclideanVector(std::initializer_list<double>);

        // Copy Constructor
        EuclideanVector(const EuclideanVector &);

        // Move Constructor
        EuclideanVector(EuclideanVector &&);

        // Destructor
        ~EuclideanVector() noexcept ;

        // Copy Assignment
        EuclideanVector &operator=(const EuclideanVector &);

        // Move Assignment
        EuclideanVector &operator=(EuclideanVector &&);

        // Subscript Operator (set)
        double& operator[] (int i);

        // Subscript Operator (get)
        double  operator[] (int i) const;

        // Compound Assignment Operator (+=)
        EuclideanVector& operator+=(const EuclideanVector&);

        // Compound Assignment Operator (+=)
        EuclideanVector& operator-=(const EuclideanVector&);

        // Compound Assignment Operator (*=)
        EuclideanVector& operator*=(double);

        // Compound Assignment Operator (/=)
        EuclideanVector& operator/=(double);

        // Type Conversion Operator (std::vector)
        operator std::vector<double>() const;

        // Type Conversion Operator (std::list)
        operator std::list<double>() const;

        // Return the number of dimensions
        unsigned getNumDimensions() const;

        // Return the value of magnitude in the dimension given as the function parameter
        double get(unsigned) const;

        // Return the euclidean norm
        double getEuclideanNorm() const;

        // Create a unit vector
        EuclideanVector createUnitVector() const;

        // Debug Helper functions
        void printInfo() const;

    private:
        unsigned numberOfDimension = 0; // Number of dimensions
        double* magnitudes = nullptr; // Array of magnitudes of each dimension
        mutable double euclideanNorm = 0; // Euclidean norm

        // return a const pointer to the head of the magnitudes array
        double const * cbegin() const { 
            double const * p = magnitudes;
            return p;
        };

        // return a const pointer to the tail of the magnitudes array
        double const * cend() const {
            double const * p = magnitudes + numberOfDimension;
            return p;
        }

        // return a pointer to the head of the magnitudes array
        double * begin() {
            double * p = magnitudes;
            return p;
        }

        // return a pointer to the tail of the magnitudes array
        double * end() {
            double * p = magnitudes + numberOfDimension;
            return p;
        }
    };

    // Equality Operator
    bool operator==(const EuclideanVector&, const EuclideanVector&);
    bool operator!=(const EuclideanVector&, const EuclideanVector&);

    // Addition Operator
    EuclideanVector operator+(const EuclideanVector&, const EuclideanVector&);

    // Subtraction Operator
    EuclideanVector operator-(const EuclideanVector&, const EuclideanVector&);

    // Multiplication Operator
    double operator*(const EuclideanVector&, const EuclideanVector&);
    EuclideanVector operator*(const EuclideanVector&, double);
    EuclideanVector operator*(double, const EuclideanVector&);

    // Division Operator
    EuclideanVector operator/(const EuclideanVector&, double);

    // Ostream Operator
    std::ostream& operator<<(std::ostream&, const EuclideanVector&);
}
#endif