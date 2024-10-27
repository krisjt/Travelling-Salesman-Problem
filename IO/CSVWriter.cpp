////
//// Created by Wladyslaw Nowak on 15.04.2021.
////
//
// Created by Wladyslaw Nowak on 15.04.2021.
//

#include "CSVWriter.h"
#include <string>
#include <fstream>
#include <iostream>

CSVWriter::CSVWriter(std::string fileName, int dataSize, double* time, double* values)
        : fileName(fileName), dataSize(dataSize), time(time), values(values), stream(fileName) {
    if (!stream.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }
    writeData();
}

void CSVWriter::writeData() {
    // Zapisujemy nagłówki
    stream << "czas,wielkość" << std::endl;

    // Zapisujemy dane
    for (int i = 0; i < dataSize; i++) {
        stream << time[i] << "," << values[i] << std::endl;
    }
}

//
//#include "CSVWriter.h"
//
//CSVWriter::CSVWriter(string fileName, int dataSize, int columnWidth,
//                     string* headers, double** data) :fileName(fileName), dataSize(dataSize),
//                                                    columnWidth(columnWidth), headers(headers), data(data), stream(fileName) {
//    writeData();
//}
//
//void CSVWriter::writeData() {
//    for (int i = 0; i < columnWidth; i++){
//        stream<<headers[i];
//        if (i+1 < columnWidth) stream<<",";
//    }
//    stream<<endl;
//    for (int i = 0; i < dataSize; i++){
//        for (int j = 0; j < columnWidth; j++){
//            stream<<data[j][i];
//            if (j+1 < columnWidth) stream<<",";
//        }
//        stream<<endl;
//    }
//}
