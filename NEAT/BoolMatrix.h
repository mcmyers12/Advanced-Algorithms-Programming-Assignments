

#ifndef __AlgorithmsWarshallAndFloyd__BoolMatrix__
#define __AlgorithmsWarshallAndFloyd__BoolMatrix__

#include <iostream>
#include <istream>
#include <ostream>
using namespace std;

//TODO add pre and post data members to Warshall (dumb because we don't need them because class)

class BoolMatrix
{
    public:
        BoolMatrix(bool** adjacencyMatrixIn, int sizeIn);
        ~BoolMatrix();

        //Completes one step of Warshall's Algorithm
        void WarshallStep(int k, int i, int j);
        void Warshall();//bool** adjacencyMatrix, bool** transitiveClosure);
        void printMatrix();
        bool   operator [] (const std::pair<int,int>& Index) const; // For reading
        bool & operator [] (const std::pair<int,int>& Index);       // For writing
        friend istream& operator>> (istream& input, BoolMatrix& A); //for inputing via file or keyboard
        friend ostream& operator<< (ostream& output, const BoolMatrix& A); //for outputing to file or command line

    private:
        //static const int MAX_SIZE = 100;
        int size;
        bool** adjacencyMatrix;
};



#endif /* defined(__AlgorithmsWarshallAndFloyd__BoolMatrix__) */
