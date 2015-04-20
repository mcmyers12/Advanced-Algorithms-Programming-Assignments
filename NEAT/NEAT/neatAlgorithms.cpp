//@file neatAlgorithms.cpp
//@author Sarah Prata (sprata)
//@author Miranda Myers
//@date 3/18/2015

//Program accomplishes the following:
//  Read two tests cases for both Floyd's algorithm and Warshall's algorithm:
//  one test case is the small one from the book and another is a 6-vertices directed graph.
//  Print each matrix at each stage in a quality-manner: from k = 0 to k = 1 to k = 2 to .. k = n.
//  Prints the changed entries bolded and red at each stage.

#include "BoolMatrix.h"
#include "IntMatrix.h"
#include "limits.h"
#include <fstream>

int main()
{
    ifstream infile;
    infile.open ("in8.dat");
    if (infile.is_open())
    {
        int sizeOfArray;
        //*************************Warshall***************************//
        infile >> sizeOfArray;
        BoolMatrix boolMatrix(sizeOfArray);
        infile >> boolMatrix;
        cout << "Warshall's Algorithm steps on Book Example" << endl;
        boolMatrix.Warshall();
        cout << "\nFinal value of matrix:" << endl;
        cout << boolMatrix;

        cout << "Hit enter for next example of Warshall Algorithm" << endl;
        cin.ignore();
        cout << "Warshall's Algorithm steps on 6x6 Matrix" << endl;
        infile >> sizeOfArray;
        BoolMatrix boolMatrix2(sizeOfArray);
        infile >> boolMatrix2;
        boolMatrix2.Warshall();
        cout << "\nFinal value of matrix:" << endl;
        cout << boolMatrix2;
        cout << "Hit enter for an example of Floyd's Algorithm" << endl;
        cin.ignore();

       //*************************Floyd***************************//
        infile >> sizeOfArray;
        IntMatrix intMatrix(sizeOfArray);
        cout << endl << "Floyd's Algorithm on Book Example" << endl;
        infile >> intMatrix;

        intMatrix.Floyd();
        cout << "\nFinal value of matrix:" << endl;
        cout << intMatrix;

        cout << "Hit enter for next example of Floyd's Algorithm" << endl;
        cin.ignore();
        infile >> sizeOfArray;
        IntMatrix intMatrix2(sizeOfArray);
        cout << endl << "Floyd's Algorithm on 6x6 Matrix" << endl;
        infile >> intMatrix2;

        intMatrix2.Floyd();
        cout << "\nFinal value of matrix:" << endl;
        cout << intMatrix2;
    }

    return 0;
}

