//
// Created by Krystyna Nowak on 27/10/2024.
//

#include "BnB.h"
#include <iostream>

BnB::BnB(Matrix& data) {
    this->size = data.getSize();

    // Initialize matrix
    matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++) {
            matrix[i][j] = data.getDistance(i, j);
        }
    }

    // Initialize other members
    bestPath = new int[size + 1];
    currentPath = new int[size + 1];
    visited = new bool[size];
    bestCost = INT_MAX;
}

BnB::~BnB() {
    // Free matrix memory
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    // Free other arrays
    delete[] bestPath;
    delete[] currentPath;
    delete[] visited;
}

int BnB::calculateLowerBound(int pos, bool* visited) {
    int bound = 0;

    // Add minimum edge cost for each unvisited city
    for (int i = 0; i < size; i++) {
        if (!visited[i]) {
            int minEdge = INT_MAX;
            for (int j = 0; j < size; j++) {
                if (i != j && (!visited[j] || j == 0) && matrix[i][j] < minEdge) {
                    minEdge = matrix[i][j];
                }
            }
            if (minEdge != INT_MAX) {
                bound += minEdge;
            }
        }
    }

    // Add cost from current position to nearest unvisited city
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

void BnB::tspRec(int pos, int count, int currentCost) {
    // If all cities are visited
    if (count == size) {
        // Add cost of returning to starting city
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

    // Calculate lower bound for current state
    int bound = currentCost + calculateLowerBound(pos, visited);
    if (bound >= bestCost) {
        return; // Prune this branch
    }

    // Try visiting all unvisited cities
    for (int i = 0; i < size; i++) {
        if (!visited[i]) {
            visited[i] = true;
            currentPath[count] = i;

            // Recursive call with updated cost
            tspRec(i, count + 1,
                   currentCost + (pos == -1 ? 0 : matrix[pos][i]));

            visited[i] = false;
        }
    }
}

void BnB::start() {
    // Initialize arrays
    for (int i = 0; i < size; i++) {
        visited[i] = false;
        currentPath[i] = -1;
        bestPath[i] = -1;
    }
    bestPath[size] = -1;
    currentPath[size] = -1;

    // Mark starting city as visited
    visited[0] = true;
    currentPath[0] = 0;

    // Start recursive solution
    tspRec(0, 1, 0);

    // Print results
    std::cout << "Najlepszy koszt: " << bestCost << std::endl;
    std::cout << "Najlepsza trasa: ";
    for (int i = 0; i <= size; i++) {
        std::cout << bestPath[i] << " ";
    }
    std::cout << std::endl;
}