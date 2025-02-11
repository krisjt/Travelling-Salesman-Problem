//
// Created by Krystyna Nowak on 27/10/2024.
//

#ifndef PEA1_BRANCHANDBOUND_H
#define PEA1_BRANCHANDBOUND_H
#include "../structures/Matrix.h"

class BranchAndBound {
private:
    // wielkosc macierzy
    int size;

    // macierz
    int**matrix;

    // najlepsza sciezka
    int* bestPath;

    // aktualna sciezka
    int* currentPath;

    // tablica przechowujaca informacje o odwiedzonych miastach
    bool* visited;

    // najlepszy koszt
    int bestCost;

    // metoda do obliczania dolnego ograniczenia
    int calculateLowerBound(int pos, bool* visited);

    // metoda do znajdowania najkrotszej trasy
    void tsp(int pos, int count, int currentCost);
public:
    // konstruktor
    BranchAndBound(Matrix& data);

    // destruktor
    ~BranchAndBound();

    // metoda ktora rozpoczyna dzialanie algorytmu
    void start();

    // metoda do wypisywania wynikow
    void printResult();
};


#endif //PEA1_BRANCHANDBOUND_H
