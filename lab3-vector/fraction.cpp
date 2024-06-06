#include <iostream>
#include <stdexcept> // std::out_of_range
#include <numeric>   // std::gcd

#include "fraction.h"


Fraction::Fraction(int numerator, int denominator) : numerator_(numerator), denominator_(denominator)
{
    if (denominator_ == 0)
        throw std::invalid_argument("Denominator cannot be zero.");
}

int Fraction::numerator() const
{
    return numerator_;
}

int Fraction::denominator() const
{
    return denominator_;
}

void Fraction::setDenominator(int denominator)
{
    if (denominator == 0)
        throw std::invalid_argument("Denominator cannot be zero.");
    denominator_ = denominator;
}

void Fraction::setNumerator(int numerator)
{
    numerator_ = numerator;
}

Fraction Fraction::operator+(const Fraction& other) const
{
    int new_numerator = numerator_ * other.denominator() + other.numerator() * denominator_;
    int new_denominator = denominator_ * other.denominator();
    int gcd = std::gcd(new_numerator, new_denominator);
    return Fraction(new_numerator / gcd, new_denominator / gcd);
}

Fraction Fraction::operator*(const Fraction& other) const
{
    int new_numerator = numerator_ * other.numerator();
    int new_denominator = denominator_ * other.denominator();
    int gcd = std::gcd(new_numerator, new_denominator);
    return Fraction(new_numerator / gcd, new_denominator / gcd);
}