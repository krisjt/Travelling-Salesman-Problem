//
// Created by Krystyna Nowak on 25/10/2024.
//

#ifndef PEA1_DYNAMICPROGRAMMING_H
#define PEA1_DYNAMICPROGRAMMING_H

#include "../structures/Matrix.h"

class DynamicProgramming {
public:
    // konstruktor
    explicit DynamicProgramming(Matrix& matrix);

    // destruktor
    ~DynamicProgramming();

    // metoda rozpoczynajaca dzialanie algorytmu
    void start();

    // metoda do wypisywania wynikow
    void printResult();

    int getCost();


private:
    // macierz sasiedztwa
    int** matrix;

    // macierz kosztow
    int** dp;

    // sciezka
    int* path;

    // ilosc miast
    int size;

    // koszt optymalny
    int optimalCost;

    // maska odwiedzonych miast
    int allVisited;

    // metoda do szukania najmneijszych kosztow
    int tsp(int mask, int pos);

    // metoda do rekonstrukcji najkrotszej sciezki
    void reconstructPath(int mask, int pos, int currentIndex);

};

#endif //PEA1_DYNAMICPROGRAMMING_H
