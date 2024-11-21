//
// Created by grons on 09.11.2024.
//

#ifndef ZADANIE2_PRIORITYQUEUE_H
#define ZADANIE2_PRIORITYQUEUE_H

#include "Node.h"
#include <climits>
#include <iostream>

// Struktura kolejki priorytetowej
struct PriorityQueue {
    Node** heap;   // Tablica dynamiczna przechowująca wskaźniki do węzłów
    int size;      // Bieżący rozmiar kolejki
    int capacity;  // Pojemność kolejki

    // Inicjalizacja kolejki priorytetowej
    PriorityQueue(int cap) {
        capacity = cap;  // Ustawienie początkowej pojemności
        size = 0;        // Początkowy rozmiar kolejki to 0
        heap = new Node*[capacity];  // Alokacja pamięci na kopiec
    }

    // Destruktor kolejki priorytetowej
    ~PriorityQueue() {
        for (int i = 0; i < size; i++) {
            delete heap[i];  // Usuwamy węzły w kolejce
        }
        delete[] heap;  // Zwalniamy pamięć kopca
    }

    // Dodawanie elementu do kolejki priorytetowej
    void enqueue(Node* node) {
        if (size == capacity) {
            resize(); // Zwiększamy rozmiar, gdy kolejka jest pełna
        }

        heap[size] = node;  // Dodajemy nowy element na końcu kopca
        int index = size;   // Ustawiamy indeks na nowy element
        size++;             // Zwiększamy rozmiar kolejki

        heapifyUp(index);  // Przywracamy właściwość kopca od nowego elementu w górę
    }

    // Usuwanie elementu (o najmniejszym koszcie) z kolejki
    Node* dequeue() {
        if (isEmpty()) {    // Jeśli kolejka jest pusta, zwracamy nullptr
            return nullptr;
        }

        Node* minNode = heap[0];       // Najmniejszy element znajduje się na początku kopca
        heap[0] = heap[size - 1];      // Ostatni element przesuwamy na początek
        size--;                        // Zmniejszamy rozmiar kolejki
        heapifyDown(0);                // Przywracamy właściwość kopca od góry w dół

        return minNode;  // Zwracamy węzeł o najmniejszym priorytecie
    }

    // Sprawdzanie, czy kolejka jest pusta
    bool isEmpty() const {
        return size == 0;
    }

    // Funkcja powiększająca tablicę heap, gdy jest pełna
    void resize() {
        capacity *= 2;  // Podwajamy pojemność
        Node** newHeap = new Node*[capacity];  // Tworzymy nową tablicę o większej pojemności

        // Kopiujemy elementy do nowej tablicy
        for (int i = 0; i < size; i++) {
            newHeap[i] = heap[i];
        }

        delete[] heap;  // Zwalniamy starą tablicę
        heap = newHeap; // Przypisujemy nową tablicę
    }

private:
    // Utrzymywanie porządku w kopcu przy dodawaniu elementu
    void heapifyUp(int index) {
        int parentIndex = (index - 1) / 2;  // Indeks rodzica w kopcu
        while (index > 0 && (heap[index]->cost + heap[index]->bound) < (heap[parentIndex]->cost + heap[parentIndex]->bound)) {
            std::swap(heap[index], heap[parentIndex]);  // Zamiana elementu z rodzicem
            index = parentIndex;  // Przechodzimy do rodzica
            parentIndex = (index - 1) / 2;  // Aktualizacja indeksu rodzica
        }
    }

    // Utrzymywanie porządku w kopcu przy usuwaniu elementu
    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;  // Indeks lewego dziecka
        int rightChild = 2 * index + 2; // Indeks prawego dziecka
        int smallest = index;          // Zakładamy, że najmniejszy element jest na pozycji `index`

        // Porównujemy z lewym dzieckiem
        if (leftChild < size && (heap[leftChild]->cost + heap[leftChild]->bound) < (heap[smallest]->cost + heap[smallest]->bound)) {
            smallest = leftChild;
        }
        // Porównujemy z prawym dzieckiem
        if (rightChild < size && (heap[rightChild]->cost + heap[rightChild]->bound) < (heap[smallest]->cost + heap[smallest]->bound)) {
            smallest = rightChild;
        }

        // Jeśli najmniejszy element nie jest w pozycji `index`, zamieniamy i powtarzamy dla dziecka
        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);  // Zamiana elementów
            heapifyDown(smallest);  // Rekurencyjne przywracanie porządku dla dziecka
        }
    }
};

#endif //ZADANIE2_PRIORITYQUEUE_H
