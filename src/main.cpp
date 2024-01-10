#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include "../include/lattice.h"
#include <cstdlib>
#include <chrono>
#include <iomanip>

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

size_t Vector::commonSize = 0;  // Definition

int main(int argc, char* argv[]) {

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<Vector> basis;
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
            basis.emplace_back(nums.begin(), nums.end());
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


    Lattice.LLL();
    SV = Lattice.schnorrEuchnerEnumeration();

   SVL = SV.norm();
   std::cout << std::fixed << std::setprecision(16) << SVL << std::endl;
   //std::cout << SVL << std::endl;




    
    
    

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<long double, std::milli> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;

    return 0;
}