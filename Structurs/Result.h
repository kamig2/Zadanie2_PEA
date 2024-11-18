//
// Created by grons on 06.11.2024.
//

#ifndef ZADANIE2_RESULT_H
#define ZADANIE2_RESULT_H

#include <climits>

struct Result {
    int cost;  // Najlepszy koszt
    int* path; // Najlepsza ścieżka
    Result() : cost(INT_MAX), path(nullptr) {} // Inicjalizacja
};

#endif //ZADANIE2_RESULT_H
