//
// Created by Krystyna Nowak on 04/12/2024.
//

#ifndef PEA1_CSVWRITERLOCAL_H
#define PEA1_CSVWRITERLOCAL_H


#include <fstream>
#include <iostream>

using namespace std;

class CSVWriterLocal {
private:
    std::string fileName;
    std::ofstream stream;

public:
    CSVWriterLocal(std::string fileName);
    ~CSVWriterLocal();
    void writeDataAnnealing(double time, int result, int iteNum, double coolingRate);
    void writeDataTabu(double time, int result, int iteNum, int moveType, int tabuSize);
//    void writeData(double time, double value);
};




#endif //PEA1_CSVWRITERLOCAL_H
