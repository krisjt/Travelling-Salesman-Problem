//
// Created by Krystyna Nowak on 09/10/2024.
//

#include "BruteForce.h"

BruteForce::BruteForce(Matrix& matrix) {
    this->size = matrix.getSize();
    this->matrix = matrix.getMatrix();
    numPermutations = 1;
    for(int i = 1; i < size; i++){
        numPermutations*=i;
    }
    cout << "Number of permutation = " << numPermutations << "\n";
    routes = new int*[numPermutations];
    for (int i = 0; i < numPermutations; i++) {
        routes[i] = new int[size];
    }
//    shortestPath = new int[size+1];
}

BruteForce::~BruteForce() {
    for (int i = 0; i < numPermutations; i++) {
        delete[] routes[i];
    }
    delete[] routes;
}

void BruteForce::start(){
    getRoutes();
    calculateRoutes();
}

//bool contains(int query, int array[], int size) {
//    for (int k = 0; k < size; k++) {
//        if (array[k] == query) {
//            return true;
//        }
//    }
//    return false;
//}

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
    int* city = new int[size-1];
    int iterator = 0;

    //initializing an array of cities with numbers of cities we want to find permutations for
    for (int i = 1; i < size; i++) {
        city[i - 1] = i;
    }

    do {
        routes[iterator][0] = 0;
        for (int i = 1; i < size; i++) {
            routes[iterator][i] = city[i - 1];
        }
        iterator++;
    } while(findNextPermutation(city, size - 1));
    delete[] city;
}

void BruteForce::printRoutes(){
    cout << "\n \n- - - - - - - - - - - - - - - - - - - - - - - \n";
    cout << "- - - - - - - - - - - - - - - - - - - - - - - \n \n";
    cout << "All possible routes: \n";
    for(int i = 0; i < numPermutations; i++){
        cout <<  i+1 << ". ";
        for(int j = 0; j < size; j++){
            cout  << routes[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "- - - - - - - - - - - - - - - - - - - - - - - ";
    cout << "\n- - - - - - - - - - - - - - - - - - - - - - - ";
}

void BruteForce::printCalculations(){
    int minWeight = INT_MAX;
    int currWeight = 0;
    cout << "\n\nCALCULATIONS:\n";
    for(int i = 0; i < numPermutations; i++) {
        cout << "- - - - - - - - - - - - - \n";
        cout << "Obliczanie odległości dla drogi ";
        for (int j = 0; j < size; j++) {
            if (j != (size - 1))cout << routes[i][j] << " - ";
            else cout << routes[i][j] << "\n";
        }
        for (int j = 0; j < size; j++) {
            if (matrix[routes[i][j]][routes[i][j + 1]] != -1) {
                currWeight += matrix[routes[i][j]][routes[i][j + 1]];
                if (j != (size - 1))cout << matrix[routes[i][j]][routes[i][j + 1]] << " + ";
                else cout << matrix[routes[i][j]][routes[i][j + 1]] << " = ";
            }
        }
        cout << currWeight << "\n";
        if (currWeight < minWeight)minWeight = currWeight;
        cout << "Minimum weight = " << minWeight << "\n";
        cout << "\n- - - - - - - - - - - - - ";
        currWeight = 0;
    }
}

void BruteForce::calculateRoutes(){
int minWeight = INT_MAX;
int currWeight = 0;
    for(int i = 0; i < numPermutations; i++){
        for(int j = 0; j < size; j++) {
            if (matrix[routes[i][j]][routes[i][j + 1]] != -1) {
                currWeight += matrix[routes[i][j]][routes[i][j + 1]];
            }
        }
        if(currWeight < minWeight){
            minWeight = currWeight;
//            shortestPath[0] = minWeight;
//            for(int j = 1; j <= size; j++)shortestPath[j]=routes[i][j-1];
        }
        currWeight = 0;
    }
//    cout << "The path:\n";
//    for(int j = 1; j <= size; j++)cout<<shortestPath[j];
//    cout << "\nLength = " << shortestPath[0];
//    return shortestPath;
}
//TODO: print routes method!
//TODO: clean up code, print everything out to see how algorithm works;