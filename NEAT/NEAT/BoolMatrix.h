//@file BoolMatrix.h
//@author Sarah Prata (sprata)
//@author Miranda Myers
//@date 3/18/2015
//
//ADT BoolMatrix: an adjacency matrix for a non-weighted directed graph that holds previous values and size,
//  2 constructors, 1 destructor

#ifndef __AlgorithmsWarshallAndFloyd__BoolMatrix__
#define __AlgorithmsWarshallAndFloyd__BoolMatrix__

#include <iostream>
#include <istream>
#include <ostream>
using namespace std;


class BoolMatrix
{
    public:
        // Initializes adjacencyMatrix and previousAdjacencyMatrix to be of sizeIn
        //  and have values in adjacencyMatrixIn
        //@post weightMatrix object will be properly initialized.
        //@usage BoolMatrix boolMatrix(adjacencyMatrixIn, sizeOfArray);
        BoolMatrix(bool** adjacencyMatrixIn, int sizeIn);

        // Initializes adjacencyMatrix and previousAdjacencyMatrix to be of sizeIn
        //@post weightMatrix object will be properly initialized.
        //@usage BoolMatrix boolMatrix(sizeOfArray);
        BoolMatrix(int sizeIn);

        // Frees memory allocated to adjacencyMatrix and previousAdjacencyMatrix
        //@pre  The adjacencyMatrix and previousAdjacencyMatrix exist
        //@post allocated memory will be freed
        ~BoolMatrix();

        //Completes one step of Warshall's Algorithm
        //@pre  The adjacency matrix  and previousAdjacencyMatrix exist
        //@post previousAdjacencyMatrix now has the contents of the adjacencyMatrix at i,j
        //       and adjacencyMatrix at i,j will be updated
        //@usage WarshallStep(k, i, j);
        void WarshallStep(int k, int i, int j);

        // Implements Warshall's algorithm
        //@pre  The adjacency matrix A of a digraph with n vertices
        //@post The transitive closure of the digraph
        //@usage boolMatrix.Warshall();
        void Warshall();//bool** adjacencyMatrix, bool** transitiveClosure);

        // Print the adjacencyMatrix with the changed values bolded and colored
        //@pre previousAdjacencyMatrix must have previous values and
        //  adjacencyMatrix must have current values
        //@post adjacencyMatrix will be output to screen
        //@usage printMatrix();
        void printMatrix();

        // Overload of subscript operator for 2-d array used for output
        // Makes use of std::pair for 2-d access
        //@pre adjacenyMatrix has been initialized
        //@usage std::pair<int, int> theIndex(i,j); output << A[theIndex] << " ";
        bool   operator [] (const std::pair<int,int>& Index) const; // For reading

        // Overload of subscript operator for 2-d array, used for input.
        // Makes use of std::pair for 2-d access
        //@pre adjacenyMatrix has been initialized
        //@usage std::pair<int, int> theIndex(i,j); input >> A[theIndex];
        bool & operator [] (const std::pair<int,int>& Index);       // For writing

        // Overload input operator for reading to file or input from keyboard
        //@pre Input has been given and BoolMatrix A exists
        //@post the matrix will be filled with the input
        //@usage infile >> boolMatrix;
        friend istream& operator>> (istream& input, BoolMatrix& A); //for inputing via file or keyboard

        // Overload output operator for outputing to file or command line
        //@pre BoolMatrix exists
        //@post the matrix will be output to screen
        //@usage cout << boolMatrix;
        friend ostream& operator<< (ostream& output, const BoolMatrix& A); //for outputing to file or command line



    private:
        //Size of Matrix
        int size;

        //Main Matrix to be operated on
        bool** adjacencyMatrix;

        //holds value of previous matrix to allow special printing
        bool** previousAdjacencyMatrix;
};



#endif /* defined(__AlgorithmsWarshallAndFloyd__BoolMatrix__) */
