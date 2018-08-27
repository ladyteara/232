/*
Name:	Tara Walton
Date:	09/0/2015
Assignment:	Asn 2 - Due Wed, Sept 9, 2015 @ 2359
Platform/IDE: Windows 10 - MS Visual Studio 2013

Description:
A brief dice game of Jack and Jill
*/

#include<time.h>
#include<iostream>
#include<iomanip>
#include<string>

using std::cout; using std::endl;

int main()
{ 
	cout << "It's a race to the top of the hill!" << endl;
	cout << "First player to 20 wins, but don't land on your opponent \n or you'll fall back down the hill!" << endl << endl;

	short roll=0, Jack=0, Jill=0;
	bool win = false;
	std::string winner = " ";

	srand(time(NULL));
	cout << std::setw(6) << "Roll" << std::setw(6) << "Jack" << std::setw(6) << "Jill" << endl;
	cout << std::setw(32) << cout.fill('-');
	cout.fill(' '); cout << endl;

	do {
		/*Jack's turn*/
		roll = rand() % 6 + 1; 
		Jack += roll; 
		if (Jack == Jill)
		{
			Jill -= rand() % 3 + 1;
			if (Jill < 0) //If tumble goes back to a negative number, set to beginning.
			{
				Jill = 0;
			}
			cout << std::setw(6) << roll << std::setw(6) << Jack << std::setw(6) << Jill;  //Output Jack and Jill.
			cout << "   Jill tumbles!" << endl;
		}
		else {
			cout << std::setw(6) << roll << std::setw(6) << Jack << std::setw(6) << ' ' << endl; //Output only Jack.
		}
		if (Jack >= 20)
		{
			winner = "Jack";
			win = true;	
		}
		else{
			/*Jill's Turn*/
			roll = rand() % 6 + 1;
			Jill += roll;
			if (Jill == Jack)   
			{
				Jack -= rand() % 3 + 1;
				if (Jack < 0)	//If tumble goes back to a negative number, set to beginning.
				{
					Jack = 0;
				}
				cout << std::setw(6) << roll << std::setw(6) << Jack << std::setw(6) << Jill;  //Output Jack and Jill.
				cout << "   Jack tumbles!" << endl;
			}
			else {
				cout << std::setw(6) << roll << std::setw(6) << ' ' << std::setw(6) << Jill << endl; //Output only Jill.
			}
			if (Jill >= 20)
			{
				winner = "Jill";
				win = true;
			}
		}
		
	} while (!win);

	cout << endl << winner <<" wins!";  //Output winner.
	cout << endl << endl;

	return EXIT_SUCCESS;
}
