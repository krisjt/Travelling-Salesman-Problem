//
// Created by Krystyna Nowak on 04/12/2024.
//

#ifndef PEA1_MEASUREMENTSLOCAL_H
#define PEA1_MEASUREMENTSLOCAL_H

#include <ctime>
#include "../IO/CSVWriterLocal.h"
#include "../IO/CSVWriter.h"
#include "../IO/FileReader.h"
#include "../algorithms/BruteForce.h"
#include "../algorithms/TabuSearch.h"
#include "../algorithms/SimulatedAnnealing.h"
#include "../algorithms/BranchAndBound.h"
#include <string>

class MeasurementsLocal {
private:
    int numRep;
    int maxSize;

public:
    void simulatedAnnealingMeasurements();
    MeasurementsLocal();
    ~MeasurementsLocal();
    void tabuSearchMeasurements();
    void bothAlgorithms(int numRep);
    void error();
};

#endif //PEA1_MEASUREMENTSLOCAL_H
