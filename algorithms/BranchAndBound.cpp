//
// Created by Krystyna Nowak on 27/10/2024.
//

#include "BranchAndBound.h"
#include <iostream>

BranchAndBound::BranchAndBound(Matrix& data) {
    this->size = data.getSize();

    // Inicjalizacja macierzy
    matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++) {
            matrix[i][j] = data.getDistance(i, j);
        }
    }

    // Inicjalizacja pozostałych elemntów
    bestPath = new int[size + 1];
    currentPath = new int[size + 1];
    visited = new bool[size];
    bestCost = INT_MAX;
}

BranchAndBound::~BranchAndBound() {
    // Zwolnienie pamieci macierzy
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    // Zwolnienie pamieci pozostalych tablic
    delete[] bestPath;
    delete[] currentPath;
    delete[] visited;
}

int BranchAndBound::calculateLowerBound(int pos, bool* visited) {
    int bound = 0;

    // Dodajemy minimalny koszt krawedzi dla kazdego nieodwiedzonego miasta
    for (int i = 0; i < size; i++) {
        if (!visited[i]) { // Sprawdzenie czy wierzcholek zostal odwiedzony
            int minEdge = INT_MAX;
            for (int j = 0; j < size; j++) {
                if (i != j && (!visited[j] || j == 0) && matrix[i][j] < minEdge) { // Spradzenie czy wierzcholek nie wraca sam do siebie
                    minEdge = matrix[i][j];                                         //, (czy nieodwiedzony lub czy nie jest zerowy)
                }                                                                   // czy waga jest mniejsza niz najmniejsza
            }
            if (minEdge != INT_MAX) {
                bound += minEdge;
            }
        }
    }

    // Dodaj koszt z aktualnej pozycji do najblizszego nieodwiedzonego miasta
    if (pos != -1) {
        int minEdge = INT_MAX;
        for (int i = 0; i < size; i++) {
            if (!visited[i] && matrix[pos][i] < minEdge) {
                minEdge = matrix[pos][i];
            }
        }
        if (minEdge != INT_MAX) {
            bound += minEdge;
        }
    }
    return bound;
}

void BranchAndBound::tsp(int pos, int count, int currentCost) {
    // Jesli wszytskie miasta zostaly odwiedzone dodajemy koszt powrotu
    if (count == size) {
        int totalCost = currentCost + matrix[pos][0];
        if (totalCost < bestCost) {
            bestCost = totalCost;
            for (int i = 0; i < size; i++) {
                bestPath[i] = currentPath[i];
            }
            bestPath[size] = 0;
        }
        return;
    }

    // Wyznaczamy dolna granice dla aktualnego stanu
    int bound = currentCost + calculateLowerBound(pos, visited);
    if (bound >= bestCost) {
        return; // Odcinamy gałąź
    }

    // Odwiedzamy wszytskie nieodwiedzone miasta
    for (int i = 0; i < size; i++) {
        if (!visited[i]) {
            visited[i] = true;
            currentPath[count] = i;

            // Wywolanie rekurencyjne
            tsp(i, count + 1,
                   currentCost + (pos == -1 ? 0 : matrix[pos][i]));

            visited[i] = false;
        }
    }
}

void BranchAndBound::start() {
    // Inicjalizacja tablic
    for (int i = 0; i < size; i++) {
        visited[i] = false;
        currentPath[i] = -1;
        bestPath[i] = -1;
    }
    bestPath[size] = -1;
    currentPath[size] = -1;

    // Ustawiamy miasto startowe jako odwiedzone i aktualizujemy trase
    visited[0] = true;
    currentPath[0] = 0;

    // Rozpoczynamy rekurencyjne rozwiązywanie problemu
    tsp(0, 1, 0);
}

// Wypisanie rozwiązania
void BranchAndBound::printResult() {
    cout << "\n-----------------------------------------\n"
         << "BRANCH AND BOUND\n"
         << "-----------------------------------------\n"
         << "Results of branch and bound algorithm.\n"
         << "Shortest path is:\n";

    for (int i = 0; i < size; i++) {
        cout << bestPath[i] << (i != size - 1 ? " - " : "");
    }

    cout << "\nIts length equals " << bestCost << ".\n"
         << "-----------------------------------------\n"
         << "-----------------------------------------\n";
}