#include <iostream>
#include <vector>
#include <set>
#include "vector.h"
#include <cfenv>

class Lattice {
public:
    std::vector<Vector> orthogonalizedVectors;

    // Constructor that takes a basis
    Lattice(const std::vector<Vector>& basis)
    : basis_(basis), n(basis.size()), norms(n) {
        mu_.resize(n, std::vector<long double>(n, 0.0));
        orthogonalizedVectors.resize(n);
    }

    

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

    bool isBasis(const std::vector<Vector>& potentialBasis) {
        // Set the basis of the lattice to the potential basis
        basis_ = potentialBasis;

        size_t dimension = basis_.size();
        for (const auto& vec : basis_) {
            if (vec.size() != dimension) {
                return false;
        }
        }

        // Gram-Schmidt for the new basis
        gramSchmidt();

        // Check if any of the norms is zero (indicating a zero vector was produced)
        for (size_t i = 0; i < n; ++i) {
            if (norms[i] == 0.0) {
                return false; // A zero norm indicates linear dependence
            }
        }

    return true; // All vectors are linearly independent
}

    void gramSchmidt(size_t startFrom = 0) {

        if (startFrom == 0) {
            orthogonalizedVectors[0] = basis_[0];
            norms[0] = orthogonalizedVectors[0].dot(orthogonalizedVectors[0]);
        }

        for (size_t i = startFrom; i < n; ++i) {
            Vector x;

            for (size_t j = 0; j < i; ++j) {
                long double normSquared = orthogonalizedVectors[j].dot(orthogonalizedVectors[j]);
                if (normSquared < epsilon) continue; // Skip zero vector to avoid division by zero

                mu_[i][j] = basis_[i].dot(orthogonalizedVectors[j]) * (1/normSquared);
                x += orthogonalizedVectors[j] * mu_[i][j];
            }

            orthogonalizedVectors[i] = basis_[i] - x;
            norms[i] = orthogonalizedVectors[i].dot(orthogonalizedVectors[i]);
        }
    }
    

    void LLL(){
        long double delta = 0.75;
        size_t k = 1;
        gramSchmidt();
        while (k < n) {
            //std::cout << k << std::endl;
            // Size Reduction
            for (int j = k -1; j >= 0; --j) {
                if (std::abs(mu_[k][j]) > 0.5) {
                    // Size reduce bk
                    basis_[k] -= basis_[j] * std::round(mu_[k][j]) ;
    
                    gramSchmidt(k);

                }
            }
            // Lovász Condition
            if (norms[k] > (delta - mu_[k][k-1] * mu_[k][k-1]) * norms[k-1]) {
                ++k;
            } else {
                // Swap bk and bk-1
                std::swap(basis_[k], basis_[k-1]);
                // Recompute Gram-Schmidt and mu
                gramSchmidt(k-1);
                k = std::max(static_cast<unsigned int>(k-1), 1u);

            }
        }
    }

    Vector schnorrEuchnerEnumeration() {
        gramSchmidt();
        long double R = norms.max()+1;
        //norms.print();
        std::vector<long double> rho(n + 1, 0.0);
        Vector v(n), c(n), w(n), s(n);
        v[0]=1;
        size_t k = 0, last_nonzero = 0;
        long double R2 = R * R;

        while (true) {
            rho[k] = rho[k + 1] + (v[k] - c[k]) * (v[k] - c[k]) * norms[k];

            // Debugging output
            // std::cout << "k: " << k << ", rho[k]: " << rho[k] << ", R2: " << R2 << std::endl;

            if (rho[k] < R2) {
                if (k == 0) {
                    R2 = rho[k];
                    s = Vector(n);
                    for (size_t i = 0; i < n; i++){
                        s += basis_[i]*v[i];
                        }
                } else {
                    k -= 1;
                    c[k] = 0;
                    for (size_t i = k; i < n; ++i){
                        c[k] -= mu_[i][k] * v[i];
                        }
                    v[k] = std::round(c[k]);
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
    size_t n;
    std::vector<std::vector<long double>> mu_; // µ coefficients
    Vector norms; // Norms of the orthogonalized vectors
    const long double epsilon = 1e-10; // Define epsilon here
    
};