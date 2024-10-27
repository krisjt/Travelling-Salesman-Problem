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
    int* bruteForce();
    void printResult();
private:
    int* shortestPath;

    int minWeight = INT_MAX;

    //number of cities/size of matrix
    int size;

    //adjacency matrix
    int** matrix;

    //method that finds one permutation
    bool findNextPermutation(int* data, int size);

    //method that reverts an array from the specified points
    static int* reverseArr(int* data, int left, int right);

};


#endif //PEA1_BRUTEFORCE_H
