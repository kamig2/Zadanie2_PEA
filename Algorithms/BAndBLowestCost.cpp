//
// Created by grons on 09.11.2024.
//

#include "BAndBLowestCost.h"
#include "../Structurs/PriorityQueue.h"
#include "BoundCalculator.h"
#include <climits>


Result BAndBLowestCost::branchAndBound(int** dist, int N, int start) {
    PriorityQueue pq(1000);

    bestCost = INT_MAX;
    bestNode = nullptr;

    Node* root = new Node(N);
    root->path[0] = start;
    root->cost = 0;
    root->level = 0;
    root->bound = BoundCalculator::calculateBound(root, dist, N);

    pq.enqueue(root);

    while (!pq.isEmpty()) {
        Node* current = pq.dequeue();

        if (current->level == N - 1) {
            int last_to_start = dist[current->path[current->level]][start];
            int total_cost = current->cost + last_to_start;

            if (total_cost < bestCost) {
                bestCost = total_cost;
                if (bestNode != nullptr) {
                    delete bestNode;
                }
                bestNode = current;
            } else {
                delete current;
            }
            continue;
        }

        for (int i = 0; i < N; i++) {
            bool alreadyVisited = false;

            for (int j = 0; j <= current->level; j++) {
                if (current->path[j] == i) {
                    alreadyVisited = true;
                    break;
                }
            }

            if (!alreadyVisited && current->level < N - 1) {
                Node* child = new Node(N);
                for (int j = 0; j <= current->level; j++) {
                    child->path[j] = current->path[j];
                }
                child->level = current->level + 1;
                child->path[child->level] = i;

                child->cost = current->cost + dist[current->path[current->level]][i];
                child->bound = BoundCalculator::calculateBound(child, dist, N);

                if (child->bound < bestCost) {
                    pq.enqueue(child);
                } else {
                    delete child;
                }
            }
        }

        delete current;
    }

    Result result;
    result.cost = bestCost;

    if (bestNode != nullptr) {
        result.path = new int[N + 1];
        for (int i = 0; i <= bestNode->level; i++) {
            result.path[i] = bestNode->path[i];
        }
        result.path[bestNode->level + 1] = start;
        delete bestNode;
    } else {
        result.path = nullptr;
    }

    return result;
}

Result BAndBLowestCost::startFromEachVertex(int** dist, int N) {
    Result bestResult;
    bestResult.cost = INT_MAX;
    bestResult.path = nullptr;

    for (int start = 0; start < N; start++) {
        Result currentResult = branchAndBound(dist, N, start);

        if (currentResult.cost < bestResult.cost) {
            if (bestResult.path != nullptr) {
                delete[] bestResult.path;
            }
            bestResult = currentResult;
        } else {
            delete[] currentResult.path;
        }
    }

    return bestResult;
}


