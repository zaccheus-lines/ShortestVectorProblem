#include <iostream>
#include <vector>
#include <cmath>
#include <initializer_list>
#include <future>
#include <iomanip>


class Vector{
public:
    static size_t commonSize;

    // Default constructor
    Vector() : data(commonSize, 0.0) {}

    // Constructor with initializer list
    Vector(std::initializer_list<long double> list) : data(list) {}

    // Constructor with size
    Vector(size_t size) : data(size, 0.0) {}

    template <typename Iter>
    Vector(Iter begin, Iter end) : data(begin, end) {}

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
    void push_back(long double value) {
        data.push_back(value);
    }

    // Method to print the vector
    void print() const {
        std::cout << std::fixed << std::setprecision(15); // Set precision to 15 decimal places
        for (const long double& element : data) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
    // Overload the [] operator for non-const access
    long double& operator[](size_t index) {
        /*
        if (index >= commonSize) {
            throw std::out_of_range("Index out of range");
        }*/
        return data[index];
    }

    // Overload the [] operator for const access
    const long double& operator[](size_t index) const {
        /*
        if (index >= commonSize) {
            throw std::out_of_range("Index out of range");
        }*/
        return data[index];
    }

    // Euclidean norm (magnitude)
    long double norm() const {
        long double sum = 0.0;
        for (auto& val : data) {
            sum += val * val;
        }
        return sqrt(sum);
    }

    // Addition
    Vector operator+(const Vector& other) const {
        //
        Vector result = *this;
        for (size_t i = 0; i < commonSize; ++i) {
            result.data[i] += other.data[i];
        }
        return result;
    }

    // Subtraction
    Vector operator-(const Vector& other) const {
        //
        Vector result = *this;
        for (size_t i = 0; i < commonSize; ++i) {
            result.data[i] -= other.data[i];
        }
        return result;
    }

    // Operator += for element-wise addition
    Vector& operator+=(const Vector& other) {
        
        for (size_t i = 0; i < commonSize; ++i) {
            data[i] += other.data[i];
        }

        return *this; // Return the current object by reference
    }

    // Operator -= for element-wise subtraction
    Vector& operator-=(const Vector& other) {

        for (size_t i = 0; i < commonSize; ++i) {
            data[i] -= other.data[i];
        }

        return *this; // Return the current object by reference
    }

    // Normalize the vector
    void normalise() {
        long double magnitude = norm();
        if (magnitude != 0.0) {
            for (long double& val : data) {
                val /= magnitude;
        }}
    }

    // Scalar multiplication
    Vector operator*(long double scalar) const {
        Vector result = *this;
        for (long double& val : result.data) {
            val *= scalar;
        }
        return result;
    }

    // Dot product
    long double dot(const Vector& other) const {
        //checkDimension(other);
        long double sum = 0.0;
        for (size_t i = 0; i < commonSize; ++i) {
            sum += this->data[i] * other.data[i];
        }
        return sum;
    }

    size_t size() const {
        return data.size();
    }

    long double max() const {
       
        long double maxElem = data[0];
        for (const long double& elem : data) {
            if (elem > maxElem) {
                maxElem = elem;
            }
        }
        return maxElem;
    }

 /*  // Utility function to check dimensions
    void checkDimension(const Vector& other) const {
        if (commonSize != other.commonSize) {
            throw std::invalid_argument("Vectors must be of the same dimension");
        }
    }*/
private:
    std::vector<long double> data;
};
