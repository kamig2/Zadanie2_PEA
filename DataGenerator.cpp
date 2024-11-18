//
// Created by grons on 13.11.2024.
//

#include <chrono>
#include "DataGenerator.h"
#include "DataGenerator.h"

void DataGenerator::generate(int r, std::vector<int> sizeVertex) {
    int** matrix = nullptr;
    for (const int& i : sizeVertex) {  // Pętla iterująca po wielkościach macierzy
        long long bbBfsTimeAsym = 0;
        long long bbDfsTimeAsym = 0;
        long long bbLCTimeAsym = 0;
        long long bbBfsTimeSym = 0;
        long long bbDfsTimeSym = 0;
        long long bbLCTimeSym = 0;

        for (int j = 0; j < r; ++j) {  // Pętla wykonująca r pomiarów
            matrix = dataReader.generateRandomAsymmetricalData(i);
            bbBfsTimeAsym = calculateTime(1, matrix, i);
            saveToCsvFile("bbBfsAsym.csv", bbBfsTimeAsym,i);
            bbDfsTimeAsym = calculateTime(2, matrix, i);
            saveToCsvFile("bbDfsAsym.csv", bbDfsTimeAsym,i);
            bbLCTimeAsym = calculateTime(3, matrix, i);
            saveToCsvFile("bbLCAsym.csv", bbLCTimeAsym,i);

            matrix = dataReader.generateRandomSymmetricalData(i);
            bbBfsTimeSym = calculateTime(4, matrix, i);
            saveToCsvFile("bbBfsSym.csv", bbBfsTimeSym,i);
            bbDfsTimeSym = calculateTime(5, matrix, i);
            saveToCsvFile("bbDfsSym.csv", bbDfsTimeSym,i);
            bbLCTimeSym = calculateTime(6, matrix, i);
            saveToCsvFile("bbLCSym.csv", bbLCTimeSym,i);

            freeMatrix(matrix, i); // Zwalniamy pamięć po każdym użyciu macierzy
        }

        /*saveToCsvFile("bruteForce.csv", bbDfsTimeAsym, i);
        saveToCsvFile("nearestNeighbour.csv", bbLCTimeAsym, i);
        saveToCsvFile("randomAlgorithm.csv", bbBfsTimeAsym, i);
        saveToCsvFile("bruteForceSym.csv", bbDfsTimeSym, i);
        saveToCsvFile("nearestNeighbourSym.csv", bbLCTimeSym, i);
        saveToCsvFile("randomAlgorithmSym.csv", bbBfsTimeSym, i);*/
    }
}

long long DataGenerator::calculateTime(int algorithm, int** matrix, int n) {
    long long time;

    auto timeStart = std::chrono::high_resolution_clock::now();
    switch (algorithm) {
        case 1:
            bbfs.startFromEachVertex(matrix,n);
            break;
        case 2:
            bdfs.startFromEachVertex(matrix,n);
            break;
        case 3:
            bLowestCost.startFromEachVertex(matrix,n);
            break;
        case 4:
            bbfs.branchAndBound(matrix,n,0);
            break;
        case 5:
            bdfs.branchAndBound(matrix,n,0);
            break;
        case 6:
            bLowestCost.branchAndBound(matrix,n,0);
        default:
            break;
    }
    auto timeEnd = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count();
    return time;
}

void DataGenerator::saveToCsvFile(std::string fileName, long long time, int n) {
    std::ofstream file(fileName, std::ios::out | std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku " << fileName << " do zapisu!" << std::endl;
        return;
    }

//    double time2 = static_cast<double>(time) / 100;
    file << n << "," << time << std::endl;
    file.close();
}

// Funkcja do zwalniania pamięci macierzy
void DataGenerator::freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
