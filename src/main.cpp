#include <chrono>
#include <fstream>
#include <iostream>
#include "../include/lattice.h"

bool isNumber(const std::string& str) {
    std::istringstream iss(str);
    double num;
    iss >> std::noskipws >> num;
    return iss.eof() && !iss.fail();
}

int main(int argc, char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
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
                std::cout << std::fixed << std::setprecision(16) << std::abs(std::stod(arg)) << std::endl;
                std::ofstream outfile("result.txt");
                outfile << std::abs(std::stod(arg)) << std::endl;
                outfile.close();
                return 0;
            }
        }
        std::cerr << "Error: Invalid argument." << std::endl;
        return 1;
    }
    // Genral case
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
                    Vector* newVector = new Vector(numsCopy, size);
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
    delete[] nums;
    Lattice Lattice(basis, size);
    if (!Lattice.isBasis()) {
        std::cerr << "Error: Provided vectors are not linearly independent." << std::endl;
        return 1;
    }
    Lattice.LLL();
    Vector SV = Lattice.schnorrEuchnerEnumeration();
    double SVL = SV.norm();
    std::cout << std::fixed << std::setprecision(16) << SVL << std::endl;
    std::ofstream outfile("result.txt");
    outfile << std::fixed << std::setprecision(16) << SVL << std::endl;
    outfile.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    //std::cout << "Duration: " << duration.count() << " milliseconds" << std::endl;
    for (int i = 0; i < size; i++) {
        delete basis[i];
    }
    delete[] basis;
    return 0;
}