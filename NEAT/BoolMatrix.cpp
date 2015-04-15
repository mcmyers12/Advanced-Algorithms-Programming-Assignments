

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

//overload of operator for 2-d array used for output
bool BoolMatrix::operator [] (const std::pair<int,int>& Index) const
{
   return adjacencyMatrix[Index.first][Index.second];
}

//overload of operator for 2-d array, used for input
bool & BoolMatrix::operator [] (const std::pair<int,int>& Index)
{
   return adjacencyMatrix[Index.first][Index.second];
}


istream& operator>> (istream& input, BoolMatrix& A)
{
    for (int i = 0; i < A.size; i++){
        for (int j = 0; j < A.size; j++){
            std::pair<int, int> theIndex(i,j);
            input >> A[theIndex]; ///ToDo need to fix this..
        }
    }
    return input;
}


ostream& operator<< (ostream& output, const BoolMatrix& A)
{
    output << A.size; ///TODO need to figure out what to output
    return output;
}



