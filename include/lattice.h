// lattice.h
#ifndef LATTICE_H
#define LATTICE_H

#include <vector>
#include "../include/vector.h" // Make sure to include the Vector header

class Lattice {
public:
    
    // Constructors
    explicit Lattice(Vector** basis, int size);
    Lattice(const Lattice& other); // Copy constructor
    Lattice(Lattice&& other) noexcept; // Move constructor

    // Destructor
    ~Lattice();

    // Assignment operators
    Lattice& operator=(const Lattice& other); // Copy assignment
    Lattice& operator=(Lattice&& other) noexcept; // Move assignment

    // Public member functions
    bool isBasis();
    void gramSchmidt(int startFrom = 0);
    void LLL();
    double gaussianHeuristic();
    Vector schnorrEuchnerEnumeration();

private:
    // Private member variables
    Vector** basis_;
    int n;
    double** mu_; // µ coefficients
    Vector norms; // Norms of the orthogonalized vectors
    const double epsilon = 1e-10; // Define epsilon here
    Vector* orthogonalizedVectors;
};

#endif // LATTICE_H