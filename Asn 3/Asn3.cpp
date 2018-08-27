/*
Name:	Tara Walton
Date:	09/14/2015
Assignment:	Asn 3 - Due Wed, Sept 21, 2015 @ 2359
Platform/IDE: Windows 10 - MS Visual Studio 2013

Description: Complete the Jack and Jill dice game with classes.
			A brief dice game of Jack and Jill - players roll a die and race to 20. 
			When a player lands at the same space as their oppenent, their opponent tumbles back 1-3 spaces. 
			Each turn is then checked to see if the player has won before the next player may take their turn.
*/

//! revise print statement to plan for tumble

#include<time.h>
#include<iostream>
#include<iomanip>
#include<string>
#include<iomanip>

using std::cout; using std::endl; using std::string;

class Player {
private:
	//variables
	short position;
	string name;
	bool winner;
	short wins;
	bool tumbled;
	bool turn;

public:
	Player(string p_name, short wins); 			//constructor
	~Player();									//destructor

	//setters
	void setPos(const short amt);			//add roll
	void setWinner(const bool win);	
	void setWins(const short n);
	void setTumbled(const bool tumb);
	void setTurn(const bool t);

	//getters
	short	getPos() const;
	string	getName() const;
	bool	getWinner() const;
	short	getWins() const;
	bool	getTumbled() const;
	bool	getTurn() const;

	//overloads
	friend std::ostream& operator <<(std::ostream& ostreem, const Player &p);
	friend bool operator ==(const Player &p, const Player &q);
};


/*******Member Functions********/
Player::Player(string p_name = "", short win = 0)
{
	name = p_name;
	wins = win;	
	//defaults
	position = 0; 
	winner = false; 
	tumbled = false;
	turn = true;
}

Player::~Player()
{}


void Player::setPos(const short amt)
{ position += amt;  }

void Player::setWinner(const bool win)
{ winner = win; }

void Player::setWins(const short n)
{	 wins += n;	 }

void Player::setTumbled(const bool tumb)
{	tumbled = tumb;	}

void Player::setTurn(const bool t)
{	turn = t;	}


string Player::getName() const
{	return name;	}

short Player::getPos() const
{	return position; }

bool Player::getWinner() const
{	return winner;	}

short Player::getWins() const
{	return wins;	}

bool Player::getTumbled() const
{	return tumbled;		}

bool Player::getTurn() const
{	return turn;	}


/*****Stand Alone Functions*****/
void roll(Player &p)
{
	p.setTurn(true);
	short roll = rand() % 6 + 1;
	p.setPos(roll);
	cout << std::setw(6) << roll;
}

void tumble(Player &p, Player &q)
{
	if (p == q)
	{
		short tumble = rand() % 3 - 3;
		q.setPos(tumble);
		q.setTumbled(true);
	}
}

void print(Player &jack, Player &jill)
{
	if (!jack.getTumbled() && !jill.getTumbled())  //If neither player tumbled...
	{
		if (jack.getTurn())							//and it's Jack's turn...
		{ 
			cout << std::setw(6) << jack << endl;	//print jack and end his turn.
			jack.setTurn(false);
		}
		else										//If it's Jill's turn...
		{ 
			cout << std::setw(6) << ' ' << std::setw(6) << jill << endl;	//print jill and end her turn.
			jill.setTurn(false);
		}
	}
	else														//If someone tumbled...
	{
		cout << std::setw(6) << jack << std::setw(6) << jill;	//output both Jack and Jill.
		//Print tumble message depending on who tumbled. 
		if (jack.getTumbled())									
		{
			cout << "\t" << jack.getName() << " tumbles!\n";
			jack.setTumbled(false);		//reset tumble variable						
		}
		else if (jill.getTumbled())								
		{
			cout << "\t" << jill.getName() << " tumbles!\n";
			jill.setTumbled(false);		//reset tumble variable	
		}
	}
}

bool gameOver(Player &p, const short n)
{
	if (p.getPos() >= n)
	{
		p.setWinner(true);
		p.setWins(1);
	}
	return p.getWinner();
};



/******Overload Functions*******/
//overload ==
bool operator==(const Player &p, const Player &q)
{ return (p.getPos() == q.getPos()); }

//overload <<
std::ostream& operator<<(std::ostream& ost, const Player& p)
{
	cout << std::setw(6) << p.getPos();
	return ost;
}



/********The Game (Main)********/
int main()
{
	short HILLTOP = 20;
	short COUNT = 0;
	srand(time(NULL));
	
	short jackWins = 0;
	short jillWins = 0;

	cout << "Please enter an odd integer for the nummber of games you woulld like to play. ";
	std::cin >> COUNT;
	while (COUNT % 2 == 0)
	{
		cout << "You entered an even number. Please try again.";
		std::cin >> COUNT;
	}
	for (int i = 1; i <= COUNT; i++)
	{	Player jack("Jack", jackWins);
		Player jill("Jill", jillWins);
		cout << endl << endl;
		cout << std::setw(6) << "Roll" << std::setw(6) << "Jack" << std::setw(6) << "Jill" << endl;
		cout << std::setw(32) << cout.fill('-'); cout.fill(' '); cout << endl;
		do {//Jack's Turn********************************
			roll(jack);
			tumble(jack, jill);
			print(jack, jill);
			if (!gameOver(jack, HILLTOP)) //If Jack has not won...
			{//Jill's Turn*******************************
				roll(jill);
				tumble(jill, jack);
				print(jack, jill);
				gameOver(jill, HILLTOP); 
			}
		} while (!jack.getWinner() && !jill.getWinner());
		if (jack.getWinner())
		{
			cout << jack.getName();
			jackWins = jack.getWins();
		}
		else
		{
			cout << jill.getName();
			jillWins = jill.getWins();
		}
		cout << " wins game " << i << "!\n\n";
		//system("PAUSE");
	}
	//Ultimate Winner Output
	cout << "\n\nJack won " << jackWins << " games and Jill won " << jillWins << " games.\n";
	if (jackWins > jillWins)
	{	cout << "Jack ";	}
	else
	{	cout << "Jill ";	}
	cout << "is the Dice Race Grand Champion!\n\n";

	return EXIT_SUCCESS;
}