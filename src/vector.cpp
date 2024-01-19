#include "../include/vector.h"


    // Default constructor
    Vector::Vector() {
        size = 0;
        data = nullptr;
}

    // Constructor for a given size
    Vector::Vector(int n) : size(n) {
        data = new double[size];
        std::fill_n(data, size, 0.0);
    }

    Vector::Vector(double* arr, int arrSize) : data(arr), size(arrSize) {
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

    /*
    // Method to print the array
    void Vector::print() const {
        std::cout << std::fixed << std::setprecision(15);
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
    */
    // Overload the [] operator for non-const access
    double& Vector::operator[](int index) {
        return data[index];
    }

    // Overload the [] operator for const access
    const double& Vector::operator[](int index) const {
        return data[index];
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

    void Vector::zero() {
        for (int i = 0; i < size; ++i) {
            data[i] = 0.0;
            }
        }


    // Euclidean norm (magnitude)
    double Vector::norm() const {
        double sum = 0.0;
        for (int i =0; i <size; i++) {
            sum += data[i] * data[i];
        }
        return sqrt(sum);
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
    // Add a scaled vector to this vector
    void Vector::addScaledVector(const Vector& other, double scalar) {
        for (int i = 0; i < size; ++i) {
            this->data[i] += other.data[i] * scalar;
        }
    }