//
//  BoolMatrix.h
//  AlgorithmsWarshallAndFloyd
//
//  Created by Miranda Myers on 4/13/15.
//  Copyright (c) 2015 Miranda Myers. All rights reserved.
//

#ifndef __AlgorithmsWarshallAndFloyd__BoolMatrix__
#define __AlgorithmsWarshallAndFloyd__BoolMatrix__

#include <stdio.h>


#include <iostream>
using namespace std;

class BoolMatrix
{
public:
    BoolMatrix(bool** adjacencyMatrixIn, int sizeIn);
    ~BoolMatrix();
    
    //Completes one step of Warshall's Algorithm
    void WarshallStep(int k, int i, int j);
    void Warshall();//bool** adjacencyMatrix, bool** transitiveClosure);
    void printMatrix();
    
private:
    //static const int MAX_SIZE = 100;
    int size;
    bool** adjacencyMatrix;
};

#endif /* defined(__AlgorithmsWarshallAndFloyd__BoolMatrix__) */
