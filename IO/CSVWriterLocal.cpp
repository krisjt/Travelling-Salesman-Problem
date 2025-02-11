//
// Created by Krystyna Nowak on 04/12/2024.
//

#include "CSVWriterLocal.h"

// konstruktor inicjalizujacy nazwę pliku, stream oraz sprawdzający, czy się otworzył
CSVWriterLocal::CSVWriterLocal(std::string fileName)
        : fileName(fileName), stream(fileName, std::ios_base::app) {
    if (!stream.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }
}

// destruktor zamykający strumień
CSVWriterLocal::~CSVWriterLocal() {
    if (stream.is_open()) {
        stream.close();
    }
}

// metoda do wpisywania danych do pliku symulowanego wyrzażania
void CSVWriterLocal::writeDataAnnealing(double time, int result, int iteNum, double coolingRate) {
    stream.seekp(0, std::ios::end);
    if (stream.tellp() == 0) {
        stream << "time,result,iteNum,coolingRate\n";
    }
    stream << time << ", " << result << ", " << iteNum << ", " << coolingRate << endl;
    stream.flush();
}

void CSVWriterLocal::writeDataTabu(double time, int result, int iteNum, int moveType, int tabuSize) {
    stream.seekp(0, std::ios::end);
    if (stream.tellp() == 0) {
        stream << "time,result,iteNum,moveType,tabuSize\n";
    }
    stream << time << ", " << result << ", " << iteNum << ", " << moveType << ", " << tabuSize << endl;
    stream.flush();
}
