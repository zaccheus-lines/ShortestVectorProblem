#include "../include/lattice.h"
#include <cmath>     // For std::sqrt, std::round, std::abs
#include <algorithm> // For std::max, std::swap

// Constructor
Lattice::Lattice(const std::vector<Vector*>& basis)
    : basis_(basis), n(basis.size()), norms(n) {
    mu_.resize(n, std::vector<long double>(n, 0.0));
    orthogonalizedVectors.resize(n);
    gramSchmidt();
}

// Destructor
Lattice::~Lattice() {
    // Clean up resources if necessary
}

// Copy constructor
Lattice::Lattice(const Lattice& other)
    : basis_(other.basis_), mu_(other.mu_), norms(other.norms) {
    // Deep copy of the basis if necessary
}

// Copy assignment operator
Lattice& Lattice::operator=(const Lattice& other) {
    if (this != &other) {
        basis_ = other.basis_;
        mu_ = other.mu_;
        norms = other.norms;
    }
    return *this;
}

// Move constructor
Lattice::Lattice(Lattice&& other) noexcept
    : basis_(std::move(other.basis_)), mu_(std::move(other.mu_)), norms(std::move(other.norms)) {
    // Move resources from 'other' to 'this'
}

// isBasis implementation
bool Lattice::isBasis(const std::vector<Vector*>& potentialBasis) {
    basis_ = potentialBasis;
    size_t dimension = basis_.size();
    for (const auto& vec : basis_) {
        if (vec->size() != dimension) {
            return false;
        }
    }

    gramSchmidt();
    for (size_t i = 0; i < n; ++i) {
        if (norms[i] == 0.0) {
            return false;
        }
    }
    return true;
}

// gramSchmidt implementation
void Lattice::gramSchmidt(size_t startFrom) {
    if (startFrom == 0) {
        orthogonalizedVectors[0] = *basis_[0];
        norms[0] = orthogonalizedVectors[0].dot(orthogonalizedVectors[0]);
    }

    for (size_t i = startFrom; i < n; ++i) {
        Vector x;
        for (size_t j = 0; j < i; ++j) {
            long double normSquared = orthogonalizedVectors[j].dot(orthogonalizedVectors[j]);
            if (normSquared < epsilon) continue;

            mu_[i][j] = basis_[i]->dot(orthogonalizedVectors[j]) * (1/normSquared);
            x += orthogonalizedVectors[j] * mu_[i][j];
        }
        orthogonalizedVectors[i] = *basis_[i] - x;
        norms[i] = orthogonalizedVectors[i].dot(orthogonalizedVectors[i]);
    }
}

// LLL implementation
void Lattice::LLL() {
    long double delta = 0.75;
    size_t k = 1;
    gramSchmidt();
    while (k < n) {
        for (int j = k - 1; j >= 0; --j) {
            if (std::abs(mu_[k][j]) > 0.5) {
                *basis_[k] -= *basis_[j] * std::round(mu_[k][j]);
                gramSchmidt(k);
            }
        }
        if (norms[k] > (delta - mu_[k][k-1] * mu_[k][k-1]) * norms[k-1]) {
            ++k;
        } else {
            std::swap(basis_[k], basis_[k-1]);
            gramSchmidt(k-1);
            k = std::max(static_cast<unsigned int>(k-1), 1u);
        }
    }
}

// schnorrEuchnerEnumeration implementation
Vector Lattice::schnorrEuchnerEnumeration() {
        gramSchmidt();
        long double R = norms.max();
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
                        s += *basis_[i]*v[i];
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