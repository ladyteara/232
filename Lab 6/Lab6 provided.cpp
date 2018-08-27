/*
Name:
Assignment:
Date:
Description:
*/

#include <iostream>
#include <vector>
//for clock_t, clock(), CLOCKS_PER_SEC, srand(), and rand()
#include <time.h>  
#include <iomanip>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;


/**** 
*****	Exmaple of how to time a code segment.
*****
clock()	returns the number of seconds since the Epoch (a date/time 
used by computers: 00:00:00, January 1, 1970).  */
//
//clock_t startTime, endTime;  //create two variables to hold clock ticks
//long startTime = clock();  //get starting clock tick
////
//// Code that you want to time goes here.
////
//long endTime = clock();  //get ending clock tick
//
//// How to convert from clock ticks to seconds.
//double runTime = (endTime - startTime) / CLOCKS_PER_SEC;


// Bubble sort using vector iterators. We know from class that with 2 for loops
// that both depend on n, the algorithm is O(n^2).
void bubbleSort(vector<int>::iterator first, vector<int>::iterator last) {
	vector<int>::iterator i, j;
	for (i = first; i != last; i++)  //i goes to n
		for (j = first; j < i; j++)  //j goes to n-1
			if (*i < *j)
				iter_swap(i, j);  //STL: swap 2 items pointed to by iterators
}

/****	MAIN	****/
int main() {
	srand( (unsigned int)time(0) );  //seed the random number generator

	// If you want to prompt for the number of elements, here is an example.
	int n;
	cout << "Enter size of array: ";
	cin >> n;
	
	// Add 10 random ints from 0-99 to the vector.
	cout << "The unsorted vector: ";
	//int n = 10;
	vector<int> vec;
	for (int i = 0; i < n; i++) {
		vec.push_back(rand() % 100);
		cout << vec[i] << ", ";
	}
	cout << endl << endl;


	int k = 9;
	clock_t startTime2, endTime2;
	startTime2 = clock();  //get starting clock tick
	for (int i = 0; i < n; i++)
	{
		if (k == vec[i])
			cout << k << " was found at " << i << endl;
		for (int i = 0; i < 100000; i++)

			int a = 100000 * 100000;
	}
	endTime2 = clock();  //get ending clock tick

	// How to convert from clock ticks to seconds.
	double runTimeL = double(endTime2 - startTime2) / CLOCKS_PER_SEC;

	
	// Sort the vector and print.
	clock_t startTime, endTime;  //create two variables to hold clock ticks
	startTime = clock();  //get starting clock tick
	bubbleSort(vec.begin(), vec.end());
	endTime = clock();  //get ending clock tick

	// How to convert from clock ticks to seconds.
	double runTime = double(endTime - startTime) / CLOCKS_PER_SEC;

	cout << "The sorted vector:";
	for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		cout << *it << ", ";
	cout << endl << endl;

	cout << std::fixed << std::setprecision(12);
	cout << "Linear Run Time for " << n << "     :  " << runTimeL << endl;
	cout << "Bubble Sort Run Time for " << n << ":  " << runTime << endl;
	
	cout << endl;
	// The clock started ticking when the program started. Get the clock 
	// now and calculate the elapsed time for the program.
	int timeItTook = clock();
	cout << "This program took " << timeItTook << " clicks ("
		<< (double)timeItTook / CLOCKS_PER_SEC << " seconds)." << endl;

	getchar();  //keep output window open
	return 0;   //return success
}
