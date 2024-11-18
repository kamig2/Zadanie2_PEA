//
// Created by grons on 06.11.2024.
//

#ifndef ZADANIE2_DATAREADER_H
#define ZADANIE2_DATAREADER_H

#include <iostream>
#include <fstream>
#include <random>
#include <stdexcept>

class DataReader {
public:
    int** readFile(const std::string& path, int& size);
    int** generateRandomAsymmetricalData(int n);
    int** generateRandomSymmetricalData(int n);
    void printMatrix(int** matrix, int n);
    void freeMatrix(int** matrix, int n);  // Metoda do zwalniania pamięci
};


#endif //ZADANIE2_DATAREADER_H
