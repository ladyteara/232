/*
 Name:	Tara Walton
Date:	08/21/15
Assignment:	Lab 4 - Due Monday, Sept 16, 2015 @ 2359
Platform/IDE: MS Visual Studio 2013

Description: Complete the function implementations using the string API such that all tests pass
			Learning to use the string member functions to complete each test in runALLtests.
  */

#include <cstdlib>
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;

// A generic test function, that prints "PASSED" if b is true
// and otherwise prints false. Do not modify this function.
void test(string message, bool b) {
	cout.width(30);
	cout << message;
	cout.width(10);
	if (b)
		cout << " PASSED\n";
	else
		cout << " FAILED\n";
}

// Returns the length of a string.
int stringLength(string s) {
	return s.length();
}

// Converts a string to the empty string.
string stringClear(string s) {
	s.clear();
	return s; 
}

// Returns true if the string is empty.
bool stringEmpty(string s) {
	if (s.length() == 0)
		return true;
	return false; 
}

// Returns the character of a string at a given index.
char charAt(string s, int index) {
	return s.at(index); 
}

// Returns a concatenation of strings left and right.
string stringAppend(string left, string right) {
	return left + right;
}

// Returns the result of inserting a string into another.
string stringInsert(string s, string toInsert) {
	return s.insert(7, toInsert); // stub
}

// Erases part of a string.
string stringErase(string s) {
	//cout << "_" << s.erase(5, 19) << "_";
	return s.erase(5, 19);
}

// Replaces part of a string.
string stringReplace(string s)
{
	return s.replace(0, 7, "Things");
}

// Returns the first index of character c in string s.
int stringFind(string s, char c) {
	return s.find(c);
}

// Returns the last index of character c in string s.
int stringRFind(string s, char c) {
	return s.rfind(c);
}

// Returns the index of the first occurance of character c.
int stringFirst(string s, char c)
{
	return s.find_first_of(c); 
}

// Returns the index of the first character in the string that is not c.
int stringFirstNot(string s, char c) {
	return s.find_first_not_of(c); 
}

//Returns part of a string.
string stringSubstring(string s) {
	//cout << s.substr(7, 7);
	return s.substr(7, 7);
}


// Returns the first name, given a full name.
string firstName(string s) {
	s.resize(s.find(' '));
	//cout << s;
	return s; 
}

//Returns the middle name, given a full name.
string middleName(string s) {
	short firstLetter = s.find_first_of(' ') + 1;
	short lastLetter = s.find_last_of(' ');
	return s.substr(firstLetter, lastLetter - firstLetter); //first letter, length
}

// Returns the last name, given a full name.
string lastName(string s) {
	//cout <<"_"<< s.substr(s.rfind(' ')+1, s.length())<<"_";
	return s.substr(s.rfind(' ') + 1, s.length()); 
}

// Returns a capitalized version of a string
string capitalize(string s) {
	s[0] = toupper(s[0]);
	return s;
}

// Returns true if the string contains character c.
bool include(string s, char c) {
	if (s.find(c) != string::npos)
	{
		return true;
	}
	return false; 
}

// Returns a string substituting character target with character replacement.
string substitute(string s, char target, char replacement) {
	do 
	{
		s.replace(s.find(target), 1, 1, replacement);
	} 
	while (s.find(target) != string::npos);
	//cout << s; 
	return s;
}

// Test suite. Read but do not modify.
void runAllTests()
{
	test("Testing length()", stringLength("Now") == 3);
	test("Testing clear()", stringClear("Is") == "");
	test("Testing empty()", stringEmpty(""));
	test("Testing at()", charAt("Elephant", 3) == 'p');
	test("Testing append()", stringAppend("There's a ", "natural mystic.") == "There's a natural mystic.");
	test("Testing insert()", stringInsert("If you carefully.", "listen ") == "If you listen carefully.");
	test("Testing erase()", stringErase("This could be the first trumpet") == "This trumpet");
	test("Testing replace()", stringReplace("Strings are not the way") == "Things are not the way");
	test("Testing find()", stringFind("Have to face reality now.", 'o') == 6);
	test("Testing rfind()", stringRFind("Have to face reality now.", 'o') == 22);
	test("Testing find_first_of()", stringFirst("XXXXOXXX", 'O') == 4);
	test("Testing find_first_not_of()", stringFirstNot("XXXXOXXX", 'X') == 4);
	test("Testing substr()", stringSubstring("Such a natural mystic") == "natural");

	test("Testing firstName()", firstName("Robert Nesta Marley") == "Robert");
	test("Testing middleName()", middleName("Robert Nesta Marley") == "Nesta");
	test("Testing lastName()", lastName("Robert Nesta Marley") == "Marley");
	test("Testing capitalize()", capitalize("eager") == "Eager");
	test("Testing include()", include("Robert", 'o'));
	test("Testing substitute()", substitute("The Gxxgle", 'x', 'o') == "The Google");
}

int main() {

	cout << "Testing your functions...\n\n";
	runAllTests();

	cin.ignore();
	return 0;
}