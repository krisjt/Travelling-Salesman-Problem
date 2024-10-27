//
// Created by Krystyna Nowak on 14/10/2024.
//

#ifndef PEA1_BRANCHANDBOUND_H
#define PEA1_BRANCHANDBOUND_H

#include "../structures//Matrix.h"

class BranchAndBound {
public:
    explicit BranchAndBound(Matrix& matrix);
    ~BranchAndBound();
    //function to reduce rows and cols and calculate lower band
    void start();
private:
    int** matrix;
    int* bestPath;
    int bestCost = INT_MAX;
    int size;

    int matrixReduction(int **currentMatrix);

    void updateMatrix(int **currentMatrix, int row, int col);

    void
    tspBranchAndBound(int **currentMatrix, int currentBound, int currentCost, int level, bool *visited,
                      int *currentPath);
};

#endif //PEA1_BRANCHANDBOUND_H
