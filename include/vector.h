// vector.h
#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

class Vector {
private:
    std::vector<double> elements;

public:
    Vector(int size) : elements(size) {}
    double& operator[](int i) { return elements[i]; }
    int size() const { return elements.size(); }
    // Add more functionalities as needed
};

#endif // VECTOR_H
