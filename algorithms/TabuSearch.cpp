// Created by Krystyna Nowak on 01/12/2024

#include "TabuSearch.h"

TabuSearch::TabuSearch(Matrix &data) {
    this->size = data.getSize();
//alokacja pamieci dla macierzy
    matrix = new int *[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++) {
            matrix[i][j] = data.getDistance(i, j);
        }
    }
//alokacja pamieci dla listy tabu
    tabuMatrix = new int*[size];
    for (int i = 0; i < size; i++) {
        tabuMatrix[i] = new int[size]();
        for (int j = 0; j < size; j++) {
            tabuMatrix[i][j] = 0;
        }
    }

    currentPath = new int[size];
    bestPath = new int[size];
}

TabuSearch::~TabuSearch() {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
        delete[] tabuMatrix[i];
    }
    delete[] matrix;
    delete[] tabuMatrix;
    delete[] currentPath;
    delete[] bestPath;
}

//tworzenie sciezki algorytmem zachlannym
void TabuSearch::initializeSolution() {
    //utworzenie listy do sprawdzania czy miasto zostalo odwiedzone, ustawienie miasta 0 jako poczatkowe
    currentPath[0] = 0;
    bool *visited = new bool[size]();
    visited[0] = true;

    //iteracja po miastach i
    for (int i = 1; i < size; i++) {
        int nearestCity = -1;
        int minDistance = INT_MAX;

        //iteracja po miastach j
        for (int j = 1; j < size; j++) {
            //jesli nie odwiedzono j to obliczamy dystans przejscia do niego
            if (!visited[j]) {
                int distance = matrix[currentPath[i - 1]][j];
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestCity = j;
                }
            }
        }
        //ustawienie najblizszego miasta do i
        currentPath[i] = nearestCity;
        visited[nearestCity] = true;
    }

    delete[] visited;
    currentCost = calculatePathCost(currentPath);
    bestCost = currentCost;
    memcpy(bestPath, currentPath, size * sizeof(int));
}

//wyznaczanie kosztu sciezki
int TabuSearch::calculatePathCost(int *path) {
    int totalCost = 0;
    for (int i = 0; i < size - 1; i++) {
        totalCost += matrix[path[i]][path[i + 1]];
    }
    totalCost += matrix[path[size - 1]][path[0]];
    return totalCost;
}

//odwrocenie segmentu
void TabuSearch::reverseSegment(int *path, int start, int end) {
    while (start < end) {
        int temp = path[start];
        path[start] = path[end];
        path[end] = temp;
        start++;
        end--;
    }
}

//void TabuSearch::swapBlocks(int *path, int start, int end) {
//    int blockSize = (end - start + 1) / 2;
//    for (int k = 0; k < blockSize; k++) {
//        int temp = path[start + k];
//        path[start + k] = path[start + blockSize + k];
//        path[start + blockSize + k] = temp;
//    }
//}

//zmniejszenie liczby iteracji przez ktore sasiedztwo bedzie tabu
void TabuSearch::decrementTabuTime() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (tabuMatrix[i][j] > 0) {
                tabuMatrix[i][j]--;
            }
        }
    }
}

//sprawdzenie czy miasto jest tabu i jego koszt jest gorszy od najlepszego
bool TabuSearch::isTabu(int i, int j, int cost) {
    return tabuMatrix[i][j] > 0 && cost >= bestCost;
}

void TabuSearch::performTabuSearch(int maxIterations, int tabuListSize, int neighborhoodType) {
    initializeSolution();

    //zmienna do przechowywania ilosci iteracji w stagnacji
    int stagnationCounter = 0;

    for (int iteration = 0; iteration < maxIterations; iteration++) {

        //best neighbor to najlepsze sasiedztwo
        int bestNeighborCost = INT_MAX;
        int *bestNeighbor = new int[size];
        int bestI = -1, bestJ = -1;

        //petla przez pary miast i, j
        for (int i = 1; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {

                //tworzenie kopii aktualnej sciezki, aby pracowac na niej bez modyfikacji sciezki
                int *neighborPath = new int[size];
                memcpy(neighborPath, currentPath, size * sizeof(int));

                //wybor rodzaju sasiedztwa i stworzenie go
                if (neighborhoodType == 0) {

                    //zamiana miejscami miast i,j
                    int temp = neighborPath[i];
                    neighborPath[i] = neighborPath[j];
                    neighborPath[j] = temp;
                } else if (neighborhoodType == 1) {

                    //odwrocenie segmentu miedzy i, j
                    reverseSegment(neighborPath, i, j);
                }
//                } else if (neighborhoodType == 2) {
//                    swapBlocks(neighborPath, i, j);
//                }

                //obliczenie kosztu przejscia po sciezce aktualnego sasiedztwa
                int neighborCost = calculatePathCost(neighborPath);

                //sprawdzenie czy aktualne miasta sa tabu oraz czy koszt sasiedztwa jest korzystny
                if (!isTabu(i, j, neighborCost) || neighborCost < bestCost) {
                    if (neighborCost < bestNeighborCost) {
                        //usatwienie wartosci najlepszego sasiedztwa
                        bestNeighborCost = neighborCost;
                        memcpy(bestNeighbor, neighborPath, size * sizeof(int));
                        bestI = i;
                        bestJ = j;
                    }
                }
                //usuniecie tablicy najlepszego sasiedztwa
                delete[] neighborPath;
            }
        }

        //wykonuje sie po przejrzeniu zestawow miast i, j
        if (bestI != -1 && bestJ != -1) {
            //zapisanie najlepszego odnlaezionego w iteracji sasiada jako aktualne rozwiazanie
            memcpy(currentPath, bestNeighbor, size * sizeof(int));
            currentCost = bestNeighborCost;

            //sprawdzenie czy najlepszy znaleziony sasiad jest tez najlepszym ogolnie znalezionym
            if (currentCost < bestCost) {
                bestCost = currentCost;
                memcpy(bestPath, currentPath, size * sizeof(int));
                //wyzerowanie licznika stagnacji
                stagnationCounter = 0;
            } else {
                //jesli nie znalezlismy rozwiazania inkrementujemy licznik stagnacji
                stagnationCounter++;
            }

            //zapisanie najlepszego znalezionego w iteracji sasiedztwa jako tabu
            tabuMatrix[bestI][bestJ] = tabuListSize;

        }
        //zmniejszenie liczby iteracji blokady
            decrementTabuTime();

        if (stagnationCounter > 50) {
            randomSolution();
//            initializeSolution();
            stagnationCounter = 0;
        }

        delete[] bestNeighbor;
    }
}

//stworzenie losowego rozwiazania
void TabuSearch::randomSolution() {

    for (int i = 0; i < size; i++) {
        currentPath[i] = i;
    }

    //tworzenie generatora liczb losowych
    std::random_device rd;
    std::mt19937 gen(rd());

    //dystrybucja do losowania liczb w zakresie [1, size-1]
    std::uniform_int_distribution<> dis(1, size - 1);


    //kazde miasto zamieniamy miejscem z losowym miastem
    for (int i = 1; i < size; i++) {
        int j = dis(gen);
        std::swap(currentPath[i], currentPath[j]);
    }
    currentCost = calculatePathCost(currentPath);
    bestCost = currentCost;
    memcpy(bestPath, currentPath, size * sizeof(int));
}

//start dzialania algorytmu
void TabuSearch::start(int maxIterations, int tabuListSize, int neighborhoodType) {
    performTabuSearch(maxIterations, tabuListSize, neighborhoodType);
}

//funkcja zwracajaca koszt
int TabuSearch::getCost() {
    return bestCost;
}

//funkcja zwracajaca sciezke
int* TabuSearch::getPath() {
    return bestPath;
}

//funkcja wypisujaca wynik
void TabuSearch::printResult() {
    std::cout << "\n-----------------------------------------\n"
              << "TABU SEARCH\n"
              << "-----------------------------------------\n"
              << "Results of Tabu Search algorithm.\n"
              << "Shortest path is:\n";

    for (int i = 0; i < size; i++) {
        std::cout << bestPath[i] << (i != size - 1 ? " - " : "");
    }
    std::cout << "\nIts length equals " << bestCost << ".\n"
              << "\n-----------------------------------------\n"
              << "-----------------------------------------\n";
}
