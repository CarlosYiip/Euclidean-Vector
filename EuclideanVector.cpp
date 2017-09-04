#include "EuclideanVector.h"

using namespace evec;

/***************************************  Constructors and destructors  ***********************************************/

// Default constructor
EuclideanVector::EuclideanVector(): EuclideanVector(1u) {}

// Constructor that takes the number of dimensions but no magnitudes
EuclideanVector::EuclideanVector(unsigned n): EuclideanVector(n, 0.0) {}

// Constructor that takes the number of dimensions and initialises the magnitude in each dimension as the second argument
EuclideanVector::EuclideanVector(unsigned n, double m):
        numberOfDimension{n}, magnitudes{new double[n]} { std::fill(begin(), end(), m); }

// Constructor that takes iterators from a vector
EuclideanVector::EuclideanVector(std::vector<double>::iterator beg, std::vector<double>::iterator end): 
numberOfDimension{static_cast<unsigned>(std::distance(beg, end))}, magnitudes{new double[numberOfDimension]} {
    std::copy(beg, end, begin());
}

// Constructor that takes iterators from a list
EuclideanVector::EuclideanVector(std::list<double>::iterator beg, std::list<double>::iterator end): 
numberOfDimension{static_cast<unsigned>(std::distance(beg, end))}, magnitudes{new double[numberOfDimension]} {
    std::copy(beg, end, begin());
}


// Constructor that takes a initialiser list of doubles
EuclideanVector::EuclideanVector(std::initializer_list<double> list): 
numberOfDimension{static_cast<unsigned>(std::distance(list.begin(), list.end()))}, magnitudes{new double[numberOfDimension]}{
    std::copy(list.begin(), list.end(), begin());
}

// Copy Constructor
EuclideanVector::EuclideanVector(const EuclideanVector& other): numberOfDimension{other.getNumDimensions()}, magnitudes{new double[other.getNumDimensions()]} { 
            std::copy(other.cbegin(), other.cend(), begin()); 
        }

// Move Constructor
EuclideanVector::EuclideanVector(EuclideanVector&& other): numberOfDimension{other.getNumDimensions()}, magnitudes{other.begin()} {
    other.numberOfDimension = 0u;
    other.magnitudes = nullptr;
}

// Destructor
EuclideanVector::~EuclideanVector() noexcept { delete[] magnitudes; }

/*******************************************  Overloading operators  **************************************************/

// Copy Assignment
EuclideanVector& EuclideanVector::operator=(const EuclideanVector& other) {
    if (this != &other) {
        numberOfDimension = other.getNumDimensions();

        // Deallocate memory before creating a new potentially different size array
        delete[] magnitudes;
        magnitudes = new double[other.getNumDimensions()];
        std::copy(other.cbegin(), other.cend(), begin());
    }
    return *this;
}

// Move Assignment
EuclideanVector& EuclideanVector::operator=(EuclideanVector&& other) {
    if (this != &other) {
        numberOfDimension = other.numberOfDimension;
        other.numberOfDimension = 0u;

        // Deallocate memory
        delete[] magnitudes;
        // Make the pointer point to the move_from object (MagnitudesOfEachDimensions)
        magnitudes = other.magnitudes;
        // Make the pointer in move_from object point to nullptr which
        // ensure the move from object is now in a valid state
        other.magnitudes = nullptr;
    }
    return *this;
}

// Subscript Operator (set)
double& EuclideanVector::operator[](int index) {
    // Euclidean norm might be changed
    euclideanNorm = -1.0;
    return magnitudes[index];
}

// Subscript Operator (get)
double EuclideanVector::operator[](int index) const {
    return magnitudes[index];
}

// Compound Assignment Operator (+=)
EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& other) {
    for (unsigned i = 0u; i < getNumDimensions(); ++i)
        magnitudes[i] += other[i];

    // Euclidean norm might be changed
    euclideanNorm = -1.0;
    return *this;
}

// Compound Assignment Operator (-=)
EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& other) {
    for (unsigned i = 0u; i < getNumDimensions(); ++i)
        magnitudes[i] -= other[i];
    // Euclidean norm might be changed
    euclideanNorm = -1.0;
    return *this;
}

// Compound Assignment Operator (*=)
EuclideanVector& EuclideanVector::operator*=(double i) {
    std::for_each(begin(), end(), [&i] (auto& d) { d *= i;});
    // Euclidean norm might be changed
    euclideanNorm = -1.0;
    return *this;
}

// Compound Assignment Operator (/=)
EuclideanVector& EuclideanVector::operator/=(double i) {
    return *this *= (1 / i);
}

// Type Conversion Operator (std::vector)
EuclideanVector::operator std::vector<double>() const {
    std::vector<double> tmp {cbegin(), cend()};
    return tmp;
}

// Type Conversion Operator (std::list)
EuclideanVector::operator std::list<double>() const {
    std::list<double> tmp {cbegin(), cend()};
    return tmp;
}

/***********************************************  Member Functions  ***************************************************/

// Return the number of dimensions
unsigned EuclideanVector::getNumDimensions() const {
    return numberOfDimension;
}

// Return the value of magnitude in the dimension given as the function parameter
double EuclideanVector::get(unsigned i) const { 
    return magnitudes[i]; 
}

// Return the euclidean norm
double EuclideanVector::getEuclideanNorm() const {
    if (euclideanNorm != -1.0) {
        // If there is cached value
        return euclideanNorm;
    } else {
        // Otherwise, calculate the value
        euclideanNorm = sqrt(std::accumulate(cbegin(), cend(), 0.0, [] (const double& a, const double& b) {return a + b * b;}));
        return euclideanNorm;
    }
}

// Return a new unit vector
EuclideanVector EuclideanVector::createUnitVector() const {
    EuclideanVector unitVector {*this};
    double norm = getEuclideanNorm();
    std::transform(cbegin(), cend(), unitVector.begin(), [&norm] (const auto& x) {return x / norm;});
    return unitVector;
}

/**********************************************  Nonmember Functions  *************************************************/
bool evec::operator==(const EuclideanVector& v1, const EuclideanVector& v2) {
    if (&v1 == &v2)
        return true;

    // Firstly, check whether the two vectors have same number of dimensions
    if (v1.getNumDimensions() != v2.getNumDimensions())
        return false;

    // Secondly, check whether magnitudes of each dimension are equal
    for (unsigned i = 0u; i < v1.getNumDimensions(); ++i) {
        if (v1[i] != v2[i])
            return false;
    }

    return true;
}

bool evec::operator!=(const EuclideanVector& v1, const EuclideanVector& v2) {
    return !(v1 == v2);
}

EuclideanVector evec::operator+(const EuclideanVector& v1, const EuclideanVector& v2) {
    EuclideanVector sum {v1};
    sum += v2;
    return sum;
}

EuclideanVector evec::operator-(const EuclideanVector& v1, const EuclideanVector& v2) {
    EuclideanVector diff {v1};
    diff -= v2;
    return diff;
}

double evec::operator*(const EuclideanVector& v1, const EuclideanVector& v2) {
    double res = 0.0;
    for (unsigned i = 0u; i < v1.getNumDimensions(); ++i)
        res += v1[i] * v2[i];
    return res;
}

EuclideanVector evec::operator*(const EuclideanVector& v, double n) {
    EuclideanVector product {v};
    for (unsigned i = 0u; i < product.getNumDimensions(); ++i)
        product[i] *= n;
    return product;
}

EuclideanVector evec::operator*(double n, const EuclideanVector& v) {
    return v * n;
}

EuclideanVector evec::operator/(const EuclideanVector& v, double n) {
    return v * (1 / n);
}

std::ostream& evec::operator<<(std::ostream& os, const EuclideanVector& v) {
    if (v.getNumDimensions() == 0u) {
        std::cout << "[]";
        return os;
    }

    std::cout << '[';
    for (unsigned i = 0u; i < v.getNumDimensions() - 1; ++i)
        std::cout << v[i] << ' ';

    std::cout << v[v.getNumDimensions() - 1] << ']';
    return os;
}