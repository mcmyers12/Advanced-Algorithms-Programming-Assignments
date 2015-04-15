
#include "BoolMatrix.h"
#include "IntMatrix.h"
#include "limits.h"


int main()
{
    //*************************Warshall***************************//
    bool **adjacencyMatrix;
    adjacencyMatrix = new bool*[4]; // dynamic array (size 4) of pointers to bool
    
    for (int i = 0; i < 4; ++i)
    {
        adjacencyMatrix[i] = new bool[4];
    }
    
    //Example from the book pg 307
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
    cout << "Warshall's Algorithm steps" << endl;
    boolMatrix.Warshall();
    
    
    //*************************Floyd***************************//
    int **weightMatrix;
    weightMatrix = new int*[4]; // dynamic array (size 4) of pointers to int
    
    for (int i = 0; i < 4; ++i)
    {
        weightMatrix[i] = new int[4];
    }
    
    int infinity = numeric_limits<int>::max();
    
    //Example from book pg 311
    weightMatrix[0][0] = 0;
    weightMatrix[0][1] = infinity;
    weightMatrix[0][2] = 3;
    weightMatrix[0][3] = infinity;
    weightMatrix[1][0] = 2;
    weightMatrix[1][1] = 0;
    weightMatrix[1][2] = infinity;
    weightMatrix[1][3] = infinity;
    weightMatrix[2][0] = infinity;
    weightMatrix[2][1] = 7;
    weightMatrix[2][2] = 0;
    weightMatrix[2][3] = 1;
    weightMatrix[3][0] = 6;
    weightMatrix[3][1] = infinity;
    weightMatrix[3][2] = infinity;
    weightMatrix[3][3] = 0;
    
    IntMatrix intMatrix(weightMatrix, 4);
    cout << endl << "Floyd's Algorithm steps" << endl;
    intMatrix.Floyd();

    cout << "\033[1;31mbold red text\033[0m\n";
    return 0;
}

