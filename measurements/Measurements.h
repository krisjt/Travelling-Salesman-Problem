//
// Created by Krystyna Nowak on 27/10/2024.
//

#ifndef PEA1_MEASUREMENTS_H
#define PEA1_MEASUREMENTS_H
#include <ctime>
#include "../IO/CSVWriter.h"
#include "../IO/FileReader.h"
#include "../algorithms/BranchAndBound.h"
#include "../algorithms/BruteForce.h"
#include "../algorithms/DynamicProgramming.h"
#include "../algorithms/BnB.h"
#include <string>

class Measurements {
private:
    int numRep;
    void calculateBnB();
    void calculateBF();
    void calculateDP();

public:
    explicit Measurements(int numRep);
    void calculate();
};
#endif //PEA1_MEASUREMENTS_H
