//@file fib3.cpp
//@author Miranda Myers (mmyers4) and Sarah Prata
//@date February 18, 2015
//@description Uses various algorithms including an iterative fibonacci algorithm,
    // the matrix power algorithm, and approximation to phi to compute and print
    // Fibonacci numbers


#include <iostream>
//This header defines constants with the limits of fundamental integral types for the
    //specific system and compiler implementation used
#include <limits.h>
using namespace std;

//Accepts user input, must be an integer greater than 1
//@pre n/a
//@post n/a
//@usage getUserInputFibonacci;
int getUserInputFibonacci();

//Computes the nth Fibonacci number iteratively
//@pre integer largestK exists
//@post int largestK contains k where F[k] is the last Fibonacci number to fit in the bytes of an unsigned int
//@usage int largestK; unsigned int* F; F = iterativeFibonacci(90, int& largestK);
unsigned int* iterativeFibonacci(int n, int& largestK);

//Prints F[0], F[1], …, F[k] in table format each column right-justified, with only 5 numbers per line
//@pre an array of unsigned integers and integer n exists
//@post prints all elements of the array in specified format
//@usage printFibon(n, fibonacciArray);
void printFibon(int n, unsigned int *F);

//Computes the square root of a given number to a tolerance using Newton's method
//@pre originalNumber should be positive, also a guess close to the square root must also be made
//@post A close approximation of the square root of the originalNumber will be returned
//@usage double squareRootOf5 = sqrt(5,2,.0000001);
float sqrt(double originalNumber, double guess, double tolerance);

//Computes the power of a number in logn time, uses recursion and division by 2.
//@pre must be passed a number that is being put to a power
//@post Final returned value will be the numberBeingRaised to the power
//   of the given powerNumber.
//@usage double powPhi = power(phi,n);
float power(float x, int y);

//Computes the approximation to phi to find the nth fibonacci number
//@pre n must be positive
//@post Returns the approximation to phi
//@usage double approx = computeApproximationToPhi(n);
unsigned int computeApproximationToPhi(int n);

//Multiplies together two matrices
//@pre Two 2x2 matrices exist in the form of one dimensional arrays
//@post returns the multiplied result of the two matrices
//@usage unsigned int* matrixArray = multiplyMatrices(matrixArray1, matrixArray2);
unsigned int* multiplyMatrices(unsigned int* matrixArray1, unsigned int* matrixArray2);

//Uses the matrix power algorithm to compute the nth fibonacci number
//@pre A 2x2 matrix in the form of a one dimensional array exists
//@post Returns the nth power of the matrix
//@usage unsigned int* matrixArray = findNthMatrixPowertoFindFibNumbers(matrixArray, power)
unsigned int* findNthMatrixPowertoFindFibNumbers(unsigned int* matrixArray, int power);


int main()
{
    cout << endl << endl << "Compute the nth Fibonacci number within limits of an unsigned int given user input:" << endl << endl;
    int userInput = getUserInputFibonacci();

    int largestK;
    unsigned int* fibNumbers = iterativeFibonacci(userInput, largestK);
    printFibon(largestK - 1, fibNumbers);

    cout << "The largest Fibonacci number computed is the " << largestK << "th" << endl << endl << endl;

    cout << "Compute the approximation to phi for Fib(k/2) and Fib(k) for the largest k found above:" << endl;
    cout << "     Fib(k): " << computeApproximationToPhi(largestK-1) << endl;
    cout << "     Fib(k/2): " << computeApproximationToPhi(largestK / 2) << endl << endl << endl;

    cout << "Matrix power algorithm to compute F(k) and F(k/2):" << endl;
    unsigned int arrayIn[4] = {0, 1, 1, 1};
    unsigned int * matrixArray = findNthMatrixPowertoFindFibNumbers(arrayIn, largestK-1);
    cout << "     Fib(k): " << matrixArray[1] << endl;
    matrixArray = findNthMatrixPowertoFindFibNumbers(arrayIn, largestK / 2);
    cout << "     Fib(k/2): " << matrixArray[1] << endl << endl << endl;
    return 0;
}


//Accepts user input, must be an integer greater than 1
//@pre n/a
//@post n/a
//@usage getUserInputFibonacci;
int getUserInputFibonacci()
{
    int userInput = 0;

    cout << "Enter an integer, n >= 1, to find the nth fibonacci number" << endl;
    cout << "The algorithm will only compute fibonacci numbers up to values that fit in the bytes of an unsigned int " << endl;
    cin >> userInput;

    while (userInput < 1 || cin.fail())
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid input, enter an integer >= 1" << endl;
        cin >> userInput;
    }
    return userInput;
}


//Computes the nth Fibonacci number iteratively
//@pre integer largestK exists
//@post int largestK contains k where F[k] is the last Fibonacci number to fit in the bytes of an unsigned int
//@usage int largestK; unsigned int* F; F = iterativeFibonacci(90, int& largestK);
unsigned int* iterativeFibonacci(int n, int& largestK)
{
    //Account for 0th index in the array
    n = n - 1;

    //Calculate the largest possible value of an unsigned int
    unsigned int maxUnsignedIntSize = UINT_MAX;
    unsigned int* F = new unsigned int[n];
    F[0] = 0;
    F[1] = 1;

    unsigned long int fibonacciNumber = 0;

    int i;
    for (i = 2; i <=n; i++)
    {
        if (F[i - 1] + F[i - 2] < fibonacciNumber)
        {
            break;
        }
        else
        {
            F[i] = F[i - 1] + F[i - 2];
            fibonacciNumber = F[i - 1] + F[i - 2];
        }
    }

    //Save the largest k value to be used in subsequent functions
    largestK = i;

    return F;
}


//Prints F[0], F[1], …, F[k] in table format each column right-justified, with only 5 numbers per line
//@pre an array of unsigned integers and integer n exists
//@post prints all elements of the array in specified format
//@usage printFibon(n, fibonacciArray);
void printFibon(int n, unsigned int *F)
{
    for(int j = 0; j <= n; j+=5){

        cout << "   n:\t";
        int y = 0;
        string spaceSize = "\t\t";

        while(y+j <= n && y < 5){//for(int y = 0; y < 5; y++){
            cout << y+j << "\t\t";
            y++;
        }

        cout << endl << "F(n):\t" ;
        int z = 0;
        while(z+j <= n && z < 5){//for(int z = 0; z < 5; z++){
            if(F[j+z] > 10000000)
            {
                spaceSize = "\t";
            }
            cout << F[z+j] << spaceSize;
            z++;
        }
        cout << endl << endl;
    }
}


//Computes the square root of a given number to a tolerance using Newton's method
//@pre originalNumber should be positive, also a guess close to the square root must also be made
//@post A close approximation of the square root of the originalNumber will be returned
//@usage double squareRootOf5 = sqrt(5,2,.0000001);
float sqrt(double originalNumber, double guess, double tolerance){
    double sqrtOfNumber = guess+1; //this just needs to be a bigger number than prevNumber
    double prevNumber = guess;
    while( (sqrtOfNumber - prevNumber) > tolerance || (prevNumber - sqrtOfNumber) > tolerance){
        prevNumber = sqrtOfNumber;
        sqrtOfNumber = .5 * (sqrtOfNumber + originalNumber/sqrtOfNumber);
    }
    return sqrtOfNumber;
}


//Computes the power of a number in logn time, uses recursion and division by 2.
//@pre must be passed a number that is being put to a power
//@post Final returned value will be the numberBeingRaised to the power
//   of the given powerNumber.
//@usage double powPhi = power(phi,n);
float power(float numberBeingRaised, int powerNumber)
{
    float numberToPower = 0;
    if( powerNumber == 0 ) // anything to the power of zero will return 1
    {
        return 1;
    }

    numberToPower = power(numberBeingRaised, powerNumber/2);

    if (powerNumber%2 == 0) //if even power
    {
        return numberToPower*numberToPower;
    }
    else
    {
        if(powerNumber > 0) //if odd power and positive
        {
            return numberBeingRaised*numberToPower*numberToPower;
        }
        else
        {
            return (numberToPower*numberToPower)/numberBeingRaised; //if negative
        }
    }
}


//Computes the approximation to phi to find the nth fibonacci number
//@pre n must be positive
//@post Returns the approximation to phi
//@usage double approx = computeApproximationToPhi(n);
unsigned int computeApproximationToPhi(int n)
{
    double squareRootOf5 = sqrt(5,2,.0000001);
    double phi = (1 + squareRootOf5)/2;
    double pho = -1/phi;
    double oneOverSqrt5 = 1/squareRootOf5;
    double powPhi = power(phi,n);
    double powPho = power(pho, n);
    return (oneOverSqrt5 * (powPhi - powPho));
}


//Multiplies together two matrices
//@pre Two 2x2 matrices exist in the form of one dimensional arrays
//@post returns the multiplied result of the two matrices
//@usage unsigned int* matrixArray = multiplyMatrices(matrixArray1, matrixArray2);
unsigned int* multiplyMatrices(unsigned int* matrixArray1, unsigned int* matrixArray2)
{
    unsigned int* newMatrixArray = new unsigned int[4];

    newMatrixArray[0] = matrixArray1[0] * matrixArray2[0] + matrixArray1[1] * matrixArray2[2];
    newMatrixArray[1] = matrixArray1[0] * matrixArray2[1] + matrixArray1[1] * matrixArray2[3];
    newMatrixArray[2] = matrixArray1[2] * matrixArray2[0] + matrixArray1[3] * matrixArray2[2];
    newMatrixArray[3] = matrixArray1[2] * matrixArray2[1] + matrixArray1[3] * matrixArray2[3];

    return newMatrixArray;
}


//Uses the matrix power algorithm to compute the nth fibonacci number
//@pre A 2x2 matrix in the form of a one dimensional array exists
//@post Returns the nth power of the matrix
//@usage unsigned int* matrixArray = findNthMatrixPowertoFindFibNumbers(matrixArray, power)
unsigned int* findNthMatrixPowertoFindFibNumbers(unsigned int* matrixArray, int power)
{
    if (power == 1)
    {
        return matrixArray;
    }

    unsigned int* tempMatrixArray = findNthMatrixPowertoFindFibNumbers(matrixArray, power / 2);

    tempMatrixArray = multiplyMatrices(tempMatrixArray, tempMatrixArray);

    if (power % 2 == 1)
        tempMatrixArray = multiplyMatrices(tempMatrixArray, matrixArray);

    return tempMatrixArray;
}


