//
// Created by grons on 13.11.2024.
//

#ifndef ZADANIE2_DATAGENERATOR_H
#define ZADANIE2_DATAGENERATOR_H
#include <string>
#include <vector>
#include "DataReader.h"
#include "Algorithms/BAndBBFS.h"
#include "Algorithms/BAndBDFS.h"
#include "Algorithms/BAndBLowestCost.h"

class DataGenerator {
private:
//    std::vector<int> arr = {12}; // Możesz dodać inne wartości w razie potrzeby
    DataReader dataReader;
    BAndBBFS bbfs;
    BAndBDFS bdfs;
    BAndBLowestCost bLowestCost;

    // Funkcja zapisująca czas do pliku CSV
    void saveToCsvFile(std::string fileName, long long time, int n);

    // Funkcja obliczająca czas dla algorytmów, teraz z int** matrix
    long long calculateTime(int algorithm, int** matrix, int n);

    // Funkcja do zwalniania pamięci alokowanej dla int** matrix
    void freeMatrix(int** matrix, int n);

public:
    // Funkcja generująca dane
    void generate(int r,std::vector<int> sizeVertex);
};


#endif //ZADANIE2_DATAGENERATOR_H
