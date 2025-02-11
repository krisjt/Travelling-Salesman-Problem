//
// Created by Krystyna Nowak on 25/10/2024.
//
#include "DynamicProgramming.h"
#include <iostream>

DynamicProgramming::DynamicProgramming(Matrix &data)
{
    this->size = data.getSize();
    this->allVisited = (1 << size) - 1;

    // Inicjalizacja macierzy matrix
    matrix = new int *[size];
    for (int i = 0; i < size; i++)
    {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = data.getDistance(i, j);
        }
    }

    // Inicjalizacja macierzy dp (mozna zmienic na unsigned long long, ale narazie int dziala)
    dp = new int *[1 << size];
    for (int i = 0; i < (1 << size); i++)
    {
        dp[i] = new int[size];
        for (int j = 0; j < size; j++)
        {
            dp[i][j] = -1;
        }
    }

    // Inicjalizacja tablicy path
    path = new int[size + 1];
}

DynamicProgramming::~DynamicProgramming()
{
    // Zwolnij pamięć macierzy
    for (int i = 0; i < size; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    // Zwolnij macierz dp
    for (int i = 0; i < (1 << size); i++)
    {
        delete[] dp[i];
    }
    delete[] dp;

    // Zwolnij tablice
    delete[] path;
}

int DynamicProgramming::tsp(int mask, int pos)
{
    // Jesli wszytskie miasta zostały odwiedzone zwróc koszt powrotu do miasta poczatkowego
    if (mask == allVisited)
    { // bitowa reprezentacja odwiedzonych miast (1 - odwiedzone)
        return matrix[pos][0];
    }

    // Sprawdzanie czy ten subproblem został rozwiązany, jesli tak to wychodzimy z rekurencji
    if (dp[mask][pos] != -1)
    {
        return dp[mask][pos];
    }

    int ans = INT_MAX;

    // Odwiedzamy wszytskie nieodwiedzone miasta
    for (int city = 0; city < size; city++)
    {
        if (((mask & (1 << city)) == 0))
        { // Sprawdzanie czy miasto zostało odwiedzone (1<<city) przesuniecie bitowe, & operator logiczny AND sprawdza czy sa rowne
            // Jeśli wynik to 0 - miasto nie zostalo odwiedzone, jesli rozne od 0 - zostało
            int newCost = matrix[pos][city] + tsp(mask | (1 << city), city); // wywolanie tsp, oblizenie nowego kosztu
            if (newCost < ans)
            {
                ans = newCost;
            }
        }
    }

    dp[mask][pos] = ans; // Ustawienie rozwiazania podproblemu
    return ans;
}

void DynamicProgramming::reconstructPath(int mask, int pos, int currentIndex)
{
    // Jesli odwiedzono wszytskie miasta
    if (mask == allVisited)
    {
        path[currentIndex] = 0; // Powrót do poczatkowego
        return;
    }

    int bestCity = -1;
    int bestCost = INT_MAX;
    // Szukanie kolejnego optymalnego miasta na sciezce
    for (int city = 0; city < size; city++)
    {
        if (((mask & (1 << city)) == 0) )
        { // sprawdzanie czy miasto jest odwiedzone

            int currentCost = matrix[pos][city] + dp[mask | (1 << city)][city];
            if (currentCost < bestCost)
            {
                bestCost = currentCost;
                bestCity = city;
            }
        }
    }

    path[currentIndex] = bestCity;
    reconstructPath(mask | (1 << bestCity), bestCity, currentIndex + 1);
}

int DynamicProgramming::tsp(int mask, int pos)
{
    // If all cities have been visited, check if there's a valid path back to start
    if (mask == allVisited)
    {
        // Return INT_MAX if there's no valid path back to start (distance = 0)
        return matrix[pos][0] == 0 ? INT_MAX : matrix[pos][0];
    }

    // Check if this subproblem has been solved
    if (dp[mask][pos] != -1)
    {
        return dp[mask][pos];
    }

    int ans = INT_MAX;

    // Visit all unvisited cities
    for (int city = 0; city < size; city++)
    {
        if ((mask & (1 << city)) == 0)  // If city hasn't been visited
        {
            // Skip if there's no valid path (distance = 0)
            if (matrix[pos][city] == 0)
                continue;

            int newCost = tsp(mask | (1 << city), city);
            // Only add the cost if the recursive call found a valid path
            if (newCost != INT_MAX)
            {
                newCost += matrix[pos][city];
                if (newCost < ans)
                {
                    ans = newCost;
                }
            }
        }
    }

    dp[mask][pos] = ans;
    return ans;
}

void DynamicProgramming::reconstructPath(int mask, int pos, int currentIndex)
{
    if (mask == allVisited)
    {
        // Only set return to start if there's a valid path
        if (matrix[pos][0] != 0)
        {
            path[currentIndex] = 0;
        }
        return;
    }

    int bestCity = -1;
    int bestCost = INT_MAX;

    for (int city = 0; city < size; city++)
    {
        if ((mask & (1 << city)) == 0)
        {
            // Skip if there's no valid path to this city
            if (matrix[pos][city] == 0)
                continue;

            int nextMask = mask | (1 << city);
            int pathCost = dp[nextMask][city];

            if (pathCost != INT_MAX)
            {
                int currentCost = matrix[pos][city] + pathCost;
                if (currentCost < bestCost)
                {
                    bestCost = currentCost;
                    bestCity = city;
                }
            }
        }
    }

    if (bestCity != -1)
    {
        path[currentIndex] = bestCity;
        reconstructPath(mask | (1 << bestCity), bestCity, currentIndex + 1);
    }
}

void DynamicProgramming::start()
{
    // Rozpoczynamy z miasta 0
    int initialMask = 1; // oznaczamy pierwsze miasto jako odwiedzone

    // znajdujemy koszt optymalny
    optimalCost = tsp(initialMask, 0);

    // rekonstrukcja sciezki
    path[0] = 0; // Start w miescie 0
    reconstructPath(initialMask, 0, 1);
}


int DynamicProgramming::getCost(){
    return optimalCost;
}

void DynamicProgramming::printResult()
{
    cout << "\n-----------------------------------------\n"
         << "DYNAMIC PROGRAMMING\n"
         << "-----------------------------------------\n"
         << "Results of dynamic programming algorithm.\n"
         << "Shortest path is:\n";

    for (int i = 0; i < size; i++)
    {
        cout << path[i] << (i != size - 1 ? " - " : "");
    }
    cout << "\nIts length equals " << optimalCost << ".\n"
         << "\n-----------------------------------------\n"
         << "-----------------------------------------\n";
}