//
// Created by Krystyna Nowak on 01/12/2024
//

#ifndef PEA1_TABUSEARCH_H
#define PEA1_TABUSEARCH_H

#include <iostream>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <random>
#include <ctime>
#include "../structures/Matrix.h"

//struct TabuStruct {
//    int i;
//    int j;
//    int tabuTime;
//    int cost;
//};

class TabuSearch {
private:
    //macierz sasiedztwa
    int **matrix;
    //aktualna sciezka
    int *currentPath;
    //najlepsza sciezka
    int *bestPath;
    //lista tabu
    int** tabuMatrix;
    //wielkosc problemu
    int size;
    //aktualny koszt
    int currentCost;
    //najlepszy koszt
    int bestCost;

    void initializeSolution();
    int calculatePathCost(int *path);
    void reverseSegment(int *path, int start, int end);
    void decrementTabuTime();
    bool isTabu(int i, int j, int cost);

public:
    TabuSearch(Matrix &data);
    ~TabuSearch();
    void performTabuSearch(int maxIterations, int tabuListSize, int neighborhoodType);
    void start(int maxIterations, int tabuListSize, int neighborhoodType);
    void printResult();

    int getCost();

    void randomSolution();

    int *getPath();
};

#endif //PEA1_TABUSEARCH_H