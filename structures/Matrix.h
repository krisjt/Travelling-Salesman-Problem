////
//// Created by Krystyna Nowak on 09/10/2024.
////
//
#ifndef PEA1_MATRIX_H
#define PEA1_MATRIX_H
#include <iostream>
using namespace std;

class Matrix {
private:
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

