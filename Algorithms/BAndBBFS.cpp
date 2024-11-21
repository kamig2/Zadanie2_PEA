//
// Created by grons on 05.11.2024.
//

#include "BAndBBFS.h"
#include "BoundCalculator.h"
#include <iostream>

using namespace std;

// Główna funkcja implementująca algorytm Branch and Bound
Result BAndBBFS::branchAndBound(int** dist, int N, int start) {
    Queue queue;
    queue.init(1000);  // Inicjalizujemy kolejkę dla 1000 elementów

    int bestCost = INT_MAX;  // Początkowo najlepszy koszt ustawiamy na nieskończoność
    Node* bestNode = nullptr;  // Wskaźnik na najlepszy węzeł, początkowo pusty

    // Tworzymy i inicjalizujemy węzeł korzenia
    Node* root = new Node(N);  // Dynamicznie alokujemy pamięć dla korzenia
    root->path[0] = start;  // Rozpoczynamy trasę od podanego miasta startowego
    root->cost = 0;  // Koszt początkowy to 0
    root->level = 0;  // Korzeń jest na poziomie 0
    root->bound = BoundCalculator::calculateBound(root, dist, N);  // Obliczamy ograniczenie dolne dla korzenia

    queue.enqueue(root);  // Dodajemy korzeń do kolejki

    // Pętla wykonująca przeszukiwanie drzewa
    while (!queue.isEmpty()) {
        Node* current = queue.dequeue();  // Pobieramy następny węzeł do przetworzenia z kolejki

        // Jeśli jesteśmy na ostatnim poziomie drzewa, sprawdzamy pełne rozwiązanie
        if (current->level == N - 1) {
            int lastToStart = dist[current->path[current->level]][start]; // Koszt powrotu do miasta początkowego
            int totalCost = current->cost + lastToStart;

            // Jeśli całkowity koszt jest lepszy, aktualizujemy najlepsze rozwiązanie
            if (totalCost < bestCost) {
                bestCost = totalCost;
                if (bestNode != nullptr) {
                    delete bestNode;  // Zwalniamy pamięć poprzedniego najlepszego węzła
                }
                bestNode = current;  // Ustawiamy obecny węzeł jako najlepszy
            } else {
                delete current;  // Zwalniamy pamięć węzła, jeśli nie jest najlepszy
                current = nullptr;
            }
            continue;  // Przechodzimy do kolejnej iteracji
        }

        // Rozwijamy dzieci bieżącego węzła
        for (int i = 0; i < N; i++) {
            bool alreadyVisited = false;

            // Sprawdzamy, czy miasto `i` już zostało odwiedzone w bieżącej ścieżce
            for (int j = 0; j <= current->level; j++) {
                if (current->path[j] == i) {
                    alreadyVisited = true;
                    break;
                }
            }

            if (!alreadyVisited && current->level < N - 1) {
                // Tworzymy nowe dziecko dynamicznie
                Node* child = new Node(N);
                for (int j = 0; j <= current->level; j++) {
                    child->path[j] = current->path[j];  // Kopiujemy bieżącą ścieżkę do dziecka
                }
                child->level = current->level + 1;  // Zwiększamy poziom o 1
                child->path[child->level] = i;  // Dodajemy miasto `i` do ścieżki

                // Sprawdzamy, czy indeksy są w zakresie
                if (current->path[current->level] >= N || i >= N) {
                    delete child;  // Zwalniamy pamięć, jeśli indeksy są poza zakresem
                    continue;  // Pomijamy ten węzeł
                }

                // Obliczamy koszt i ograniczenie dla dziecka
                child->cost = current->cost + dist[current->path[current->level]][i];
                child->bound = BoundCalculator::calculateBound(child, dist, N);

                // Jeśli ograniczenie dziecka jest obiecujące, dodajemy je do kolejki
                if (child->bound < bestCost) {
                    queue.enqueue(child);
                } else {
                    delete child;  // Zwalniamy pamięć, jeśli węzeł nie spełnia warunku
                }
            }
        }
        delete current;  // Zwalniamy pamięć przetworzonego węzła
    }

    // Przygotowujemy wynik
    Result result;
    result.cost = bestCost;

    if (bestNode != nullptr) {
        result.path = new int[N + 1];  // Alokujemy pamięć na ścieżkę, włącznie z powrotem do miasta startowego
        for (int i = 0; i <= bestNode->level; i++) {
            result.path[i] = bestNode->path[i];  // Kopiujemy najlepszą ścieżkę
        }
        result.path[bestNode->level + 1] = start;  // Dodajemy powrót do miasta początkowego
        delete bestNode;  // Zwalniamy pamięć najlepszego węzła
    } else {
        result.path = nullptr;  // Jeśli nie znaleziono rozwiązania, ścieżka jest pusta
    }

    return result;  // Zwracamy wynik
}

// Funkcja uruchamiająca algorytm dla każdego miasta jako punktu startowego
Result BAndBBFS::startFromEachVertex(int **dist, int N) {
    Result bestResult;
    bestResult.cost = INT_MAX;
    bestResult.path = nullptr;

    // Iterujemy po wszystkich miastach jako punktach startowych
    for (int i = 0; i < N; i++) {
        Result currentResult = branchAndBound(dist, N, i);

        // Jeśli obecny wynik jest lepszy, aktualizujemy najlepszy wynik
        if (currentResult.cost < bestResult.cost) {
            if (bestResult.path != nullptr) {
                delete[] bestResult.path;  // Zwalniamy pamięć poprzedniej najlepszej ścieżki
            }
            bestResult.cost = currentResult.cost;
            bestResult.path = currentResult.path;
        } else {
            delete[] currentResult.path;  // Zwalniamy pamięć, jeśli ścieżka nie jest najlepsza
        }
    }
    return bestResult;  // Zwracamy najlepszy wynik
}


