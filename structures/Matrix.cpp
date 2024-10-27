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
    this->data = matrix;
}

Matrix::~Matrix() {
    for (int i = 0; i < size; i++) {
        delete[] data[i];  // Zwalnianie pamięci dla każdego wiersza
    }
    delete[] data;  // Zwalnianie pamięci dla tablicy wskaźników
}

void Matrix::printMatrix(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cout << data[i][j] << ' ';
        }
        cout<<'\n';
    }

}

int** Matrix::getMatrix(){
    return data;
}

void Matrix::copyMatrix(int** &other){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            other[i][j]=data[i][j];
        }
    }
}

int Matrix::getDistance(int i, int j) const {
    return data[i][j];
}

int Matrix::getSize() const{
    return size;
}