//
// Created by Krystyna Nowak on 09/10/2024.
//

#include "FileReader.h"
#include <random>

// Konstruktor inicjalizujacy nazwe pliku, otwierajacy input
FileReader::FileReader(string filename) {
    this->filename = filename;
    input.open(filename);

    if (!input.is_open()) {
        throw runtime_error("Could not read the file");
    }
}

// metoda do odczytywania jednej wartosci z pliku
int FileReader::readOneValue() {
    int nextVal;
    while (input.is_open()) {
//        char c;
//        input >> std::ws; // Pomija biale znaki (np. spacje, tabulatory)
//        c = input.peek(); // Podejrzyj kolejny znak
//        if (c == EOF) {
//            input.close();
//            throw runtime_error("End of file reached");
//        }
//        if (std::isspace(c)) {
//            input.get(); // Pobierz znak, aby go pominac
//            continue; // Przejdz do kolejnej iteracji
//        }
        input >> nextVal;
        if (input.fail()) {
            throw runtime_error("File error - stopping program");
        }
        return nextVal;
    }
    throw runtime_error("File error - stopping program");
}

// metoda do odczytywania wartosci z pliku
Matrix FileReader::readFile(){
    int size = readOneValue();
    int** matrix = new int*[size];
    for(int i = 0; i < size; i++){
        matrix[i] = new int[size];
        for(int j = 0; j < size; j++) {
            if(i!=j)matrix[i][j] = readOneValue();
            else{
                matrix[i][j] = -1;
                readOneValue();
            }
        }
    }
    return Matrix(matrix, size);;
}

// metoda do generacji macierzy i wpisywania do pliku
void FileReader::generateMatrix(int size){
    int** matrix = new int*[size];
    std::random_device rd; // Źródło entropii
    std::mt19937 gen(rd()); // Generator Mersenne Twister zainicjalizowany entropią
    std::uniform_int_distribution<> dis(1, 50); // Rozkład dla liczb od 1 do 50

    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++) {
            if (i != j) {
                matrix[i][j] = dis(gen); // Losowa liczba z rozkładu
            } else {
                matrix[i][j] = -1; // Wartość na przekątnej
            }
        }
    }

    std::ofstream stream(filename);
    if (!stream.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
        stream << size << endl;

        for (int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                stream << matrix[i][j] << " ";
            }
            stream << endl;
        }
        stream.flush();
}