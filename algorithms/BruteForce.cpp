//
// Created by Krystyna Nowak on 09/10/2024.
//

#include "BruteForce.h"

BruteForce::BruteForce(Matrix matrix) : matrix(matrix) {
    int size = matrix.getSize();
    route = new int[size + 1];
}

BruteForce::~BruteForce() {
    delete[] route;
}

bool contains(int query, int array[], int size) {
    for (int k = 0; k < size; k++) {
        if (array[k] == query) {
            return true;
        }
    }
    return false;
}

void BruteForce::findWay(){
    int size = matrix.getSize();
    int seenCity [size];
    int weight = 0;

    for (int i = 0; i < size; i++) {
        seenCity[i] = -1;
    }

    for(int i = 0; i < size; i++){
        route[i+1] = i;
        for(int j = 0; j < size; j++) {
            if (matrix.getMatrix()[i][j] != -1) {
                if(!contains(j,seenCity,size)){
                    weight += matrix.getMatrix()[i][j];
                    seenCity[i] = j;
                    break;
                }
                else continue;
            } else continue;
        }
    }
    route[0] = weight;
}

void BruteForce::printRoutes(){
    findWay();
    for(int i = 0; i < matrix.getSize()+1; i++){
        cout << "From " << route[i] << " to " << route[i+1];
        cout << "Weight = " << matrix.getMatrix()[route[i]][route[i+1]];
    }
    cout << "Total weight = " << route[0];
}

// Wybieramy wierzcholek 0, iterujemy po sasiadach i wybieramy pierwszego, ktory nie jest na liscie seenCity
//wybrany sasiad staje się teraz wierzcholkiem docelowym i iterujemy po jego sasiadach
//przy kazdej iteracji sprawdzamy czy i == arr.size()-1, jesli tak to szukamy drogi do wierzcholka poczatkowego

