#include "../include/vector.h"
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <iostream>

    // Default constructor
    Vector::Vector() {
        // Initialize size to 0
        size = 0;
        // Initialize data pointer to nullptr
        data = nullptr;
}

        // Constructor for a given size
    Vector::Vector(int n) : size(n) {
        data = new double[size];
        std::fill_n(data, size, 0.0);
    }

    // Constructor taking a std::vector
    Vector::Vector(const std::vector<double>& vec) : size(vec.size()) {
        data = new double[size];
        std::copy(vec.begin(), vec.end(), data);
    }
    Vector::Vector(double* arr, int arrSize) : data(arr), size(arrSize) {
    // No need to allocate new memory or copy data
    // data now directly points to the passed array
}

    // Copy Constructor
    Vector::Vector(const Vector& other) : size(other.size) {
        data = new double[size];
        std::copy(other.data, other.data + size, data);
    }

    // Move Constructor
    Vector::Vector(Vector&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    // Destructor
    Vector::~Vector() {
        delete[] data;
    }

    // Copy Assignment Operator
    Vector& Vector::operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new double[size];
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }

    // Move Assignment Operator
    Vector& Vector::operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
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
void Vector::zero() {
        for (int i = 0; i < size; ++i) {
            data[i] = 0.0;
        }
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