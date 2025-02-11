//
// Created by Krystyna Nowak on 29/12/2024.
//

#include "AntColonyOptimization.h"

AntColonyOptimization::AntColonyOptimization(Matrix &matrix, double tau) {
    this->size = matrix.getSize();
    this->tau = tau;

    this->matrix = new int *[size];
    this->tauOnEdge = new double *[size];

    for (int i = 0; i < size; i++) {
        this->matrix[i] = new int[size];
        this->tauOnEdge[i] = new double[size];
        for (int j = 0; j < size; j++) {
            this->matrix[i][j] = matrix.getDistance(i, j);
            this->tauOnEdge[i][j] = this->tau;
        }
    }

    bestPath = new int[size];
    bestCost = INT_MAX;
    visited = new bool [size];
}

AntColonyOptimization::~AntColonyOptimization() {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
        delete[] tauOnEdge[i];
    }
    delete[] matrix;
    delete[] tauOnEdge;
    delete[] bestPath;
    delete[] visited;
}


 void AntColonyOptimization::start(int numberOfAnts, int numberOfIterations, double alpha, double beta, double rho) {
    mt19937 mt(rand());
    uniform_real_distribution<double> dist(0.0, 1.0);
    uniform_int_distribution<int> cityDist(0, size - 1);
    this->rho = rho;

    //tablice dla przechowywania ścieżek i kosztów wszystkich mrówek
    int** antPaths = new int*[numberOfAnts];
    int* antCosts = new int[numberOfAnts];

    for(int i = 0; i < numberOfAnts; i++) {
        antPaths[i] = new int[size];
        antCosts[i] = 0;
    }

    for(int iteration = 0; iteration < numberOfIterations; iteration++) {

        for(int ant = 0; ant < numberOfAnts; ant++) {

            //ustawiamy wszytskie miasta na nieodwiedzone
            fill(visited, visited + size, false);

            //ustawianie miasta startowego
            int currentCity = cityDist(mt);
            visited[currentCity] = true;
            antPaths[ant][0] = currentCity;

            //konstruowanie ścieżki
            for(int step = 1; step < size; step++) {
                double* probability = new double[size];
                fill(probability, probability + size, 0.0);
                double totalProbability = 0.0;

                //obliczanie prawdopodobieństw dla wszystkich dostępnych miast
                for(int nextCity = 0; nextCity < size; nextCity++) {
                    if(!visited[nextCity] && matrix[currentCity][nextCity] != 0) {
                        double pheromone = pow(tauOnEdge[currentCity][nextCity], alpha);
                        double distance = pow(1.0 / matrix[currentCity][nextCity], beta);
                        probability[nextCity] = pheromone * distance;
                        totalProbability += probability[nextCity];
                    }
                }

                //wybór miasta
                int nextCity = -1;
                if(totalProbability > 0) {
                    double r = dist(mt) * totalProbability;
                    double sum = 0.0;

                    for(int city = 0; city < size; city++) {
                        if(!visited[city] && matrix[currentCity][city] != 0 && currentCity != city) {
                            sum += probability[city];
                            if(sum >= r) {
                                nextCity = city;
                                break;
                            }
                        }
                    }
                }

                //nie znaleziono miasta
                if(nextCity == -1) {
//                        int city2;
//                        do {
//                            city2 = cityDist(mt);
//                        }while(visited[city2]);
//
//                        nextCity = city2;
                    break;
                }

                delete[] probability;

                visited[nextCity] = true;
                antPaths[ant][step] = nextCity;
                antCosts[ant] += matrix[currentCity][nextCity];
                currentCity = nextCity;

            }

            //dodanie kosztu powrotu do miasta początkowego
            antCosts[ant] += matrix[currentCity][antPaths[ant][0]];

            //ustawienie najkrotszej sciezki
            if(antCosts[ant] < bestCost) {
                bestCost = antCosts[ant];
                for(int i = 0; i < size; i++) {
                    bestPath[i] = antPaths[ant][i];
                }
            }

            //dodanie feromonów
            for(int i = 0; i < size - 1; i++) {
                int city1 = antPaths[ant][i];
                int city2 = antPaths[ant][i + 1];
                tauOnEdge[city1][city2] += tau / antCosts[ant];
                tauOnEdge[city2][city1] += tau / antCosts[ant];
            }


            //dodanie feromonów na ścieżce powrotnej
            int lastCity = antPaths[ant][size - 1];
            int firstCity = antPaths[ant][0];
            tauOnEdge[lastCity][firstCity] += 1.0 / antCosts[ant];
            tauOnEdge[firstCity][lastCity] += 1.0 / antCosts[ant];

            //zerowanie tablicy kosztow
            antCosts[ant] = 0;
        }

        //aktualizacja feromonów
        updatePheromone();

    }

    //zwalnianie pamięci
    for(int i = 0; i < numberOfAnts; i++) {
        delete[] antPaths[i];
    }
    delete[] antPaths;
    delete[] antCosts;
}


void AntColonyOptimization::updatePheromone() {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            tauOnEdge[i][j] = (1 - rho) * tauOnEdge[i][j];
            if(tauOnEdge[i][j] < tau) {
                tauOnEdge[i][j] = tau;  //ustawienie minimalnej wartości feromonu
            }
        }
    }
}

int AntColonyOptimization::getCost(){
    return bestCost;
}

void AntColonyOptimization::printResult() {
    std::cout << "\n-----------------------------------------\n"
              << "ANT COLONY OPTIMIZATION ALGORITHM\n"
              << "-----------------------------------------\n"
              << "Results of ant colony optimization algorithm.\n"
              << "Shortest path is:\n";

    for (int i = 0; i < size; ++i) {
        std::cout << bestPath[i] << (i != size - 1 ? " - " : "");
    }
    std::cout << "\nIts length equals " << bestCost << ".\n"
              << "\n-----------------------------------------\n"
              << "-----------------------------------------\n";
}
