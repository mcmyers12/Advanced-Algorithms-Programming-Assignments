//@file intMatrix.cpp
//@author Sarah Prata (sprata)
//@author Miranda Myers
//@date 3/18/2015

#include "IntMatrix.h"

// Initializes weightMatrix and previousWeightMatrix to be of sizeIn
//  and have the values of weightMatrixIn
//@post weightMatrix will be properly initialized.
//@usage IntMatrix intMatrix(weightMatrixIn, sizeOfArray);
IntMatrix::IntMatrix(int** weightMatrixIn, int sizeIn)
{
    weightMatrix = weightMatrixIn;
    size = sizeIn;
    infinity = numeric_limits<int>::max();
    previousWeightMatrix = new int*[sizeIn];
    for (int i = 0; i < sizeIn; ++i)
    {
        previousWeightMatrix[i] = new int[sizeIn];
    }
    for(int j = 0; j < sizeIn; j++){
        for(int i = 0; i < sizeIn; i++){
            previousWeightMatrix[j][i] = weightMatrixIn[j][i];
        }
    }
}

// Initializes weightMatrix and previousWeightMatrix to be of sizeIn
//@post weightMatrix will be properly initialized.
//@usage IntMatrix intMatrix(sizeOfArray);
IntMatrix::IntMatrix(int sizeIn)
{
    size = sizeIn;
    infinity = numeric_limits<int>::max();
    weightMatrix = new int*[sizeIn];
    for (int i = 0; i < sizeIn; ++i)
    {
        weightMatrix[i] = new int[sizeIn];
    }
    previousWeightMatrix = new int*[sizeIn];
    for (int i = 0; i < sizeIn; ++i)
    {
        previousWeightMatrix[i] = new int[sizeIn];
    }
    for(int j = 0; j < sizeIn; j++){
        for(int i = 0; i < sizeIn; i++){
            previousWeightMatrix[j][i] = 0;
        }
    }
}

// Frees memory allocated to weightMatrix and previousWeightMatrix
//@pre  The adjacencyMatrix and previousAdjacencyMatrix exist
//@post allocated memory will be freed
IntMatrix::~IntMatrix()
{
    for(int i = 0; i < size; i++)
	  {
		delete[ ] weightMatrix[i];
	  }
	  delete[ ] weightMatrix;
    for(int i = 0; i < size; i++)
    {
        delete[ ] previousWeightMatrix[i];
    }
    delete[ ] previousWeightMatrix;
}


// Completes one step of Floyd's Algorithm
//@pre  The weightMatrix and previousWeightMatrix exist
//@post previousWeightMatrix now has the contents of the weightMatrix at i,j
//       and weightMatrix at i,j will be updated
//@usage FloydStep(k, i, j);
void IntMatrix::FloydStep(int k, int i, int j)
{
    previousWeightMatrix[i][j] = weightMatrix[i][j];

    if (weightMatrix[i][k] != infinity && weightMatrix[k][j] != infinity)
    {
        int newWeight = weightMatrix[i][k] + weightMatrix[k][j];

        if ((newWeight) < weightMatrix[i][j])
        {
            weightMatrix[i][j] = newWeight;
        }
    }

}


//Implements Floyd’s algorithm for the all-pairs shortest-paths problem
//@pre  The weight matrix W of a graph with no negative-length cycle
//@post The distance matrix of the shortest paths’ lengths
//@usage intMatrix.Floyd();
void IntMatrix::Floyd()
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            previousWeightMatrix[i][j] = weightMatrix[i][j];
        }
    }

    cout << "\nInitial value of matrix:" << endl;
    printMatrix();
    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                FloydStep(k, i, j);
            }
        }
        printMatrix();
    }
}

// Print the weightMatrix with the changed values bolded and colored
//@pre previousWeightMatrix must have previous values and
//  weightMatrix must have current values
//@post weightMatrix will be output to screen
//@usage printMatrix();
void IntMatrix::printMatrix()
{
    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            if(previousWeightMatrix[k][i] != weightMatrix[k][i])
            {
                cout << "\033[1;31m" << weightMatrix[k][i] << "\033[0m ";
            }
            else{
                if (weightMatrix[k][i] == infinity)
                    cout << "i" << " ";
                else
                    cout << weightMatrix[k][i] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}


// Overload of subscript operator for 2-d array used for output
// Makes use of std::pair for 2-d access
//@pre weightMatrix has been initialized
//@usage std::pair<int, int> theIndex(i,j); output << A[theIndex] << " ";
int IntMatrix::operator [] (const std::pair<int,int>& Index) const
{
   return weightMatrix[Index.first][Index.second];
}

// Overload of subscript operator for 2-d array, used for input.
// Makes use of std::pair for 2-d access
//@pre weightMatrix has been initialized
//@usage std::pair<int, int> theIndex(i,j); input >> A[theIndex];
int & IntMatrix::operator [] (const std::pair<int,int>& Index)
{
   return weightMatrix[Index.first][Index.second];
}


// Overload input operator for reading to file or input from keyboard
//@pre Input has been given and BoolMatrix A exists
//@post the matrix will be filled with the input
//@usage infile >> intMatrix;
istream& operator>> (istream& input, IntMatrix& A) //for inputing via file or keyboard
{
    char value;
    for (int i = 0; i < A.size; i++){
        for (int j = 0; j < A.size; j++){
            input >> value;
            if(value == 'i')
            {
                std::pair<int, int> theIndex(i,j);
                A[theIndex] = A.infinity;
            }
            else
            {
                std::pair<int, int> theIndex(i,j);
                int intValue = value-48;
                A[theIndex] = intValue; ///ToDo need to fix this..
            }

        }
    }
    return input;
}


// Overload output operator for outputing to file or command line
//@pre BoolMatrix exists
//@post the matrix will be output to screen
//@usage cout << intMatrix;
ostream& operator<< (ostream& output, const IntMatrix& A)
{
    for (int i = 0; i < A.size; i++){
        for (int j = 0; j < A.size; j++){
            std::pair<int, int> theIndex(i,j);
            if(A[theIndex] == A.infinity)
            {
                output << 'i' << " ";
            }
            else{
                output << A[theIndex] << " ";
            }
        }
        output << endl;
    }
    return output;
}




