//
// Created by Krystyna Nowak on 09/10/2024.
//

#ifndef PEA1_BRUTEFORCE_H
#define PEA1_BRUTEFORCE_H

#include "../structures/Matrix.h"

//Użyj funkcji do generowania wszystkich możliwych permutacji tras. Każda permutacja to potencjalna trasa, którą można przetestować.
//Dla każdej permutacji oblicz długość trasy, sumując odległości między kolejnymi miastami i dodając odległość powrotną do miasta startowego.
//Zapisuj najkrótszą trasę, aktualizując ją, gdy znajdziesz trasę krótszą od dotychczasowej.
//Zwróć najkrótszą trasę i jej długość.
class BruteForce {//ASYMETRYCZNE
// 1) zaczynamy w wybranym miescie i musimy odwiedzic kazde miasto raz i wrocic do siebie
public:
    explicit BruteForce(Matrix& matrix);
    ~BruteForce();
    void getRoutes();
private:
    int numPermutations;
    int** matrix;
    bool findNextPermutation(int* data, int size);
    int size;
    static int* reverseArr(int* data, int left, int right);
//    bool getPermutations(int begin, int end);
    int** routes;
    int *calculateRoutes();
};


#endif //PEA1_BRUTEFORCE_H
