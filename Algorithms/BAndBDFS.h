//
// Created by grons on 06.11.2024.
//

#ifndef ZADANIE2_BANDBDFS_H
#define ZADANIE2_BANDBDFS_H


#include <climits>
#include "../Structurs/Node.h"
#include "../Structurs/Result.h"

class BAndBDFS {
private:
    Node* bestNode;  // Wskaźnik do najlepszego węzła
    int bestCost;    // Najlepszy koszt
public:
    BAndBDFS() : bestNode(nullptr), bestCost(INT_MAX) {} // Inicjalizacja
    ~BAndBDFS(); // Destruktor
    // Algorytm Branch and Bound rozwiązujący problem komiwojażera
    Result branchAndBound(int** dist, int N, int start);
    Result startFromEachVertex(int** dist, int N);
//    int branchAndBound(int** dist, int N,int*& bestPath);
};


#endif //ZADANIE2_BANDBDFS_H
