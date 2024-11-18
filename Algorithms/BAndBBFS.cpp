//
// Created by grons on 05.11.2024.
//

#include "BAndBBFS.h"
#include "BoundCalculator.h"
#include <iostream>

using namespace std;

BAndBBFS::~BAndBBFS() {
    if (bestNode != nullptr) {
        delete bestNode; // Zwalniamy pamięć najlepszego węzła
    }
}

/*Result BAndBBFS::branchAndBound(int** dist, int N, int start) {
    Queue queue;
    queue.init(1000);  // Inicjalizujemy kolejkę dla 1000 elementów

    int bestCost = INT_MAX;
    Node* bestNode = nullptr;

    Node* root = new Node(N);  // Alokacja dynamiczna dla korzenia
    root->path[0] = start;  // Zaczynamy od miasta start
    root->cost = 0;
    root->level = 0;
    root->bound = BoundCalculator::calculateBound(root, dist, N);

//    cout << "Root node created: " << root << ", bound: " << root->bound << endl;

    queue.enqueue(root);

    while (!queue.isEmpty()) {
        Node* current = queue.dequeue();

//        cout << "Pobieranie węzła z kolejki: " << current << ", level: " << current->level << ", cost: " << current->cost << ", bound: " << current->bound << endl;

        // Jeśli jesteśmy na ostatnim poziomie, sprawdzamy rozwiązanie
        if (current->level == N - 1) {
            int last_to_start = dist[current->path[current->level]][0]; // Powrót do miasta 0
            int total_cost = current->cost + last_to_start;

//            cout << "Sprawdzanie rozwiązania, total_cost: " << total_cost << endl;

            if (total_cost < bestCost) {
                bestCost = total_cost;
                if (bestNode != nullptr) {
//                    cout << "Zwalnianie pamięci poprzedniego najlepszego węzła: " << bestNode << endl;
                    delete bestNode;  // Zwalniamy pamięć poprzedniego najlepszego węzła
                }
                bestNode = current;  // Zapisujemy nowy najlepszy węzeł
//                cout << "Aktualizacja najlepszego węzła: " << bestNode << ", koszt: " << bestCost << endl;
            } else {
//                cout << "Odrzucenie węzła: " << current << " z kosztami większymi niż najlepszy: " << total_cost << endl;
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

//            cout << "Rozważanie miasta " << i << ", już odwiedzone? " << (alreadyVisited ? "Tak" : "Nie") << endl;

            if (!alreadyVisited && current->level < N - 1) {
                Node* child = new Node(N);  // Dynamicznie alokujemy nowy węzeł
                for (int j = 0; j <= current->level; j++) {
                    child->path[j] = current->path[j];  // Kopiujemy dotychczasową ścieżkę
                }
                child->level = current->level + 1;
                child->path[child->level] = i;

//                cout << "Tworzenie dziecka: " << child << " z level: " << child->level << endl;

                // Sprawdzamy, czy indeksy są w zakresie
                if (current->path[current->level] >= N || i >= N) {
//                    cout << "Dziecko " << child << " ma niepoprawne indeksy, pomijamy." << endl;
                    delete child;
                    continue;  // Pomijamy ten węzeł, jeśli indeksy są poza zakresem
                }

                child->cost = current->cost + dist[current->path[current->level]][i];
//                cout<<"cost: "<< child->cost<<endl;
                child->bound = BoundCalculator::calculateBound(child, dist, N);

//                cout << "Obliczono koszt dla dziecka: " << child->cost << ", bound: " << child->bound << endl;

                // Jeśli ograniczenie jest mniejsze niż najlepszy koszt, dodajemy do kolejki
                if (child->bound < bestCost) {
//                    cout << "Dziecko " << child << " dodane do kolejki." << endl;
                    queue.enqueue(child);
                } else {
//                    cout << "Dziecko " << child << " odrzucone z powodu złego bound." << endl;
                    delete child;  // Zwalniamy pamięć węzła, jeśli nie spełnia warunku
                }
            }
        }

//        cout << "Zwalnianie pamięci przetworzonego węzła: " << current << endl;
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
//        cout << "Najlepsza ścieżka została skopiowana. Zwalniamy pamięć najlepszego węzła." << endl;
        delete bestNode;  // Usuwamy bestNode po skopiowaniu ścieżki
    } else {
        result.path = nullptr;  // Jeśli nie znaleziono ścieżki
    }

//    cout << "Zwracamy wynik. Minimalny koszt: " << result.cost << endl;
    return result;  // Zwracamy wynik
}

Result BAndBBFS::startFromEachVertex(int **dist, int N) {
    Result bestResult;
    bestResult.cost = INT_MAX;
    for(int i = 0;i<N;i++){
        Result currentResult = branchAndBound(dist,N,i);
        if (currentResult.cost<bestResult.cost){
            bestResult.cost = currentResult.cost;
            bestResult.path = currentResult.path;
        }
    }
    return bestResult;
}*/

Result BAndBBFS::branchAndBound(int** dist, int N, int start) {
    Queue queue;
    queue.init(1000);  // Inicjalizujemy kolejkę dla 1000 elementów

    int bestCost = INT_MAX;
    Node* bestNode = nullptr;

    Node* root = new Node(N);  // Alokacja dynamiczna dla korzenia
    root->path[0] = start;  // Zaczynamy od miasta start
    root->cost = 0;
    root->level = 0;
    root->bound = BoundCalculator::calculateBound(root, dist, N);

    queue.enqueue(root);

    while (!queue.isEmpty()) {
        Node* current = queue.dequeue();

        // Jeśli jesteśmy na ostatnim poziomie, sprawdzamy rozwiązanie
        if (current->level == N - 1) {
            int last_to_start = dist[current->path[current->level]][start]; // Powrót do miasta start
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

                // Jeśli ograniczenie jest mniejsze niż najlepszy koszt, dodajemy do kolejki
                if (child->bound < bestCost) {
                    queue.enqueue(child);
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
        result.path = new int[N + 1];  // Alokacja dla ścieżki z powrotem do miasta start
        for (int i = 0; i <= bestNode->level; i++) {
            result.path[i] = bestNode->path[i];  // Kopiujemy najlepszą ścieżkę
        }
        result.path[bestNode->level + 1] = start;  // Dodajemy powrót do miasta start
        delete bestNode;  // Usuwamy bestNode po skopiowaniu ścieżki
    } else {
        result.path = nullptr;  // Jeśli nie znaleziono ścieżki
    }

    return result;  // Zwracamy wynik
}

Result BAndBBFS::startFromEachVertex(int **dist, int N) {
    Result bestResult;
    bestResult.cost = INT_MAX;
    bestResult.path = nullptr;

    for (int i = 0; i < N; i++) {
        Result currentResult = branchAndBound(dist, N, i);

        if (currentResult.cost < bestResult.cost) {
            if (bestResult.path != nullptr) {
                delete[] bestResult.path;  // Zwalniamy pamięć poprzedniej najlepszej ścieżki
            }
            bestResult.cost = currentResult.cost;
            bestResult.path = currentResult.path;
        } else {
            delete[] currentResult.path;  // Zwalniamy pamięć ścieżki, jeśli nie jest najlepsza
        }
    }
    return bestResult;
}


