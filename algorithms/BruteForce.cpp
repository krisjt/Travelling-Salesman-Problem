//
// Created by Krystyna Nowak on 09/10/2024.
//
//
//#include "BruteForce.h"
//
//BruteForce::BruteForce(Matrix& matrix) {
//    this->size = matrix.getSize();
//    this->matrix = matrix.getMatrix();
//    shortestPath = new int[size];
//}
//
//BruteForce::~BruteForce() {
//    delete[] shortestPath;
//}
//
//int* BruteForce::reverseArr(int* data, int left, int right)
//{
//    // Reverse the sub-array
//    while (left < right) {
//        int temp = data[left];
//        data[left++] = data[right];
//        data[right--] = temp;
//    }
//
//    // Return the updated array
//    return data;
//}
//
//bool BruteForce::findNextPermutation(int* data, int size)
//{
//    // Pomijamy pierwszy element, więc rozważamy tylko elementy od indeksu 1
//    if (size <= 2) // jeśli tablica zawiera tylko 1 miasto (poza pierwszym), nie ma kolejnej permutacji
//        return false;
//
//    // Punkt początkowy to indeks 1 (bo ignorujemy pierwszy element)
//    int last = size - 2;
//
//    // Znalezienie najdłuższego nie-rosnącego sufiksu, zaczynając od drugiego elementu
//    while (last >= 1) { // zmieniamy tu granicę na 1, aby nie brać pierwszego elementu pod uwagę
//        if (data[last] < data[last + 1]) {
//            break;
//        }
//        last--;
//    }
//
//    // Jeśli nie znaleziono rosnącej pary, to brak wyższej permutacji
//    if (last < 1) // sprawdzamy czy last jest mniejszy niż 1, ponieważ indeks 0 ignorujemy
//        return false;
//
//    int nextGreater = size - 1;
//
//    // Znalezienie najmniejszego elementu większego od pivotu
//    for (int i = size - 1; i > last; i--) {
//        if (data[i] > data[last]) {
//            nextGreater = i;
//            break;
//        }
//    }
//
//    // Zamieniamy pivot z elementem następnym
//    swap(data[nextGreater], data[last]);
//
//    // Odwracamy sufiks, czyli elementy od last + 1 do końca tablicy
//    reverseArr(data, last + 1, size - 1);
//
//    return true;
//}
//
//
//int* BruteForce::bruteForce(){
//    int* city = new int[size];
//    int it = 0;
//    for (int i = 0; i < size; i++) {
//        city[i] = i;
//    }
//    do {
////        cout << "\nPaths:\n";
//        //wyznaczanie dlugosci kazdej trasy
//        int currweight = 0;
//        for(int i = 0; i < size-1; i++){
//            if(matrix[city[i]][city[i+1]]!=-1){
////                cout << "\nweight between " << city[i] << " and " << city[i+1] << " = " << matrix[city[i]][city[i+1]] << "\n";
//                currweight+=matrix[city[i]][city[i+1]];
//            }
////            cout << city[i] << " ";
//        }
//        if(currweight != INT_MAX && matrix[city[size-1]][city[0]] != -1) {
//            currweight += matrix[city[size-1]][city[0]];
////            cout << "\nweight for returning from " << city[size-1] << " to " << city[0] << " = " << matrix[city[size-1]][city[0]] << "\n";
//        } else {
//            currweight = INT_MAX;  // Jeśli nie ma powrotu, ustawiamy nieskończoną wagę
//        }
//        if(currweight<minWeight){
//            minWeight = currweight;
//            for(int k = 0; k < size; k++){
//                shortestPath[k]=city[k];
//            }
//        }
////        cout << "\n Current weight = " << currweight;
////        cout << "\nMin weight = " << minWeight <<"\n";
////        cout << "Shortest route:\n";
////        for(int k = 0; k < size; k++){
////            cout << shortestPath[k] << " ";
////        }
////        cout << "\n- - - - - - - - - - - - - -\n";
//    } while(findNextPermutation(city, size ));
//    delete[] city;
//    return shortestPath;
//}
//
//void BruteForce::printResult(){
//    cout << "\n-----------------------------------------\n";
//    cout << "BRUTE FORCE\n";
//    cout << "-----------------------------------------\n";
//    cout << "Results of brute force algorithm. \n";
//    cout << "Shortest path is: \n";
//    for(int i = 0; i < size; i++){
//        if(i!=size-1) {
//            cout << shortestPath[i] << " - ";
//        }
//        else cout << shortestPath[i];
//    }
//    cout << "\nIts length equals " << minWeight << ".\n";
//    cout << "-----------------------------------------\n";
//    cout << "-----------------------------------------\n";
//}
//
////TODO: clean up code;
////TODO: rodzaj pamieci jest istotony! czy na ram czy szybka, nie za duzo tablic, bo to operacje na pamieci i zlosonosc czasowa chujowa
////TODO: BroteForce ma zwrócić ścieżkę!
////TODO: Wypytuje mocno o kod!
////TODO: Jak uzywa sie duzo tablic to algorytm ograniczony jest tez przez czas;
#include "BruteForce.h"
#include <vector>
#include <algorithm>

BruteForce::BruteForce(Matrix& matrix) {
    this->size = matrix.getSize();
    this->matrix = matrix.getMatrix();
    this->shortestPath = new int[size];
    this->minWeight = INT_MAX;
}

BruteForce::~BruteForce() {
    delete[] shortestPath;
}

int* BruteForce::bruteForce() {
    // Używamy std::vector zamiast zwykłej tablicy dla lepszego zarządzania pamięcią
    std::vector<int> cities(size);
    for (int i = 0; i < size; i++) {
        cities[i] = i;
    }

    // Cache'ujemy wartości macierzy dla często używanych indeksów
    std::vector<std::vector<int>> distanceCache(size, std::vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            distanceCache[i][j] = matrix[i][j];
        }
    }

    do {
        // Obliczamy wagę aktualnej ścieżki z wczesnym przerywaniem
        int currWeight = 0;
        bool validPath = true;

        // Sprawdzamy ścieżkę i obliczamy wagę w jednej pętli
        for (int i = 0; i < size - 1; i++) {
            int currentDist = distanceCache[cities[i]][cities[i + 1]];
            if (currentDist == -1) {
                validPath = false;
                break;
            }
            currWeight += currentDist;

            // Wczesne przerwanie jeśli już przekroczyliśmy minimalną wagę
            if (currWeight >= minWeight) {
                validPath = false;
                break;
            }
        }

        // Sprawdzamy powrót do punktu startowego tylko jeśli ścieżka jest nadal ważna
        if (validPath) {
            int returnDist = distanceCache[cities[size - 1]][cities[0]];
            if (returnDist != -1) {
                currWeight += returnDist;

                // Aktualizujemy najkrótszą ścieżkę tylko jeśli znaleźliśmy lepszą
                if (currWeight < minWeight) {
                    minWeight = currWeight;
                    std::copy(cities.begin(), cities.end(), shortestPath);
                }
            }
        }
    } while (std::next_permutation(cities.begin() + 1, cities.end()));  // Pomijamy pierwszy element

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