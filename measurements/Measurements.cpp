//
// Created by Krystyna Nowak on 27/10/2024.
//

#include "Measurements.h"

// Konstruktor inicjalizuje maksymalna wielkosc oraz liczbe powtorzen
Measurements::Measurements(int numRep, int maxSize) : numRep(numRep), maxSize(maxSize) {
}

// Destruktor
Measurements::~Measurements(){
}

// Metoda do zbierania danych / oblciznaia czasow
void Measurements::calculate() {

    CSVWriter bnbWriter("../data/results/BranchAndBound.csv");
    CSVWriter bfWriter("../data/results/BruteForce.csv");
    CSVWriter dpWriter("../data/results/DynamicProgramming.csv");

    for(int i = 14; i <= maxSize; i++) {
        cout << "Strating to calculate for size " << i <<" ..." <<endl;

        for(int j = 0; j < numRep; j++) {
            FileReader fileReader("../data/file.txt");
            fileReader.generateMatrix(i);
            Matrix matrix = fileReader.readFile();
            matrix.printMatrix();

//            BRANCH AND BOUND
//            BranchAndBound bnb(matrix);
//
//            clock_t start = clock();
//            bnb.start();
//            double time = (1000*static_cast<double>(clock() - start)) / CLOCKS_PER_SEC;
//
//            bnbWriter.writeData(time,i);
//
//            BRUTE FORCE
            BruteForce bf(matrix);

            clock_t  start = clock();
            bf.start();
            double time = (1000*static_cast<double>(clock() - start)) / CLOCKS_PER_SEC;
            bfWriter.writeData(time,i);

//
////            DYNAMIC PROGRAMMING
//            DynamicProgramming dp(matrix);
//            clock_t start = clock();
//            dp.start();
//            double time = (1000*static_cast<double>(clock() - start)) / CLOCKS_PER_SEC;
//            dpWriter.writeData(time,i);

//            matrix.printMatrix();
//            cout << endl;

        }
    }
}
