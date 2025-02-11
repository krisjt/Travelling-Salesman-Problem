//
// Created by Krystyna Nowak on 03/01/2025.
//

#include "MeasurementsACO.h"
#include <iostream>

MeasurementsACO::MeasurementsACO() {
}

MeasurementsACO::~MeasurementsACO(){
}

// Metoda do zbierania danych oblciznaia czasow
void MeasurementsACO::calculate(int numberRepetitions) {

    CSVWriterACO acoWriter("../data/results/AntColonyOptimizationMeasurements55.csv");

//    int accurateResult = 39;
//    int accurateResult = 1163; plik 358
//    int accurateResult = 2755;170
    int accurateResult = 1608;
    int size = 17;
    int numberIterations = 25;
    int numberOfAnts = 50;
    double tau = 1;
//    double rho = 0.3;

//    int numberOfAntsArray[] = {10,25, 50, 75, 100};

//    double tau = 0.1;
    double rho = 0.1;
    double alpha = 2;
    double beta = 10;

//    int sizeArray[] = {5,10,50,100,200,300,400,500,1000};
    double tauArray[] = {0.1, 0.5, 1.0, 5.0, 10.0};
//    double rhoArray[] = {0.1,0.3,0.5,0.7,0.9};
//    int iterationsArray[] = {10,25,50,75,100};
//    double alphaArray[] = {1,2,3, 5,7};
//    double betaArray[] = {1,3,5,7,10};

    FileReader fileReader("/Users/krystynanowak/Desktop/PEA1/plik55.txt");
    Matrix matrix = fileReader.readFile();

//        int size = 56;

        //int alpha, int beta
//        for(int numberOfAnts : numberOfAntsArray) {

            for (double tau : tauArray) {
//
//                for(double rho : rhoArray) {
//
//                            for(double alpha : alphaArray) {
//
//                                for(double beta : betaArray) {

//                                    for(int numberIterations : iterationsArray) {
                                        double totalError = 0;
                                        double totalTime = 0;

                                cout << "\n\nStrating to calculate for: \nsize = " << size <<"\n tau = " << tau << "\n rho = " << rho
                                << "\nnumber of iterations = " << numberIterations << "\nbeta = " << beta << "\nalpha = "
                                << alpha <<"...\n\n" <<endl;

                                for (int j = 0; j < numberRepetitions; j++) {

                                    AntColonyOptimization aco(matrix,tau);

                                    clock_t start = clock();

                                    aco.start(numberOfAnts,numberIterations,alpha,beta,rho);

                                    double time = (1000 * static_cast<double>(clock() - start)) / CLOCKS_PER_SEC;

                                    double error = abs((double) (accurateResult - aco.getCost()) / accurateResult);

                                    totalError+=error;
                                    totalTime+=time;

                                }
                                double avgTime = totalTime/numberRepetitions;
                                double avgError = 100*totalError/numberRepetitions;

                                acoWriter.writeData(size,avgTime,avgError,tau,numberOfAnts,numberIterations,alpha,beta,rho);
                            }
//                        }
//                    }
//                }
//            }
        }
//    }
//}


void MeasurementsACO::error(){

    for(int i = 5; i < 25; i++) {
        FileReader fileReader("../data/file.txt");
        CSVWriterACO csvWriterAco("../data/results/errorsACO.csv");
        fileReader.generateMatrix(i);
        Matrix matrix = fileReader.readFile();

        DynamicProgramming dp(matrix);

        dp.start();
        int actualCost = dp.getCost();

        double totalErrorACO = 0;
        double totalErrorSA = 0;
        double totalErrorTS = 0;
        double totalTimeACO = 0;
        double totalTimeSA = 0;
        double totalTimeTS = 0;
        for(int j = 0; j < 50; j++){
            AntColonyOptimization aco(matrix,1);
            SimulatedAnnealing sa(matrix);
            TabuSearch ts(matrix);

            clock_t startACO = clock();
            aco.start(25,25,2,10,0.1);
            double timeACO = (1000 * static_cast<double>(clock() - startACO)) / CLOCKS_PER_SEC;
            totalTimeACO+=timeACO;

            clock_t startSA = clock();
            sa.start(5000,0.9);
            double timeSA = (1000 * static_cast<double>(clock() - startSA)) / CLOCKS_PER_SEC;
            totalTimeSA+=timeSA;

            clock_t startTS = clock();
            ts.start(1000,20,0);
            double timeTS = (1000 * static_cast<double>(clock() - startTS)) / CLOCKS_PER_SEC;
            totalTimeTS+=timeTS;

            double errorACO = abs((double) (actualCost - aco.getCost()) / actualCost);
            totalErrorACO+=errorACO;

            double errorSA = abs((double) (actualCost - sa.getCost()) / actualCost);
            totalErrorSA+=errorSA;

            double errorTS = abs((double) (actualCost - ts.getCost()) / actualCost);
            totalErrorTS+=errorTS;
        }

        double avgErrorACO = 100*totalErrorACO/50;
        double avgErrorSA = 100*totalErrorSA/50;
        double avgErrorTS = 100*totalErrorTS/50;
        double avgTimeACO = totalTimeACO/50;
        double avgTimeSA = totalTimeSA/50;
        double avgTimeTS = totalTimeTS/50;

        csvWriterAco.writeErrorData(i,avgErrorACO,avgTimeACO,avgErrorSA,avgTimeSA,avgErrorTS,avgTimeTS);
    }
}

//time

void MeasurementsACO::time(){
    for(int i = 25; i < 500; i+=25){
        FileReader fileReader("../data/file.txt");
        CSVWriterACO csvWriterAco("../data/results/timeACO.csv");
        fileReader.generateMatrix(i);
        Matrix matrix = fileReader.readFile();

        double totalTimeACO = 0;
        AntColonyOptimization aco(matrix,1);
        for(int j = 0; j < 25; j++){
            clock_t startACO = clock();
            aco.start(25,25,2,10,0.1);
            double timeACO = (1000 * static_cast<double>(clock() - startACO)) / CLOCKS_PER_SEC;
            totalTimeACO+=timeACO;
        }
        double avgTimeACO = totalTimeACO/25;

        csvWriterAco.writeTimeData(i,avgTimeACO);
    }
}

void MeasurementsACO::timeAllAlgorithms(){
    for(int i = 5; i < 25; i+=1){
        cout << "Starting to calculate " << i << "..." << endl;
        FileReader fileReader("../data/file.txt");
        CSVWriterACO csvWriterAco("../data/results/timeAllAlgorithms.csv");
        fileReader.generateMatrix(i);
        Matrix matrix = fileReader.readFile();

        double totalTimeACO = 0;
        double totalTimeSA = 0;
        double totalTimeTS = 0;
        double totalTimeBNB = 0;
        double totalTimeBF = 0;
        double totalTimeDP = 0;
        AntColonyOptimization aco(matrix,1);
        SimulatedAnnealing sa(matrix);
        TabuSearch ts(matrix);
        BruteForce bf(matrix);
        BranchAndBound bnb(matrix);
        DynamicProgramming dp(matrix);

        for(int j = 0; j < 25; j++){
            clock_t startACO = clock();
            aco.start(25,25,2,10,0.1);
            double timeACO = (1000 * static_cast<double>(clock() - startACO)) / CLOCKS_PER_SEC;
            totalTimeACO+=timeACO;

            clock_t startBF = clock();
            bf.start();
            double timeBF = (1000 * static_cast<double>(clock() - startBF)) / CLOCKS_PER_SEC;
            totalTimeBF+=timeBF;

            clock_t startDP = clock();
            dp.start();
            double timeDP = (1000 * static_cast<double>(clock() - startDP)) / CLOCKS_PER_SEC;
            totalTimeDP+=timeDP;

            clock_t startBNB = clock();
            bnb.start();
            double timeBNB = (1000 * static_cast<double>(clock() - startBNB)) / CLOCKS_PER_SEC;
            totalTimeBNB+=timeBNB;

            clock_t startSA = clock();
            sa.start(3000,0.9);
            double timeSA = (1000 * static_cast<double>(clock() - startSA)) / CLOCKS_PER_SEC;
            totalTimeSA+=timeSA;

            clock_t startTS = clock();
            ts.start(1000,20,0);
            double timeTS = (1000 * static_cast<double>(clock() - startTS)) / CLOCKS_PER_SEC;
            totalTimeTS+=timeTS;
        }
        double avgTimeACO = totalTimeACO/25;
        double avgTimeTS = totalTimeTS/25;
        double avgTimeSA = totalTimeSA/25;
        double avgTimeBNB = totalTimeBNB/25;
        double avgTimeBF = totalTimeBF/25;
        double avgTimeDP = totalTimeDP/25;

        csvWriterAco.writeTimeDataAll(
                i,
                avgTimeACO,
                avgTimeSA,
                avgTimeTS,
                avgTimeBNB,
                avgTimeBF,
                avgTimeDP
        );
    }
}