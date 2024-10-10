//
// Created by Krystyna Nowak on 09/10/2024.
//

#ifndef PEA1_FILEREADER_H
#define PEA1_FILEREADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../structures/Matrix.h"

using namespace std;

class FileReader {
private:
    string filename;
    ifstream input;
    int readOneValue();

public:
    explicit FileReader(string filename);
    Matrix readFile();
};


#endif //PEA1_FILEREADER_H
