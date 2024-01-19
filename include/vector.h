#ifndef VECTOR_H
#define VECTOR_H

#include <iomanip>
#include <cmath>

class Vector {
    public:
        double* data;  // Pointer to the array
        int size;  // Size of the array

        // Constructors
        Vector();
        Vector(int size);
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

        void normalise();
        void zero();

        double norm() const;
        double dot(const Vector& other) const;
        double max() const;

        void addScaledVector(const Vector& other, double scalar);
       
};
#endif  // VECTOR_H