#include "CSVWriterACO.h"
#include <iostream>

// Konstruktor inicjalizujacy nazwe pliku, stream oraz sprawdzajacy czy sie otworzyl
CSVWriterACO::CSVWriterACO(std::string fileName)
        : fileName(fileName), stream(fileName, std::ios_base::app) {
    if (!stream.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }
}

// Destruktor zamykajacy strumien/plik
CSVWriterACO::~CSVWriterACO() {
    if (stream.is_open()) {
        stream.close();
    }
}

// Metoda do wpisywania błędów do pliku
void CSVWriterACO::writeErrorData(double size, double errorACO, double timeACO, double errorSA, double timeSA, double errorTS, double timeTS) {
    stream.seekp(0, std::ios::end);
    if (stream.tellp() == 0) {
        stream << "wielkość,mrowki,cas,wyzarzanie,cas,tabu,czas\n";
    }
    stream << size << ", " << errorACO << ", " << timeACO << ", " << errorSA << ", " << timeSA << ", " << errorTS << ", " << timeTS << endl;
    stream.flush();
}

// Metoda do wpisywania danych do pliku
void CSVWriterACO::writeData(double size, double time, double error, double tau, int numberOfAnts, int numberOfIterations,
                             double alpha, double beta, double rho) {
    stream.seekp(0, std::ios::end);
    if (stream.tellp() == 0) {
        stream << "wielkosc,czas,błąd,initialPher,liczbaMrowek,liczbaIteracji,wspolczynnikParowania,znaczenieFeromonu,znaczenieHeurystyki\n";
    }
       stream << size << ", " << time << ", " << error << ", " << tau << ", " << numberOfAnts << ", " << numberOfIterations << ", " << rho << ", " << alpha << ", " << beta << endl;
    stream.flush();
}

void CSVWriterACO::writeTimeData(double size, double time){
    stream.seekp(0, std::ios::end);
    if (stream.tellp() == 0) {
        stream << "wielkość,cas\n";
    }
    stream << size << ", " << time << endl;
    stream.flush();
}

void CSVWriterACO::writeTimeDataAll(double size, double timeACO, double avgTimeSA, double avgTimeTS, double avgTimeBNB, double avgTimeBF, double avgTimeDP){
    stream.seekp(0, std::ios::end);
    if (stream.tellp() == 0) {
        stream << "wielkość,mrowkowy,sa,dp,bf,ts,bnb\n";
    }
    stream << size << ", " << timeACO << ", " << avgTimeSA << ", " << avgTimeDP << ", " << avgTimeBF << ", " << avgTimeTS << ", " << avgTimeBNB << endl;
    stream.flush();
}

//int alpha, int beta, double rho