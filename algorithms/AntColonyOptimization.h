//
// Created by Krystyna Nowak on 29/12/2024.
//

#ifndef PEA1_ANTCOLONYOPTIMIZATION_H
#define PEA1_ANTCOLONYOPTIMIZATION_H

#include "../structures/Matrix.h"
#include <random>

class AntColonyOptimization {
public:
    AntColonyOptimization(Matrix &matrix, double tau);
    ~AntColonyOptimization();
    void start(int numberOfAnts, int numberOfIterations, double alpha, double beta, double rho);
    void printResult();
    int getCost();

private:
    int size;
    int** matrix;
    bool* visited;
    int* bestPath;
    int bestCost;
    double rho;
    double ** tauOnEdge;
    double tau;
    random_device rand;

    void updatePheromone();

};


#endif //PEA1_ANTCOLONYOPTIMIZATION_H
