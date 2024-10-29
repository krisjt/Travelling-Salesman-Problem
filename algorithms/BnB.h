//
// Created by Krystyna Nowak on 27/10/2024.
//

#ifndef PEA1_BNB_H
#define PEA1_BNB_H
#include "../structures/Matrix.h"

class BnB {
private:
    int size;
    int**matrix;
    int* bestPath;
    int* currentPath;
    bool* visited;
    int bestCost;
    int calculateLowerBound(int pos, bool* visited);
    void tspRec(int pos, int count, int currentCost);
public:
    BnB(Matrix& data);
    ~BnB();
    void start();
};


#endif //PEA1_BNB_H
