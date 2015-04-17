

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

    int   operator [] (const std::pair<int,int>& Index) const; // For reading
    int & operator [] (const std::pair<int,int>& Index);       // For writing
    friend istream& operator>> (istream& input, IntMatrix& A); //for inputing via file or keyboard
    friend ostream& operator<< (ostream& output, const IntMatrix& A); //for outputing to file or command line


private:
    int size;
    int** weightMatrix;
    int infinity;

};


#endif /* defined(__AlgorithmsWarshallAndFloyd__IntMatrix__) */
