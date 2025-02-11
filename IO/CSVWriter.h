//
// Created by Wladyslaw Nowak on 15.04.2021.
//

#ifndef SDIZO2_CSVWRITER_H
#define SDIZO2_CSVWRITER_H

#include <fstream>

using namespace std;

class CSVWriter {
private:
    std::string fileName;
    std::ofstream stream;

public:
    CSVWriter(std::string fileName);
    ~CSVWriter();

    void writeData(double time, double value);
};


#endif //SDIZO2_CSVWRITER_H
