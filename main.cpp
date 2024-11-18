#include <iostream>
#include "DataReader.h"
#include "Algorithms/BAndBBFS.h"
#include "Algorithms/BoundCalculator.h"
#include "Algorithms/BAndBDFS.h"
#include "Algorithms/BAndBLowestCost.h"
#include "ConfigFileHandler.h"


using namespace  std;
int main() {
    /*DataReader dataReader;
    int size;
    int** matrix;
    matrix = dataReader.readFile("C:\\Users\\grons\\Desktop\\Studia\\5 sem\\PEA\\zadanie2\\sym.txt",size);
//    matrix = dataReader.generateRandomAsymmetricalData(n);
//    dataReader.printMatrix(matrix,3);
    BAndBBFS bbfs;
//    Result result1 = bbfs.branchAndBound(matrix,size,0); //dla macierzy asym
//    Result result1  = bbfs.startFromEachVertex(matrix,size);



    BAndBDFS  bbdfs;

//    Result result = bbdfs.startFromEachVertex(matrix,size);
//    Result result = bbdfs.branchAndBound(matrix,size,0);
//    BoundCalculator::printSolution(result,size);
    *//*cout<< "wynik: " << result<<endl;*//*

    BAndBLowestCost bbLowestCost;
//    Result result1= bbLowestCost.startFromEachVertex(matrix,size);
    Result result2 = bbLowestCost.branchAndBound(matrix,size,0);
//    BoundCalculator::printSolution(result2,size);
//    BoundCalculator::printSolution(result1,size);
    return 0;*/
    ConfigFileHandler configHandler("C:\\Users\\grons\\Desktop\\Studia\\5 sem\\PEA\\zadanie2\\plik_config.cfg");
    configHandler.parseConfig();
    return 0;
}
