#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include "../include/lattice.h"

std::vector<long double> parseNumbers(const std::string& str) {
    std::vector<long double> numbers;
    std::stringstream ss(str);
    char ch;  // used to consume the '[' and ']' characters
    long double num;
    while (ss >> ch && ch == '[') {
        while (ss >> num) {
            numbers.push_back(num);
            if (ss.peek() == ']') {
                ss.ignore();
                break;
            }
        }
    }
    return numbers;

}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "Error: No vectors provided." << std::endl;
        return 1;
    }

    double sqrt_val = std::sqrt(argc - 1);
    if (std::floor(sqrt_val) != sqrt_val) {
        std::cerr << "Wrong format: Number of arguments is not a perfect square." << std::endl;
        return 1;
    }

    std::vector<Vector*> basis;
    basis.reserve(sqrt_val);
    std::string currentVector;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg.find('[') != std::string::npos) {
            // Start of a new vector
            currentVector = arg;
        } 
        else {
            // Middle or end of a vector
            currentVector += " " + arg;
        }

        if (arg.find(']') != std::string::npos) {
            // End of the current vector, parse it
            std::vector<long double> nums = parseNumbers(currentVector);
            Vector* newVector = new Vector(nums.begin(), nums.end());
            basis.push_back(newVector);
            currentVector.clear(); // Clear the current vector string
        }
    }
  

    // n is the common size of a vector. 
    Vector::commonSize = basis.size();
    // Create an instance of the Lattice class
    Lattice Lattice(basis);
    if (!Lattice.isBasis(basis)) {
        std::cerr << "Error: The provided vectors do not form a valid basis." << std::endl;
        return 1;}
    Vector SV;
    long double SVL;

    auto start = std::chrono::high_resolution_clock::now();

    Lattice.LLL();
    SV = Lattice.schnorrEuchnerEnumeration();
    
    for (Vector* vec : basis) {
        delete vec;
    }

   SVL = SV.norm();
   std::cout << std::fixed << std::setprecision(16) << SVL << std::endl;
   //std::cout << SVL << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<long double, std::milli> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;

    return 0;
}