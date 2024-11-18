//
// Created by grons on 06.11.2024.
//

#include <iostream>
#include "BAndBDFS.h"
#include "BoundCalculator.h"
#include "../Structurs/Stack.h"

using namespace std;
BAndBDFS::~BAndBDFS() {
    if (bestNode != nullptr) {
        delete bestNode; // Zwalniamy pamięć najlepszego węzła
    }
}

Result BAndBDFS::branchAndBound(int** dist, int N, int start) {
    Stack stack;
    stack.init(1000);

    int bestCost = INT_MAX;
    Node* bestNode = nullptr;

    Node* root = new Node(N);
    root->path[0] = start;  // Ustawiamy startowy wierzchołek
    root->cost = 0;
    root->level = 0;
    root->bound = BoundCalculator::calculateBound(root, dist, N);

    stack.push(root); // Dodajemy korzeń na stos

    while (!stack.isEmpty()) {
        Node* current = stack.pop();  // Pobieramy węzeł ze stosu

        // Jeśli jesteśmy na ostatnim poziomie, sprawdzamy rozwiązanie
        if (current->level == N - 1) {
            int last_to_start = dist[current->path[current->level]][start]; // Powrót do miasta 0
            int total_cost = current->cost + last_to_start;

            if (total_cost < bestCost) {
                bestCost = total_cost;
                if (bestNode != nullptr) {
                    delete bestNode;  // Zwalniamy pamięć poprzedniego najlepszego węzła
                }
                bestNode = current;  // Zapisujemy nowy najlepszy węzeł
            } else {
                delete current;  // Zwalniamy pamięć niewykorzystanego węzła
                current = nullptr;
            }
            continue;
        }

        // Rozwijanie dzieci węzła
        for (int i = 0; i < N; i++) {
            bool alreadyVisited = false;

            // Sprawdź, czy miasto już zostało odwiedzone
            for (int j = 0; j <= current->level; j++) {
                if (current->path[j] == i) {
                    alreadyVisited = true;
                    break;
                }
            }

            if (!alreadyVisited && current->level < N - 1) {
                Node* child = new Node(N);  // Dynamicznie alokujemy nowy węzeł
                for (int j = 0; j <= current->level; j++) {
                    child->path[j] = current->path[j];  // Kopiujemy dotychczasową ścieżkę
                }
                child->level = current->level + 1;
                child->path[child->level] = i;

                // Sprawdzamy, czy indeksy są w zakresie
                if (current->path[current->level] >= N || i >= N) {
                    delete child;
                    continue;  // Pomijamy ten węzeł, jeśli indeksy są poza zakresem
                }

                child->cost = current->cost + dist[current->path[current->level]][i];
                child->bound = BoundCalculator::calculateBound(child, dist, N);

                // Jeśli ograniczenie jest mniejsze niż najlepszy koszt, dodajemy do stosu
                if (child->bound < bestCost) {
                    stack.push(child);
                } else {
                    delete child;  // Zwalniamy pamięć węzła, jeśli nie spełnia warunku
                }
            }
        }

        delete current;  // Zwalniamy pamięć przetworzonego węzła
    }

    Result result;
    result.cost = bestCost;

    if (bestNode != nullptr) {
        result.path = new int[N + 1];  // Alokacja dla ścieżki z powrotem do miasta 0
        for (int i = 0; i <= bestNode->level; i++) {
            result.path[i] = bestNode->path[i];  // Kopiujemy najlepszą ścieżkę
        }
        result.path[bestNode->level + 1] = 0;  // Dodajemy powrót do miasta 0
        delete bestNode;  // Usuwamy bestNode po skopiowaniu ścieżki
    } else {
        result.path = nullptr;  // Jeśli nie znaleziono ścieżki
    }

    return result;  // Zwracamy wynik
}

Result BAndBDFS::startFromEachVertex(int** dist, int N) {
    Result bestResult;
    bestResult.cost = INT_MAX;
    bestResult.path = nullptr;

    // Wywołanie branch and bound dla każdego wierzchołka początkowego
    for (int start = 0; start < N; start++) {
        Result currentResult = branchAndBound(dist, N, start);  // Wywołanie z wierzchołkiem początkowym `start`

        // Aktualizacja najlepszego wyniku, jeśli znaleziono lepszą trasę
        if (currentResult.cost < bestResult.cost) {
            // Zwalniamy pamięć poprzedniego najlepszego wyniku
            if (bestResult.path != nullptr) {
                delete[] bestResult.path;
            }
            bestResult = currentResult;
        } else {
            // Jeśli wynik nie jest lepszy, zwalniamy pamięć dla bieżącej trasy
            delete[] currentResult.path;
        }
    }

    return bestResult;
}
