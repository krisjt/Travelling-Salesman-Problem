#include <iostream>
#include "structures/Matrix.h"
#include "IO/FileReader.h"
#include "algorithms/BruteForce.h"

int main() {
    FileReader fileReader("/Users/krystynanowak/Desktop/PEA1/file.txt");
    Matrix matrix = fileReader.readFile();
    matrix.printMatrix();

    cout<<"\nSize of matrix: " << matrix.getSize();

    cout << "Doing that.";
    BruteForce brute(matrix);
    cout << "Doing that.";

    brute.printRoutes();
    return 0;
}
