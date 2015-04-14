

#ifndef __AlgorithmsWarshallAndFloyd__BoolMatrix__
#define __AlgorithmsWarshallAndFloyd__BoolMatrix__

#include <iostream>
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
    
    private:
        //static const int MAX_SIZE = 100;
        int size;
        bool** adjacencyMatrix;
};

#endif /* defined(__AlgorithmsWarshallAndFloyd__BoolMatrix__) */
