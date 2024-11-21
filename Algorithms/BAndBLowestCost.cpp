//
// Created by grons on 09.11.2024.
//

#include "BAndBLowestCost.h"
#include "../Structurs/PriorityQueue.h"
#include "BoundCalculator.h"
#include <climits>


Result BAndBLowestCost::branchAndBound(int** dist, int N, int start) {
    PriorityQueue pq(1000);  // Tworzymy kolejkę priorytetową o maksymalnym rozmiarze 1000

    bestCost = INT_MAX;       // Inicjalizujemy najlepszy koszt jako maksymalną wartość
    bestNode = nullptr;       // Wskaźnik na najlepszy węzeł (początkowo brak)

    // Tworzymy korzeń drzewa (węzeł startowy)
    Node* root = new Node(N);
    root->path[0] = start;    // Startowe miasto
    root->cost = 0;           // Początkowy koszt to 0
    root->level = 0;          // Poziom korzenia to 0
    root->bound = BoundCalculator::calculateBound(root, dist, N);  // Obliczamy ograniczenie dolne

    pq.enqueue(root);  // Dodajemy korzeń do kolejki priorytetowej

    while (!pq.isEmpty()) {   // Dopóki kolejka nie jest pusta
        Node* current = pq.dequeue();  // Pobieramy węzeł o najniższym ograniczeniu dolnym

        // Sprawdzenie, czy osiągnęliśmy ostatni poziom drzewa (pełna ścieżka)
        if (current->level == N - 1) {
            int lastToStart = dist[current->path[current->level]][start];  // Koszt powrotu do miasta początkowego
            int totalCost = current->cost + lastToStart;  // Całkowity koszt ścieżki

            // Aktualizacja najlepszego kosztu, jeśli znaleziono lepsze rozwiązanie
            if (totalCost < bestCost) {
                bestCost = totalCost;  // Aktualizacja najlepszego kosztu
                if (bestNode != nullptr) {
                    delete bestNode;  // Zwalniamy pamięć poprzedniego najlepszego węzła
                }
                bestNode = current;  // Zapisujemy nowy najlepszy węzeł
            } else {
                delete current;  // Zwalniamy pamięć, jeśli węzeł nie jest potrzebny
            }
            continue;  // Przechodzimy do następnego węzła w kolejce
        }

        // Rozwijanie dzieci węzła (odwiedzanie kolejnych miast)
        for (int i = 0; i < N; i++) {
            bool alreadyVisited = false;

            // Sprawdzamy, czy miasto `i` zostało już odwiedzone
            for (int j = 0; j <= current->level; j++) {
                if (current->path[j] == i) {  // Jeśli miasto `i` jest na ścieżce
                    alreadyVisited = true;
                    break;
                }
            }

            // Tworzymy nowe dziecko, jeśli miasto nie było odwiedzone
            if (!alreadyVisited && current->level < N - 1) {
                Node* child = new Node(N);  // Tworzymy nowy węzeł dziecka
                for (int j = 0; j <= current->level; j++) {
                    child->path[j] = current->path[j];  // Kopiujemy dotychczasową ścieżkę
                }
                child->level = current->level + 1;  // Zwiększamy poziom dziecka
                child->path[child->level] = i;      // Dodajemy miasto `i` do ścieżki

                // Obliczamy koszt i ograniczenie dla dziecka
                child->cost = current->cost + dist[current->path[current->level]][i];
                child->bound = BoundCalculator::calculateBound(child, dist, N);

                // Dodajemy dziecko do kolejki, jeśli ograniczenie jest mniejsze niż najlepszy koszt
                if (child->bound < bestCost) {
                    pq.enqueue(child);
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

Result BAndBLowestCost::startFromEachVertex(int** dist, int N) {
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


