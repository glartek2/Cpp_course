#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>   

using namespace std;

#include "matrix.h"


TwoDimensionMatrix::TwoDimensionMatrix() {
   
    for (size_t i = 0; i < size_; ++i) {
        for (size_t j = 0; j < size_; ++j) {
            matrix_[i][j] = MatrixElement();
        }
    }
}


TwoDimensionMatrix::TwoDimensionMatrix(const TwoDimensionMatrix& other) {
    
    for (size_t i = 0; i < size_; ++i) {
        for (size_t j = 0; j < size_; ++j) {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
}


TwoDimensionMatrix::TwoDimensionMatrix(const MatrixElement matrix[size_][size_]) {
    
    for (size_t i = 0; i < size_; ++i) {
        for (size_t j = 0; j < size_; ++j) {
            matrix_[i][j] = matrix[i][j];
        }
    }
}


TwoDimensionMatrix& TwoDimensionMatrix::operator=(const TwoDimensionMatrix& other) {    // Check for self-assignment
    if (this != &other) {

        for (size_t i = 0; i < size_; ++i) {
            for (size_t j = 0; j < size_; ++j) {
                matrix_[i][j] = other.matrix_[i][j];
            }
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const TwoDimensionMatrix& matrix) {
    for (size_t i = 0; i < TwoDimensionMatrix::size(); ++i) {
        for (size_t j = 0; j < TwoDimensionMatrix::size(); ++j) {
            os << matrix.get(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, TwoDimensionMatrix& matrix) {
    constexpr size_t size_ = TwoDimensionMatrix::size();
    MatrixElement temp[size_][size_];

    for (size_t i = 0; i < size_; ++i) {
        for (size_t j = 0; j < size_; ++j) {
            is >> temp[i][j];
            std::cout << "Read value: " << temp[i][j] << std::endl; // Debug print
        }
    }


    matrix = TwoDimensionMatrix(temp);

    return is;
}

TwoDimensionMatrix operator+(const TwoDimensionMatrix& matrix1, const TwoDimensionMatrix& matrix2) {
    MatrixElement resultArray[TwoDimensionMatrix::size()][TwoDimensionMatrix::size()];
    for (size_t i = 0; i < TwoDimensionMatrix::size(); ++i) {
        for (size_t j = 0; j < TwoDimensionMatrix::size(); ++j) {
            resultArray[i][j] = matrix1.get(i, j) + matrix2.get(i, j);
        }
    }
    return TwoDimensionMatrix(resultArray);
}


MatrixElement TwoDimensionMatrix::get(size_t row, size_t col) const {
    if (row < size_ && col < size_) {
        return matrix_[row][col];

    } else {
        throw std::out_of_range("Indices out of bounds");
    }
}


MatrixElement* TwoDimensionMatrix::operator[](size_t i) {
    if (i >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return matrix_[i];
}

const MatrixElement* TwoDimensionMatrix::operator[](size_t i) const {
    if (i >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return matrix_[i];
}


TwoDimensionMatrix::operator size_t() const {
    return size();
}