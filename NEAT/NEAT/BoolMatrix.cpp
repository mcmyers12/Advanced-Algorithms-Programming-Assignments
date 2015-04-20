//@file BoolMatrix.cpp
//@author Sarah Prata (sprata)
//@author Miranda Myers
//@date 3/18/2015

#include "BoolMatrix.h"

// Initializes adjacencyMatrix and previousAdjacencyMatrix to be of sizeIn
//  and have values in adjacencyMatrixIn
//@post weightMatrix object will be properly initialized.
//@usage BoolMatrix boolMatrix(adjacencyMatrixIn, sizeOfArray);
BoolMatrix::BoolMatrix(bool** adjacencyMatrixIn, int sizeIn)
{
    size = sizeIn;
    adjacencyMatrix = adjacencyMatrixIn;
    previousAdjacencyMatrix = new bool*[sizeIn];
    for (int i = 0; i < sizeIn; ++i)
    {
        previousAdjacencyMatrix[i] = new bool[sizeIn];
    }
    for(int j = 0; j < sizeIn; j++){
        for(int i = 0; i < sizeIn; i++){
            previousAdjacencyMatrix[j][i] = adjacencyMatrixIn[j][i];
        }
    }
}

// Initializes adjacencyMatrix and previousAdjacencyMatrix to be of sizeIn
//@post weightMatrix object will be properly initialized.
//@usage BoolMatrix boolMatrix(sizeOfArray);
BoolMatrix::BoolMatrix(int sizeIn)
{
    size = sizeIn;
    adjacencyMatrix = new bool*[sizeIn];
    for (int i = 0; i < sizeIn; ++i)
    {
        adjacencyMatrix[i] = new bool[sizeIn];
    }

    previousAdjacencyMatrix = new bool*[sizeIn];
    for (int i = 0; i < sizeIn; ++i)
    {
        previousAdjacencyMatrix[i] = new bool[sizeIn];
    }
    for(int j = 0; j < sizeIn; j++){
        for(int i = 0; i < sizeIn; i++){
            previousAdjacencyMatrix[j][i] = 0;
        }
    }
}

// Frees memory allocated to adjacencyMatrix and previousAdjacencyMatrix
//@pre  The adjacencyMatrix and previousAdjacencyMatrix exist
//@post allocated memory will be freed
BoolMatrix::~BoolMatrix()
{
    for(int i = 0; i < size; i++)
    {
        delete[ ] adjacencyMatrix[i];
    }
    delete[ ] adjacencyMatrix;

    for(int i = 0; i < size; i++)
    {
        delete[ ] previousAdjacencyMatrix[i];
    }
    delete[ ] previousAdjacencyMatrix;
}


// Completes one step of Warshall's Algorithm
//@pre  The adjacency matrix  and previousAdjacencyMatrix exist
//@post previousAdjacencyMatrix now has the contents of the adjacencyMatrix at i,j
//       and adjacencyMatrix at i,j will be updated
//@usage WarshallStep(k, i, j);
void BoolMatrix::WarshallStep(int k, int i, int j)
{
    previousAdjacencyMatrix[i][j] = adjacencyMatrix[i][j];
    adjacencyMatrix[i][j] = adjacencyMatrix[i][j] || (adjacencyMatrix[i][k] && adjacencyMatrix[k][j]);
}

// Implements Warshall's algorithm
//@pre  The adjacency matrix A of a digraph with n vertices
//@post The transitive closure of the digraph
//@usage boolMatrix.Warshall();
void BoolMatrix::Warshall()//bool** adjacencyMatrix, bool** transitiveClosure)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            previousAdjacencyMatrix[i][j] = adjacencyMatrix[i][j];
        }
    }

    cout << "\nInitial value of Matrix:" << endl;
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
        cout << endl;
    }
}

// Print the adjacencyMatrix with the changed values bolded and colored
//@pre previousAdjacencyMatrix must have previous values and
//  adjacencyMatrix must have current values
//@post adjacencyMatrix will be output to screen
//@usage printMatrix();
void BoolMatrix::printMatrix()
{
    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            if (adjacencyMatrix[k][i] != previousAdjacencyMatrix[k][i])
            {
                cout << "\033[1;31m" << adjacencyMatrix[k][i] << "\033[0m ";
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


// Overload of subscript operator for 2-d array used for output
// Makes use of std::pair for 2-d access
//@pre adjacenyMatrix has been initialized
//@usage std::pair<int, int> theIndex(i,j); output << A[theIndex] << " ";
bool BoolMatrix::operator [] (const std::pair<int,int>& Index) const
{
   return adjacencyMatrix[Index.first][Index.second];
}

// Overload of subscript operator for 2-d array, used for input.
// Makes use of std::pair for 2-d access
//@pre adjacenyMatrix has been initialized
//@usage std::pair<int, int> theIndex(i,j); input >> A[theIndex];
bool & BoolMatrix::operator [] (const std::pair<int,int>& Index)
{
   return adjacencyMatrix[Index.first][Index.second];
}

// Overload input operator for reading to file or input from keyboard
//@pre Input has been given and BoolMatrix A exists
//@post the matrix will be filled with the input
//@usage infile >> boolMatrix;
istream& operator>> (istream& input, BoolMatrix& A)
{
  for (int i = 0; i < A.size; i++){
        for (int j = 0; j < A.size; j++){
            std::pair<int, int> theIndex(i,j);
            input >> A[theIndex];
        }
    }
    return input;
}

// Overload output operator for outputing to file or command line
//@pre BoolMatrix exists
//@post the matrix will be output to screen
//@usage cout << boolMatrix;
ostream& operator<< (ostream& output, const BoolMatrix &A)
{
    for (int i = 0; i < A.size; i++){
        for (int j = 0; j < A.size; j++){
            std::pair<int, int> theIndex(i,j);
            output << A[theIndex] << " ";
        }
        output << endl;
    }
    return output;
}



