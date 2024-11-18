cmake_minimum_required(VERSION 3.23)
project(zadanie2)

set(CMAKE_CXX_STANDARD 23)

add_executable(zadanie2 main.cpp Algorithms/BAndBBFS.cpp Algorithms/BAndBBFS.h Structurs/Node.h Structurs/Queue.h Structurs/Result.h DataReader.cpp DataReader.h Structurs/Stack.h Algorithms/BAndBDFS.cpp Algorithms/BAndBDFS.h Algorithms/BoundCalculator.cpp Algorithms/BoundCalculator.h Algorithms/BAndBLowestCost.cpp Algorithms/BAndBLowestCost.h Structurs/PriorityQueue.h ConfigFileHandler.cpp ConfigFileHandler.h DataGenerator.cpp DataGenerator.h)
