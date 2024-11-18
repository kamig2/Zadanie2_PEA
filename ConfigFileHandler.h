//
// Created by grons on 13.11.2024.
//

#ifndef ZADANIE2_CONFIGFILEHANDLER_H
#define ZADANIE2_CONFIGFILEHANDLER_H

#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include "DataGenerator.h"

class ConfigFileHandler {
public:
    // Konstruktor klasy, przyjmuje nazwę pliku konfiguracyjnego
    ConfigFileHandler(const std::string &filename);

    // Funkcja odpowiedzialna za parsowanie pliku konfiguracyjnego
    void parseConfig();

    void printSolution(const Result& result, int size);
private:
    std::string filename;
    DataGenerator generator;
    DataReader dataReader;
    BAndBBFS bbfs;
    BAndBDFS bdfs;
    BAndBLowestCost bLowestCost;
};


#endif //ZADANIE2_CONFIGFILEHANDLER_H
