#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <initializer_list>

class Vector {
public:
    // Constructors
    Vector();
    Vector(std::initializer_list<long double> list);
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
    void push_back(long double value);
    void print() const;
    long double& operator[](size_t index);
    const long double& operator[](size_t index) const;
    long double norm() const;
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    void normalise();
    Vector operator*(long double scalar) const;
    long double dot(const Vector& other) const;
    size_t size() const;
    long double max() const;

    static size_t commonSize;

private:
    std::vector<long double> data;
};

#endif // VECTOR_H
