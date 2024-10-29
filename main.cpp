#include <iostream>
#include <time.h>
#include "structures/Matrix.h"
#include "IO/FileReader.h"
#include "algorithms/BruteForce.h"
#include "algorithms/BranchAndBound.h"
#include "algorithms/DynamicProgramming.h"
#include "measurements/Measurements.h"


int main() {
//    FileReader fileReader("/Users/krystynanowak/Desktop/PEA1/file.txt");
//    Matrix matrix = fileReader.readFile();
//    matrix.printMatrix();
//
//    cout<<"\nSize of matrix: " << matrix.getSize() << "\n";
//
//    cout << "Dynamic Programming: " << endl;
//    DynamicProgramming dp(matrix);
//    dp.start();
//
//    cout << "B&B" << endl;
//    BranchAndBound bb(matrix);
//    bb.start();
//
//    cout << "Brute Force" << endl;
//    BruteForce brute(matrix);
//    int* path = brute.bruteForce();
//    for(int i = 0; i < matrix.getSize(); i++){
//        cout << path[i];
//    }

    Measurements mes(1);
    mes.calculate();
    return 0;
}

