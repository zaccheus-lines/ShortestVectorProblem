#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <initializer_list>

class Vector {

private:

    double* data;  // Pointer to the array
    

public:
    int size;    // Size of the array

    // Constructors
    Vector(int size);
    Vector(const std::vector<double>& vec);

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
    Vector& operator-=(const Vector& other);
    void normalise();
    Vector operator*(double scalar) const;
    double dot(const Vector& other) const;
    double max() const;


};

#endif // VECTOR_H