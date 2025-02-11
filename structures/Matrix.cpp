//
// Created by Krystyna Nowak on 09/10/2024.
//

#include "Matrix.h"

// Konstruktor
Matrix::Matrix(int** matrix, int size){
    this->size = size;
    this->data = matrix;
}

// Destruktor
Matrix::~Matrix() {
    for (int i = 0; i < size; i++) {
        delete[] data[i];  // Zwalnianie pamięci dla każdego wiersza
    }
    delete[] data;  // Zwalnianie pamięci dla tablicy wskaźników
}

// Metoda do wypisywania macierzy
void Matrix::printMatrix(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cout << data[i][j] << ' ';
        }
        cout<<'\n';
    }

}

// Metoda zwracajaca dane z maciezry
int** Matrix::getMatrix(){
    return data;
}

// Metoda kopiujaca macierz
void Matrix::copyMatrix(int** &other){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            other[i][j]=data[i][j];
        }
    }
}

// Metoda zwracajaca dlugosc krawedzi
int Matrix::getDistance(int i, int j) const {
    return data[i][j];
}

// Metoda zwracajaca wielkosc macierzy
int Matrix::getSize() const{
    return size;
}