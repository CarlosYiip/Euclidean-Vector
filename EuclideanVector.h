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
        // Equality Operator
        friend bool operator==(const EuclideanVector&, const EuclideanVector&);
        friend bool operator!=(const EuclideanVector&, const EuclideanVector&);

        // Addition Operator
        friend EuclideanVector operator+(const EuclideanVector&, const EuclideanVector&);

        // Subtraction Operator
        friend EuclideanVector operator-(const EuclideanVector&, const EuclideanVector&);

        // Multiplication Operator
        friend double operator*(const EuclideanVector&, const EuclideanVector&);
        friend EuclideanVector operator*(const EuclideanVector&, double);
        friend EuclideanVector operator*(double, const EuclideanVector&);

        // Division Operator
        friend EuclideanVector operator/(const EuclideanVector&, double);

        // Ostream Operator
        friend std::ostream& operator<<(std::ostream&, const EuclideanVector&);

    public:
        // Default constructor
        EuclideanVector();

        // Constructor that takes the number of dimensions but no magnitudes
        EuclideanVector(unsigned);

        // Constructor that takes the number of dimensions and initialises the magnitude in each dimension as the second argument
        EuclideanVector(unsigned, double);

        // Constructor that takes the start and end of an iterator
        EuclideanVector(std::vector<double>::iterator, std::vector<double>::iterator);
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
        double getEuclideanNorm();

        // Create a unit vector
        EuclideanVector createUnitVector();

        // Debug Helper functions
        void printInfo() const;

    private:
        unsigned* p1 = nullptr; // Number of dimensions
        double* p2 = nullptr; // Magnitudes of dimensions
        double* p3 = nullptr; // Euclidean norm
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