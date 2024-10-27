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
    /**
     * Name of file to be written.
     */
    const string fileName;

    /**
     * Amount of data points.
     */
    const int dataSize;

    /**
     * Amount of corresponding data every data point has.
     */
//    const int columnWidth;

    /**
     * 2D array of data.
     */
    double** data;

    /**
     * Column names.
     */
    string * headers;

    double* time;
    double* values;
    /**
     * File output stream.
     */
    ofstream stream;

    /**
     * Write data to file.
     */
    void writeData();
public:
    CSVWriter(std::string fileName, int dataSize, double* time, double* values);

};


#endif //SDIZO2_CSVWRITER_H
