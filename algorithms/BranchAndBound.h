//
// Created by Krystyna Nowak on 14/10/2024.
//

#ifndef PEA1_BRANCHANDBOUND_H
#define PEA1_BRANCHANDBOUND_H


class BranchAndBound {
public:
    BranchAndBound();
private:
    int** matrix;
};

//lower band: two nearest cities for each city, plus them together, divide by 2 and find ceiling
#endif //PEA1_BRANCHANDBOUND_H
