#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

#include "fraction.h"

#ifdef UNIMPLEMENTED_classFraction
#ifdef _MSC_FULL_VER // if Visual Studio Compiler
    #pragma message ("Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym")
#else
    #warning "Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym"
#endif // #ifdef _MSC_FULL_VER
#endif // #ifdef UNIMPLEMENTED_classFraction

#include "fraction.h"

#include <iostream>
#include <sstream>

int Fraction::removedFractions_ = 0;

Fraction::Fraction() : numerator_(0), denominator_(1) {}

Fraction::Fraction(int numerator, int denominator, string fractionName) : numerator_(numerator), denominator_(denominator), fractionName_(fractionName) {}

Fraction::~Fraction() {
    removedFractions_++;
}

int Fraction::getNumerator() const {
    return numerator_;
}

void Fraction::setNumerator(int numerator) {
    numerator_ = numerator;
}

int Fraction::getDenominator() const {
    return denominator_;
}

void Fraction::setDenominator(int denominator) {
    denominator_ = denominator;
}

void Fraction::print() const {
    std::cout << numerator_ << "/" << denominator_ << std::endl;
}

int Fraction::removedFractions() {
    return removedFractions_;
}

void Fraction::save(std::ostream& os) const {
    os << numerator_ << "/" << denominator_;
}

void Fraction::load(std::istream& is) {
    char slash;
    is >> numerator_ >> slash >> denominator_;
}

int Fraction::getInvalidDenominatorValue() {
    return invalidDenominatorValue;
}

int Fraction::getDefaultDenominatorValue() {
    return defaultDenominatorValue;
}

std::string Fraction::getFractionName() const{
    return fractionName_;
}