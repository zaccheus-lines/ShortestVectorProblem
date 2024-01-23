#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include "../include/lattice.h"

// Function to verify whether input is number or not.
bool isNumber(const std::string& str) {
    std::istringstream iss(str);
    double num;
    iss >> std::noskipws >> num;
    return iss.eof() && !iss.fail();
}

int main(int argc, char* argv[]) {
    // auto start = std::chrono::high_resolution_clock::now();
    // No argument case
    if (argc <= 1) {
        std::cerr << "Error: Invalid argument." << std::endl;
        return 1;
    }
    // Single argument case
    std::string arg = argv[1];
    if (argc == 2) {
        if (arg.front() == '[' && arg.back() == ']') {
            arg = arg.substr(1, arg.size() - 2);
            if (isNumber(arg)) {
                if (std::abs(std::stod(arg)) == 0){
                    std::cerr << "Error: Provided vectors are not linearly independent." << std::endl;
                    return 1;
                }
                // auto end = std::chrono::high_resolution_clock::now();
                // std::chrono::duration<double, std::milli> duration = end - start;
                std::ofstream outfile("result.txt");
                outfile << std::setprecision(16) << std::abs(std::stod(arg)) << std::endl;
                outfile.close();
                return 0;
            }
        }
        std::cerr << "Error: Invalid argument." << std::endl;
        return 1;
    }
    // General case
    double sqrt_val = std::sqrt(argc - 1);
    if (std::round(sqrt_val) != sqrt_val) {
        std::cerr << "Error: Invalid argument." << std::endl;
        return 1;
    }
    int size = static_cast<int>(sqrt_val);
    Vector** basis = new Vector*[size];
    double* nums = new double[size];
    int k = 0;
    for (int i = 0; i+1 < argc; ++i) {
        arg = argv[i+1];
        int residue = i % size;
        if (residue == 0) {
            if (arg[0] == '[') {
                arg.erase(0, 1);
                if (isNumber(arg)) {
                    nums[0] = std::stod(arg);
                    continue;
                }
            }
            std::cerr << "Error: Invalid argument." << std::endl;
            return 1;
        } else if (residue == size - 1) {
            if (arg.back() == ']') {
                arg.pop_back();
                if (isNumber(arg)) {
                    nums[residue] = std::stod(arg);
                    double* numsCopy = new double[size];
                    std::copy(nums, nums + size, numsCopy);
                    Vector* newVector = new Vector(numsCopy, size);  //malloc for each vector in basis
                    basis[k++] = newVector;
                    continue;
                }
            }
            std::cerr << "Error: Invalid argument." << std::endl;
            return 1;
        } else {
            if (isNumber(arg)) {
                nums[residue] = std::stod(arg);
                continue;
            }
            std::cerr << "Error: Invalid argument." << std::endl;
            return 1;
        }
    }
    delete[] nums;  //free nums memory
    Lattice Lattice(basis, size);
    if (!Lattice.isBasis()) {
        std::cerr << "Error: Provided vectors are not linearly independent." << std::endl;
        return 1;
    }
    Lattice.LLL(); // LLL reduce basis
    Vector SV = Lattice.schnorrEuchnerEnumeration(); //Enumerate basis
    double SVL = SV.norm();
    //auto end = std::chrono::high_resolution_clock::now();
    std::ofstream outfile("result.txt");
    outfile << std::fixed << std::setprecision(16) << SVL << std::endl;
    outfile.close(); //output shortest vector length to result.txt
    //std::chrono::duration<double, std::milli> duration = end - start;
    //std::cout << "Duration: " << duration.count() << " milliseconds" << std::endl;
    for (int i = 0; i < size; i++) {
        delete basis[i];  //free basis[i] memory
    }
    delete[] basis;  //free basis memory
    return 0;
}