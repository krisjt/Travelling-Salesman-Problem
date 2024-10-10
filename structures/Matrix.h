////
//// Created by Krystyna Nowak on 09/10/2024.
////
//
#ifndef PEA1_MATRIX_H
#define PEA1_MATRIX_H
#include <iostream>
using namespace std;

//class Matrix {
//    int size;
//    int** matrix;

//public:
//    Matrix(int size) : size(size) {
//        matrix = new int*[size];
//        for (int i = 0; i < size; i++) {
//            matrix[i] = new int[size]{0}; // Initialize with zeros or other values as needed
//        }
//    }
//
//    Matrix(int** matrix, int size) : size(size), matrix(nullptr) {
//        this->matrix = new int*[size];
//        for (int i = 0; i < size; i++) {
//            this->matrix[i] = new int[size];
//            std::copy(matrix[i], matrix[i] + size, this->matrix[i]);
//        }
//    }
//
//    ~Matrix() {
//        for (int i = 0; i < size; i++) {
//            delete[] matrix[i];
//        }
//        delete[] matrix;
//    }
//};

class Matrix {

    Matrix(int size);

    int size;
    int** matrix;
public:
//    Matrix();
    Matrix(int** matrix, int size);
    ~Matrix();
    void printMatrix();
    int getSize() const;
    int getDistance(int i, int j) const;
    int** getMatrix();
};

#endif //PEA1_MATRIX_H

