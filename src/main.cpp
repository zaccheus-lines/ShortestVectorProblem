#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include "../include/lattice.h"

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

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "Error: No vectors provided." << std::endl;
        return 1;
    }

    double sqrt_val = std::sqrt(argc - 1);
    
        
    if (sqrt_val * sqrt_val != argc - 1) {
        std::cerr << "Wrong format: Number of arguments is not a perfect square." << std::endl;
        return 1;
        }
    
    int size = static_cast<int>(sqrt_val);
    //std::cout << "size " << size << std::endl;
    
    
Vector** basis = new Vector*[size];

 // Initialize k here
int k = 0;
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
        std::vector<double> nums = parseNumbers(currentVector);
        if (k < size) {
            Vector* newVector = new Vector(nums);
            basis[k] = newVector;
            k += 1;
        } else {
            // Handle the case where k exceeds the size of basis (error or resizing)
            // You can print an error message or resize basis if needed.
        }
        currentVector.clear(); // Clear the current vector string
    }
}

    // Create an instance of the Lattice class
    Lattice Lattice(basis,size);

    if (!Lattice.isBasis()) {
        std::cerr << "Error: The provided vectors do not form a valid basis." << std::endl;
        return 1;}
    Vector SV = Vector(size);
    double SVL;

    auto start = std::chrono::high_resolution_clock::now();

    Lattice.LLL();
    SV = Lattice.schnorrEuchnerEnumeration();
    
    
    

   SVL = SV.norm();
   //delete[] SV.data;
   std::cout << std::fixed << std::setprecision(16) << SVL << std::endl;
   //std::cout << SVL << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    //std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
    for (int i = 0; i < size; i++) {
        delete basis[i];
      // Free memory for each Vector object
    }
    delete[] basis; // Free memory for the array
    return 0;
}