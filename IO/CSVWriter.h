//
// Created by Wladyslaw Nowak on 15.04.2021.
//

#ifndef SDIZO2_CSVWRITER_H
#define SDIZO2_CSVWRITER_H

#include <fstream>

using namespace std;

/**
 * Simple class that writes data to csv file. <br/>
 * This class is copy of class I created in previous project.
 */
class CSVWriter {
private:
    std::string fileName;
    int dataSize;
    const double* times;
    const double* values;
    std::ofstream stream;

    void writeData();

public:
    CSVWriter(std::string fileName, int dataSize, const double* times, const double* values);
    ~CSVWriter();
};


#endif //SDIZO2_CSVWRITER_H
