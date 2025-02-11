//
// Created by Krystyna Nowak on 03/01/2025.
//

#ifndef PEA1_MEASUREMENTSACO_H
#define PEA1_MEASUREMENTSACO_H

#include "../IO/CSVWriterACO.h"
#include "../structures/Matrix.h"
#include "../IO/FileReader.h"
#include "../algorithms/AntColonyOptimization.h"
#include "../algorithms/DynamicProgramming.h"
#include "../algorithms/BranchAndBound.h"
#include "../algorithms/BruteForce.h"
#include "../algorithms/DynamicProgramming.h"
#include "../algorithms/SimulatedAnnealing.h"
#include "../algorithms/TabuSearch.h"

class MeasurementsACO {
public:
    MeasurementsACO();
    ~MeasurementsACO();
    void calculate(int numberRepetitions);
    void error();
    void time();
    void timeAllAlgorithms();

private:
};


#endif //PEA1_MEASUREMENTSACO_H
