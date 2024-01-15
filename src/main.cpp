#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include "../include/lattice.h"


bool isNumber(const std::string& str) {
    std::istringstream iss(str);
    double num;
    iss >> std::noskipws >> num; // Try to extract a number

    // Check if extraction was successful and the stream is in a good state
    return iss.eof() && !iss.fail();
}

int main(int argc, char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    if (argc <= 1) {
        std::cerr << "Error: Invalid argument" << std::endl;
        return 1;
    }
    
    std::string arg = argv[1];
    if (argc ==2){
        if (arg[0]=='[' && arg.back() == ']'){
            arg.erase(0,1);
            arg.pop_back();
            if(isNumber(arg)){
                
                std::cout << std::fixed << std::setprecision(16) << std::abs(std::stod(arg)) << std::endl;
                return 0;
            }
            else{
                std::cerr << "Error: Invalid argument" << std::endl;
                return 1;
            }

        }
        else{
            std::cerr << "Error: Invalid argument" << std::endl;
            return 1;
        }
    }
    
    
    double sqrt_val = std::sqrt(argc - 1);
    if (std::round(sqrt_val) != sqrt_val)
    {
        std::cerr << "Error: Invalid argument" << std::endl;
        return 1;
    }
    int size = static_cast<int>(sqrt_val);
    Vector** basis = new Vector*[size];

    // Initialize k here
    int k = 0;
    
    
    double* nums = new double[size];
    for (int i = 0; i+1 < argc; ++i) {
        arg = argv[i+1];
        int result = i % size;
        

        if (result == 0) {
            if (arg[0] == '[') 
            {
                arg.erase(0,1);
                if(isNumber(arg)){
                    nums[0] = std::stod(arg);
                }
                else {
                    std::cerr << "Error: Invalid argument" << std::endl;
                    return 1;
                }
            }
            else {
                std::cerr << "Error: Invalid argument" << std::endl;
                return 1;
            }
        } 
        else if (result == size - 1) {
            if (arg.back() == ']'){
                arg.pop_back();
                if (isNumber(arg)){
                    nums[size - 1] = std::stod(arg);
                    double* numsCopy = new double[size];
                    std::copy(nums, nums + size, numsCopy);

                    // Create a new Vector with the copied array
                    Vector* newVector = new Vector(numsCopy, size);
                    basis[k++] = newVector;
                }
                else{
                    std::cerr << "Error: Invalid argument" << std::endl;
                    return 1;
                }
                
                }
            else{
                std::cerr << "Error: Invalid argument" << std::endl;
                std::cerr << 2.2 << std::endl;
                return 1;
            }
        } else {
            if (isNumber(arg)) {
                nums[result] = std::stod(arg);
            } else {
                std::cerr << "Error: Invalid argument" << std::endl;
                return 1;
            }
        }
        
        }
    delete[] nums;

        // Create an instance of the Lattice class
        Lattice Lattice(basis,size);

        if (!Lattice.isBasis()) {
            std::cerr << "Error: The provided vectors do not form a valid basis." << std::endl;
            return 1;}
        Vector SV = Vector(size);
        double SVL;

        

        Lattice.LLL();
        //Lattice.gramSchmidt();
        
        
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