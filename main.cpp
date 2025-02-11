#include <iostream>
#include <time.h>
#include "structures/Matrix.h"
#include "IO/FileReader.h"
#include "algorithms/BruteForce.h"
#include "algorithms/BranchAndBound.h"
#include "algorithms/DynamicProgramming.h"
#include "algorithms/TabuSearch.h"
#include "algorithms/SimulatedAnnealing.h"
#include "algorithms/AntColonyOptimization.h"
#include <unistd.h>
#include <limits.h>
#include "measurements/MeasurementsLocal.h"

double coolingRate = 0.99;
int iterationNumberSimA = 3000;
int iterationNumberTS = 2000;
int tabuListSize = 20;
int neighbourhoodType = 0;

double tau =1;
int numberOfAnts = 25;
int numberOfIterations = 25;
double alpha = 2;
double beta = 10;
double rho = 0.1;


void firstProject(){
    int choice = 1;
    bool flag = true;

    while(flag) {
        cout << "\n------------------------------\n"
             << "MENU\n"
             << "------------------------------\n"
             << "Here is what you can do: \n"
             << "1. Load matrix from file. \n"
             << "2. Generate new matrix. \n"
             << "3. Brute Force algorithm. \n"
             << "4. Branch and Bound algorithm. \n"
             << "5. Dynamic Programming algorithm. \n"
             << "6. Return. \n"
             << "0. Exit.\n"
             << "------------------------------\n"
             << "------------------------------\n\n";

        int size = 5;
        clock_t start;
        double timeA;

        FileReader fileReader("../data/file.txt");
        Matrix matrix = fileReader.readFile();
        BranchAndBound bnb(matrix);
        BruteForce bf(matrix);
        DynamicProgramming dp(matrix);

        cin >> choice;
        switch (choice) {
            case 1:
                cout <<
                     "\n------------------------------\n" <<
                     "MATRIX\n" <<
                     "------------------------------\n";
                matrix.printMatrix();
                cout << "\n------------------------------\n" <<
                     "------------------------------\n\n";
                break;
            case 2:
                cout << "Insert size of the matrix you want to generate: \n";
                cin >> size;
                fileReader.generateMatrix(size);
                break;
            case 3:
                start = clock();
                bf.start();
                timeA = (static_cast<double>(clock() - start)) / CLOCKS_PER_SEC;

                bf.printResult();
                cout <<
                     "\n------------------------------\n" <<
                     "TIME\n" <<
                     "------------------------------\n";
                cout << "Brute Force algorithm took " << timeA << " seconds";
                cout << "\n------------------------------\n" <<
                     "------------------------------\n\n";
                cout << endl;
                break;
            case 4:
                start = clock();
                bnb.start();
                timeA = (static_cast<double>(clock() - start)) / CLOCKS_PER_SEC;

                bnb.printResult();
                cout <<
                     "\n------------------------------\n" <<
                     "TIME\n" <<
                     "------------------------------\n";
                cout << "Branch and Bound algorithm took " << timeA << " seconds";
                cout << "\n------------------------------\n" <<
                     "------------------------------\n\n";
                cout << endl;
                break;
            case 5:
                start = clock();
                dp.start();
                timeA = (static_cast<double>(clock() - start)) / CLOCKS_PER_SEC;

                dp.printResult();
                cout <<
                     "\n------------------------------\n" <<
                     "TIME\n" <<
                     "------------------------------\n";
                cout << "Dynamic Programming algorithm took " << timeA << " seconds";
                cout << "\n------------------------------\n" <<
                     "------------------------------\n\n";
                cout << endl;
                break;
            case 6:
                flag = false;
                break;
            case 0:
                exit(0);
            default:
                cout <<
                     "\n------------------------------\n" <<
                     "------------------------------\n" <<
                     "You've entered the wrong number!\n" <<
                     "------------------------------\n" <<
                     "------------------------------\n\n";
                break;
        }
    }
}

void secondProject(){
    int choice = 1;
    bool flag = true;
    while(flag) {
        cout << "\n------------------------------\n"
             << "MENU\n"
             << "------------------------------\n"
             <<"Here is what you can do: \n"
             << "1. Load matrix from file. \n"
             << "2. Generate new matrix. \n"
             << "3. Simulated Annealing algorithm. \n"
             << "4. Tabu Search algorithm. \n"
                << "5. Set data for Simulated Annealing algorithm. \n"
                << "6. Set data for Tabu Search algorithm. \n"
                << "7. Check data for Simulated Annealing and Tabu Search. \n"
             << "8. Return. \n"
             << "0. Exit.\n"
             << "------------------------------\n"
             << "------------------------------\n\n";

        int size = 5;
        clock_t start;
        double timeA;

        FileReader fileReader("../data/file.txt");
        Matrix matrix = fileReader.readFile();
        SimulatedAnnealing sa(matrix);
        TabuSearch ts(matrix);


        cin >> choice;
        switch (choice) {
            case 1:
                cout <<
                     "\n------------------------------\n" <<
                     "MATRIX\n" <<
                     "------------------------------\n";
                matrix.printMatrix();
                cout << "\n------------------------------\n" <<
                     "------------------------------\n\n";
                break;
            case 2:
                cout << "Insert size of the matrix you want to generate: \n";
                cin >> size;
                fileReader.generateMatrix(size);
                break;
            case 3:
                start = clock();
                sa.start(iterationNumberSimA,coolingRate);
                timeA = (static_cast<double>(clock() - start)) / CLOCKS_PER_SEC;

                sa.printResult();
                cout<<
                    "\n------------------------------\n" <<
                    "TIME\n" <<
                    "------------------------------\n";
                cout << "Simulated Annealing algorithm took " << timeA << " seconds";
                cout<< "\n------------------------------\n" <<
                    "------------------------------\n\n";
                cout << endl;
                break;
            case 4:
                start = clock();
                ts.start(iterationNumberTS,tabuListSize,neighbourhoodType);
                timeA = (static_cast<double>(clock() - start)) / CLOCKS_PER_SEC;

                ts.printResult();
                cout<<
                    "\n------------------------------\n" <<
                    "TIME\n" <<
                    "------------------------------\n";
                cout << "Tabu Search algorithm took " << timeA << " seconds";
                cout<< "\n------------------------------\n" <<
                    "------------------------------\n\n";
                cout << endl;
                break;

            case 5:
                cout<<
                    "\n------------------------------\n" <<
                    "SET DATA FOR SIMULATED ANNEALING\n" <<
                    "------------------------------\n";
                cout << "Current iteration number is: " << iterationNumberSimA << endl;
                cout << "Choose maximal iteration number: ";
                cin >> iterationNumberSimA;
                cout << endl << "Chosen number of iterations: " << iterationNumberSimA << endl;
                cout << "------------------------------\n";
                cout << "Current cooling rate is: " << coolingRate << endl;
                cout << "Choose cooling rate: ";
                cin >> coolingRate;
                cout << endl << "Chosen cooling rate: " << coolingRate << endl;
                cout<< "\n------------------------------\n" <<
                    "------------------------------\n\n";
                cout << endl;
                break;
            case 6:
                cout<<
                    "\n------------------------------\n" <<
                    "SET DATA FOR TABU SEARCH\n" <<
                    "------------------------------\n";
                cout << "Current iteration number is: " << iterationNumberTS << endl;
                cout << "Choose maximal iteration number: ";
                cin >> iterationNumberTS;
                cout << endl << "Chosen number of iterations: " << iterationNumberTS << endl;
                cout << "------------------------------\n";
                cout << "Current tabu list size is: " << tabuListSize << endl;
                cout << "Choose tabu list size: ";
                cin >> tabuListSize;
                cout << endl << "Chosen tabu list size: " << tabuListSize << endl;
                cout << "------------------------------\n";
                if (neighbourhoodType == 0) {
                    cout << "Current neighbourhood type is: swap." << endl;
                }
                else if (neighbourhoodType == 1){
                    cout << "Current neighbourhood type is: reverse. " << endl;
                }
                else{
                    cout << "Current neighbourhood type is unknown." << endl;
                }
                cout << "Choose neighbourhood type: ";
                cin >> neighbourhoodType;
                if (neighbourhoodType == 0) {
                    cout << endl << "Chosen neighbourhood type: swap." << endl;
                }
                else if (neighbourhoodType == 1){
                    cout << endl << "Chosen neighbourhood type: reverse." << endl;
                }
                else{
                    cout << endl << "Chosen neighbourhood type: unknown." << endl;
                }
                cout<< "\n------------------------------\n" <<
                    "------------------------------\n\n";
                cout << endl;
                break;
            case 7:
                cout<<
                    "\n------------------------------\n" <<
                    "CHECK DATA FOR SIMULATED ANNEALING AND TABU SEARCH\n" <<
                    "------------------------------\n";
                cout<< "SIMULATED ANNEALING\n------------------------------\n";
                cout << "Current iteration number is: " << iterationNumberSimA << endl;
                cout << "Current cooling rate is: " << coolingRate << endl;
                cout<< "------------------------------\n" <<
                    "TABU SEARCH\n------------------------------\n";
                cout << "Current iteration number is: " << iterationNumberTS << endl;
                cout << "Current tabu list size is: " << tabuListSize << endl;
                if (neighbourhoodType == 0) {
                    cout << "Current neighbourhood type is: swap." << endl;
                }
                else if (neighbourhoodType == 1){
                    cout << "Current neighbourhood type is: reverse. " << endl;
                }
                else{
                    cout << "Current neighbourhood type is unknown." << endl;
                }
                cout << endl;
                break;
            case 8:
                flag = false;
                break;
            case 0:
                exit(0);
            default:
                cout <<
                     "\n------------------------------\n" <<
                     "------------------------------\n" <<
                     "You've entered the wrong number!\n" <<
                     "------------------------------\n" <<
                     "------------------------------\n\n";
                break;
        }
    }

}

void thirdProject(){
    int choice = 1;
    string filePath = "../data/plik55.txt";
    bool flag = true;
    while(flag) {
        cout << "\n------------------------------\n"
             << "MENU\n"
             << "------------------------------\n"
             <<"Here is what you can do: \n"
             << "1. Load matrix from file. \n"
             << "2. Generate new matrix. \n"
             << "3. Ant Colony Optimization algorithm. \n"
             << "4. Set data for Ant Colony Optimization algorithm. \n"
             << "5. Check data for Ant Colony Optimization algorithm. \n"
             << "6. Choose file. \n"
             << "7. Branch and bound algorithm. \n"
             << "8. Return. \n"
             << "0. Exit.\n"
             << "------------------------------\n"
             << "------------------------------\n\n";

        int size = 5;
        clock_t start;
        double timeA;

        FileReader fileReader(filePath);
        Matrix matrix = fileReader.readFile();
        AntColonyOptimization aco(matrix,tau);
        BranchAndBound bnb(matrix);

        cin >> choice;
        switch (choice) {
            case 1:
                cout <<
                     "\n------------------------------\n" <<
                     "MATRIX\n" <<
                     "------------------------------\n";
                matrix.printMatrix();
                cout << "\n------------------------------\n" <<
                     "------------------------------\n\n";
                break;
            case 2:
                cout << "Insert size of the matrix you want to generate: \n";
                cin >> size;
                fileReader.generateMatrix(size);
                break;
            case 3:
                start = clock();
                aco.start(numberOfAnts,numberOfIterations,alpha,beta,rho);
                timeA = (static_cast<double>(clock() - start)) / CLOCKS_PER_SEC;

                aco.printResult();
                cout<<
                    "\n------------------------------\n" <<
                    "TIME\n" <<
                    "------------------------------\n";
                cout << "Ant Colony Optimization algorithm took " << timeA << " seconds";
                cout<< "\n------------------------------\n" <<
                    "------------------------------\n\n";
                cout << endl;
                break;

            case 4:
                cout<<
                    "\n------------------------------\n" <<
                    "SET DATA FOR ANT COLONY OPTIMIZATION\n" <<
                    "------------------------------\n";
                cout << "Current iteration number is: " << numberOfIterations << endl;
                cout << "Choose iteration number: ";
                cin >> numberOfIterations;
                cout << endl << "Chosen number of iterations: " << numberOfIterations << endl;
                cout << "------------------------------\n";
                cout << "Current number of ants is: " << numberOfAnts << endl;
                cout << "Choose number of ants: ";
                cin >> numberOfAnts;
                cout << endl << "Chosen number of ants: " << numberOfAnts << endl;
                cout << "------------------------------\n";
                cout << "Current tau (amount of pheromone) is: " << tau << endl;
                cout << "Choose tau: ";
                cin >> tau;
                cout << endl << "Chosen tau: " << tau << endl;
                cout << "------------------------------\n";
                cout << "Current rho (pheromone evaporation coefficient) is: " << rho << endl;
                cout << "Choose rho: ";
                cin >> rho;
                cout << endl << "Chosen rho: " << rho << endl;
                cout << "------------------------------\n";
                cout << "Current alpha (meaning of pheromone) is: " << alpha << endl;
                cout << "Choose alpha: ";
                cin >> alpha;
                cout << endl << "Chosen alpha: " << alpha << endl;
                cout << "------------------------------\n";
                cout << "Current beta (meaning of heuristics) is: " << beta << endl;
                cout << "Choose beta: ";
                cin >> beta;
                cout << endl << "Chosen beta: " << beta << endl;
                cout<< "\n------------------------------\n" <<
                    "------------------------------\n\n";
                cout << endl;
                break;
            case 5:
                cout<<
                    "\n------------------------------\n" <<
                    "CHECK DATA FOR ANT COLONY OPTIMIZATION\n" <<
                    "------------------------------\n";
                cout << "Current iteration number is: " << numberOfIterations << endl;
                cout << "Current number of ants: " << numberOfAnts << endl;
                cout << "Current tau (amount of pheromone): " << tau << endl;
                cout << "Current rho (pheromone evaporation coefficient): " << rho << endl;
                cout << "Current alpha (meaning of pheromone): " << alpha << endl;
                cout << "Current beta (meaning of heuristics): " << beta << endl;
                cout<< "------------------------------\n" << endl;
                break;
            case 6: {
                cout << "Choose a file to load:\n";
                cout << "1. 10a.txt\n";
                cout << "2. 10b.txt\n";
                cout << "3. 10c.txt\n";
                cout << "4. 14.txt\n";
                cout << "5. br.txt\n";
                cout << "6. file.txt (default)\n";
                int fileChoice;
                cin >> fileChoice;

                switch (fileChoice) {
                    case 1:
                        filePath = "../data/tsp_10a.txt";
                        break;
                    case 2:
                        filePath = "../data/tsp_10b.txt";
                        break;
                    case 3:
                        filePath = "../data/tsp_10c.txt";
                        break;
                    case 4:
                        filePath = "../data/tsp_14_db.txt";
                        break;
                    case 5:
                        filePath = "../data/br.txt";
                        break;
                    case 6:
                        filePath = "../data/file.txt";
                        break;
                    default:
                        cout << "Invalid choice.\n";
                        break;
                }
                break;
            }
            case 7:
                start = clock();
                bnb.start();
                timeA = (static_cast<double>(clock() - start)) / CLOCKS_PER_SEC;

                bnb.printResult();
                cout <<
                     "\n------------------------------\n" <<
                     "TIME\n" <<
                     "------------------------------\n";
                cout << "Branch and Bound algorithm took " << timeA << " seconds";
                cout << "\n------------------------------\n" <<
                     "------------------------------\n\n";
                cout << endl;
                break;
            case 8:
                flag = false;
                break;
            case 0:
                exit(0);
            default:
                cout <<
                     "\n------------------------------\n" <<
                     "------------------------------\n" <<
                     "You've entered the wrong number!\n" <<
                     "------------------------------\n" <<
                     "------------------------------\n\n";
                break;
        }
    }
}

// metoda menu
void menu(){
    int firstChoice = 1;
    while(true) {
        cout << "\n------------------------------\n"
             << "MENU\n"
             << "------------------------------\n"
             <<"Here is what you can do: \n"
             << "1. First Project. \n"
             << "2. Second Project. \n"
             << "3. Third Project. \n"
             << "0. Exit.\n"
             << "------------------------------\n"
             << "------------------------------\n\n";


        cin >> firstChoice;
        switch (firstChoice) {
            case 1:
                firstProject();
                break;

            case 2:
                secondProject();
                break;
            case 3:
                thirdProject();
                break;
            case 0:
                exit(0);
            default:
                cout<<
                "\n------------------------------\n" <<
                "------------------------------\n" <<
                "You've entered the wrong number!\n" <<
                "------------------------------\n" <<
                "------------------------------\n\n";
        }
    }
}

int main() {

    menu();

    return 0;
}

