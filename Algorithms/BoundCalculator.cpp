//
// Created by grons on 06.11.2024.
//

#include <climits>
#include <algorithm>
#include <iostream>
#include "BoundCalculator.h"
#include "../Structurs/Result.h"

using namespace std;

int BoundCalculator::calculateBound(Node *node, int **dist, int N) {
    int bound = node->cost;
    bool* visited = new bool[N];  // Alokujemy dynamicznie tablicę odwiedzin
    for (int i = 0; i < N; i++) visited[i] = false;

    // Oznacz miasta już odwiedzone
    for (int i = 0; i <= node->level; i++) {
        visited[node->path[i]] = true;
    }

    // Dodaj minimalny koszt krawędzi wychodzących z nieodwiedzonych miast
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            int min_cost = INT_MAX;
            for (int j = 0; j < N; j++) {
                if (i != j && !visited[j]) {
                    min_cost = min(min_cost, dist[i][j]);
                }
            }
            if(min_cost == INT_MAX){
                min_cost = 0;
            }
            bound += min_cost;
        }
    }

    delete[] visited;  // Zwalniamy pamięć tablicy odwiedzin
    return bound;
}

//void BoundCalculator::printSolution(const Result& result, int size) {
//    if (result.path != nullptr) {
//        cout << "Najlepsza trasa: ";
//
//        // Używamy size do iterowania po ścieżce
//        for (int i = 0; i < size; i++) {
//            cout << result.path[i] << " -> ";
//        }
//
//        cout << result.path[0] << endl; // Powrót do miasta startowego
//        cout << "Minimalny koszt: " << result.cost << endl;
//    } else {
//        cout << "Brak znalezionego rozwiązania." << endl;
//    }
//}