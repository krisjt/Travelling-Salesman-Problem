//
// Created by Krystyna Nowak on 09/10/2024.
//

#include "BruteForce.h"

BruteForce::BruteForce(Matrix& matrix) {
    this->size = matrix.getSize();
    this->matrix = matrix.getMatrix();
    shortestPath = new int[size];
}

BruteForce::~BruteForce() {
    delete[] shortestPath;
}

int* BruteForce::reverseArr(int* data, int left, int right)
{
    // Odwroc tablice
    while (left < right) {
        int temp = data[left];
        data[left++] = data[right];
        data[right--] = temp;
    }

    // Zwroc zupdatowana tablce
    return data;
}

bool BruteForce::findNextPermutation(int* data, int size)
{
    // Pomijamy pierwszy element, więc rozważamy tylko elementy od indeksu 1
    if (size <= 2) // jeśli tablica zawiera tylko 1 miasto (poza pierwszym), nie ma kolejnej permutacji
        return false;

    // Punkt początkowy to indeks 1 (bo ignorujemy pierwszy element)
    int last = size - 2;

    // Znalezienie najdłuższego nie-rosnącego sufiksu, zaczynając od drugiego elementu
    while (last >= 1) { // zmieniamy tu granicę na 1, aby nie brać pierwszego elementu pod uwagę
        if (data[last] < data[last + 1]) {
            break;
        }
        last--;
    }

    // Jeśli nie znaleziono rosnącej pary, to brak wyższej permutacji
    if (last < 1) // sprawdzamy czy last jest mniejszy niż 1, ponieważ indeks 0 ignorujemy
        return false;

    int nextGreater = size - 1;

    // Znalezienie najmniejszego elementu większego od pivotu
    for (int i = size - 1; i > last; i--) {
        if (data[i] > data[last]) {
            nextGreater = i;
            break;
        }
    }

    // Zamieniamy pivot z elementem następnym
    swap(data[nextGreater], data[last]);

    // Odwracamy sufiks, czyli elementy od last + 1 do końca tablicy
    reverseArr(data, last + 1, size - 1);

    return true;
}


int* BruteForce::start(){
    int* city = new int[size];

    for (int i = 0; i < size; i++) {
        city[i] = i;
    }

    do {
        // wyznaczanie dlugosci kazdej trasy
        int currweight = 0;

        for(int i = 0; i < size-1; i++){

            if(matrix[city[i]][city[i+1]]!=-1){
                currweight+=matrix[city[i]][city[i+1]];
            }
        }

        if(currweight != INT_MAX && matrix[city[size-1]][city[0]] != -1) {
            currweight += matrix[city[size-1]][city[0]];
        } else {
            currweight = INT_MAX;  // Jeśli nie ma powrotu, ustawiamy nieskończoną wagę
        }

        if(currweight<minWeight){
            minWeight = currweight;

            for(int k = 0; k < size; k++){
                shortestPath[k]=city[k];
            }
        }

    } while(findNextPermutation(city, size ));

    delete[] city;
    return shortestPath;
}

void BruteForce::printResult() {
    cout << "\n-----------------------------------------\n"
         << "BRUTE FORCE\n"
         << "-----------------------------------------\n"
         << "Results of brute force algorithm.\n"
         << "Shortest path is:\n";

    for (int i = 0; i < size; i++) {
        cout << shortestPath[i] << (i != size-1 ? " - " : "");
    }

    cout << "\nIts length equals " << minWeight << ".\n"
         << "-----------------------------------------\n"
         << "-----------------------------------------\n";
}