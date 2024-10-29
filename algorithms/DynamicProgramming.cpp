//
// Created by Krystyna Nowak on 25/10/2024.
//
#include "DynamicProgramming.h"
#include <iostream>

DynamicProgramming::DynamicProgramming(Matrix& data) {
    this->size = data.getSize();
    this->allVisited = (1 << size) - 1;

    // Initialize matrix
    matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++) {
            matrix[i][j] = data.getDistance(i, j);
        }
    }

    // Initialize dp table
    dp = new int*[1 << size];
    for (int i = 0; i < (1 << size); i++) {
        dp[i] = new int[size];
        for (int j = 0; j < size; j++) {
            dp[i][j] = -1;
        }
    }

    // Initialize path array
    path = new int[size + 1];
}

DynamicProgramming::~DynamicProgramming() {
    // Free matrix memory
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    // Free dp table memory
    for (int i = 0; i < (1 << size); i++) {
        delete[] dp[i];
    }
    delete[] dp;

    // Free path array
    delete[] path;
}

int DynamicProgramming::tsp(int mask, int pos) {
    // If all cities are visited, return cost of returning to starting city
    if (mask == allVisited) {
        return matrix[pos][0];
    }

    // If this subproblem has already been solved
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int ans = INT_MAX;

    // Try to visit all unvisited cities
    for (int city = 0; city < size; city++) {
        if ((mask & (1 << city)) == 0) { // if city is not visited
            int newCost = matrix[pos][city] + tsp(mask | (1 << city), city);
            if (newCost < ans) {
                ans = newCost;
            }
        }
    }

    dp[mask][pos] = ans;
    return ans;
}

void DynamicProgramming::reconstructPath(int mask, int pos, int currentIndex) {
    // If we've visited all cities
    if (mask == allVisited) {
        path[currentIndex] = 0; // Return to starting city
        return;
    }

    int bestCity = -1;
    int bestCost = INT_MAX;

    // Find the next city in the optimal path
    for (int city = 0; city < size; city++) {
        if ((mask & (1 << city)) == 0) { // if city is not visited
            int currentCost = matrix[pos][city] + dp[mask | (1 << city)][city];
            if (currentCost < bestCost) {
                bestCost = currentCost;
                bestCity = city;
            }
        }
    }

    path[currentIndex] = bestCity;
    reconstructPath(mask | (1 << bestCity), bestCity, currentIndex + 1);
}

void DynamicProgramming::start() {
    // Start with city 0
    int initialMask = 1; // mark first city as visited

    // Find optimal cost
    int optimalCost = tsp(initialMask, 0);

    // Reconstruct the path
    path[0] = 0; // Start from city 0
    reconstructPath(initialMask, 0, 1);
}