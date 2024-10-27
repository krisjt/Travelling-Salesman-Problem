//
// Created by Krystyna Nowak on 25/10/2024.
//

#ifndef PEA1_DYNAMICPROGRAMMING_H
#define PEA1_DYNAMICPROGRAMMING_H

#include "../structures/Matrix.h"

class DynamicProgramming {
public:
    explicit DynamicProgramming(Matrix& matrix);
    ~DynamicProgramming();
    void start();

private:
    int** matrix;
    int** dp;
    int* path;
    int size;
    int allVisited;

    int tsp(int mask, int pos);
    void reconstructPath(int mask, int pos, int currentIndex);
};

#endif //PEA1_DYNAMICPROGRAMMING_H
