#include <iostream>
#include <vector>
#include "vector.h"

class LLL {
public:
    // Constructor that takes a basis
    LLL(const std::vector<Vector>& basis) : basis_(basis) {}

    // Destructor
    ~LLL() {
        // Implement necessary cleanup here
    }

    // Copy constructor
    LLL(const LLL& other) : basis_(other.basis_) {
        // Perform deep copy of resources if needed
    }

    // Copy assignment operator
    LLL& operator=(const LLL& other) {
        if (this != &other) {
            // Perform deep copy of resources if needed
            basis_ = other.basis_;
        }
        return *this;
    }

    // Move constructor
    LLL(LLL&& other) noexcept : basis_(std::move(other.basis_)) {
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

    // Perform Gram-Schmidt orthogonalization on the basis
    void gramSchmidt() {
        size_t n = basis_.size();
        size_t m = basis_[0].size(); // Assuming all vectors have the same size
        double tol = 10e-7;

        // Create orthogonalizedVectors as a copy of basis
        std::vector<Vector> orthogonalizedVectors = basis_;

        for (size_t i = 0; i < n; ++i) {
            orthogonalizedVectors[i][i] = basis_[i].norm(); // r_ii = ||a_i||

            if (orthogonalizedVectors[i][i] > tol) {
                basis_[i].normalise(); // a_i = a_i/r_ii
            }
            else if (i == 0) { // set a[0] = [1 0 0 ... 0]^T
                basis_[i][0] = 1;
                for (size_t j = 1; j < m; ++j) {
                    basis_[i][j] = 0;
                }
            }
            else { // need to choose a_i orthogonal to < a_1, ... a_{i-1} >
                for (size_t j = 0; j < m; ++j) {
                    basis_[i][j] = -basis_[0][i] * basis_[0][j];
                }
                basis_[i][i] += 1;

                for (size_t j = 1; j < i; ++j) {
                    double projection = basis_[i].dot(basis_[j]);
                    basis_[i].scalar_sub(projection, basis_[j]);
                    
                }

                basis_[i].normalise();
            }

            for (size_t j = i + 1; j < n; ++j) {
                orthogonalizedVectors[j][i] = basis_[i].dot(basis_[j]); // r_ij = a_i*a_j
                basis_[j].scalar_sub(orthogonalizedVectors[j][i], basis_[i]);
            }
        }
    }

private:
    std::vector<Vector> basis_;
};

