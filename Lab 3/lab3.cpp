/*
Name: Tara Walton
Date: Tues, Sept 8, 2015
Assignment: Getting to know Classes
Platfrom/IDE: Windows 10 MS Visual Studio 2013

Description: Using classes, vectors and functions
*/

#include <iostream>
#include <math.h>  //for sqrt() if you add a distance method
#include <vector>

using std::cout;
using std::endl;
using std::ostream;
using std::vector;


// Class to represent a 2D point.
class Point {

	public:
	Point();  //standard default constructor
	Point(const Point& pt);  //copy constructor
	~Point();  //default destructor
	float getX() const;  //get x-coord
	float getY() const;

	void setX(const float x);  //set the x-coord value
	void setY(const float y);
	void translate(const float dx, const float dy);  //move a point
	void revert();
	float distance(const Point b); //? Not working

	// Override for printing a point. Designate as friend so that
	// it can access private class members.
	friend ostream& operator <<(ostream& ostreem, const Point& pt);

	// Class fields.
	private:
	float xCoord;  //x coordinate
	float yCoord;  //y coordinate
	float xOld, yOld;

};

/*	A standard default constructor. You must manually initialize
	all class fields in the body. */
Point::Point() {
	// <Insert code to initialize all class fields here>
	xCoord = 0; yCoord = 0; 
	xOld = xCoord; yOld = yCoord;
}

 //Copy constructor.
Point::Point(const Point& pt) {
	xCoord = pt.xCoord;
	yCoord = pt.yCoord;
	xOld = pt.getX();
	yOld = pt.getY();
}

// Default destructor.
Point::~Point() { }

// Getters.
float Point::getX() const {
	return xCoord; 
}

float Point::getY() const
{
	return yCoord;
}


// Setters.
void Point::setX(const float x) {
	xCoord = x;
}

void Point::setY(const float y)
{
	yCoord = y;
}

// Translate the existing point by delta x and delta y.
void Point::translate(const float dx, const float dy) {
	xOld = xCoord;		yOld = yCoord;
	xCoord += dx;
	yCoord += dy;
}


void Point::revert()
{
	xCoord = xOld;
	yCoord = yOld;
}

float Point::distance(const Point b)
{
	float	aX = getX(), aY = getY(),
		bX = b.getX(), bY = b.getY();
	float dist = sqrt(pow((aX + bX), 2) + pow((aY + bY), 2));
	return dist;
}

// Print a point using familiar notation. Overrides the output
// operator.
ostream& operator<<(ostream& ost, const Point& p) {
	cout << "(" << p.xCoord << ", " << p.yCoord << ")";
	return ost;
}

int main() {
	
	// Create a few points.
	Point a;  //uses default constructor
	Point b;

	// Print point a.
	a.setX(0.0);
	a.setY(0.0);
	/*cout << "The x-coord of point A is " << a.getX() << endl;
	cout << "The y-coord of point A is " << a.getY() << endl;*/
	cout << a <<endl;

	// Print point b.
	b.setX(1.5);
	b.setY(3.0);
	/*cout << "The x-coord of point B is " << b.getX() << endl;
	cout << "The y-coord of point B is " << b.getY() << endl;*/
	cout << b << endl;
	
	Point c = b;  //uses  copy constructor
	/*cout << "The x-coord of point C is " << c.getX() << endl;
	cout << "The y-coord of point C is " << c.getY() << endl;*/
	// Print point c using the override << operator
	cout << c << endl;

	b.translate(0.5, 2);
	cout << "Translated B to: " << b << endl;

	b.revert();
	cout << "Reverted B to " << b << endl;

	// Name point c; set it to (3.0, 4.0)



	//Create a vector of 3 pts
	cout << "\n\nCreate a vector of 3 pts" << endl;
	vector<Point> myVector(3);
	cout << "[ ";
	for (int i = 0; i < 3; i++)
	{
		cout << myVector.at(i) << " ";
	}
	cout << "]\n";

	//translate the first point and reprint.
	cout << "\nTranslate the first point and reprint." << endl;
	myVector.at(0).translate(3.0, 4.0);
	cout << "[ ";
	for (int i = 0; i < 3; i++)
	{
		cout << myVector.at(i) << " ";
	}
	cout << "]\n";
	//translate thesecond pt and reprint.
	cout << "\nTranslate the second point and reprint." << endl;
	myVector.at(1).translate(5.0, 1.5);
	cout << "[ ";
	for (int i = 0; i < 3; i++)
	{
		cout << myVector.at(i) << " ";
	}
	cout << "]\n";
	//revert and reprint
	cout << "\nRevert and reprint." << endl;
	myVector.at(1).revert();
	cout << "[ ";
	for (int i = 0; i < 3; i++)
	{
		cout << myVector.at(i) << " ";
	}
	cout << "]\n";

	float dist = a.distance(b);
	cout << "\n\nThe distance between A " <<a << " and B "<<b<<", is " << dist << endl;

	std::cin.ignore();
	return EXIT_SUCCESS;
}