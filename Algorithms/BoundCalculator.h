//
// Created by grons on 06.11.2024.
//

#ifndef ZADANIE2_BOUNDCALCULATOR_H
#define ZADANIE2_BOUNDCALCULATOR_H


#include "../Structurs/Node.h"
#include "../Structurs/Result.h"

class BoundCalculator {
public:
    static int  calculateBound(Node* node, int** dist, int N);
//    static void printSolution(const Result& result, int size);

};


#endif //ZADANIE2_BOUNDCALCULATOR_H
