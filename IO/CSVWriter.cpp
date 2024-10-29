#include "CSVWriter.h"
#include <iostream>

CSVWriter::CSVWriter(std::string fileName, int dataSize, const double* times, const double* values)
        : fileName(fileName), dataSize(dataSize), times(times), values(values), stream(fileName) {
    if (!stream.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }
    writeData();
}

CSVWriter::~CSVWriter() {
    if (stream.is_open()) {
        stream.close();
    }
}

void CSVWriter::writeData() {
    // Zapisujemy nagłówki
    stream << "wielkosc,czas\n";

    // Zapisujemy dane
    for (int i = 0; i < dataSize; i++) {
        stream << values[i] << "," << times[i] << "\n";
    }
    stream.flush();
}