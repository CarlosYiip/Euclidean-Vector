#include "EuclideanVector.h"

using namespace evec;

/***************************************  Constructors and destructors  ***********************************************/

// Default constructor
EuclideanVector::EuclideanVector(): EuclideanVector(1) {}

// Constructor that takes the number of dimensions but no magnitudes
EuclideanVector::EuclideanVector(unsigned n): EuclideanVector(n, 0) {}

// Constructor that takes the number of dimensions and initialises the magnitude in each dimension as the second argument
EuclideanVector::EuclideanVector(unsigned n, double m):
        p1{new unsigned {n}}, p2{new double[n]} { std::fill(p2, p2 + n, m); }

// Constructor that takes the start and end of an iterator
EuclideanVector::EuclideanVector(std::vector<double>::iterator beg, std::vector<double>::iterator end):
        p1{new unsigned {static_cast<unsigned>(std::distance(beg, end))}},
        p2{new double[*p1]} { std::copy(beg, end, p2); }
EuclideanVector::EuclideanVector(std::list<double>::iterator beg, std::list<double>::iterator end):
        p1{new unsigned {static_cast<unsigned>(std::distance(beg, end))}},
        p2{new double[*p1]} { std::copy(beg, end, p2); }


// Constructor that takes a initialiser list of doubles
EuclideanVector::EuclideanVector(std::initializer_list<double> list):
        p1{new unsigned {static_cast<unsigned>(std::distance(list.begin(), list.end()))}},
        p2{new double[*p1]} { std::copy(list.begin(), list.end(), p2); }

// Copy Constructor
EuclideanVector::EuclideanVector(const EuclideanVector& other):
        p1{new unsigned {*other.p1}}, p2{new double[*p1]} { std::copy(other.p2, other.p2 + *other.p1, p2); }

// Move Constructor
EuclideanVector::EuclideanVector(EuclideanVector&& other): p1{new unsigned {*other.p1}}, p2{new double[*p1]} {
    p2 = other.p2;
    p1 = other.p1;
    other.p1 = nullptr;
    other.p2 = nullptr;
}

// Destructor
EuclideanVector::~EuclideanVector() noexcept { delete p1; delete[] p2; }

/*******************************************  Overloading operators  **************************************************/

// Copy Assignment
EuclideanVector& EuclideanVector::operator=(const EuclideanVector& other) {
    if (this != &other) {
        *p1 = *other.p1;

        delete[] p2;
        p2 = new double[*other.p1];
        std::copy(other.p2, other.p2 + *other.p1, p2);

        if (other.p3 != nullptr) {
            delete p3;
            p3 = new double {*other.p3};
        }
    }
    return *this;
}

// Move Assignment
EuclideanVector& EuclideanVector::operator=(EuclideanVector&& other) {
    if (this != &other) {
        delete p1;
        p1 = other.p1;
        other.p1 = nullptr;

        delete[] p2;
        p2 = other.p2;
        other.p2 = nullptr;

        if (other.p3 != nullptr) {
            delete p3;
            p3 = other.p3;
            other.p3 = nullptr;
        }
    }
    return *this;
}

// Subscript Operator (set)
double& EuclideanVector::operator[](int index) {
    p3 = nullptr;
    return p2[index];
}

// Subscript Operator (get)
double EuclideanVector::operator[](int index) const { return p2[index]; }

// Compound Assignment Operator (+=)
EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& other) {
    for (int i = 0; i < *p1; ++i)
        p2[i] += other.p2[i];
    p3 = nullptr;
    return *this;
}

// Compound Assignment Operator (-=)
EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& other) {
    for (int i = 0; i < *p1; ++i)
        p2[i] -= other.p2[i];
    p3 = nullptr;
    return *this;
}

// Compound Assignment Operator (*=)
EuclideanVector& EuclideanVector::operator*=(double i) {
    std::transform(p2, p2 + *p1, p2, [&i] (double& d) {return d * i;});
    p3 = nullptr;
    return *this;
}

// Compound Assignment Operator (/=)
EuclideanVector& EuclideanVector::operator/=(double i) {
    return *this *= (1 / i);
}

// Type Conversion Operator (std::vector)
EuclideanVector::operator std::vector<double>() const {
    std::vector<double> tmp {p2, p2 + *p1};
    return tmp;
}

// Type Conversion Operator (std::list)
EuclideanVector::operator std::list<double>() const {
    std::list<double> tmp {p2, p2 + *p1};
    return tmp;
}

/***********************************************  Member Functions  ***************************************************/

// Return the number of dimensions
unsigned EuclideanVector::getNumDimensions() const {
    return *p1;
}

// Return the value of magnitude in the dimension given as the function parameter
double EuclideanVector::get(unsigned i) const { return p2[i]; }

// Return the euclidean norm
double EuclideanVector::getEuclideanNorm() {
    if (p3 != nullptr) {
        return *p3;
    } else {
        double res = std::accumulate(p2, p2 + *p1, 0.0, [] (const auto& a, const auto& b) {return a + b * b;});
        p3 = new double {sqrt(res)};
        return *p3;
    }
}

// Return a new unit vector
EuclideanVector EuclideanVector::createUnitVector() {
    EuclideanVector unitVector {*this};
    double norm = getEuclideanNorm();
    std::transform(p2, p2 + *p1, unitVector.p2, [&norm] (const auto& x) {return x / norm;});
    return unitVector;
}

/**********************************************  Nonmember Functions  *************************************************/


bool evec::operator==(const EuclideanVector& v1, const EuclideanVector& v2) {
    if (v1.getNumDimensions() != v2.getNumDimensions())
        return false;

    for (unsigned i = 0; i < v1.getNumDimensions(); ++i) {
        if (v1.p2[i] != v2.p2[i])
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
    return std::inner_product(v1.p2, v1.p2 + *v1.p1, v2.p2, 0);
}

EuclideanVector evec::operator*(const EuclideanVector& v, double n) {
    EuclideanVector product {v};
    std::transform(product.p2, product.p2 + *product.p1, product.p2, [&n] (auto& i) {return i * n;});
    return product;
}

EuclideanVector evec::operator*(double n, const EuclideanVector& v) {
    return v * n;
}

EuclideanVector evec::operator/(const EuclideanVector& v, double n) {
    return v * (1 / n);
}


std::ostream& evec::operator<<(std::ostream& os, const EuclideanVector& v) {
    if (v.p1 == nullptr) {
        std::cout << "[]";
        return os;
    }
    std::cout << '[';
    std::for_each(v.p2, v.p2 + *v.p1 - 1, [] (const auto& i) {std::cout << i << ' ';});
    std::cout << v.p2[*v.p1-1] << ']';
    return os;
}

/***********************************************  Debug  Functions  ***************************************************/

void EuclideanVector::printInfo() const {
    if (p1 == nullptr) {
        std::cout << "Null\n\n";
        return;
    }


    std::cout << "Number of dimensions: " << *p1 << '\n';
    std::cout << "Magnitudes: ";
    for (auto i = 0; i != *p1; ++i) {
        std::cout << p2[i] << ' ';
    }
    std::cout << '\n';
    if (p3 != nullptr)
        std::cout << "Euclidean norm = " << *p3 << '\n';
    else
        std::cout << "Euclidean norm = undefined" << '\n';
    std::cout << "Array memory address = " << p2 << '\n';
    std::cout << "Dimensionality memory address = " << p1 << '\n';
    std::cout << "Euclidean norm address = " << p3 << '\n' << '\n';

}