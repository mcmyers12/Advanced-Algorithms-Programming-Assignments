

#include "BoolMatrix.h"


BoolMatrix::BoolMatrix(bool** adjacencyMatrixIn, int sizeIn)
{
    adjacencyMatrix = adjacencyMatrixIn;
    size = sizeIn;
}


BoolMatrix::~BoolMatrix()
{
    
}


//Completes one step of Warshall's Algorithm
void BoolMatrix::WarshallStep(int k, int i, int j)
{
    adjacencyMatrix[i][j] = adjacencyMatrix[i][j] || (adjacencyMatrix[i][k] && adjacencyMatrix[k][j]);
}


//Implements Warshall’s algorithm for computing the transitive closure
//Input: The adjacency matrix A of a digraph with n vertices
//Output: The transitive closure of the digraph
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




