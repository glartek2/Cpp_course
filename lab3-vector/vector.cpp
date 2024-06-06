#include <algorithm>
#include <stdexcept>
#include <utility> // std::swap()
#include "vector.h"

Vector::Vector(std::size_t initial_capacity) : size_(0), capacity_(initial_capacity)
{
    if (initial_capacity > 0)
        data_ = std::make_unique<Fraction[]>(initial_capacity);
}

Vector::Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_)
{
    data_ = std::make_unique<Fraction[]>(capacity_);
    std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
}

Vector& Vector::operator=(const Vector& other)
{
    if (this != &other)
    {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = std::make_unique<Fraction[]>(capacity_);
        std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
    }
    return *this;
}

Vector::Vector(Vector&& other) noexcept : size_(other.size_), capacity_(other.capacity_), data_(std::move(other.data_))
{
    other.size_ = 0;
    other.capacity_ = 0;
}

Vector& Vector::operator=(Vector&& other) noexcept
{
    if (this != &other)
    {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = std::move(other.data_);
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

std::size_t Vector::size() const
{
    return size_;
}

std::size_t Vector::capacity() const
{
    return capacity_;
}

Fraction* Vector::data() const
{
    return data_.get();
}

void Vector::push_back(const Fraction& value)
{
    if (size_ >= capacity_)
        expand_capacity();
    data_[size_] = value;
    size_++;
}

Fraction& Vector::operator[](std::size_t index)
{
    if (index >= size_)
        throw std::out_of_range("Index out of range.");
    return data_[index];
}

const Fraction& Vector::operator[](std::size_t index) const
{
    if (index >= size_)
        throw std::out_of_range("Index out of range.");
    return data_[index];
}

void Vector::expand_capacity()
{
    if (capacity_ == 0)
        capacity_ = 1;
    else
        capacity_ = capacity_ + 1;

    std::unique_ptr<Fraction[]> new_data = std::make_unique<Fraction[]>(capacity_);
    std::copy(data_.get(), data_.get() + size_, new_data.get());
    data_ = std::move(new_data);
}





