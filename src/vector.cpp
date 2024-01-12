#include "../include/vector.h"
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <iostream>

    Vector::Vector(int n) : size(n) {
    data = new double[size];
    for (int i=0; i<size; i++){
        data[i] = 0;
    };
    }

    // Constructor taking a std::vector
    Vector::Vector(const std::vector<double>& vec) : size(vec.size()) {
    data = new double[size];
    std::copy(vec.begin(), vec.end(), data);
    }

    // Destructor
    Vector::~Vector() {
        delete[] data;
    }

// Method to print the array
    void Vector::print() const {
        std::cout << std::fixed << std::setprecision(15);
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    // Overload the [] operator for non-const access
    double& Vector::operator[](int index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Overload the [] operator for const access
    const double& Vector::operator[](int index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }


// Euclidean norm (magnitude)
double Vector::norm() const {
    double sum = 0.0;
    for (int i =0; i <size; i++) {
        sum += data[i] * data[i];
    }
    return sqrt(sum);
}

// Addition
Vector Vector::operator+(const Vector& other) const {
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.data[i] = data[i] + other.data[i];
    }
    return result;
}

// Subtraction
Vector Vector::operator-(const Vector& other) const {
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.data[i] = data[i] - other.data[i];
    }
    return result;
}

// Operator += for element-wise addition
Vector& Vector::operator+=(const Vector& other) {
    for (int i = 0; i < size; ++i) {
        data[i] += other.data[i];
    }
    return *this;
}

// Operator -= for element-wise subtraction
Vector& Vector::operator-=(const Vector& other) {
    for (int i = 0; i < size; ++i) {
        data[i] -= other.data[i];
    }
    return *this;
}
// Normalise the vector
void Vector::normalise() {
    double magnitude = norm();
    if (magnitude != 0.0) {
        for (int i = 0; i < size; ++i) {
            data[i] /= magnitude;
        }
    }
}
// Scalar multiplication
Vector Vector::operator*(double scalar) const {
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.data[i] = data[i] * scalar;
    }
    return result;
}

// Dot product
double Vector::dot(const Vector& other) const {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += data[i] * other.data[i];
    }
    return sum;
}

// Find the maximum element
double Vector::max() const {
    double maxElem = data[0];
    for (int i = 1; i < size; ++i) {
        if (data[i] > maxElem) {
            maxElem = data[i];
        }
    }
    return maxElem;
}