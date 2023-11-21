// vector.h
#include <vector>
#include <stdexcept>
#include <cmath>

class Vector {
private:
    std::vector<double> elements;

public:
    // Constructor
    Vector(int size) : elements(size) {}

    // Accessor with bounds checking
    double& operator[](int i) {
        if (i < 0 || i >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return elements[i];
    }

    // Const accessor
    double operator[](int i) const {
        if (i < 0 || i >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return elements[i];
    }

    // Get the size of the vector
    int size() const { return elements.size(); }

    // Add another vector to this vector
    Vector& operator+=(const Vector& rhs) {
        if (size() != rhs.size()) {
            throw std::invalid_argument("Vectors must be of the same size");
        }
        for (int i = 0; i < size(); ++i) {
            elements[i] += rhs[i];
        }
        return *this;
    }

    // Subtract another vector from this vector
    Vector& operator-=(const Vector& rhs) {
        if (size() != rhs.size()) {
            throw std::invalid_argument("Vectors must be of the same size");
        }
        for (int i = 0; i < size(); ++i) {
            elements[i] -= rhs[i];
        }
        return *this;
    }

    // Calculate the dot product of this vector and another vector
    double dot(const Vector& rhs) const {
        if (size() != rhs.size()) {
            throw std::invalid_argument("Vectors must be of the same size");
        }
        double product = 0;
        for (int i = 0; i < size(); ++i) {
            product += elements[i] * rhs[i];
        }
        return product;
    }

    // Calculate the Euclidean norm of the vector
    double norm() const {
        double sum = 0;
        for (double elem : elements) {
            sum += elem * elem;
        }
        return std::sqrt(sum);
    }

    // Normalize this vector
    Vector& normalize() {
        double n = norm();
        if (n == 0) {
            throw std::runtime_error("Cannot normalize a zero vector");
        }
        for (double& elem : elements) {
            elem /= n;
        }
        return *this;
    }
};
