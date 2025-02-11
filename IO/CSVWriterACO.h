//
// Created by Wladyslaw Nowak on 15.04.2021.
//

#ifndef SDIZO2_CSVWRITER_H
#define SDIZO2_CSVWRITER_H

#include <fstream>

using namespace std;

class CSVWriterACO {
private:
    std::string fileName;
    std::ofstream stream;

public:
    CSVWriterACO(std::string fileName);
    ~CSVWriterACO();

    void writeErrorData(double size, double error);
    void writeData(double size, double time, double error, double tau, int numberOfAnts, int numberOfIterations,
                   double alpha, double beta, double rho);

    void writeErrorData(double size, double errorACO, double errorSA, double errorTS);

    void writeErrorData(double size, double errorACO, double timeACO, double errorSA, double timeSA, double errorTS,
                        double timeTS);

    void writeTimeData(double size, double time);
    void writeTimeDataAll(double size, double timeACO, double avgTimeSA, double avgTimeTS, double avgTimeBNB, double avgTimeBF, double avgTimeDP);
};


#endif //SDIZO2_CSVWRITER_H
