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


/****************************************************  Friends ********************************************************/
        friend bool operator==(const EuclideanVector& v1, const EuclideanVector& v2) {
            if (v1.getNumDimensions() != v2.getNumDimensions())
                return false;
            for (unsigned i = 0; i < v1.getNumDimensions(); ++i) {
                if (v1.p2[i] != v2.p2[i])
                    return false;
            }
            return true;
        };

        friend bool operator!=(const EuclideanVector& v1, const EuclideanVector& v2) {
            return !(v1 == v2);
        }

        friend EuclideanVector operator+(const EuclideanVector& v1, const EuclideanVector& v2) {
            EuclideanVector sum {v1};
            sum += v2;
            return sum;
        }

        friend EuclideanVector operator-(const EuclideanVector& v1, const EuclideanVector v2) {
            EuclideanVector diff {v1};
            diff -= v2;
            return diff;
        }

        friend double operator*(const EuclideanVector& v1, const EuclideanVector& v2) {
            return std::inner_product(v1.p2, v1.p2 + *v1.p1, v2.p2, 0.0);
        }

        friend EuclideanVector operator*(const EuclideanVector& v, double d) {
            EuclideanVector product {v};
            std::transform(product.p2, product.p2 + product.getNumDimensions(), product.p2, [&d] (const auto& i) {return i * d;});
            return product;
        }

        friend EuclideanVector operator*(double d, const EuclideanVector& v) {
            return v * d;
        }

        friend EuclideanVector operator/(const EuclideanVector& v, double d) {
            return v * (1 / d);
        }

        friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) {
            if (v.p1 == nullptr) {
                std::cout << "[]";
                return os;
            }
            std::cout << '[';
            std::for_each(v.p2, v.p2 + *v.p1 - 1, [] (const auto& i) {std::cout << i << ' ';});
            std::cout << v.p2[*v.p1-1] << ']';
            return os;
        }

/****************************************************  Friends ********************************************************/


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
        unsigned* p1; // Number of dimensions
        double* p2; // Magnitudes of dimensions
        double* p3 = nullptr; // Euclidean norm


    };
}


#endif
