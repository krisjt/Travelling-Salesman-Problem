//
// Created by Krystyna Nowak on 09/10/2024.
//

#include "FileReader.h"

//ilosc miast
//nxn macierz (przekatna -1)
FileReader::FileReader(string filename) {
    input.open(filename);

    if (!input.is_open()) {
        throw runtime_error("Could not read the file");
    }
}

int FileReader::readOneValue() {
    int nextVal;
    if (input.is_open()) {
        input >> nextVal;
        if (input.fail()) {
            throw runtime_error("File error - stopping program");
        }
        if (input.eof()) {
            input.close();
        }
        return nextVal;
    }
    throw runtime_error("File not opened - maybe it was already closed?");
}

Matrix FileReader::readFile(){
    int size = readOneValue();
    int** matrix = new int*[size];
    for(int i = 0; i < size; i++){
        matrix[i] = new int[size];
        for(int j = 0; j < size; j++) {
            matrix[i][j] = readOneValue();
        }
    }
    return Matrix(matrix, size);;
}
