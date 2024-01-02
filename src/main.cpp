#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include "../include/lattice.h"

int main() {
    // Example input basis vectors using Vector
    std::vector<Vector> basis = {
        Vector{33572.0, 1.0, 0.0, 0.0, 0.0},
        Vector{29630.0, 0.0, 1.0, 0.0, 0.0},
        Vector{37745.0, 0.0, 0.0, 1.0, 0.0},
        Vector{33964.0, 0.0, 0.0, 0.0, 1.0},
        Vector{30041.0, 0.0, 0.0, 0.0 ,0.0}
    };

    // Create an instance of the Lattice class
    Lattice Lattice(basis);
    Vector SV;

    // Get the Gram-Schmidt basis vectors
    //Lattice.gramSchmidt();
    SV = Lattice.schnorrEuchnerEnumeration(100);
    //Lattice.schnorrEuchnerEnumeration(10000);
    SV.print();
    //SV.print();
    std::cout << "SV length: " << SV.norm() << std::endl;
    // Print out the Gram-Schmidt basis vectors
    return 0;
    }
/*
Vector parseVector(const std::vector<std::string>& args) {
    Vector result;
    for (const auto& item : args) {
        result.push_back(std::stod(item));
    }
    return result;
}

int main(int argc, char* argv[]) {
    std::vector<Vector> vectors;
    std::vector<std::string> currentVectorArgs;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.front() == '[') {
            // Remove the leading '['
            arg = arg.substr(1);
        }
        if (arg.back() == ']') {
            // Remove the trailing ']' and add the last element of the current vector
            currentVectorArgs.push_back(arg.substr(0, arg.size() - 1));
            vectors.push_back(parseVector(currentVectorArgs));
            currentVectorArgs.clear();
        } else {
            currentVectorArgs.push_back(arg);
        }
    }

    // Example: Print the parsed vectors
    for (const auto& vec : vectors) {
        vec.print();
    }

    return 0;
}
*/