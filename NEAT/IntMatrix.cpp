

#include "IntMatrix.h"

IntMatrix::IntMatrix(int** weightMatrixIn, int sizeIn)
{
    weightMatrix = weightMatrixIn;
    size = sizeIn;
    int infinity = numeric_limits<int>::max();
}


IntMatrix::~IntMatrix()
{
    //TODO implement
    for(int i = 0; i < size; i++)
	  {
		delete[ ] weightMatrix[i];
	  }
	  delete[ ] weightMatrix;
}


void IntMatrix::FloydStep(int k, int i, int j)
{
    //weightMatrix[i][j] = min(weightMatrix[i][j], weightMatrix[i][k] + weightMatrix[k][j])

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
//Input: The weight matrix W of a graph with no negative-length cycle
//Output: The distance matrix of the shortest paths’ lengths

void IntMatrix::Floyd()
{
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


void IntMatrix::printMatrix()
{
    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            cout << weightMatrix[k][i] << " ";
            /*
            if (weightMatrix[k][i] == infinity)
                cout << "inf" << " ";
            else
                cout << weightMatrix[k][i] << " ";*/
        }
        cout << endl;
    }
    cout << endl;
}


//overload of operator for 2-d array used for output
int IntMatrix::operator [] (const std::pair<int,int>& Index) const
{
   return weightMatrix[Index.first][Index.second];
}

//overload of operator for 2-d array, used for input
int & IntMatrix::operator [] (const std::pair<int,int>& Index)
{
   return weightMatrix[Index.first][Index.second];
}



istream& operator>> (istream& input, IntMatrix& A) //for inputing via file or keyboard
{
    for (int i = 0; i < A.size; i++){
        for (int j = 0; j < A.size; j++){
            std::pair<int, int> theIndex(i,j);
            input >> A[theIndex]; ///ToDo need to fix this..
        }
    }
    return input;
}

ostream& operator<< (ostream& output, const IntMatrix& A) //for outputing to file or command line
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




