//
// Created by Krystyna Nowak on 04/12/2024.
//

#include "MeasurementsLocal.h"

MeasurementsLocal::MeasurementsLocal() {
}
MeasurementsLocal::~MeasurementsLocal(){
}

void MeasurementsLocal::simulatedAnnealingMeasurements() {

    FileReader fileReader("../data/br.txt");
    Matrix matrix = fileReader.readFile();
    matrix.printMatrix();

    CSVWriterLocal annealingWriter("../data/results/SimulatedAnnealingBR17.csv");

    SimulatedAnnealing simA(matrix);

    double coolingRate;
    int iteNum;


    double coolingRateArr[] = {0.8, 0.9, 0.99};
    int iteNumArr[] = {3000, 4000, 5000};

    for (int i = 0; i < 10; i++) {
        for (int k = 0; k < 3; k++) {
            iteNum = iteNumArr[k];
            for (int l = 0; l < 3; l++) {
                coolingRate = coolingRateArr[l];
                cout << i + 1 << ". Starting to calcualte for cooling rate = " << coolingRate
                     << ", iteration number " << iteNum << endl;

                clock_t start = clock();
                simA.start(iteNum, coolingRate);
                double time = (1000 * static_cast<double>(clock() - start)) / CLOCKS_PER_SEC;

                int cost = simA.getCost();

                cout << "Time = " << time << " and cost = " << cost << endl;

                annealingWriter.writeDataAnnealing(time, cost, iteNum, coolingRate);
            }
        }
    }
}

void MeasurementsLocal::bothAlgorithms(int numRep){
        int size = 50;
        for (int i = 0; i <= 10 ; i++) {
            CSVWriter annealingWriter("../data/results/SimulatedAnnealingMerge.csv");
            CSVWriter tabuWriter("../data/results/TabuSearchMerge.csv");
            double avgSW = 0;
            double avgTS = 0;
            for(int j = 0; j < 25; j++) {
                FileReader fileReader("../data/file.txt");
                fileReader.generateMatrix(size);
                Matrix matrix = fileReader.readFile();
                matrix.printMatrix();


                SimulatedAnnealing simA(matrix);

                TabuSearch tabS(matrix);

                cout << "Calculating " << j << ". waiting for next..." << endl;
            clock_t start = clock();
            tabS.start(1000, 20, 0);
            double timeTS = (1000 * static_cast<double>(clock() - start)) / CLOCKS_PER_SEC;

                clock_t start2 = clock();
                simA.start(5000, 0.9);
                double timeSW = (1000 * static_cast<double>(clock() - start2)) / CLOCKS_PER_SEC;
                 avgSW += timeSW;
                 avgTS += timeTS;
            }
            double time1 = avgTS/25;
            double time2 = avgSW/25;

            tabuWriter.writeData(time1, size);
            annealingWriter.writeData(time2, size);

            size += 50;
        }
    }

void MeasurementsLocal::tabuSearchMeasurements(){

    FileReader fileReader("../data/plik170.txt");
    Matrix matrix = fileReader.readFile();
    matrix.printMatrix();

    CSVWriterLocal tabuWriter("../data/results/TabuSearch170.csv");

    TabuSearch tabS(matrix);
    int moveType = 0;
    int tabuSize = 30;
    int iteNum = 2000;

        int moveTypeArr[] = {0,1};
        int iteNumArr[] = {1000,2000,3000};
        int tabuSizeArr[] = {10,20, 30};
        for (int i = 0; i < 10; i ++){
            for(int j = 0; j < 2; j++){
                moveType = moveTypeArr[j];
                for(int k = 0; k < 3; k++){
                    iteNum = iteNumArr[k];
                    for(int l = 0; l < 3; l ++){
                        tabuSize = tabuSizeArr[l];
                        cout << i+1 << ". Starting to calcualte for tabu size = " << tabuSize
                             << ", iteration number " << iteNum << " move type "<< moveType << endl;

                        clock_t  start = clock();
                        tabS.start(iteNum,tabuSize,moveType);
                        double time = (1000*static_cast<double>(clock() - start)) / CLOCKS_PER_SEC;

                        int cost = tabS.getCost();

                        cout << "Time = " << time << " and cost = " << cost << endl;

                        tabuWriter.writeDataTabu(time,cost,iteNum,moveType,tabuSize);
                    }
                }
            }
        }
}
