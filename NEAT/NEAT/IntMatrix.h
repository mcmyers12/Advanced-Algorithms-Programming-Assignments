//@file intMatrix.h
//@author Sarah Prata (sprata)
//@author Miranda Myers
//@date 3/18/2015
//
//ADT IntMatrix: a weight matrix for a weighted directed graph that holds previous values and size,
//  2 constructors, 1 destructor


#ifndef __AlgorithmsWarshallAndFloyd__IntMatrix__
#define __AlgorithmsWarshallAndFloyd__IntMatrix__

#include <iostream>
using namespace std;

class IntMatrix
{
public:

    // Initializes weightMatrix and previousWeightMatrix to be of sizeIn
    //  and have the values of weightMatrixIn
    //@post weightMatrix will be properly initialized.
    //@usage IntMatrix intMatrix(weightMatrixIn, sizeOfArray);
    IntMatrix(int** weightMatrixIn, int sizeIn);

    // Initializes weightMatrix and previousWeightMatrix to be of sizeIn
    //@post weightMatrix will be properly initialized.
    //@usage IntMatrix intMatrix(sizeOfArray);
    IntMatrix(int sizeIn);

    // Frees memory allocated to weightMatrix and previousWeightMatrix
    //@pre  The adjacencyMatrix and previousAdjacencyMatrix exist
    //@post allocated memory will be freed
    ~IntMatrix();

    // Completes one step of Floyd's Algorithm
    //@pre  The weightMatrix and previousWeightMatrix exist
    //@post previousWeightMatrix now has the contents of the weightMatrix at i,j
    //       and weightMatrix at i,j will be updated
    //@usage FloydStep(k, i, j);
    void FloydStep(int k, int i, int j);

    //Implements Floyd’s algorithm for the all-pairs shortest-paths problem
    //@pre  The weight matrix W of a graph with no negative-length cycle
    //@post The distance matrix of the shortest paths’ lengths
    //@usage intMatrix.Floyd();
    void Floyd();

    // Print the weightMatrix with the changed values bolded and colored
    //@pre previousWeightMatrix must have previous values and
    //  weightMatrix must have current values
    //@post weightMatrix will be output to screen
    //@usage printMatrix();
    void printMatrix();

    // Overload of subscript operator for 2-d array used for output
    // Makes use of std::pair for 2-d access
    //@pre weightMatrix has been initialized
    //@usage std::pair<int, int> theIndex(i,j); output << A[theIndex] << " ";
    int   operator [] (const std::pair<int,int>& Index) const; // For reading

    // Overload of subscript operator for 2-d array, used for input.
    // Makes use of std::pair for 2-d access
    //@pre weightMatrix has been initialized
    //@usage std::pair<int, int> theIndex(i,j); input >> A[theIndex];
    int & operator [] (const std::pair<int,int>& Index);       // For writing

    // Overload input operator for reading to file or input from keyboard
    //@pre Input has been given and BoolMatrix A exists
    //@post the matrix will be filled with the input
    //@usage infile >> intMatrix;
    friend istream& operator>> (istream& input, IntMatrix& A); //for inputing via file or keyboard

    // Overload output operator for outputing to file or command line
    //@pre BoolMatrix exists
    //@post the matrix will be output to screen
    //@usage cout << intMatrix;
    friend ostream& operator<< (ostream& output, const IntMatrix& A); //for outputing to file or command line


private:
    //Size of Matrix
    int size;

    //Main Matrix to be operated on
    int** weightMatrix;

    //holds value of previous matrix to allow special printing
    int** previousWeightMatrix;

    //Infinity for values in the matrix that are unknown
    int infinity;


};


#endif /* defined(__AlgorithmsWarshallAndFloyd__IntMatrix__) */
