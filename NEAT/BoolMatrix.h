
#include <iostream>
using namespace std;

class BoolMatrix
{
    public:
        BoolMatrix(bool (&adjacencyMatrixIn)[size][size]);
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