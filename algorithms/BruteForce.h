//
// Created by Krystyna Nowak on 09/10/2024.
//

#ifndef PEA1_BRUTEFORCE_H
#define PEA1_BRUTEFORCE_H

#include "../structures/Matrix.h"

class BruteForce {
public:
    explicit BruteForce(Matrix& matrix);
    ~BruteForce();
    void printRoutes();
    void start();
    void printCalculations();
private:
    //number of cities/size of matrix
    int size;

    //adjacency matrix
    int** matrix;

    //number of possible routes
    int numPermutations;

    //array of all possible routes
    int** routes;

    //method that creates all permutations for routes
    void getRoutes();

    //method that finds one permutation
    bool findNextPermutation(int* data, int size);

    //method that reverts an array from the specified points
    static int* reverseArr(int* data, int left, int right);

    //method that finds the shortest route
    void calculateRoutes();
};


#endif //PEA1_BRUTEFORCE_H
