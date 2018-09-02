//@file hull6.cpp
//@author Miranda Myers (mmyers4)
//@author Sarah Prata
//@date 3/18/15

//Program accomplishes the following:
// * Finds the pairs of extreme points that are to be connected to form the boundary of 
//   the convex hull of a set of points by the recursive QuickHull “divide and conquer” 
//   algorithm
// * Does the partition and recursive calls per the design of QuickHull

#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include <math.h> 
using namespace std;

//********** NOTE TO DR. Y: per our meeting on Monday: This program seg faults when points
//                          are entered with a value of .1, (but not in all cases):
// Here is an example input file that causes this issue
/*
16
-3.1 1.1
-2 4
-1.1 2.1
1 -3
1 1
3 -1
3 6
3 10
4 4
5.1 -2.1
6.1 1.1
6 3
6 10.1
7 7.1
8 9.1
9 2.1
*/

//A structure that defines a point
//Contains two elements, x coordinate and y coordinate
struct point
{
    double x;
    double y;
};


//Finds the convex hull given a set of points
//@pre An array exists of n ≥ 2 points sorted in nondecreasing order of their x coordinates, 
//       with ties resolved by increasing order of the y coordinates of the points
//@post the global variable convex hull is populated with the points on the convex hull
//@usage quickHull(pointVectorInput, convexHull)
void quickHull(vector<point> pointVectorInput, vector<point> &convexHull);

//Finds points on the convex hull given a set of points, that are on the left side of the 
//      line from point1 to point2
//@pre a vector of points on one side of the line and two points to define the line exist
//@post recursively builds the convex hull using variable convexHull
//@usage findHull(pointVectorOneSide, point1, point2, convexHull)
void findHull(vector<point> pointVectorOneSide, point point1, point point2, vector<point> &convexHull);

//Given a vector of points and a point in the vector, finds the index location of the point
//      in the vector, used to insert points in the correct location in the convex hull
//@pre A point vector exists, and the given point is in the vector
//@post Returns the index of the point
//@usage int pointLocation = findLocationOfAPoint(pointVector, pointToFind)
int findLocationOfAPoint(vector<point> pointVector, point pointToFind);

//Given a list of points and two points that make up a line, finds the points that are to
//      the left of the line using the determinant formula
//@pre A point vector and two points exist
//@post Returns a list of points, returns empty list if no points on left of line
//@usage vector<point> leftPoints = findPointsOnLeftofLine(pointVector, point1, point2)
vector<point> findPointsOnLeftofLine(vector<point> pointVector, point point1, point point2);

//Calculates the 'a' in our equation: ax + by - c = 0
//@pre y1, and y2 are integers
//@post Returns a double with our 'a' value for our equation
//@usage double a = calculateA(y1, y2);
double calculateA(double y1, double y2);

//Calculates the 'b' in our equation: ax + by - c = 0
//@pre x1, and x2 are integers
//@post Returns a double with our 'b' value for our equation
//@usage double b = calculateB(x1, x2);
double calculateB(double x1, double x2);

//Calculates the 'c' in our equation: ax + by - c = 0
//@pre x1, x2, y1, and y2 are integers
//@pst Returns a double with our 'c' value for our equation
//@usage double c = calculateC(x1, x2, y1, y2);
double calculateC(double x1, double x2, double y1, double y2);

//Calculates the distance between a point and a line defined by two points
//@pre Three points exist, two to define a line
//@post Returns the distance between the point and the line
//@usage double distance = calculateDistanceBetweenLineAndPoint(point1, point2, point3)
double calculateDistanceBetweenLineAndPoint(point point1, point point2, point point3);

//Calculates the area of a triangle given three points, 
//      used to break a tie for the pMax calculation using the distance formula
//@pre Three points exist
//@post Returns the area of the triangle defined by the three points
//@usage double area = calculateTriangleArea(point1, point2, point3)
double calculateTriangleArea(point point1, point point2, point point3);

//Finds the point farthest away from the line, pMax, given two points and a set of points
//      Uses distance formula, and then triangle area calculation to resolve tie
//@pre A vector of points and two points to define a line exist
//@post Returns the pont that is the farthest away from the line
//@usage point pMax = findPmax(pointVectorOneSide, point1, point2)
point findPmax(vector<point> pointVectorOneSide, point point1, point point2);

//Determinant formula: Calculates the determinant given three points
//      Used to check whether a point lies to the left of the line determined by two other
//      points as well as find the distance from the point to the line
//@pre Three points exist
//@post Returns the determinant of the three points
//@usage double determinant = calculateDeterminant(point1, point2, point3)
double calculateDeterminant(point point1, point point2, point point3);

//Reads point values from a file in6.dat in a specified format
//@pre A vector of points, pointVector, exists
//@post The points from the file populate pointVector
//@usage readPointsFromFile(pointVector)
void readPointsFromFile(vector<point> &pointVectorInput);

//Prints out the points on the convex hull in the correct format.
//@pre pointVector exists and has elements in it
//@post The points are printed out in the desired format
//@usage printPointsOnConvexHull(convexHullPoints)
void printPointsOnConvexHull(vector<point> pointVector);


int main()
{
    vector<point> convexHull;
    vector<point> pointVectorInput;
    readPointsFromFile(pointVectorInput);

    quickHull(pointVectorInput, convexHull);
    printPointsOnConvexHull(convexHull);

    return 0;
}


//Finds the convex hull given a set of points
//@pre An array exists of n ≥ 2 points sorted in nondecreasing order of their x coordinates, 
//       with ties resolved by increasing order of the y coordinates of the points
//@post the global variable convex hull is populated with the points on the convex hull
//@usage quickHull(pointVectorInput, convexHull)
void quickHull(vector<point> pointVectorInput, vector<point> &convexHull)
{
    //Add P1 and Pn (left and right points) to convex hull
    point p1 = pointVectorInput[0];
    point pn = pointVectorInput[pointVectorInput.size() - 1];
    convexHull.push_back(p1);
    convexHull.push_back(pn);
    
    //Divide points into groups S1 and S2 
    //    S1: points in S on the left side of the line p1 to pn 
    //    S2: points in S on the right side of the line p1 to pn
    vector<point> leftSidePointsS1 = findPointsOnLeftofLine(pointVectorInput, p1, pn);
    vector<point> leftSidePointsS2 = findPointsOnLeftofLine(pointVectorInput, pn, p1);

    findHull (leftSidePointsS1, p1, pn, convexHull); 
    findHull (leftSidePointsS2, pn, p1, convexHull);
}


//Finds points on the convex hull given a set of points, that are on the left side of the 
//      line from point1 to point2
//@pre a vector of points on one side of the line and two points to define the line exist
//@post recursively builds the convex hull using variable convexHull
//@usage findHull(pointVectorOneSide, point1, point2, convexHull)
void findHull(vector<point> pointVectorOneSide, point point1, point point2, vector<point> &convexHull)
{
    if (pointVectorOneSide.size() == 0) //Base case: no points left on one side
        return;
    
    //From the given set of points, find farthest point from line of point1 to point2
    point pMax = findPmax(pointVectorOneSide, point1, point2);
        
    //Add point pMax to convex hull at the location between point1 and point2
    int point2Location = findLocationOfAPoint(convexHull, point2);
    //vector<int>::iterator it;
    //it = convexHull.begin();
    //it = convexHull.insert (it , point2Location);
    convexHull.insert(convexHull.begin() + point2Location, pMax);
    
    //Three points point1, point2, and pMax partition the remaining points 
    //    S1: points on the left side of the line point1 to pMax 
    //    S2: points on the left side of the line pMax to point2
    vector<point> pointVectorSet1 = findPointsOnLeftofLine(pointVectorOneSide, point1, pMax);
    vector<point> pointVectorSet2 = findPointsOnLeftofLine(pointVectorOneSide, pMax, point2);
    
    findHull(pointVectorSet1, point1, pMax, convexHull); 
    findHull(pointVectorSet2, pMax, point2, convexHull);
}


//Given a vector of points and a point in the vector, finds the index location of the point
//      in the vector, used to insert points in the correct location in the convex hull
//@pre A point vector exists, and the given point is in the vector
//@post Returns the index of the point
//@usage int pointLocation = findLocationOfAPoint(pointVector, pointToFind)
int findLocationOfAPoint(vector<point> pointVector, point pointToFind)
{
    for (int i = 0; i < pointVector.size(); i++)
    {
        if (pointVector[i].x == pointToFind.x and pointVector[i].y == pointToFind.y)
            return i;
    }
    
    return 0;
}


//Given a list of points and two points that make up a line, finds the points that are to
//      the left of the line using the determinant formula
//@pre A point vector and two points exist
//@post Returns a list of points, returns empty list if no points on left of line
//@usage vector<point> leftPoints = findPointsOnLeftofLine(pointVector, point1, point2)
vector<point> findPointsOnLeftofLine(vector<point> pointVector, point point1, point point2)
{
    vector<point> pointsOnLeft;
    
    //For each point in the list of given points, calculate its determinant
    //Use the sign value of the determinant to determine if point is on left side
    for (int i = 0; i < pointVector.size(); i++)
    {
        point pointToEvaluate = pointVector[i];
        double determinant = calculateDeterminant(point1, point2, pointToEvaluate);
        if (determinant > 0)
            pointsOnLeft.push_back(pointToEvaluate);
    }
    
    return pointsOnLeft;
}


//Calculates the 'a' in our equation: ax + by - c = 0
//@pre y1, and y2 are integers
//@post Returns a double with our 'a' value for our equation
//@usage double a = calculateA(y1, y2);
double calculateA(double y1, double y2)
{
    return y2 - y1;
}


//Calculates the 'b' in our equation: ax + by - c = 0
//@pre x1, and x2 are integers
//@post Returns a double with our 'b' value for our equation
//@usage double b = calculateB(x1, x2);
double calculateB(double x1, double x2)
{
    return x1 - x2;
}


//Calculates the 'c' in our equation: ax + by - c = 0
//@pre x1, x2, y1, and y2 are integers
//@pst Returns a double with our 'c' value for our equation
//@usage double c = calculateC(x1, x2, y1, y2);
double calculateC(double x1, double x2, double y1, double y2)
{
    return x1 * y2 - y1 * x2;
}


//Calculates the distance between a point and a line defined by two points
//@pre Three points exist, two to define a line
//@post Returns the distance between the point and the line
//@usage double distance = calculateDistanceBetweenLineAndPoint(point1, point2, point3)
double calculateDistanceBetweenLineAndPoint(point point1, point point2, point point3)
{
    double a = calculateA(point1.y, point2.y);
    double b = calculateB(point1.x, point2.x);
    double c = calculateC(point1.x, point2.x, point1.y, point2.y);
    
    //*******NOTE TO Dr. Y: per our meeting on Monday, here is the elimination of the
    //                      denominator of the distance function to improve efficiency
    
    double distance = abs(a * point3.x + b * point3.y - c); 
    
    return distance;
}


//Calculates the area of a triangle given three points, 
//      used to break a tie for the pMax calculation using the distance formula
//@pre Three points exist
//@post Returns the area of the triangle defined by the three points
//@usage double area = calculateTriangleArea(point1, point2, point3)
double calculateTriangleArea(point point1, point point2, point point3)
{
    return 0.5 * calculateDeterminant(point1, point2, point3);
}


//Finds the point farthest away from the line, pMax, given two points and a set of points
//      Uses distance formula, and then triangle area calculation to resolve tie
//@pre A vector of points and two points to define a line exist
//@post Returns the pont that is the farthest away from the line
//@usage point pMax = findPmax(pointVectorOneSide, point1, point2)
point findPmax(vector<point> pointVectorOneSide, point point1, point point2)
{
    double maxDistance = 0;
    point pMax;
    
    for (int i = 0; i < pointVectorOneSide.size(); i++)
    {
        point pointToCheck = pointVectorOneSide[i];
        double currentDistance = calculateDistanceBetweenLineAndPoint(point1, point2, pointToCheck);
    
        if (currentDistance > maxDistance)
        {
            maxDistance = currentDistance;
            pMax = pointToCheck;
        }
        
        else if (currentDistance == maxDistance)
        {
            double pointToCheckArea = calculateTriangleArea(point1, point2, pointToCheck);
            double pMaxArea = calculateTriangleArea(point1, point2, pMax);
            
            if (pointToCheckArea > pMaxArea)
            {
                maxDistance = currentDistance;
                pMax = pointToCheck;
            }
        }
    }

    return pMax;
}


//Determinant formula: Calculates the determinant given three points
//      Used to check whether a point lies to the left of the line determined by two other
//      points as well as find the distance from the point to the line
//@pre Three points exist
//@post Returns the determinant of the three points
//@usage double determinant = calculateDeterminant(point1, point2, point3)
double calculateDeterminant(point point1, point point2, point point3)
{
    //              x1y2 +                x3y1 +                  x2y3 −                  x3y2 −                  x2y1 −                  x1y3
    return (point1.x * point2.y) + (point3.x * point1.y) + (point2.x * point3.y) - (point3.x * point2.y) - (point2.x * point1.y) - (point1.x * point3.y);
}


//Reads point values from a file in6.dat in a specified format
//@pre A vector of points, pointVector, exists
//@post The points from the file populate pointVector
//@usage readPointsFromFile(pointVector)
void readPointsFromFile(vector<point> &pointVector)
{
    ifstream infile;
    int NumPoints;
    infile.open ("in6.dat");
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


//Prints out the points on the convex hull in the correct format.
//@pre pointVector exists and has elements in it
//@post The points are printed out in the desired format
//@usage printPointsOnConvexHull(convexHullPoints)
void printPointsOnConvexHull(vector<point> pointVector)
{
    cout << endl << endl <<"Points on the Convex Hull:" << endl;
    int i;
    for (i = 0; i < pointVector.size() - 1; i++)
    {
        cout << "     (" << pointVector[i].x << ", " << pointVector[i].y << ")" << " and ";
        cout << "(" << pointVector[i + 1].x << ", " << pointVector[i + 1].y << ")" << endl;
    }
    cout << "     (" << pointVector[i].x << ", " << pointVector[i].y << ")" << " and ";
    cout << "(" << pointVector[0].x << ", " << pointVector[0].y << ")" << endl;
    cout << endl << endl;
}




