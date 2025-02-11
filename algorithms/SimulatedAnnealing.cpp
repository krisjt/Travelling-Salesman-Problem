//
// Created by Krystyna Nowak on 02/12/2024.
//

#include "SimulatedAnnealing.h"
#include <cmath>
#include <ctime>

SimulatedAnnealing::SimulatedAnnealing(Matrix &inputMatrix)
        : matrix(inputMatrix),
          rng(std::time(nullptr)),
          distribution(0.0, 1.0),
          size(inputMatrix.getSize()) {
    path = new int[size];
    for (int i = 0; i < size; ++i) {
        path[i] = i;
    }
    initSolution();
}

SimulatedAnnealing::~SimulatedAnnealing() {
    delete[] path;
}

//funcja do wyliczania kosztu trasy
int SimulatedAnnealing::calculateCost() {
    int totalCost = 0;
    for (int i = 0; i < size - 1; ++i) {
        totalCost += matrix.getDistance(path[i], path[i + 1]);
    }
    totalCost += matrix.getDistance(path[size - 1], path[0]);
    return totalCost;
}

//tworzenie sasiada poprzez zamiane miejscami dwoch losowych miast
void SimulatedAnnealing::generateNeighbor() {
    std::uniform_int_distribution<int> indexDist(0, size - 1);
    int i = indexDist(rng);
    int j = indexDist(rng);
    std::swap(path[i], path[j]);
}

//wyznaczanie temperatury maksymalnej ze wzoru maksymalny koszt * wielkosc problemu * 10
double SimulatedAnnealing::calculateInitialTemperature() {
    double maxCost = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix.getDistance(i, j) > maxCost) {
                maxCost = matrix.getDistance(i, j);
            }
        }
    }
    return maxCost * size * 10;
}

//tworzenie poczatkowego rozwiazania
void SimulatedAnnealing::initSolution() {
    bool *visited = new bool[size];
    for (int i = 0; i < size; ++i) {
        visited[i] = false;
    }

    int currentCity = 0;
    path[0] = currentCity;
    visited[currentCity] = true;

    for (int step = 1; step < size; ++step) {
        int nearestCity = -1;
        int shortestDistance = INT_MAX;

        for (int i = 0; i < size; ++i) {
            if (!visited[i] && matrix.getDistance(currentCity, i) < shortestDistance) {
                nearestCity = i;
                shortestDistance = matrix.getDistance(currentCity, i);
            }
        }

        currentCity = nearestCity;
        path[step] = currentCity;
        visited[currentCity] = true;
    }

    delete[] visited;
}


// start algorytmu
void SimulatedAnnealing::start(int maxIterations, double coolingRate, double initialTemperature) {
    //sprawdzenie czy uzytkownik przekazal maksymalna temperature i jej ustawienie
    if (initialTemperature < 0) {
        initialTemperature = calculateInitialTemperature();
    }

    //ustawienie temperatury granicznej
//    double minTemperature = initialTemperature/100000;
    double minTemperature = initialTemperature/(100*maxIterations);

    //tablica do przechowywania najlepszej znalezionej sciezki
    int *bestPath = new int[size];
    for (int i = 0; i < size; ++i) {
        bestPath[i] = path[i];
    }
    int bestCost = calculateCost();
    int currentCost = bestCost;

    double temperature = initialTemperature;

    //petla temperatury
    while(temperature>minTemperature) {
        //petla iteracji na temperature
        for (int iteration = 0; iteration < maxIterations; iteration++) {

            //sprawdzenie czy temperatura przekroczyla minimalna
            if (temperature < minTemperature) {
                break;
            }

            //tworzenie aktualnej sciezki jako kopia globalnej
            int *currentPath = new int[size];
            for (int i = 0; i < size; ++i) {
                currentPath[i] = path[i];
            }

            //tworzenie sasiedztwa w globalnej sciezce
            generateNeighbor();
            int neighborCost = calculateCost();

            //obliczanie roznicy kosztow
            double costDifference = neighborCost - currentCost;

            //jesli koszt lepszy od najlepszego lub wylosujemy liczbe mniejsza od prawdopodobienstwa
            // to ustawiamy aktualnie najlepszy kosszt
            if (costDifference < 0 || distribution(rng) < std::exp(-costDifference / temperature)) {
                currentCost = neighborCost;
            } else {
                //w przeciwnym wypadku przywracamy sciezke do pierwotnej postaci
                for (int i = 0; i < size; ++i) {
                    path[i] = currentPath[i];
                }
            }

            //jesli aktualny koszt jest lepszy od najlepszego to ustawiamy najlepszy
            if (currentCost < bestCost) {
                bestCost = currentCost;
                for (int i = 0; i < size; ++i) {
                    bestPath[i] = path[i];
                }
            }

            delete[] currentPath;
        }
        //zmniejszamy temperature
        temperature *= coolingRate;
    }
    //ustawienie wyniku
    optimalCost = bestCost;
    for (int i = 0; i < size; ++i) {
        path[i] = bestPath[i];
    }

    delete[] bestPath;
}

int SimulatedAnnealing::getCost() {
    return optimalCost;
}
int* SimulatedAnnealing::getPath() {
    return path;
}

void SimulatedAnnealing::printResult() {
    std::cout << "\n-----------------------------------------\n"
              << "SIMULATED ANNEALING\n"
              << "-----------------------------------------\n"
              << "Results of simulated annealing algorithm.\n"
              << "Shortest path is:\n";

    for (int i = 0; i < size; ++i) {
        std::cout << path[i] << (i != size - 1 ? " - " : "");
    }
    std::cout << "\nIts length equals " << optimalCost << ".\n"
              << "\n-----------------------------------------\n"
              << "-----------------------------------------\n";
}
