#ifndef VECTOR_H
#define VECTOR_H

#include <iomanip>
#include <cmath>

class Vector {
    public:
        double* data;  // Pointer to the array
        int size;  // Size of the array

        // Constructors
        Vector();  // Default constructor
        Vector(int size); // Zero vector size n constructor.
        Vector(double* arr, int arrSize);  // Vector populated with array constructor. 
        Vector(const Vector& other);  // Copy constructor.
        Vector(Vector&& other) noexcept;  // Move constructor.

        // Assignment operators
        Vector& operator=(const Vector& other); // Copy assignment.
        Vector& operator=(Vector&& other) noexcept; // Move assignment.

        // Destructor
        ~Vector();

        // Methods
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