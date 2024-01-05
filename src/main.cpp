#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include "../include/lattice.h"
#include <cstdlib> 
#include <chrono>

std::vector<double> parseNumbers(const std::string& str) {
    std::vector<double> numbers;
    std::stringstream ss(str);
    char ch;  // used to consume the '[' and ']' characters
    double num;
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
        } else {
            // Middle or end of a vector
            currentVector += " " + arg;
        }

        if (arg.find(']') != std::string::npos) {
            // End of the current vector, parse it
            std::vector<double> nums = parseNumbers(currentVector);
            basis.emplace_back(nums.begin(), nums.end());
            currentVector.clear(); // Clear the current vector string
        }
    }
/*    // Output constructed vectors
    for (const Vector& v : basis) {
        v.print();
    }*/

    // n is the common size for most vectors
    Vector::commonSize = basis.size();
    // Create an instance of the Lattice class
    Lattice Lattice(basis);
    //Vector SV;
    //double SVL;

    //Lattice.LLL();
    //SV = Lattice.schnorrEuchnerEnumeration();
    /*for (Vector& vector : Lattice) {
            vector.print();} */
    //SV.print();

   //SVL = SV.norm();
   //std::cout << SVL << std::endl;




    
    
    

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;

    return 0;
}