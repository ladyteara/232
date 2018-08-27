/*
Name: Conrad Bell IV
Date: 02-01-15
Assignment: 3, Part 1 - convert to class
Platfrom/IDE: Windows/VS2013

Description: Convert Asn2 Dice Race program to a class. This is a minimal 
class design, with only two fields and a minimal number of methods. It 
does not implement multiple games. The output is slightly different than Asn2.

(C)2015 cbell4. For private use only. Do not post on any website without
permission. Your cooperation is much appreciated!
*/

#include <time.h>  //for random number generator seed
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

const int TOP_OF_HILL = 20;  //example of global constant (use UPPERCASE)

class Player {
	private:
		int position;
		string name;

	public:
		Player(string name);  //name constructor
		~Player();  //destructor

		// Getter methods
		string getName() const;  //name
		int getPosition() const;  //position

		// Setter methods
		void moves(int roll);  //move a player
		void printBoard(int roll, Player player2, bool tumbled);  //print the board
};

/* 
	Class Constructors & destructors
*/
Player::Player(string playersName) {  //name constructor
	position = 0;
	name = playersName;  //parameters and fields can have different names
}

Player::~Player() {  //destructor
}

/* 
	Class Member Methods 
*/
string Player::getName() const {  //return player's name
	return name; 
}

void Player::moves(int roll) {  //move a player up the hill
	position += roll; 
}

int Player::getPosition() const {  //return player's position
	return position;
}

/* Print the board. */
void Player::printBoard(int roll, Player player2, bool tumbled) {

	bool jacksTurn = name == "Jack";
	cout << roll << "\t";  //print roll
	
	if (jacksTurn)  //jill is player2
		cout << position << "\t" << player2.position;
	else  //jack is player2
		cout << player2.position << "\t" << position;

	// If player2 tumbled, print it
	if (tumbled)
		cout << "\t" << player2.name << " got tumbled!" << endl;
	else  //end the line
		cout << endl;
}


/** Main Program **/
int main() {
	// "seed" the random number generator with the current time. 
	//Don't uncomment to test with same random sequence of numbers each run.
	//srand(time(0));  

	Player jack("Jack");  //"activates" the class
	Player jill("Jill");

	bool finished = false, tumbled = false, jackIsTheWinner = false;
	int roll;

	// Print column headers
	cout << "Roll \tJack \tJill \n--------------------" << endl;

	do {  //Play until someone wins.

		// Jack's turn.
		roll = rand() % 6 + 1;
		jack.moves(roll);  //move forward 1-6
		if (jack.getPosition() == jill.getPosition()) {   //tumble jill?
			jill.moves(-(rand() % 3 + 1));	//move her backwards 1-3
			tumbled = true;
		}
		jack.printBoard(roll, jill, tumbled);  //print board
		tumbled = false;  //reset tumble

		if (jack.getPosition() >= TOP_OF_HILL) {  //if jack won
			jackIsTheWinner = true;
			finished = true;
		}

		// Jill's turn. Take it only if Jack didn't win.
		if (!finished) {
			roll = rand() % 6 + 1;
			jill.moves(roll);	 //move forward 1-6
			if (jill.getPosition() == jack.getPosition()) {  //tumble jack?
				jack.moves(-(rand() % 3 + 1));  //move him backwards 1-3
				tumbled = true;
			}

			jill.printBoard(roll, jack, tumbled);  //print board, reset tumble
			tumbled = false;  //reset tumble
			finished = jill.getPosition() >= TOP_OF_HILL;
		}
	} 
	while (!finished);

	// Print winner. If jill won, jackIsTheWinner is false. 
	// This syntax is commonly called the shortcut if.
	(jackIsTheWinner) 
		? cout << jack.getName() << " wins!\n"   //true
		: cout << jill.getName() << " wins!\n";  //false

	std::cin.ignore();  //pause output window
	return EXIT_SUCCESS;
}
/** My output looks like this every game with srand(time(0)) commented out. **/
//Roll    Jack    Jill
//--------------------
//6       6       0
//6       4       6       Jack got tumbled!
//5       9       6
//6       9       12
//5       14      12
//1       14      13
//1       15      13
//5       15      18
//3       18      15      Jill got tumbled!
//6       18      21
//Jill wins!
