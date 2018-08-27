/*
Name:	Tara Walton
Date:	08/21/15
Assignment:	Asn 1 - Due Monday, August 31, 2015 @ 2359
Platform/IDE: MS Visual Studio 2013

Description:
Initial code written by Mr. Bell
Additional code added includes "parlor trick" for calculating a 3 digit giving the original digit followed by (my) age
*/

#include <cstdlib>
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
int main()
{ /*
	// This is the first few sentences from the book "Tarzan," by Edgar Rice Burroughs
	string s = "IhadthisstoryfromonewhohadnobusinesstotellittomeortoanyotherImaycredittheseductiveinfluenceofanoldvintageuponthenarratorforthebeginningofitandmyownskepticalincredulityduringthedaysthatfollowedforthebalanceofthestrangetaleWhenmyconvivialhostdiscovered";

	// Declare a variable named c, whose type is array of char and
	// whose size is the same as the length of the string s

	// GCC compatible IDEs will accept array c declared this way:
	// char c[ s.size() ];

	// In VS, this is what works:
	char* c = new char[s.size()];   //an array and a pointer to an array
	//are the same
	int size = s.size();  //VS disallows use of s.size() in for loops below
	//so assign it to an int first
	char temp;

	// Print the data, one character at a time
	// GCC compatible IDEs allow direct use of s.size() in the
	// for loop headers below, like this: for (int i = 0; i < s.size(); i++)
	for (int i = 0; i < size; i++)
	{
		c[i] = s[i]; // c[] is an array of chars, s is a string
		cout << "c[" << i << "]: " << c[i] << std::endl;
	}

	// Sort the characters in the c[] array
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (c[i] > c[j])
			{
				temp = c[i];
				c[i] = c[j];
				c[j] = temp;
			}
		}
	}

	// Print the sorted data
	for (int i = 0; i < size; i++)
	{
		cout << c[i];
	}
	cout << std::endl;
*/

	//CODE ADDED BY TARA
	unsigned short var = 0;
	for (short i=1; i <= 9; i++)
	{
		var = i * 2;
		var += 5;
		var *= 50;
		var += 2015;  //corrected to current year for parlor trick to work
		var -= 251;
		var -= 1984;
		cout << "Current chosen value is " << i << ", so the three-digit number is " << var << std::endl;
	}
}