//
// Created by Krystyna Nowak on 27/10/2024.
//

#ifndef PEA1_MEASUREMENTS_H
#define PEA1_MEASUREMENTS_H
#include <ctime>
#include "../IO/CSVWriter.h"
#include "../IO/FileReader.h"
#include "../algorithms/BruteForce.h"
#include "../algorithms/DynamicProgramming.h"
#include "../algorithms/BranchAndBound.h"
#include <string>

class Measurements {
private:
    // liczba powtorzen badania
    int numRep;

    // maksymalna wielksoc macierzy
    int maxSize;

public:
    explicit Measurements(int numRep, int maxSize);
    void calculate();
    ~Measurements();
};
#endif //PEA1_MEASUREMENTS_H
