//
// Created by Krystyna Nowak on 02/12/2024.
//

//#endif //PEA1_SIMULATEDANNEALING_H
#ifndef PEA1_SIMULATEDANNEALING_H
#define PEA1_SIMULATEDANNEALING_H

#include "../structures/Matrix.h"
#include <random>
#include <iostream>
#include <cmath>
#include <ctime>

class SimulatedAnnealing {
private:
    //macierz kosztow
    Matrix &matrix;
    //generator
    std::mt19937 rng;
    std::uniform_real_distribution<double> distribution;
    //wielkosc problemu
    int size;
    //sciezka
    int *path;
    //optymalny koszt
    int optimalCost;

    int calculateCost();
    void generateNeighbor();
    double calculateInitialTemperature();

public:
    SimulatedAnnealing(Matrix &inputMatrix);
    ~SimulatedAnnealing();

    void start(int maxIterations, double coolingRate, double initialTemperature = -1);
    int getCost();
    void printResult();

    void initSolution();

    int *getPath();
};

#endif //PEA1_SIMULATEDANNEALING_H
