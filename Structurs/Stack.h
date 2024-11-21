//
// Created by grons on 06.11.2024.
//

#ifndef ZADANIE2_STACK_H
#define ZADANIE2_STACK_H

#include "Node.h"

//Struktura stosu do przeszukiwania w głąb (DFS)
struct Stack {
    Node** nodes;  //Dynamiczna tablica wskaźników na obiekty typu Node
    int top, size; // top wskazuje na szczyt stosu, a size to maksymalna pojemność stosu

    // Inicjalizacja stosu
    void init(int maxSize) {
        nodes = new Node*[maxSize];  //Alokacja dynamicznej tablicy wskaźników o rozmiarze maxSize
        top = -1;  //Ustawienie wskaźnika top na -1 oznacza, że stos jest pusty
        size = maxSize;  //Ustawienie maksymalnej pojemności stosu
    }

    //Sprawdzenie, czy stos jest pusty
    bool isEmpty() {
        return top == -1;  //Stos jest pusty, jeśli wskaźnik top wynosi -1
    }

    //Dodanie elementu do stosu
    void push(Node* node) {
        if (top < size - 1) {  //Jeśli jest miejsce na stosie
            nodes[++top] = node;  //Umieszczamy element na szczycie stosu i przesuwamy wskaźnik top
        } else {
            //Jeśli stos jest pełny, zwiększamy jego rozmiar
            resize(size * 2);  //Zwiększamy rozmiar stosu, podwajając jego pojemność
            nodes[++top] = node;  //Po powiększeniu dodajemy element
        }
    }

    //Pobranie elementu ze stosu
    Node* pop() {
        return nodes[top--];  //Pobieramy element ze szczytu stosu i przesuwamy wskaźnik `top` w dół
    }

    //Powiększenie rozmiaru stosu
    void resize(int newSize) {
        Node** newNodes = new Node*[newSize];  //Tworzymy nową tablicę wskaźników o większej pojemności
        for (int i = 0; i <= top; i++) {  //Kopiujemy istniejące elementy do nowej tablicy
            newNodes[i] = nodes[i];
        }
        delete[] nodes;  //Usuwamy starą tablicę wskaźników
        nodes = newNodes;  // rzypisujemy nową tablicę do stosu
        size = newSize;  //Aktualizujemy pojemność stosu
    }

    // Destruktor
    ~Stack() {
        for (int i = 0; i <= top; i++) {  // Iterujemy po wszystkich elementach na stosie
            delete nodes[i];  // Usuwamy obiekty wskazywane przez tablicę wskaźników
        }
        delete[] nodes;  // Zwalniamy pamięć zajmowaną przez tablicę wskaźników
    }
};



#endif //ZADANIE2_STACK_H
