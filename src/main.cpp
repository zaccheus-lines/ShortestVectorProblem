#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../include/svp_solver.h" // Include the header for your SVP solver
#include "../include/vector.h" // Include the header for your SVP solver


int main() {
    Vector myVector(5);
    
    for (int i = 0; i < myVector.size(); ++i) {
        myVector[i] = i * 2.0;
    }

    std::cout << "Norm before normalization: " << myVector.norm() << std::endl;
    
    myVector.normalize();
    
    std::cout << "Norm after normalization: " << myVector.norm() << std::endl;
    
    return 0;
}