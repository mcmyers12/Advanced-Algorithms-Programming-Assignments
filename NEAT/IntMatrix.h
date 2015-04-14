

#ifndef __AlgorithmsWarshallAndFloyd__IntMatrix__
#define __AlgorithmsWarshallAndFloyd__IntMatrix__

#include <iostream>
using namespace std;

class IntMatrix
{
public:
    IntMatrix(int** weightMatrixIn, int sizeIn);
    ~IntMatrix();
    
    void FloydStep(int k, int i, int j);
    void Floyd();
    void printMatrix();
    
private:
    int size;
    int** weightMatrix;
    int infinity;

};


#endif /* defined(__AlgorithmsWarshallAndFloyd__IntMatrix__) */
