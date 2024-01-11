#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <initializer_list>

class Vector {
public:
    // Constructors
    Vector();
    Vector(std::initializer_list<double> list);
    Vector(size_t size);

    template <typename Iter>
    Vector(Iter begin, Iter end) : data(begin, end) {}

    // Copy constructor
    Vector(const Vector& other);

    // Move constructor
    Vector(Vector&& other) noexcept;

    // Destructor
    ~Vector();

    // Copy assignment operator
    Vector& operator=(const Vector& other);

    // Move assignment operator
    Vector& operator=(Vector&& other) noexcept;

    // Methods
    void push_back(double value);
    void print() const;
    double& operator[](size_t index);
    const double& operator[](size_t index) const;
    double norm() const;
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    void normalise();
    Vector operator*(double scalar) const;
    double dot(const Vector& other) const;
    size_t size() const;
    double max() const;

    static size_t commonSize;

private:
    std::vector<double> data;
};

#endif // VECTOR_H
