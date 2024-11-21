//
// Created by grons on 06.11.2024.
//

#include <climits>
#include <iostream>
#include "BoundCalculator.h"


using namespace std;

// Funkcja oblicza dolne ograniczenie (bound) kosztu dla danego węzła
int BoundCalculator::calculateBound(Node *node, int **dist, int N) {
    int bound = node->cost;  // Początkowe ograniczenie to koszt trasy w aktualnym węźle
    bool* visited = new bool[N];  // Alokujemy dynamicznie tablicę odwiedzin
    for (int i = 0; i < N; i++) visited[i] = false;  // Ustawiamy wszystkie miasta jako nieodwiedzone

    // Oznacz miasta, które już znajdują się na trasie
    for (int i = 0; i <= node->level; i++) {
        visited[node->path[i]] = true;  // Miasta na ścieżce oznaczamy jako odwiedzone
    }

    // Przeglądaj wszystkie nieodwiedzone miasta
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {  // Jeśli miasto `i` nie zostało odwiedzone
            int min_cost = INT_MAX;  // Inicjalizujemy minimalny koszt jako nieskończoność
            for (int j = 0; j < N; j++) {
                if (i != j && !visited[j]) {  // Jeśli `j` jest inne niż `i` i nieodwiedzone
                    min_cost = min(min_cost, dist[i][j]);  // Znajdujemy minimalny koszt przejścia z `i` do `j`
                }
            }
            if (min_cost == INT_MAX) {  // Jeśli nie znaleziono kosztu, ustawiamy 0
                min_cost = 0;
            }
            bound += min_cost;  // Dodajemy minimalny koszt do ograniczenia
        }
    }

    delete[] visited;
    return bound;  // Zwracamy obliczone ograniczenie
}

