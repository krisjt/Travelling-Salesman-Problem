//#include "BranchAndBound.h"
//
//BranchAndBound::BranchAndBound(Matrix& data) {
//    this->size = data.getSize();
//    bestCost = INT_MAX;
//    bestPath = new int[size + 1];
//
//    // Initialize matrix
//    matrix = new int*[size];
//    for (int i = 0; i < size; i++) {
//        matrix[i] = new int[size];
//        for (int j = 0; j < size; j++) {
//            matrix[i][j] = data.getDistance(i, j);
//        }
//    }
//}
//
//BranchAndBound::~BranchAndBound() {
//    for (int i = 0; i < size; i++) {
//        delete[] matrix[i];
//    }
//    delete[] matrix;
//    delete[] bestPath;
//}
//
//int BranchAndBound::matrixReduction(int** currentMatrix) {
//    int lowerBound = 0;
//
//    // Row reduction
//    for (int i = 0; i < size; i++) {
//        int minRow = INT_MAX;
//        for (int j = 0; j < size; j++) {
//            if (currentMatrix[i][j] != INT_MAX && currentMatrix[i][j] < minRow) {
//                minRow = currentMatrix[i][j];
//            }
//        }
//        if (minRow != INT_MAX && minRow > 0) {
//            for (int j = 0; j < size; j++) {
//                if (currentMatrix[i][j] != INT_MAX) {
//                    currentMatrix[i][j] -= minRow;
//                }
//            }
//            lowerBound += minRow;
//        }
//    }
//
//    // Column reduction
//    for (int j = 0; j < size; j++) {
//        int minCol = INT_MAX;
//        for (int i = 0; i < size; i++) {
//            if (currentMatrix[i][j] != INT_MAX && currentMatrix[i][j] < minCol) {
//                minCol = currentMatrix[i][j];
//            }
//        }
//        if (minCol != INT_MAX && minCol > 0) {
//            for (int i = 0; i < size; i++) {
//                if (currentMatrix[i][j] != INT_MAX) {
//                    currentMatrix[i][j] -= minCol;
//                }
//            }
//            lowerBound += minCol;
//        }
//    }
//
//    return lowerBound;
//}
//
//void BranchAndBound::updateMatrix(int** currentMatrix, int row, int col) {
//    // Set row and column to infinity instead of -1
//    for (int i = 0; i < size; i++) {
//        currentMatrix[row][i] = INT_MAX;
//        currentMatrix[i][col] = INT_MAX;
//    }
//    // Prevent returning to starting city except for the last move
//    if (col != 0) {
//        currentMatrix[col][0] = INT_MAX;
//    }
//}
//
//void BranchAndBound::tspBranchAndBound(int** currentMatrix, int currentBound, int currentCost,
//                                       int level, bool visited[], int currentPath[]) {
//    // Base case: if all cities are visited
//    if (level == size) {
//        // Check if we can return to the starting city
//        int returnCost = matrix[currentPath[level - 1]][currentPath[0]];
//        if (returnCost != INT_MAX) {
//            int totalCost = currentCost + returnCost;
//            if (totalCost < bestCost) {
//                bestCost = totalCost;
//                for (int i = 0; i < size; i++) {
//                    bestPath[i] = currentPath[i];
//                }
//                bestPath[size] = currentPath[0]; // Complete the circuit
//            }
//        }
//        return;
//    }
//
//    for (int i = 0; i < size; i++) {
//        if (!visited[i] && matrix[currentPath[level - 1]][i] != INT_MAX) {
//            int tempBound = currentBound;
//            int nextCost = currentCost + matrix[currentPath[level - 1]][i];
//
//            // Create new matrix for this branch
//            int** newMatrix = new int*[size];
//            for (int j = 0; j < size; j++) {
//                newMatrix[j] = new int[size];
//                for (int k = 0; k < size; k++) {
//                    newMatrix[j][k] = currentMatrix[j][k];
//                }
//            }
//
//            // Update matrix and calculate new bound
//            updateMatrix(newMatrix, currentPath[level - 1], i);
//            int reduction = matrixReduction(newMatrix);
//            int totalBound = nextCost + reduction;
//
//            // Only proceed if the lower bound is less than current best solution
//            if (totalBound < bestCost) {
//                currentPath[level] = i;
//                visited[i] = true;
//
//                tspBranchAndBound(newMatrix, reduction, nextCost, level + 1, visited, currentPath);
//
//                visited[i] = false;
//            }
//
//            // Cleanup
//            for (int j = 0; j < size; j++) {
//                delete[] newMatrix[j];
//            }
//            delete[] newMatrix;
//        }
//    }
//}
//
//void BranchAndBound::start() {
//    int* currentPath = new int[size + 1];
//    bool* visited = new bool[size];
//
//    // Initialize visited array
//    for (int i = 0; i < size; i++) {
//        visited[i] = false;
//    }
//
//    // Start from city 0
//    currentPath[0] = 0;
//    visited[0] = true;
//
//    // Create initial matrix
//    int** currentMatrix = new int*[size];
//    for (int i = 0; i < size; i++) {
//        currentMatrix[i] = new int[size];
//        for (int j = 0; j < size; j++) {
//            currentMatrix[i][j] = matrix[i][j];
//        }
//    }
//
//    // Calculate initial lower bound
//    int initialBound = matrixReduction(currentMatrix);
//
//    // Start branch and bound
//    tspBranchAndBound(currentMatrix, initialBound, 0, 1, visited, currentPath);
//
//    // Print results
//    std::cout << "Najlepszy koszt: " << bestCost << std::endl;
//    std::cout << "Najlepsza trasa: ";
//    for (int i = 0; i <= size; i++) {
//        std::cout << bestPath[i] << " ";
//    }
//    std::cout << std::endl;
//
//    // Cleanup
//    for (int i = 0; i < size; i++) {
//        delete[] currentMatrix[i];
//    }
//    delete[] currentMatrix;
//    delete[] currentPath;
//    delete[] visited;
//}

#include "BranchAndBound.h"

BranchAndBound::BranchAndBound(Matrix& data) {
    size = data.getSize();
    bestCost = INT_MAX;
    bestPath = new int[size + 1];
    matrix = new int*[size];

    // Zoptymalizowana inicjalizacja macierzy
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
        int* row = matrix[i];
        for (int j = 0; j < size; j++) {
            row[j] = data.getDistance(i, j);
        }
    }
}

BranchAndBound::~BranchAndBound() {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] bestPath;
}

int BranchAndBound::matrixReduction(int** currentMatrix) {
    int lowerBound = 0;
    int minRow, minCol;

    // Zoptymalizowana redukcja wierszy
    for (int i = 0; i < size; i++) {
        minRow = INT_MAX;
        int* row = currentMatrix[i];

        // Znajdź minimum w wierszu
        for (int j = 0; j < size; j++) {
            if (row[j] < minRow) minRow = row[j];
        }

        // Redukcja wiersza tylko jeśli znaleziono wartość mniejszą niż INT_MAX
        if (minRow < INT_MAX && minRow > 0) {
            for (int j = 0; j < size; j++) {
                if (row[j] != INT_MAX) row[j] -= minRow;
            }
            lowerBound += minRow;
        }
    }

    // Zoptymalizowana redukcja kolumn
    for (int j = 0; j < size; j++) {
        minCol = INT_MAX;

        // Znajdź minimum w kolumnie
        for (int i = 0; i < size; i++) {
            if (currentMatrix[i][j] < minCol) minCol = currentMatrix[i][j];
        }

        // Redukcja kolumny tylko jeśli znaleziono wartość mniejszą niż INT_MAX
        if (minCol < INT_MAX && minCol > 0) {
            for (int i = 0; i < size; i++) {
                if (currentMatrix[i][j] != INT_MAX) currentMatrix[i][j] -= minCol;
            }
            lowerBound += minCol;
        }
    }

    return lowerBound;
}

inline void BranchAndBound::updateMatrix(int** currentMatrix, int row, int col) {
    // Szybsza aktualizacja macierzy używając wskaźników
    int* rowPtr = currentMatrix[row];
    for (int i = 0; i < size; i++) {
        rowPtr[i] = INT_MAX;
        currentMatrix[i][col] = INT_MAX;
    }
    if (col != 0) currentMatrix[col][0] = INT_MAX;
}

void BranchAndBound::tspBranchAndBound(int** currentMatrix, int currentBound, int currentCost,
                                       int level, bool visited[], int currentPath[]) {
    if (level == size) {
        int returnCost = matrix[currentPath[level - 1]][0];
        if (returnCost != INT_MAX) {
            int totalCost = currentCost + returnCost;
            if (totalCost < bestCost) {
                bestCost = totalCost;
                // Użyj szybszego kopiowania pamięci
                for (int i = 0; i < size; i++) {
                    bestPath[i] = currentPath[i];
                }
                bestPath[size] = currentPath[0];
            }
        }
        return;
    }

    int prevCity = currentPath[level - 1];
    int* prevCityConnections = matrix[prevCity];

    for (int i = 0; i < size; i++) {
        if (!visited[i] && prevCityConnections[i] != INT_MAX) {
            int nextCost = currentCost + prevCityConnections[i];

            // Early pruning - przerwij jeśli przekroczono najlepszy koszt
            if (nextCost >= bestCost) continue;

            // Alokuj nową macierz tylko jeśli potrzebna
            int** newMatrix = new int*[size];
            for (int j = 0; j < size; j++) {
                newMatrix[j] = new int[size];
                // Użyj szybszego kopiowania pamięci
                for (int k = 0; k < size; k++) {
                    newMatrix[j][k] = currentMatrix[j][k];
                }
            }

            updateMatrix(newMatrix, prevCity, i);
            int reduction = matrixReduction(newMatrix);
            int totalBound = nextCost + reduction;

            if (totalBound < bestCost) {
                currentPath[level] = i;
                visited[i] = true;
                tspBranchAndBound(newMatrix, reduction, nextCost, level + 1, visited, currentPath);
                visited[i] = false;
            }

            // Zwolnij pamięć
            for (int j = 0; j < size; j++) {
                delete[] newMatrix[j];
            }
            delete[] newMatrix;
        }
    }
}

void BranchAndBound::start() {
    int* currentPath = new int[size + 1];
    bool* visited = new bool[size];

    // Zoptymalizowana inicjalizacja
    for (int i = 0; i < size; i++) {
        visited[i] = false;
    }

    currentPath[0] = 0;
    visited[0] = true;

    int** currentMatrix = new int*[size];
    for (int i = 0; i < size; i++) {
        currentMatrix[i] = new int[size];
        // Użyj szybszego kopiowania pamięci
        for (int j = 0; j < size; j++) {
            currentMatrix[i][j] = matrix[i][j];
        }
    }

    int initialBound = matrixReduction(currentMatrix);
    tspBranchAndBound(currentMatrix, initialBound, 0, 1, visited, currentPath);

    // Zwolnij pamięć
    for (int i = 0; i < size; i++) {
        delete[] currentMatrix[i];
    }
    delete[] currentMatrix;
    delete[] currentPath;
    delete[] visited;
}