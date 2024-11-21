//
// Created by grons on 05.11.2024.
//

#ifndef ZADANIE2_QUEUE_H
#define ZADANIE2_QUEUE_H

#include "Node.h"

struct Queue {
    Node** nodes;  // Dynamiczna tablica wskaźników na obiekty typu Node
    int front, rear, size;  // Indeksy dla początku (front), końca (rear) oraz maksymalnej pojemności (size)

    // Inicjalizacja kolejki
    void init(int maxSize) {
        nodes = new Node*[maxSize];  // Alokacja dynamiczna tablicy wskaźników o wielkości maxSize
        front = 0;  // Wskaźnik początku kolejki
        rear = 0;   // Wskaźnik końca kolejki
        size = maxSize;  // Maksymalna pojemność kolejki
    }

    // Sprawdzenie, czy kolejka jest pusta
    bool isEmpty() {
        return front == rear;  // Jeśli front == rear, oznacza to, że kolejka nie zawiera elementów
    }

    // Dodanie elementu do kolejki
    void enqueue(Node* node) {
        if (rear >= size) {  // Jeśli wskaźnik rear osiągnie maksymalny rozmiar
            resize(size * 2);  // Zwiększamy rozmiar kolejki, podwajając jej pojemność
        }
        nodes[rear++] = node;  // Umieszczamy element w kolejce i przesuwamy wskaźnik rear
    }

    // Pobranie elementu z kolejki
    Node* dequeue() {
        return nodes[front++];  // Pobieramy element z przodu kolejki i przesuwamy wskaźnik front
    }

    // Zwiększenie rozmiaru kolejki
    void resize(int newSize) {
        Node** newNodes = new Node*[newSize];  // Tworzymy nową tablicę o większym rozmiarze
        int i = 0;  // Indeks do nowej tablicy
        for (int j = front; j < rear; j++) {  // Przepisujemy elementy od front do rear
            newNodes[i++] = nodes[j];
        }
        delete[] nodes;  // Zwolnienie starej tablicy
        nodes = newNodes;  // Przypisanie nowej tablicy jako głównej
        front = 0;  // Aktualizacja wskaźnika front
        rear = i;   // Aktualizacja wskaźnika rear
        size = newSize;  // Ustawienie nowej pojemności
    }

    // Destruktor
    ~Queue() {
        for (int i = front; i < rear; i++) {  // Iterujemy po wszystkich elementach w kolejce
            if (nodes[i] != nullptr) {
                delete nodes[i];  // Zwalniamy pamięć każdego elementu, jeśli nie jest nullptr
            }
        }
        delete[] nodes;  // Zwalniamy tablicę wskaźników
    }
};

#endif //ZADANIE2_QUEUE_H
