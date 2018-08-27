/*
Name:	Tara Walton
Date:	08/25/15 
Assignment: Lab 2 - Due Friday Aug 28, 2015 @ 2359 
Platform/IDE: Windows 10 - MS Visual Studio 2013	

Description: Vectors - create and use vectors from the stl
*/

#include <iostream>  //for console output
#include <vector>    //vector support
#include <algorithm> //for random numbers
#include <ctime>	//CLOSER TO RANDOM NUMBERS

// Ok for this lab so that you don't have to prefix 
// with std::. Comment this out and see what happens!
using namespace std;


bool compare(int & a, int & b)
{
	return  a < b;
}

int main ()
{	/*// Ouput 5 random myVector from 0-9
	for (int i = 0; i < 5; i++) 
	{
		int digit = rand () % 10;  //int between 0-9
		cout << "The next digit is " << digit << endl;
	}
	cout << endl << endl;*/
	
	/*Step 3 - Create a vector w/ 5 entries of 99 */
	cout << "\nStep 3 - Create a vector w/ 5 entries of 99\n";
	vector<int> myVector (5, 99);

	/*Step 4 - Print each element*/
	cout << "\nStep 4 - Print each element\n";
	int vSize = myVector.size();
	//cout << vSize;
	cout << "[ ";
	for (int i = 0; i < vSize; i++)
	{
		cout << myVector.at(i) <<" ";
	}
	cout << "]\n";

	/*Step 5 - Set all elements to 0*/
	cout << "\nStep 5 - Set all elements to 0\n";
	myVector.assign(5, 0);
	cout << "[ ";
	for (int j = 0; j < vSize; j++)
	{
		cout << myVector.at(j) <<" ";
	}
	cout << "]\n\n";

	/*Step 6 - resize to 7, and fill vector with 71- 77*/
	cout << "Step 6 - resize to 7, and fill vector with 71- 77\n";
	myVector.resize(7);
	vSize = myVector.size();
	cout << "[ ";
	for (int k = 0; k < vSize; k++)
	{
		myVector.at(k) = 71 + k;
		cout << myVector.at(k) <<" ";
	}
	cout << "]\n\n";

	/*Step 7 - delete the last element, print size */
	cout << "Step 7 - delete the last element, print size\n";
	myVector.pop_back();
	cout << "After deleting the last entry, we have a vector size of " << myVector.size() << endl << endl;

	/*Step 8 - insert 100 before first element*/
	cout<<"Step 8 - insert 100 before first element\n";
	myVector.insert(myVector.begin(), 100);
	//cout << myVector.size() << endl;


	/*Step 9 - resize to 10*/
	cout << "Step 9 - resize to 10\n";
	myVector.resize(10);
	vSize = myVector.size();

	/*Step 10 - create an iterator for the vector*/
	cout << "Step 10 - create an iterator for the vector\n"; 
	vector<int>::iterator it = myVector.begin();

	/*Step 11 - Use iterator to print elements */
	cout << "Step 11 - Use iterator to print elements\n";
	cout << "[ ";
	for (; it != myVector.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << "]\n\n";

	/*Step 12 - Use an iterator to replace each element with a random number 0 - 9*/
	cout << "Step 12 - Use an iterator to replace each element with a random number 0 - 9\n";
	vector<int>::iterator it2 = myVector.begin();
	srand(time(0));  //generates different randomg numbers every time prog is ran. see #include <ctime>
	cout << "And the random vector is... [ ";
	for (; it2 != myVector.end(); ++it2)
	{
		int randumb = rand () % 10;
		it2 = myVector.erase(it2);
		it2 = myVector.insert(it2, randumb);
		cout << *it2 << " ";
	}
	cout << "]\n\n";

	/*Step 13a - Sort and print.*/
	cout << "Step 13a - Sort and print.\n";
	sort(myVector.begin(), myVector.end(), compare);
	cout << "Sorted:   [ ";
	for (int i = 0; i < vSize; i++)
	{
		cout << myVector.at(i) << " ";
	}
	cout << "]\n\n";

	/*Step 13b - Shuffle, then print.*/
	cout << "Step 13b - Shuffle, then print.\n";
	random_shuffle(myVector.begin(), myVector.end());
	cout << "Shuffled: [ ";
	for (int i = 0; i < vSize; i++)
	{
		cout << myVector.at(i) << " ";
	}
	cout << "]\n\n";

	cin.ignore ();  //keep output window open
	return EXIT_SUCCESS;  //return a value on exit
}