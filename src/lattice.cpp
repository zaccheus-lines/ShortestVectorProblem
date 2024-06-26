#include "../include/lattice.h"

// Constructor
Lattice::Lattice(Vector** basis, int size)
    : basis_(basis), n(size), norms(n) {
    mu_ = new double*[n];
    orthogonalizedVectors = new Vector[n];
    for (int i = 0; i < n; ++i) {
        mu_[i] = new double[n];
        std::fill(mu_[i], mu_[i] + n, 0.0);
        orthogonalizedVectors[i] = Vector(n);
    }
}

// Destructor
Lattice::~Lattice() {
    // Deallocate the memory for mu
    for (int i = 0; i < n; ++i) {
        delete[] mu_[i];
    }
    delete[] mu_;
    delete[] orthogonalizedVectors;
}

// Copy constructor
Lattice::Lattice(const Lattice& other)
    : basis_(other.basis_), mu_(other.mu_), norms(other.norms) {
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
}

// isBasis implementation
bool Lattice::isBasis() {
    gramSchmidt();
    for (int i = 0; i < n; ++i) {
        if (norms[i] < epsilon) {
            return false;
        }
    }
    return true;
}

// gramSchmidt implementation
void Lattice::gramSchmidt(int startFrom) {
    if (startFrom == 0) {
        orthogonalizedVectors[0] = *basis_[0];
        norms[0] = orthogonalizedVectors[0].dot(orthogonalizedVectors[0]);
    }
    Vector x(n);
    for (int i = startFrom; i < n; ++i) {
        x.zero();
        for (int j = 0; j < i; ++j) {
            if (norms[j] < epsilon) continue;
            mu_[i][j] = basis_[i]->dot(orthogonalizedVectors[j]) * (1/norms[j]);
            x.addScaledVector(orthogonalizedVectors[j], mu_[i][j]);
        for (int k = 0; k < n; ++k) {
            orthogonalizedVectors[i][k] = (*basis_[i])[k] - x[k];
        }

        norms[i] = orthogonalizedVectors[i].dot(orthogonalizedVectors[i]);
    }
}
}
// gaussianHeuristic implementation
double Lattice::gaussianHeuristic() {
    double sum = 1.0;
    for (int i = 0; i < n; ++i) {
        sum *= basis_[i]->dot(*basis_[i]);
    }
    double recip = 1.0 / static_cast<double>(n);
    sum = std::pow(sum, recip);
    double z = 1.0 + n * 0.25;
    sum *= z;
    return sum;
}

// LLL implementation
void Lattice::LLL() {
    double delta = 0.75;
    int k = 1;
    gramSchmidt();
    while (k < n) {
        for (int j = k - 1; j >= 0; --j) {
            if (std::abs(mu_[k][j]) > 0.5) {
                basis_[k]->addScaledVector(*basis_[j], -std::round(mu_[k][j]));
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
        double R = gaussianHeuristic();
        double R2 = R * R;
        Vector v(n), c(n), w(n), s(n), rho(n + 1);
        v[0] = 1;
        int k = 0, last_nonzero = 0;

        while (true) {
            rho[k] = rho[k + 1] + (v[k] - c[k]) * (v[k] - c[k]) * norms[k];
            if (rho[k] < R2) {
                if (k == 0) {
                    R2 = rho[k];
                    s.zero();
                    for (int i = 0; i < n; i++) {
                        s.addScaledVector(*basis_[i], v[i]);
                        }
                } else {
                    k -= 1;
                    c[k] = 0;
                    for (int i = k; i < n; ++i) {
                        c[k] -= mu_[i][k] * v[i];
                        }
                    v[k] = std::round(c[k]);
                    w[k] = 1;
                }
            } else {
                k += 1;
                if (k == n) {
                    return s;
                }
                if (k >= last_nonzero) {
                    last_nonzero = k;
                    v[k] += 1;
                } else {
                    if (v[k] > c[k]) {
                        v[k] -= w[k];
                    } else {
                        v[k] += w[k];
                    }
                    w[k] += 1;
                }
            }
        }
    }