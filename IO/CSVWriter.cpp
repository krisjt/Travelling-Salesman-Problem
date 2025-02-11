#include "CSVWriter.h"
#include <iostream>

// Konstruktor inicjalizujacy nazwe pliku, stream oraz sprawdzajacy czy sie otworzyl
CSVWriter::CSVWriter(std::string fileName)
        : fileName(fileName), stream(fileName, std::ios_base::app) {
    if (!stream.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }
}

// Destruktor zamykajacy strumien/plik
CSVWriter::~CSVWriter() {
    if (stream.is_open()) {
        stream.close();
    }
}

// Metoda do wpisywania danych do pliku
void CSVWriter::writeData(double time, double value) {
    stream.seekp(0, std::ios::end);
    if (stream.tellp() == 0) {
        stream << "wielkosc,czas\n";
    }
       stream << value << ", " << time << endl;
    stream.flush();
}
