//
// Created by Krystyna Nowak on 09/10/2024.
//

#include "Matrix.h"

//Matrix::Matrix() {
//    this->size = 0;
//    this->matrix = nullptr;
//}

Matrix::Matrix(int** matrix, int size){
    this->size = size;
    this->matrix = matrix;
}
//Matrix::Matrix(int size) : size(size) {
//    matrix = new int*[size];
//    for (int i = 0; i < size; i++) {
//        matrix[i] = new int[size]; // Initialize elements as needed
//    }
//}

Matrix::~Matrix() {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];  // Zwalnianie pamięci dla każdego wiersza
    }
    delete[] matrix;  // Zwalnianie pamięci dla tablicy wskaźników
}

//void Matrix::matrixInit(int** matrix, int size){
//
//}

void Matrix::printMatrix(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cout << matrix[i][j] << ' ';
        }
        cout<<'\n';
    }
}

int** Matrix::getMatrix(){
    return matrix;
}

int Matrix::getDistance(int i, int j) const {
    return matrix[i][j];
}

int Matrix::getSize() const{
    return size;
}