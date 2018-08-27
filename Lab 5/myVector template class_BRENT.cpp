/*

INSTRUCTIONS

	The program below is an almost complete templated class. 
	It is also an example of good coding style following 
	guidelines in the Coding Style Cheat Sheet.
	
	Your mission is to complete this program. Search for
	"///ADD" to find each of the 7 places where code is needed.
	Code for setting up the template is already included and
	correct so you only need knowledge of classes and
	overloading to make this program work.

	Grading:
	Correctly code and get working all 3 declarations plus
	95% = 4 working methods
	85% = 2-3 working methods
	75% = 1 working method

	Submit what you have completed by the end of class. I may 
	extend the due date depending on how it goes.
*/

/*	***                                                 ***
	*** The cost of not completing this section on this ***
	*** assignment is 15%. It's your call...            ***
	***                                                 ***

---> DELETE THIS LINE AND EVERYTHING ABOVE BEFORE SUBMITTING <--- */
/*
Name: Brent Eaves
Date: 09/29/2015
Assignment: Lab5 - Templates and Classes
Platfrom/IDE: MS Visual Studio 2013/Windows 8.1

Description: Finding the 7 locations in nearly-complete code that are missing appropriate code, all involving templates and classes


*/

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::ostream;

/*
	This is a forward declaration for the class. It
	is required in 2 instances:
	1) for code compatibility between VS and Xcode
	2) when a friend is declared in a templated class

	This program falls under #2 for the << overload.

	Forward declarations make more sense if you keep
	in mind that the class declaration is usually in
	a separate file from the class definitions. They
	tell the compiler that a class or function will be
	instantiated as a template instead of being tied
	to one data type.
*/
template <typename T> class myVector;

/*	
	This forward declaration tells the compiler to instantiate
	the << overload as a template and not as a function
	tied to a specific data type i.e. as operator<< <T> instead
	of operator<< <int>.*/
template <typename T>
ostream& operator<< (ostream& out, const myVector<T>& v);


/*	
	This class implements basic vector functionality using
	using a class template. It stores its data in an array.
	The constructors use 'new' to allocate storage, therefore
	the destructor is required.
*/
template <typename T>
class myVector {
	public:
	myVector(int size = 10); //constructor - set size
	///ADD DECLARE CONSTRUCTOR THAT SETS SIZE AND VALUES
	myVector(const int size, const int value);
	///ADD DECLARE DESTRUCTOR
	~myVector();

	// Getters.
	///ADD DECLARE FOR at() METHOD HERE
	int size() const;  //get size
	T& at(const int index) const;

	// Setters.
	void assign(const int value);  //set every element to value
	void insert(const int index, const T& value);  //insert at index

	// Overloads.
	T& operator[] (const int index);  //for subscripting

	// Even with the forward declaration, have to remind the compiler
	// here that this is a template function. Do that by adding the <T>
	// after operator<<.
	friend ostream& operator<< <T>(ostream& out, const myVector<T>& v);

	// Class object.
	private:
	T* arr;  //array of elements
	int arrSize; //array size
};

/*	Constructors
*/
template <typename T>  //default 
myVector<T>::myVector(int size) {
	///ADD CODE HERE. For hint, see DSA 2.3.2 or 09/28 lecture slides.
	arrSize = size;
	arr = new T[arrSize]; //allocate array storage
}

template <typename T>  //specify size and initial value of elements
myVector<T>::myVector(const int size, const int value) {
	///ADD CODE HERE
	arrSize = size;
	arr = new T[arrSize];
	for (int i = 0; i < arrSize; i++) {
		arr[i] = value;
	}
}

// *REQUIRED* since we used "new" in the constructors, otherwise
// the program will leak memory.
template <typename T>
myVector<T>::~myVector() {
	/*	Optional: uncomment the next line to see when
		the destructor gets called. Note that normally
		you do not put cout statements in constructors
		or destructors.*/
	//cout << "Deleting myVector." << endl;
	delete [] arr;
}

/*
	Getters.
*/
// Return element at index with subscript boundary checking.
template <typename T>
T& myVector<T>::at(const int index) const {
	/*	Standard technique when required to return a
		template type. First set to null. If conditions are
		satisfied, set value to something 'real'. In
		case of an error value will still be null. The
		caller can then check for null to verify 
		if valid data was returned or not.
	*/
	T value = NULL;

	if ((index >= 0) && (index < arrSize))
		value = arr[index];
	else
		cout << "at: Index out of bounds!" << endl;

	return value;
}

// Get size.
template <typename T>
int myVector<T>::size() const {
	///ADD CODE HERE
	return arrSize;
}

/*
	Setters.
*/
// Set every element to value.
template <typename T>
void myVector<T>::assign(const T& value) {
	///ADD CODE HERE
	for (int i = 0; i < arrSize; i++) {
		arr[i] = value;
}

// Insert at index.
template <typename T>
void myVector<T>::insert(const int index, const T& value) {
	///ADD CODE HERE
	///if index is valid, then put value into the array
	///otherwise output an error message.
	if (index <= 0) && (index < arrSize) {
		arr[index] = value; //T missing a closing }
}

/*
	Overloads.
*/
// Array subscripting overload.
template <typename T>
T& myVector<T>::operator [](const int index) {
	///ADD CODE HERE
	T& myVector::operator[](int index) {
		return arr[index];
	}
}

// Output operator overload. Print vector as [1, 2, 3] but
// don't include trailing endl in this function.
template <typename T>
ostream& operator <<(ostream& out, const myVector<T>& v) {
	///ADD CODE HERE
	//T this is what I used
	cout << "[ ";
	for (int j = 0; j < v.size(); j++)
	{
		cout << v.at(j) << " ";
	}
	cout << "]";
	return out;
}

/*
	Test on a subset of steps from Lab2 - Vectors. 
	It's the same code except that printing is 
	easier because we overloaded <<.
*/
void lab2Tests() {
	// 1 Initialize to size 5, elements all = 99
	myVector<int> v(5, 99);
	cout << "1) all elements = 99" << endl;
	cout << v << endl;

	//2
	v.assign(0);
	cout << "2) now all = 0" << endl;
	cout << v << endl;

	//4
	cout << "4) current size is " << v.size() << endl;

	//5
	cout << "5) insert 100 as first element" << endl;
	v.insert(0, 100);
	cout << v << endl;

	//9
	cout << "9) fill vector with numbers from 0-4" << endl;
	for (int i = 0; i < v.size(); i++)
		v.insert(i, i);
	cout << v << endl;

}// End Lab2 tests.


/*** Main ***/
int main() {

	// Execute subset of code from Lab2 Vectors.
	lab2Tests();
	
	// Test on other data types
	myVector<double> dv(20); // vector of 20 doubles
	myVector<string> sv(10); // vector of 10 strings

	dv[0] = 3.14;
	cout << "First element of double vector is "
		<< dv[0] << endl;

	sv[0] = "Hello, World!";
	cout << "First element of string vector is "
		<< sv[0] << endl;

	system("pause");  //keep output window open
	return EXIT_SUCCESS;  //return a value on exit
}