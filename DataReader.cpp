//
// Created by grons on 06.11.2024.
//

#include "DataReader.h"

// Metoda do odczytu danych z pliku
int** DataReader::readFile(const std::string& path, int& size) {
    std::ifstream file(path);  // Otwiera plik do odczytu
    if (!file) {
        throw std::runtime_error("Nie można otworzyć pliku: " + path);
    }

    file >> size;  // Odczytuje rozmiar macierzy
    int** matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            file >> matrix[i][j];  // Odczyt wartości do macierzy
        }
    }

    return matrix;
}

// Metoda do generowania losowych danych asymetrycznych
int** DataReader::generateRandomAsymmetricalData(int n) {
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }

    int min = 1;
    int max = 100;
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(min, max);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                matrix[i][j] = -1;  // Ustawia wartość -1 dla elementów na przekątnej
            } else {
                matrix[i][j] = distribution(generator);  // Generuje losową wartość
            }
        }
    }
    return matrix;
}

// Metoda do generowania losowych danych symetrycznych
int** DataReader::generateRandomSymmetricalData(int n) {
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }

    int min = 1;
    int max = 100;
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(min, max);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int randomValue = distribution(generator);
            matrix[i][j] = randomValue;  // Wartość nad przekątną
            matrix[j][i] = randomValue;  // Symetryczna wartość pod przekątną
        }
        matrix[i][i] = -1;  // Diagonalne elementy ustawione na -1
    }

    return matrix;
}

// Metoda do wyświetlania macierzy
void DataReader::printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Metoda do zwalniania pamięci
void DataReader::freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
