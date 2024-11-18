//
// Created by grons on 09.11.2024.
//

#ifndef ZADANIE2_BANDBLOWESTCOST_H
#define ZADANIE2_BANDBLOWESTCOST_H


#include "../Structurs/Result.h"
#include "../Structurs/Node.h"

class BAndBLowestCost {
public:
    Result branchAndBound(int** dist, int N, int start);   // Główna metoda branch and bound z argumentem start
    Result startFromEachVertex(int** dist, int N);          // Metoda wywołująca branch and bound dla każdego wierzchołka
private:
    int bestCost;
    Node* bestNode;

};


#endif //ZADANIE2_BANDBLOWESTCOST_H
