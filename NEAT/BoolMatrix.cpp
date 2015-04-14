
#include "BoolMatrix.h"

BoolMatrix::BoolMatrix(bool** adjacencyMatrixIn)
{
    adjacencyMatrix = adjacencyMatrixIn;
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
    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                WarshallStep(k, i, j);
                printMatrix();
            }
        }
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
}

int main()
{
    cout << "hi" << endl << endl;
    int **adjacencyMatrix;
    p = new int*[4]; // dynamic `array (size 4) of pointers to int`

    for (int i = 0; i < 4; ++i) 
    {
        adjacencyMatrix[i] = new int[4];
    }
    
    for (int i = 0; i < 4; ++i) 
    {
        for (int j = 0; j < 4; ++j)
            adjacencyMatrix[i][j] = 1;
    } 
    
    /*
    bool adjacencyMatrix[4][4] = {  
        {0, 1, 0, 0} ,   /*  initializers for row indexed by 0 */
        {0, 0, 0, 1} ,
        {0, 0, 0, 0} ,   /*  initializers for row indexed by 1 */
        {1, 0, 1, 0}   /*  initializers for row indexed by 2 */
    };*/
    
    BoolMatrix boolMatrix(adjacencyMatrix);
    boolMatrix.Warshall();
    return 0;
}

