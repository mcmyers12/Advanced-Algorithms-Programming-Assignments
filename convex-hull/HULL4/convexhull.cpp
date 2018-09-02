//@file fib3.cpp
//@author Miranda Myers (mmyers4)
//@author Sarah Prata
//@date 2/25/15

//Program accomplishes the following:
// * Reads point values from a file in4.dat in a specified format
// * Puts those values into a vector of struct points
// * Determines the value of ax + by – c given two points
// * Finds all points on convex hull by determining if all other points are in one and 
//      only one of the two half-planes; that is, when the x and y coordinates of each 
//      other point is substituted into ax + by – c, the quantity is always positive or 
//      always negative
// * Prints the values that are in the convex hull vector in the correct format


#include <vector>
#include <fstream>
#include <iostream>
using namespace std;


//A structure that defines a point
//Contains two elements, x coordinate and y coordinate
struct point
{
    double x;
    double y;
};

// Calculates the 'a' in our equation: ax + by - c = 0
//@pre y1, and y2 are integers
//@returns a double with our 'a' value for our equation
//@usage int a = calculateA(y1, y2);
double calculateA(double y1, double y2);

// Calculates the 'b' in our equation: ax + by - c = 0
//@pre x1, and x2 are integers
//@returns a double with our 'b' value for our equation
//@usage int b = calculateB(x1, x2);
double calculateB(double x1, double x2);

// Calculates the 'c' in our equation: ax + by - c = 0
//@pre x1, x2, y1, and y2 are integers
//@returns a double with our 'c' value for our equation
//@usage int c = calculateC(x1, x2, y1, y2);
double calculateC(double x1, double x2, double y1, double y2);

// Determines the sign value of a point
//@pre a, b, c, x and y are all integers
//@returns a double with a value of 1, -1 or 0
//@usage int signValue = determineSignValueOfPoint(a, b, c, pointVector[i].x, pointVector[i].y);
int determineSignValueOfPoint(double a, double b, double c, double x, double y);

// Determines if a given two points are on the Convex Hull
//@pre pointVector has input values, x1, y1, x2 and y2 do not form a vertical or horizontal line
//@returns true or false, whether the set of points are on Convex Hull
//@usage if (determineIfPointsOnConvexHull(x1, y1, x2, y2, pointVector))
bool determineIfPointsOnConvexHull(double x1, double y1, double x2, double y2, vector<point> pointVector);

// Goes through all possible points and finds all the points that are on the Convex Hull
// and puts those points in an new vector.
//@pre pointVector has input values
//@post all the points that are a part of the convex hull are not in the new vector of points
//@returns a vector containing all the points that are on the convex hull
//@usage vector<point> convexHullPoints = findAllPointsOnConvexHull(pointVector);
vector<point> findAllPointsOnConvexHull(vector<point> pointVector);

// Prints out the points on the convex hull in the correct format.
//@pre pointVector exists and has elements in it
//@post the points will be printed out in the desired format
//@usage printPointsOnConvexHull(convexHullPoints);
void printPointsOnConvexHull(vector<point> pointVector);

// Reads point values from a file in4.dat in a specified format
//@pre a vector of points, pointVector, exists
//@post the points from the file populate pointVector
//@usage readPointsFromFile(pointVector)
void readPointsFromFile(vector<point> &pointVector);


int main(int argc, char ** argv)
{
    vector<point> pointVector;
    readPointsFromFile(pointVector);
    vector<point> convexHullPoints = findAllPointsOnConvexHull(pointVector);
    printPointsOnConvexHull(convexHullPoints);

    return 0;
}

// Reads point values from a file in4.dat in a specified format
//@pre a vector of points, pointVector, exists
//@post the points from the file populate pointVector
//@usage readPointsFromFile(pointVector)
void readPointsFromFile(vector<point> &pointVector)
{
    ifstream infile;
    int NumPoints;
    infile.open ("in4.dat");
    //vector<point> pointVector;
    if (infile.is_open())
    {
        infile >> NumPoints;
        for(int i = 0; i < NumPoints; i++)
        {
            pointVector.push_back(point());
            infile >> pointVector[i].x;
            infile >> pointVector[i].y;
        }
        infile.close();
    }
    infile.close();
}

// Calculates the 'a' in our equation: ax + by - c = 0
//@pre y1, and y2 are integers
//@returns a double with our 'a' value for our equation
//@usage int a = calculateA(y1, y2);
double calculateA(double y1, double y2)
{
    return y2 - y1;
}

// Calculates the 'b' in our equation: ax + by - c = 0
//@pre x1, and x2 are integers
//@returns a double with our 'b' value for our equation
//@usage int b = calculateB(x1, x2);
double calculateB(double x1, double x2)
{
    return x1 - x2;
}

// Calculates the 'c' in our equation: ax + by - c = 0
//@pre x1, x2, y1, and y2 are integers
//@returns a double with our 'c' value for our equation
//@usage int c = calculateC(x1, x2, y1, y2);
double calculateC(double x1, double x2, double y1, double y2)
{
    return x1 * y2 - y1 * x2;
}

// Determines the sign value of a point
//@pre a, b, c, x and y are all integers
//@returns a double with a value of 1, -1 or 0
//@usage int signValue = determineSignValueOfPoint(a, b, c, pointVector[i].x, pointVector[i].y);
int determineSignValueOfPoint(double a, double b, double c, double x, double y)
{
    int value = a * x + b * y - c;

    if (value < 0)
        return -1;
    else if (value > 0)
        return 1;
    return 0;
}

// Determines if a given two points are on the Convex Hull
//@pre pointVector has input values, x1, y1, x2 and y2 do not form a vertical or horizontal line
//@returns true or false, whether the set of points are on Convex Hull
//@usage if (determineIfPointsOnConvexHull(x1, y1, x2, y2, pointVector))
bool determineIfPointsOnConvexHull(double x1, double y1, double x2, double y2, vector<point> pointVector)
{
    //Calculate a, b, and c values
    double a = calculateA(y1, y2);
    double b = calculateB(x1, x2);
    double c = calculateC(x1, x2, y1, y2);

    //Determine the number of points that the vector contains, subtract 2 to account for
        //two points being tested
    int numPoints = pointVector.size() - 2;
    int signCount = 0;

    //Determine whether all subsequent points have the same sign
    for (int i = 0; i < pointVector.size(); i++)
    {
        int signValue = determineSignValueOfPoint(a, b, c, pointVector[i].x, pointVector[i].y);
        signCount += signValue;
    }

    if (signCount == numPoints || -signCount == numPoints)
        return true;

    return false;
}

// Goes through all possible points and finds all the points that are on the Convex Hull
// and puts those points in an new vector.
//@pre pointVector has input values
//@post all the points that are a part of the convex hull are not in the new vector of points
//@returns a vector containing all the points that are on the convex hull
//@usage vector<point> convexHullPoints = findAllPointsOnConvexHull(pointVector);
vector<point> findAllPointsOnConvexHull(vector<point> pointVector)
{
    vector<point> pointsOnConvexHull;
    for (int i = 0; i < pointVector.size(); i++)
    {
        for (int j = i + 1; j < pointVector.size(); j++)
        {
            double x1 = pointVector[i].x;
            double y1 = pointVector[i].y;
            double x2 = pointVector[j].x;
            double y2 = pointVector[j].y;

            if (determineIfPointsOnConvexHull(x1, y1, x2, y2, pointVector))
            {
                //Add both points to vector
                point point1 = {x1, y1};
                point point2 = {x2, y2};
                pointsOnConvexHull.push_back(point1);
                pointsOnConvexHull.push_back(point2);
            }

        }
    }
    return pointsOnConvexHull;
}

// Prints out the points on the convex hull in the correct format.
//@pre pointVector exists and has elements in it
//@post the points will be printed out in the desired format
//@usage printPointsOnConvexHull(convexHullPoints);
void printPointsOnConvexHull(vector<point> pointVector)
{
    cout << endl << endl <<"Points on the Convex Hull:" << endl;
    for (int i = 0; i < pointVector.size() - 1; i+=2)
    {
        cout << "     (" << pointVector[i].x << ", " << pointVector[i].y << ")" << " and ";
        cout << "(" << pointVector[i + 1].x << ", " << pointVector[i + 1].y << ")" << endl;
    }
    cout << endl << endl;
}



