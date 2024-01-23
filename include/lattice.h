// lattice.h
#ifndef LATTICE_H
#define LATTICE_H

#include "../include/vector.h"

class Lattice {
    public:
        // Constructors
        explicit Lattice(Vector** basis, int size);
        Lattice(const Lattice& other);  // Copy constructor.
        Lattice(Lattice&& other) noexcept;  // Move constructor.

        // Destructor
        ~Lattice();

        // Assignment operators
        Lattice& operator=(const Lattice& other);  // Copy assignment.
        Lattice& operator=(Lattice&& other) noexcept;  // Move assignment.

        // Methods
        bool isBasis(); 
        void gramSchmidt(int startFrom = 0);
        void LLL();
        double gaussianHeuristic();
        Vector schnorrEuchnerEnumeration();


    private:
        // Private class variables
        Vector** basis_;
        int n;  //Dimension of array.
        double** mu_;  // µ coefficients.
        Vector* orthogonalizedVectors;  // Gram-Schmidt Orthogonalised Vectors
        Vector norms;  // Squared norms of the orthogonalized vectors.
        const double epsilon = 1e-10;  // epsilon for floating point commparison.
};

#endif  // LATTICE_H