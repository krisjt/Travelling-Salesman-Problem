#include <iostream>
#include "structures/Matrix.h"
#include "IO/FileReader.h"
#include "algorithms/BruteForce.h"

int main() {
    FileReader fileReader("/Users/krystynanowak/Desktop/PEA1/file.txt");
    Matrix matrix = fileReader.readFile();
    matrix.printMatrix();

    cout<<"\nSize of matrix: " << matrix.getSize() << "\n";

    BruteForce brute(matrix);

    brute.getRoutes();
    return 0;
}
