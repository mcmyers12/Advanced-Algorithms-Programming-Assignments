

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


int main()
{
    bool **adjacencyMatrix;
    adjacencyMatrix = new bool*[4]; // dynamic `array (size 4) of pointers to int`
    
    for (int i = 0; i < 4; ++i)
    {
        adjacencyMatrix[i] = new bool[4];
    }
    
    //Example from the book
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

