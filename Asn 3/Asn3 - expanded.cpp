/*
Name: Conrad Bell IV
Date: 09-22-15
Assignment: 3, Part 1 - convert to class
Platfrom/IDE: Windows/VS2015

Description: Convert Asn2 Dice Race program to a class. This class
design expands upon the minimal solution with additional fields and
methods. It does not implement multiple games. Beyond the minimal 
solution, it includes:
	* overload >> operator example with struct
	* how the printBoard function would look if not in the class
	* test of access to class fields from outside the class
	* extended comments

(C)2015 cbell4. For private use only. Do not post on any website without
permission. Your cooperation is much appreciated!
*/

#include <time.h>  //for random number generator seed
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::ostream;
using std::string;

const int TOP_OF_HILL = 20;  //global constant (use UPPERCASE)
							 // For overloading <<

class Player {
	public:
	Player();  //Default constructor
	Player(string name);  //Name constructor
	~Player();  //destructor

	// Can list as all getters first then setters
	// OR by field with getter and setter together.

	// Getters
	int getPosition() const;  //Position
	string getName() const;  //Name
	bool getTumbled() const;  //Did player tumble?

	// Setters
	void moves(int roll);  //Position
	void tumbles();  //Tumble a player, set tumble status
	void resetTumbled();  //Reset tumble status
	bool isTheWinner();  //Player is the winner

	// This is how a print board method should be declared. It is only
	// printing, so should not modify any class object or parameter.
	void printBoard(const int roll, const Player& player2) const;

	/*	This is meant as an example of what NOT TO DO. 
		A method should only do ONE thing. */
	//void printBoard(int roll, Player& player2);  //Print the board

	bool operator== (const Player& player) const;  //Overload for ==

	// For << overload; both must be friends for access to private class fields.
	friend struct Turn;  
	friend ostream& operator <<(ostream& out, Turn& t);

	//In this design I chose these fields
	private:
	int position;
	string name;
	bool tumbled;
	bool winner;

};

/* 
	Class Constructors & destructors
	Fields must *all* be initialized.
*/
Player::Player() {  //default Constructor
	position = 0;
	name = "";
	tumbled = false;
	winner = false;
}

Player::Player(string playersName) {  //name constructor
	position = 0;
	//parameters and fields SHOULD have different names to keep
	//down any confusion
	name = playersName;
	tumbled = false;
	winner = false;
}

Player::~Player() {  //destructor
	//used in Asn4
}

/*
	Class Member Methods
*/
// Get position - needed for printBoardNon()
int Player::getPosition() const {  /* Return player's position */
	return position;
}

// Return player's name
string Player::getName() const {
	return name;
}

// Needed for printBoardNon()
bool Player::getTumbled() const {  //get tumble status for this turn
	return tumbled;
}

void Player::moves(int roll) {  //move a player up the hill
	position += roll;
}

void Player::tumbles() {  //tumble player backwards 1-3 spaces
	position -= rand() % 3 + 1;
	tumbled = true;
}

// Needed for printBoardNon()
void Player::resetTumbled() {  //Reset player's tumble status
	tumbled = false;
}

bool Player::isTheWinner() {  //set and return player's winner field
	(position >= TOP_OF_HILL) ? winner = true : winner = false;
	return winner;
}

// Print the results of a turn.
// Matching definition for the bad example printBoard which modifies player2.
//void Player::printBoard(int roll, Player& player2) {
void Player::printBoard(const int roll, const Player& player2) const {
/*
		In-class print board *method*. We can read and write
		player2's data directly, so syntax is less cumbersome.
		The non-class printBoardNon() is a *function*.

		in-class, direct access:		player2.tumbled = false;
		non-class requires a getter:	player2.resetTumbled();
		NOTE: If no getter exists, then access is denied.
*/
	cout << roll << "\t";  //always print roll
	bool jacksTurn = (name == "Jack");

	// There are four cases for printing.
	if (jacksTurn)  //jill is player2
		if (!player2.tumbled)   //no tumble
			cout << position;
		else  //jill tumbled and is player2
			cout << position << "\t" << player2.position << "\t" << player2.name << " got tumbled!";

	else  //jill's turn
		if (!player2.tumbled)   //no tumble
			cout << "\t" << position;
		else  //jack tumbled
			cout << player2.position << "\t" << position << "\t" << player2.name << " got tumbled!";
	
	cout << endl;

	// With printing done, now can reset tumble status. 
	/* This seems harmless but turns what should be a getter
		into a setter and has this method doing 2 things insteaqd
		of one. Plus, the reset can be done after the board is
		printed, so this doesn't & shouldn't be here.
	*/
	//player2.tumbled = false;
}

bool Player::operator== (const Player& player2) const {
	/* Override for 'is equal to' operator is a member function,
		so access to the left-hand side player of the == is done directly.
	*/
	return position == player2.position;
}
/*
	Friend functions given private access to class.
*/
	
/*	
	For << overloading since it only takes 1 parameter. 
	
	NOTE: Still a work in progress! Turn& t should be
	able to be const, but that gets a "member is inaccessible"
	error I'm still tracking down.
*/
struct Turn {  
	int roll;   //current move roll
	Player p1;  //jack is player 1
	Player p2;  //jill is player 2
	// In order to know what to print, you
	// have to know who's turn it is.
	string whosTurn;  //current player taking a turn
};

ostream& operator<<(ostream& ost, Turn& t) {
	cout << t.roll << "\t";  //print roll
	bool jacksTurn = (t.whosTurn == "Jack");
	
	// There are four cases for printing.
	if (jacksTurn)
		if (!t.p2.tumbled)   //no tumble
			cout << t.p1.position;
		else  //jill tumbled
			cout << t.p1.position << "\t" << t.p2.position << "\t" << t.p2.name << " got tumbled!";

	else  //jill's turn
		if (!t.p1.tumbled)   //no tumble
			cout << "\t" << t.p2.position;
		else  //jack tumbled
			cout << t.p1.position << "\t" << t.p2.position << "\t" << t.p1.name << " got tumbled!";

	return ost;
}
/* END << OVLERLOAD */


/*
	Outside the class (these are functions not methods)
*/
void printBoardNon(int roll, const Player& player1, const Player& player2) {
	/* 
		A non-class function to print the board.

		Class fields must be get and set through methods. If a method
		isn't defined to get or set a field in the class object, this
		function *cannot* access that data.
	*/

	cout << roll << "\t";  //always print roll
	bool jacksTurn = (player1.getName() == "Jack");

	// There are four cases for printing.
	if (jacksTurn)  //jill is player2
		if (!player2.getTumbled())   //no tumble
			cout << player1.getPosition();
		else  //jill tumbled and is player2
			cout << player1.getPosition() << "\t" 
			<< player2.getPosition() << "\t" 
			<< player2.getName() << " got tumbled!";

	else  //jill's turn
		if (!player2.getTumbled())   //no tumble
			cout << "\t" << player1.getPosition();
		else  //jack tumbled
			cout << player2.getPosition() << "\t" 
			<< player1.getPosition() << "\t" 
			<< player2.getName() << " got tumbled!";

	cout << endl;
}

int main() {

	/* "seed" the random number generator with the current time. time(0)
		returns the number of seconds since the Epoch (a date/time
		used in all computers: 00:00:00, January 1, 1970).
		Leave this line commented out to get the same exact sequence
		of rolls each game. On my system, this sequence includes both
		a jack tumble and a jill tumble. */
		//srand(time(0));  //uncomment after testing

		// Example showing class object creation using the default constructor.
	Player dummy;
	/** Next line causes this error: "cannot access private member
	* declared in class 'Player'". That's because main() is NOT in
	* the class. Variables declared here do not have direct access
	* to private class data. In fact, dummy.name can't be set from
	* here since there is no setter for name. **/
	//dummy.name = "Jack";  //uncomment to see error

	Player jack("Jack");
	Player jill("Jill");  //create with name constructor

	bool finished = false;
	int roll;

	// Print column headers
	cout << "Roll \tJack \tJill \n--------------------" << endl;

	do {  
		// Jack and Jill roll and move until someone wins and
		// the game is finished.

		// Jack's turn.
		roll = rand() % 6 + 1;
		jack.moves(roll);

		if (jack == jill)  //uses opertor override
			jill.tumbles();
		
		jack.printBoard(roll, jill);
		jill.resetTumbled();

		//printBoardNon(roll, jack, jill);  //non-class print board
		finished = jack.isTheWinner();  //if jack won, finished is true

		// Jill's turn. Take it only if Jack didn't win.
		if (!finished) {
			roll = rand() % 6 + 1;
			jill.moves(roll);

			if (jill == jack)  //uses opertor override
				jack.tumbles();

			jill.printBoard(roll, jack);
			jack.resetTumbled();
			//printBoardNon(roll, jill, jack);  //non-class print board
			finished = jill.isTheWinner();
		}
	}
	while (!finished);

	// Print winner. Another example of the shortcut if syntax.
	(jack.isTheWinner())
		? cout << jack.getName() << " wins!\n"   //true
		: cout << jill.getName() << " wins!\n";  //false

	// Some quick and dirty testing for the << overload
	cout << endl << endl << "Testing for << overload" << endl;
	Player jak("Jack");
	Player jil("Jill");
	Turn t;
	t.roll = 6;
	t.p1 = jak;
	t.p2 = jil;

	// Print column headers
	cout << "Roll \tJack \tJill \n--------------------" << endl;

	// From here on, must use the Turn struct and not individual
	// Player variables.
	//cout << "results from JILL'S turn 1" << endl;
	t.whosTurn = "Jack";
	t.p1.moves(t.roll);
	if (t.p1 == t.p2)  //jack == jill
		t.p2.tumbles();  //jill tumbles
	cout << t << endl;
	t.p2.resetTumbled();

	//cout << "results from JILL'S turn 1" << endl;
	t.whosTurn = "Jill";
	t.p2.moves(t.roll);
	if (t.p2 == t.p1)  //jill == jack
		t.p1.tumbles();  //jack tumbles
	cout << t << endl;
	t.p1.resetTumbled();

	std::cin.ignore();  //pause output window
	return EXIT_SUCCESS;
}

/** My output looks like this every game until I uncomment srand(time(0)) **/
//Roll    Jack    Jill
//--------------------
//6       6
//6       4       6       Jack got tumbled!
//5       9
//6               12
//5       14
//1               13
//1       15
//5               18
//3       18      15      Jill got tumbled!
//6               21
//Jill wins!
