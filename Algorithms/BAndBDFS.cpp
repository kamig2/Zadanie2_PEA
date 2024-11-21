//
// Created by grons on 06.11.2024.
//

#include <iostream>
#include "BAndBDFS.h"
#include "BoundCalculator.h"
#include "../Structurs/Stack.h"

using namespace std;
Result BAndBDFS::branchAndBound(int** dist, int N, int start) {
    Stack stack;  // Tworzymy stos do implementacji DFS
    stack.init(1000);  // Inicjalizujemy stos z maksymalnym rozmiarem 1000 elementów

    int bestCost = INT_MAX;// Początkowo najlepszy koszt ustawiamy na nieskończoność
    Node* bestNode = nullptr;  // Wskaźnik na najlepszy węzeł, początkowo pusty

    // Tworzymy korzeń drzewa
    Node* root = new Node(N);
    root->path[0] = start;  // Ustawiamy wierzchołek początkowy
    root->cost = 0;         // Koszt początkowy to 0
    root->level = 0;        // Poziom korzenia to 0
    root->bound = BoundCalculator::calculateBound(root, dist, N);  // Obliczamy dolne ograniczenie

    stack.push(root);  // Dodajemy korzeń na stos

    while (!stack.isEmpty()) {  // Przeszukiwanie w głąb dopóki stos nie jest pusty
        Node* current = stack.pop();  // Pobieramy węzeł ze stosu

        // Sprawdzenie, czy osiągnęliśmy ostatni poziom (pełna ścieżka)
        if (current->level == N - 1) {
            int lastToStart = dist[current->path[current->level]][start];  // Koszt powrotu do miasta początkowego
            int totalCost = current->cost + lastToStart;  // Całkowity koszt ścieżki

            // Aktualizujemy najlepszy koszt, jeśli znaleziono lepsze rozwiązanie
            if (totalCost < bestCost) {
                bestCost = totalCost;  // Aktualizacja najlepszego kosztu
                if (bestNode != nullptr) {
                    delete bestNode;  // Zwalniamy pamięć poprzedniego najlepszego węzła
                }
                bestNode = current;  // Zapisujemy nowy najlepszy węzeł
            } else {
                delete current;  // Zwalniamy pamięć, jeśli węzeł nie jest potrzebny
                current = nullptr;
            }
            continue;  // Przechodzimy do następnej iteracji
        }

        // Rozwijamy dzieci węzła (odwiedzamy kolejne miasta)
        for (int i = 0; i < N; i++) {
            bool alreadyVisited = false;

            // Sprawdzamy, czy miasto `i` zostało już odwiedzone
            for (int j = 0; j <= current->level; j++) {
                if (current->path[j] == i) {  // Jeśli miasto `i` jest na ścieżce
                    alreadyVisited = true;
                    break;
                }
            }

            if (!alreadyVisited && current->level < N - 1) {  // Jeśli miasto nie zostało odwiedzone
                Node* child = new Node(N);  // Tworzymy nowy węzeł dziecka
                for (int j = 0; j <= current->level; j++) {
                    child->path[j] = current->path[j];  // Kopiujemy dotychczasową ścieżkę
                }
                child->level = current->level + 1;  // Zwiększamy poziom dziecka
                child->path[child->level] = i;     // Dodajemy miasto `i` do ścieżki

                // Sprawdzamy poprawność indeksów
                if (current->path[current->level] >= N || i >= N) {
                    delete child;  // Zwalniamy pamięć węzła, jeśli indeksy są niepoprawne
                    continue;  // Przechodzimy do kolejnego miasta
                }

                // Obliczamy koszt i ograniczenie dla dziecka
                child->cost = current->cost + dist[current->path[current->level]][i];
                child->bound = BoundCalculator::calculateBound(child, dist, N);

                // Dodajemy dziecko na stos, jeśli ograniczenie jest obiecujące
                if (child->bound < bestCost) {
                    stack.push(child);
                } else {
                    delete child;  // Zwalniamy pamięć dziecka, jeśli nie spełnia warunku
                }
            }
        }

        delete current;  // Zwalniamy pamięć przetworzonego węzła
    }

    // Przygotowanie wyniku końcowego
    Result result;
    result.cost = bestCost;

    if (bestNode != nullptr) {  // Jeśli znaleziono najlepszy węzeł
        result.path = new int[N + 1];  // Alokujemy pamięć na pełną trasę
        for (int i = 0; i <= bestNode->level; i++) {
            result.path[i] = bestNode->path[i];  // Kopiujemy ścieżkę
        }
        result.path[bestNode->level + 1] = start;  // Dodajemy powrót do miasta startowego
        delete bestNode;  // Zwalniamy pamięć najlepszego węzła
    } else {
        result.path = nullptr;  // Jeśli nie znaleziono rozwiązania
    }

    return result;  // Zwracamy najlepszy wynik
}

Result BAndBDFS::startFromEachVertex(int** dist, int N) {
    Result bestResult;
    bestResult.cost = INT_MAX;
    bestResult.path = nullptr;

    // Wywołanie algorytmu dla każdego wierzchołka początkowego
    for (int start = 0; start < N; start++) {
        Result currentResult = branchAndBound(dist, N, start);  // Rozpoczęcie z wierzchołka `start`

        // Aktualizacja najlepszego wyniku
        if (currentResult.cost < bestResult.cost) {
            if (bestResult.path != nullptr) {  // Zwalniamy pamięć poprzedniego wyniku
                delete[] bestResult.path;
            }
            bestResult = currentResult;  // Zapisujemy lepszy wynik
        } else {
            delete[] currentResult.path;  // Zwalniamy pamięć ścieżki, jeśli nie jest najlepsza
        }
    }

    return bestResult;  // Zwracamy najlepszy wynik
}





