//
// Created by Krystyna Nowak on 09/10/2024.
//

#ifndef PEA1_MATRIX_H
#define PEA1_MATRIX_H
#include <iostream>
using namespace std;

class Matrix {
private:
    // wielkosc macierzy
    int size;

    // dane w maciezry
    int** data;
public:
    Matrix(int** matrix, int size);
    ~Matrix();
    void printMatrix();
    int getSize() const;
    int getDistance(int i, int j) const;
    int** getMatrix();

    void copyMatrix(int **&other);
};

#endif //PEA1_MATRIX_H

