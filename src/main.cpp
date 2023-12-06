#include "../include/LLL.h"

int main() {
    // Example input basis vectors using Vector
    std::vector<Vector> basis = {
        Vector{1.0, 2.0, 3.0},
        Vector{4.0, 5.0, 6.0},
        Vector{7.0, 8.0, 9.0}
    };

    // Create an instance of the LLL class
    LLL lll(basis);

    // Get the Gram-Schmidt basis vectors
    lll.gramSchmidt();
    
    // Print out the Gram-Schmidt basis vectors
    for (const Vector vector : lll) {
        vector.print();
    }
    return 0;
}