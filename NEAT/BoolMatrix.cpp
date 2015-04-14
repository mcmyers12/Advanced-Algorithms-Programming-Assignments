//
//  BoolMatrix.cpp
//  AlgorithmsWarshallAndFloyd
//
//  Created by Miranda Myers on 4/13/15.
//  Copyright (c) 2015 Miranda Myers. All rights reserved.
//

#include "BoolMatrix.h"


#include "BoolMatrix.h"

BoolMatrix::BoolMatrix(bool** adjacencyMatrixIn, int sizeIn)
{
    adjacencyMatrix = adjacencyMatrixIn;
    size = sizeIn;
}


BoolMatrix::~BoolMatrix()
{
    
}

//R(k)[i, j] ← R(k−1)[i, j] or (R(k−1)[i, k] and R(k−1)[k, j])
//Completes one step of Warshall's Algorithm
void BoolMatrix::WarshallStep(int k, int i, int j)
{
    adjacencyMatrix[i][j] = adjacencyMatrix[i][j] || (adjacencyMatrix[i][k] && adjacencyMatrix[i][k]);
}


/*
 ALGORITHM Warshall(A[1..n, 1..n])
 //Implements Warshall’s algorithm for computing the transitive closure
 //Input: The adjacency matrix A of a digraph with n vertices //Output: The transitive closure of the digraph
 R(0) ← A
 for k ← 1 to n do
 for i ← 1 to n do
 forj ←1tondo
 R(k)[i, j] ← R(k−1)[i, j] or (R(k−1)[i, k] and R(k−1)[k, j]) return R(n)
 */
void BoolMatrix::Warshall()//bool** adjacencyMatrix, bool** transitiveClosure)
{
    printMatrix();
    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                WarshallStep(k, i, j);
                
            }
        }
        printMatrix();
    }
    //transitiveClosure = adjacencyMatrix;
}

void BoolMatrix::printMatrix()
{
    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            cout << adjacencyMatrix[k][i] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    bool **adjacencyMatrix;
    adjacencyMatrix = new bool*[4]; // dynamic `array (size 4) of pointers to int`
    
    for (int i = 0; i < 4; ++i)
    {
        adjacencyMatrix[i] = new bool[4];
    }
    
    adjacencyMatrix[0][0] = 0;
    adjacencyMatrix[0][1] = 1;
    adjacencyMatrix[0][2] = 0;
    adjacencyMatrix[0][3] = 0;
    adjacencyMatrix[1][0] = 0;
    adjacencyMatrix[1][1] = 0;
    adjacencyMatrix[1][2] = 0;
    adjacencyMatrix[1][3] = 1;
    adjacencyMatrix[2][0] = 0;
    adjacencyMatrix[2][1] = 0;
    adjacencyMatrix[2][2] = 0;
    adjacencyMatrix[2][3] = 0;
    adjacencyMatrix[3][0] = 1;
    adjacencyMatrix[3][1] = 0;
    adjacencyMatrix[3][2] = 1;
    adjacencyMatrix[3][3] = 0;
    
    


BoolMatrix boolMatrix(adjacencyMatrix, 4);
boolMatrix.Warshall();
return 0;
}

