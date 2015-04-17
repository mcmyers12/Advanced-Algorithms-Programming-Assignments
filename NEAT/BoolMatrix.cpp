

#include "BoolMatrix.h"


BoolMatrix::BoolMatrix(bool** adjacencyMatrixIn, int sizeIn)
{
    adjacencyMatrix = adjacencyMatrixIn;
    previousAdjacencyMatrix = adjacencyMatrix;
    size = sizeIn;
}


BoolMatrix::~BoolMatrix()
{
    for(int i = 0; i < size; i++)
    {
        delete[ ] adjacencyMatrix[i];
    }
    delete[ ] adjacencyMatrix;
}


//Completes one step of Warshall's Algorithm
void BoolMatrix::WarshallStep(int k, int i, int j)
{
    previousAdjacencyMatrix[i][j] = adjacencyMatrix[i][j];
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
        ///previousAdjacencyMatrix = adjacencyMatrix;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                WarshallStep(k, i, j);

            }
        }
        cout << "current" << endl;
        printMatrix();
        cout << "prev" << endl;
        printMatrixPrev();
        cout << endl;
    }
    //transitiveClosure = adjacencyMatrix;
}

void BoolMatrix::printMatrix()
{
    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            if (adjacencyMatrix[k][i] != previousAdjacencyMatrix[k][i])
            {
                cout << adjacencyMatrix[k][i] << "c";
            }
            else
            {
                cout << adjacencyMatrix[k][i] << " ";
            }

        }
        cout << endl;
    }
    cout << endl;
}


void BoolMatrix::printMatrixPrev()
{
    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            cout << previousAdjacencyMatrix[k][i] << " ";

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
    ///input >> A[0][0];
   ///A.size;
  for (int i = 0; i < A.size; i++){
        for (int j = 0; j < A.size; j++){
            std::pair<int, int> theIndex(i,j);
            input >> A[theIndex]; ///ToDo need to fix this..
        }
    }
    return input;
}


ostream& operator<< (ostream& output, const BoolMatrix &A)
{
    for (int i = 0; i < A.size; i++){
        for (int j = 0; j < A.size; j++){
            std::pair<int, int> theIndex(i,j);
            output << A[theIndex] << " "; ///TODO need to figure out what to output
        }
        output << endl;
    }
    return output;
}



