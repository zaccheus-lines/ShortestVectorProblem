#include "../include/vector.h"
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <iostream>

// Static member initialization
size_t Vector::commonSize = 0;

// Default constructor
Vector::Vector() : data(commonSize, 0.0) {}

// Constructor with initializer list
Vector::Vector(std::initializer_list<double> list) : data(list) {}

// Constructor with size
Vector::Vector(size_t size) : data(size, 0.0) {}

// Copy constructor
Vector::Vector(const Vector& other) : data(other.data) {}

// Move constructor
Vector::Vector(Vector&& other) noexcept : data(std::move(other.data)) {}

// Destructor
Vector::~Vector() {}

// Copy assignment operator
Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        data = other.data;
    }
    return *this;
}

// Move assignment operator
Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        data = std::move(other.data);
    }
    return *this;
}

// Dynamic addition
void Vector::push_back(double value) {
    data.push_back(value);
}

// Method to print the vector
void Vector::print() const {
    std::cout << std::fixed << std::setprecision(15); // Set precision to 15 decimal places
    for (const double& element : data) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// Overload the [] operator for non-const access
double& Vector::operator[](size_t index) {
    if (index >= data.size()) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Overload the [] operator for const access
const double& Vector::operator[](size_t index) const {
    if (index >= data.size()) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Euclidean norm (magnitude)
double Vector::norm() const {
    double sum = 0.0;
    for (auto& val : data) {
        sum += val * val;
    }
    return sqrt(sum);
}

// Addition
Vector Vector::operator+(const Vector& other) const {
    Vector result = *this;
    for (size_t i = 0; i < data.size(); ++i) {
        result.data[i] += other.data[i];
    }
    return result;
}

// Subtraction
Vector Vector::operator-(const Vector& other) const {
    Vector result = *this;
    for (size_t i = 0; i < data.size(); ++i) {
        result.data[i] -= other.data[i];
    }
    return result;
}

// Operator += for element-wise addition
Vector& Vector::operator+=(const Vector& other) {
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] += other.data[i];
    }
    return *this;
}

// Operator -= for element-wise subtraction
Vector& Vector::operator-=(const Vector& other) {
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] -= other.data[i];
    }
    return *this;
}

// Normalize the vector
void Vector::normalise() {
    double magnitude = norm();
    if (magnitude != 0.0) {
        for (double& val : data) {
            val /= magnitude;
        }
    }
}

// Scalar multiplication
Vector Vector::operator*(double scalar) const {
    Vector result = *this;
    for (double& val : result.data) {
        val *= scalar;
    }
    return result;
}

// Dot product
double Vector::dot(const Vector& other) const {
    double sum = 0.0;
    for (size_t i = 0; i < commonSize; ++i) {
        sum += this->data[i] * other.data[i];
    }
    return sum;
}

size_t Vector::size() const {
    return data.size();
}

double Vector::max() const {
    double maxElem = data[0];
    for (const double& elem : data) {
        if (elem > maxElem) {
            maxElem = elem;
        }
    }
    return maxElem;
}
