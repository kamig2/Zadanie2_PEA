//
// Created by grons on 05.11.2024.
//

#ifndef ZADANIE2_BANDBBFS_H
#define ZADANIE2_BANDBBFS_H

#include <iostream>
#include <climits>
#include "../Structurs/Node.h"
#include "../Structurs/Queue.h"
#include "../Structurs/Result.h"



class BAndBBFS {
public:
    Result branchAndBound(int** dist, int N,int start);
    Result startFromEachVertex(int** dist, int N);

};


#endif //ZADANIE2_BANDBBFS_H
