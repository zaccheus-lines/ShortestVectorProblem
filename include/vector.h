#include <iostream>
#include <vector>
#include <cmath>
#include <initializer_list>

class Vector{
public:
    // Default constructor
    Vector() {}

    // Constructor with initializer list
    Vector(std::initializer_list<double> list) : data(list) {}

    // Constructor with size
    Vector(size_t size) : data(size, 0.0) {}

    // Copy constructor
    Vector(const Vector& other) : data(other.data) {}

    // Move constructor
    Vector(Vector&& other) noexcept : data(std::move(other.data)) {}

    // Destructor
    ~Vector() {}

    // Copy assignment operator
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    // Move assignment operator
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }

    // Dynamic addition
    void push_back(double value) {
        data.push_back(value);
    }

    // Method to print the vector
    void print() const {
        for (const double& element : data) {
            std::cout << element << " ";
        }
        std::cout << std::endl; 
}
    // Overload the [] operator for non-const access
    double& operator[](size_t index) {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Overload the [] operator for const access
    const double& operator[](size_t index) const {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Euclidean norm (magnitude)
    double norm() const {
        double sum = 0.0;
        for (auto& val : data) {
            sum += val * val;
        }
        return sqrt(sum);
    }

    // Addition
    Vector operator+(const Vector& other) const {
        checkDimension(other);
        Vector result = *this;
        for (size_t i = 0; i < data.size(); ++i) {
            result.data[i] += other.data[i];
        }
        return result;
    }

    // Subtraction
    Vector operator-(const Vector& other) const {
        checkDimension(other);
        Vector result = *this;
        for (size_t i = 0; i < data.size(); ++i) {
            result.data[i] -= other.data[i];
        }
        return result;
    }

    // Normalize the vector
    void normalise() {
        double magnitude = norm();
        if (magnitude != 0.0) {
            for (double& val : data) {
                val /= magnitude;
        }}
    }

    void scalar_mult(double& r) {
        for (size_t i = 0; i < this->size(); ++i) {
            (*this)[i] = r * (*this)[i];
        }}

    void scalar_sub(double& r, Vector& other) {
        if (this->size() != other.size()) {
            throw std::invalid_argument("Input vectors must have the same size");
        }

        for (size_t i = 0; i < this->size(); ++i) {
            other[i] -= r * (*this)[i];
        }}

    // Scalar multiplication
    Vector operator*(double scalar) const {
        Vector result = *this;
        for (double& val : result.data) {
            val *= scalar;
        }
        return result;
    }

    // Dot product
    double dot(const Vector& other) const {
        checkDimension(other);
        double sum = 0.0;
        for (size_t i = 0; i < data.size(); ++i) {
            sum += this->data[i] * other.data[i];
        }
        return sum;
    }

    size_t size() const {
        return data.size();
    }
    
    // Utility function to check dimensions
    void checkDimension(const Vector& other) const {
        if (data.size() != other.data.size()) {
            throw std::invalid_argument("Vectors must be of the same dimension");
        }
    }
private:
    std::vector<double> data;
};