#include <iostream>
#include <vector>
#include <set>
#include "vector.h"

class Lattice {
public:
    std::vector<Vector> orthogonalizedVectors;

    // Constructor that takes a basis
    Lattice(const std::vector<Vector>& basis) : basis_(basis) {}
    

    // Destructor
    ~Lattice() {
        // Implement necessary cleanup here
    }

    // Copy constructor
    Lattice(const Lattice& other) 
    : basis_(other.basis_), mu_(other.mu_), norms(other.norms) {
    // Ensure that all members, especially norms, are copied properly
    }


    // Copy assignment operator
    Lattice& operator=(const Lattice& other) {
    if (this != &other) {
        basis_ = other.basis_;
        mu_ = other.mu_;
        norms = other.norms;
        // Ensure that all members, especially norms, are copied properly
    }
    return *this;
    }

    // Move constructor
    Lattice(Lattice&& other) noexcept : basis_(std::move(other.basis_)) {
        // Move resources from 'other' to 'this'
    }

      // Define a custom iterator to iterate over the basis vectors
    typedef std::vector<Vector>::iterator iterator;
    typedef std::vector<Vector>::const_iterator const_iterator;
    
    iterator begin() {
        return basis_.begin();
    }

    iterator end() {
        return basis_.end();
    }

    const_iterator begin() const {
        return basis_.begin();
    }

    const_iterator end() const {
        return basis_.end();
    }

    Vector gramSchmidt(){

        size_t n = basis_.size();

        // Resize the mu matrix
        mu_.resize(n, std::vector<double>(n, 0.0));
        Vector norms(n);

        // Orthogonalized vectors
        std::vector<Vector> orthogonalizedVectors(n);
        orthogonalizedVectors[0] = basis_[0];

        for (size_t i = 1; i < n; ++i) {
            
            Vector x(n);

            for (size_t j = 0; j < i; ++j) {
                // Calculate mu coefficient
                mu_[i][j] = basis_[i].dot(orthogonalizedVectors[j]) / orthogonalizedVectors[j].dot(orthogonalizedVectors[j]);
            }
            for (size_t j = 0; j < i; ++j) {
                x = x + orthogonalizedVectors[j]*mu_[i][j];
            }
            orthogonalizedVectors[i] = basis_[i] - x; 


        // Store the squared norm before normalization
        

        /*for (Vector& vector : orthogonalizedVectors) {
            vector.print();}*/

        }
        for (size_t i = 0; i < n; ++i){
            norms[i] = orthogonalizedVectors[i].norm()*orthogonalizedVectors[i].norm();
            }
        return norms;
    }

    Vector schnorrEuchnerEnumeration(double R) {
    norms = gramSchmidt();
    norms.print();
    size_t n = basis_.size();
    Vector rho(n + 1), v(n), c(n), w(n), s(n);
    v[0]=1;
    size_t k = 0, last_nonzero = 0;
    double R2 = R * R;

    while (true) {
        rho[k] = rho[k + 1] + (v[k] - c[k]) * (v[k] - c[k]) * norms[k];

        // Debugging output
        std::cout << "k: " << k << ", rho[k]: " << rho[k] << ", R2: " << R2 << std::endl;

        if (rho[k] < R2) {
            if (k == 0) {
                R2 = rho[k];
                s = Vector(n);
                for (size_t i = 0; i < n; i++){
                    s = s + basis_[i]*v[i];
                    }
            } else {
                k -= 1;
                c[k] = 0;
                for (size_t i = k; i < n; ++i){
                    c[k] = c[k] - mu_[i][k] * v[i];
                    }
                v[k] = round(c[k]);
                w[k] = 1;
            }
        } else {
            k += 1;
            if (k == n) return s;
            if (k >= last_nonzero) {
                last_nonzero = k;
                v[k] += 1;
            } else {
                if (v[k] > c[k]) v[k] -= w[k];
                else v[k] += w[k];
                w[k] += 1;
            }
        }
    }
}



private:
    std::vector<Vector> basis_;
    std::vector<std::vector<double>> mu_; // µ coefficients
    Vector norms; // Norms of the orthogonalized vectors
    
};