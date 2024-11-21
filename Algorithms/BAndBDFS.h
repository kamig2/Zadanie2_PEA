//
// Created by grons on 06.11.2024.
//

#ifndef ZADANIE2_BANDBDFS_H
#define ZADANIE2_BANDBDFS_H


#include <climits>
#include "../Structurs/Node.h"
#include "../Structurs/Result.h"

class BAndBDFS {
public:
    Result branchAndBound(int** dist, int N, int start);
    Result startFromEachVertex(int** dist, int N);
};


#endif //ZADANIE2_BANDBDFS_H
