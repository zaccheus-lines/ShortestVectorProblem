#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <initializer_list>

class Vector {

private:

public:
    double* data;  // Pointer to the array
    int size;    // Size of the array

    // Constructors
    Vector();
    Vector(int size);
    Vector(const std::vector<double>& vec);
    Vector(double* arr, int arrSize);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
    // Destructor
    ~Vector();

    

    

    // Methods
    void print() const;
    double& operator[](int index);
    const double& operator[](int index) const;
    double norm() const;
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector& operator+=(const Vector& other);
    void zero();
    Vector& operator-=(const Vector& other);
    void normalise();
    Vector operator*(double scalar) const;
    double dot(const Vector& other) const;
    double max() const;


};

#endif // VECTOR_H