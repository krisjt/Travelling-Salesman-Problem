////
//// Created by Krystyna Nowak on 27/10/2024.
////
//
#include "Measurements.h"

Measurements::Measurements(int numRep) : numRep(numRep) {}

//void Measurements::calculateBnB() {
//    const int size = 5;
//    double* sizeBnB = new double[numRep];
//    double* timesBnB = new double[numRep];
//
//    FileReader fileReader("/Users/krystynanowak/Desktop/PEA1/br.txt");
//    Matrix matrix = fileReader.readFile();
//    matrix.printMatrix();
//
//    BranchAndBound bnb(matrix);
//
//    for(int i = 0; i < numRep; i++) {
//        clock_t start = clock();
//        bnb.start();
//        double timeBnB = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
//
//        timesBnB[i] = timeBnB;
//        sizeBnB[i] = size;
//
//        std::cout << "BnB" << std::endl;
//        std::cout << timeBnB << std::endl;
//    }
//
//    CSVWriter bnbWriter("/Users/krystynanowak/Desktop/PEA1/BranchAndBound.csv", numRep, timesBnB, sizeBnB);
//
//    delete[] timesBnB;
//    delete[] sizeBnB;
//}
//Measurements::Measurements(int numRep) : numRep(numRep) {}

void Measurements::calculateBnB() {
    const int size = 5;
    double* sizeBnB = new double[numRep];
    double* timesBnB = new double[numRep];

    FileReader fileReader("/Users/krystynanowak/Desktop/PEA1/15.txt");
    Matrix matrix = fileReader.readFile();
    matrix.printMatrix();

    BnB bnb(matrix);

    for(int i = 0; i < numRep; i++) {
        clock_t start = clock();
        bnb.start();
        double timeBnB = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;

        timesBnB[i] = timeBnB;
        sizeBnB[i] = size;

        std::cout << "BnB" << std::endl;
        std::cout << timeBnB << std::endl;
    }

    CSVWriter bnbWriter("/Users/krystynanowak/Desktop/PEA1/BranchAndBound.csv", numRep, timesBnB, sizeBnB);

    delete[] timesBnB;
    delete[] sizeBnB;
}


void Measurements::calculateBF() {
    const int size = 5;
    double* sizeBF = new double[numRep];
    double* timesBF = new double[numRep];

    FileReader fileReader("/Users/krystynanowak/Desktop/PEA1/15.txt");
    Matrix matrix = fileReader.readFile();
    matrix.printMatrix();

    BruteForce bf(matrix);

    for(int i = 0; i < numRep; i++) {
        clock_t start = clock();
        bf.bruteForce();
        double timeBF = static_cast<double>(clock() - start)/ CLOCKS_PER_SEC;

        timesBF[i] = timeBF;
        sizeBF[i] = size;

        std::cout << "BF" << std::endl;
        std::cout << timeBF << std::endl;
    }

    CSVWriter bfWriter("/Users/krystynanowak/Desktop/PEA1/BruteForce.csv", numRep, timesBF, sizeBF);

    delete[] timesBF;
    delete[] sizeBF;
}

//
//void Measurements::calculateBF() {
//    const int size = 5;
//    double* sizeBF = new double[numRep];
//    double* timesBF = new double[numRep];
//
//    FileReader fileReader("/Users/krystynanowak/Desktop/PEA1/file.txt");
//    Matrix matrix = fileReader.readFile();
//    matrix.printMatrix();
//
//    BruteForce bf(matrix);
//
//    for(int i = 0; i < numRep; i++) {
//        // Use high-resolution clock for more precise measurements
//        auto start = std::chrono::high_resolution_clock::now();
//
//        // Force CPU to execute the code (prevent optimization)
//        volatile int* result = bf.bruteForce();
//
//        auto end = std::chrono::high_resolution_clock::now();
//
//        // Calculate duration in microseconds for better precision with small datasets
//        double timeBF = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;
//
//        timesBF[i] = timeBF;
//        sizeBF[i] = size;
//
//        std::cout << "BF Iteration " << i + 1 << std::endl;
//        std::cout << "Time (ms): " << std::fixed << std::setprecision(6) << timeBF << std::endl;
//
////        // Add a small delay between iterations to prevent CPU caching effects
////        std::this_thread::sleep_for(std::chrono::milliseconds(10));
//    }
//
//    // Calculate and display statistics
//    double avgTime = 0;
//    double minTime = timesBF[0];
//    double maxTime = timesBF[0];
//
//    for(int i = 0; i < numRep; i++) {
//        avgTime += timesBF[i];
//        minTime = std::min(minTime, timesBF[i]);
//        maxTime = std::max(maxTime, timesBF[i]);
//    }
//    avgTime /= numRep;
//
//    std::cout << "\nStatistics for " << numRep << " iterations:" << std::endl;
//    std::cout << "Average time: " << std::fixed << std::setprecision(6) << avgTime << " ms" << std::endl;
//    std::cout << "Min time: " << minTime << " ms" << std::endl;
//    std::cout << "Max time: " << maxTime << " ms" << std::endl;
//
//    CSVWriter bfWriter("/Users/krystynanowak/Desktop/PEA1/BruteForce.csv", numRep, timesBF, sizeBF);
//
//    delete[] timesBF;
//    delete[] sizeBF;
//}

void Measurements::calculateDP() {
    const int size = 5;
    double* sizeDP = new double[numRep];
    double* timesDP = new double[numRep];

    FileReader fileReader("/Users/krystynanowak/Desktop/PEA1/15.txt");
    Matrix matrix = fileReader.readFile();
    matrix.printMatrix();

    DynamicProgramming dp(matrix);

    for(int i = 0; i < numRep; i++) {
        clock_t start = clock();
        dp.start();
        double timeDP = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;

        timesDP[i] = timeDP;
        sizeDP[i] = size;

        std::cout << "DP" << std::endl;
        std::cout << timeDP << std::endl;
    }

    CSVWriter bfWriter("/Users/krystynanowak/Desktop/PEA1/DynamicProgramming.csv", numRep, timesDP, sizeDP);

    delete[] timesDP;
    delete[] sizeDP;
}
void Measurements::calculate() {
    cout << "Strating to calculate ...";
    calculateDP();
    cout << "after DP";
    calculateBnB();
    cout << "after BnB";
//    calculateBF();
//    cout << "after BF";
}