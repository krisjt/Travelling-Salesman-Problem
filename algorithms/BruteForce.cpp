//
// Created by Krystyna Nowak on 09/10/2024.
//

#include "BruteForce.h"

BruteForce::BruteForce(Matrix& matrix) {
    this->size = matrix.getSize();
    this->matrix = matrix.getMatrix();
    numPermutations = 1;
    for(int i = 1; i <= size; i++){
        numPermutations*=i;
    }
    cout << "Number of permutation = " << numPermutations << "\n";
    routes = new int*[numPermutations];  // Alokujemy tablicę wskaźników
    for (int i = 0; i < numPermutations; i++) {
        routes[i] = new int[size];       // Alokujemy pamięć dla każdej permutacji
    }
}

BruteForce::~BruteForce() {
}

bool contains(int query, int array[], int size) {
    for (int k = 0; k < size; k++) {
        if (array[k] == query) {
            return true;
        }
    }
    return false;
}

int* BruteForce::reverseArr(int* data, int left, int right)
{

    // Reverse the sub-array
    while (left < right) {
        int temp = data[left];
        data[left++] = data[right];
        data[right--] = temp;
    }

    // Return the updated array
    return data;
}

bool BruteForce::findNextPermutation(int* data, int size)
{

    // If the given dataset is empty
    // or contains only one element
    // next_permutation is not possible
    if (size <= 1)
        return false;

    int last = size - 2;

    // find the longest non-increasing suffix
    // and find the pivot
    while (last >= 0) {
        if (data[last] < data[last + 1]) {
            break;
        }
        last--;
    }// If there is no increasing pair
    // there is no higher order permutation
    if (last < 0)
        return false;

    int nextGreater = size - 1;

    // Find the rightmost successor to the pivot
    for (int i = size - 1; i > last; i--) {
        if (data[i] > data[last]) {
            nextGreater = i;
            break;
        }
    }

    // Swap the successor and the pivot
    swap(data[nextGreater], data[last]);

    // Reverse the suffix
    reverseArr(data, last + 1, size - 1);

    // Return true as the next_permutation is done
    return true;
}


void BruteForce::getRoutes(){
    int* city;
    int iterator = 0;
    for(int i = 0; i < size; i++){
        city[i] = i;
    }
    findNextPermutation(city, size);
    bool flag = true;
    while(flag) {
        flag = findNextPermutation(city, size);
        cout << "Permutation : " << "\n";
        for (int i = 0; i < size; i++) {
            cout << city[i] << " ";
            routes[iterator][i] = city[i];
        }
        cout << "\n";
        iterator++;
    }
    cout << "array = \n";
    for(int i = 0; i < numPermutations-1; i++){
        for(int j = 0; j < size; j++){
            cout << routes[i][j] << " ";
        }
        cout << "\n";
    }
}

int* BruteForce::calculateRoutes(){
int minWeight = INT_MAX;
for(int i = 0; i < numPermutations; i++){

}
}