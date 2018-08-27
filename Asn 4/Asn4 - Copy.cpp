/*
Name:	Tara Walton
Date:	09/14/2015
Assignment:	Asn 3 - Due Wed, Sept 21, 2015 @ 2359
Platform/IDE: Windows 10 - MS Visual Studio 2013

Description: Design a data structure that can take advantage of random memory address function.
Currently all data stored in each memory location is a floating point number, but this needs to
be flexible for future changes. Create a Node class and a SLinkedList using templates, pointers
and good memory management.
*/


#include<iostream>
#include<ctime>
#include<iomanip>
#include<string>

using namespace std;

int LISTSIZE = 10;

template <typename E> class Node;
template <typename E> class SLinkedList;

template <typename E> ostream& operator<< (ostream& out, const SLinkedList<E>& l);

//***** Singlely Linked List *****//
template <typename E>
class SLinkedList
{
public:
	SLinkedList();					// empty list constructor
	~SLinkedList();					// destructor
	//!Best practice dictates an assignment overload and a copy constructor
	//E& operator =(const E& e);		//indexing overload
	SLinkedList

	bool empty() const;				// is list empty?
	const E& front() const;			// return front element
	void addFront(const E& e);		// add to front of list
	void removeFront();				// remove front item list
	void insertSort(const int s);								//alter links to list in non-descending order
	void swap(Node<E>* n1, Node<E>* n2);		//swap two nodes by swapping links
	Node<E>* getNode(const int index) const;	//get a node a specific number away
	E& operator [](const int index);			//indexing overload
	void printDetails() const;

	friend ostream& operator<< <E>(ostream& out, const SLinkedList<E>& l);

private:
	Node<E>* head;								// head of the list
};

template <typename E>
SLinkedList<E>::SLinkedList()					// constructor
	: head(NULL) {}

template <typename E>
bool SLinkedList<E>::empty() const				// is list empty?
{ return head == NULL; }

template <typename E>
const E& SLinkedList<E>::front() const			// return front element
{ return head->elem; }

template <typename E>
SLinkedList<E>::~SLinkedList()					// destructor
{ while (!empty()) removeFront(); }

template <typename E>
void SLinkedList<E>::addFront(const E& e)
{		// add to front of list
	Node<E>* v = new Node<E>;					// create new node
	v->elem = e;								// store data
	v->next = head;								// head now follows v
	head = v;									// v is now the head
}

template <typename E>
void SLinkedList<E>::removeFront()
{		// remove front item
	Node<E>* old = head;
	head = old->next;
	delete old;
}

/** Print details as much as possible even if list structure is borked. **/
template <typename E>
void SLinkedList<E>::printDetails() const
{	/*Note: I have a class field   sllSize that is an up-to-date size of the list.
	If you didn't implement that, then comment out the next line.*/
	//cout << "size=" << sllSize << "\n"; // <<   typeid(  sllSize).name()
	Node<E>* itr = head;
	int i = 0;
	while (itr != nullptr) {
		cout << "index: " << i << "   data: " << itr->elem << "   node: " << itr << endl;
		itr = itr->next;
		i++;
		if (i > LISTSIZE + 1)					//if structure of list gets messed up
			break;								//avoid infinite loop
	}
}

template <typename E>
Node<E>* SLinkedList<E>::getNode(const int index) const
{		//get a Node that is a specific number of links away
	Node<E>* current = head;
	for (int i = 0; i < index - 1; i++)
	{
		current = current->next;
	}
	return current;
}

template <typename E>
void SLinkedList<E>::insertSort(const int size)
{		//insertion sort by rearranging links
	short i = 1;
	while ((getNode(i - 1))->next != nullptr)
	{
		E current = (*this)[i];
		int j = i - 1;
		while ((j >= 0) && ((*this)[j] > current))
		{
			swap(getNode(j), getNode(j + 1));
			j -= 1;
		}
		i += 1;
	}
}

template <typename E>
E& SLinkedList<E>::operator [](int index)
{		//indexing operator overload
	Node<E>* temp = head;
	for (int i = 0; i < index - 1; i++)
	{
		temp = temp->next;
	}
	return temp->elem;
}

//template <typename E>
//E& SLinkedList<E>::operator =(const E& e)
//{

//	return 0;
//}
template <typename E>
SLinkedList<E>(const SLinkedList<E>& original)
{
	Node<E>* cur = original.head;
	Node<E>* end = NULL;

	while (cur)
	{
		Node<E>* n = new Node<E>;
		n->data = cur->data;

		if (!head) 
		{
			head = n;
			end = head;
		}
		else 
		{
			end->next = n;
			end = n;
		}

		cur = cur->next;
	}
}

template<typename E>
void SLinkedList<E>::swap(Node<E>* n1, Node<E>* n2)
{		// Swaps the placement of two given nodes
	Node<E>* temp = head;

	while (temp->next != n1 && n1 != head)		//If n1 is not head or head->next...
		temp = temp->next;						//move to next node.

	if (n1 == head)								//If n1 is head
	{
		n1->next = n2->next;					//n1->next = n3
		n2->next = n1;
		head = n2;
	}
	else
	{
		n1->next = n2->next;					//n1->next = n3
		n2->next = n1;
		temp->next = n2;						//head->next = n2
	}
}



template <typename E>
class Node
{
	//!Best practice dictates an assignment overload and a copy constructor
public:


private:
	E elem;										// linked list element value
	Node<E>* next;								// next item in the list


	friend class SLinkedList<E>;				// provide SLinkedList access
	friend ostream& operator<< <E>(ostream& out, const SLinkedList<E>& l);
};

template <typename E>
ostream& operator <<(ostream& out, const SLinkedList<E>& l)
{		//ostream overload - printing all elements of a singly linked list
	Node<E>* current = l.head;

	cout << "{";
	while (current != NULL)
	{
		cout << fixed << setprecision(2);		//formatting
		cout << current->elem;
		if (current->next != NULL)
			cout << ", ";						//if not the last Node, print comma
		current = current->next;				//move to next Node
	}
	cout << "}";

	return out;
}



int main()
{
	SLinkedList<float> lyst;
	srand(time(NULL));
	//srand(0);
	for (short i = 0; i < LISTSIZE; i++)
	{
		float newNum = rand() % 999 + 1;		// 0 - 998 + 1 
		newNum /= 100;							//change to decimal (2 digs)
		//cout << newNum << ' ';				//test output
		lyst.addFront(newNum);
	}
	cout << endl;
	cout << "The original list:" << lyst << endl;
	cout << "Node 3: " << lyst[3] << endl;		//test indexing overload
	lyst[1] = 9.99;								//test indexing assignment
	cout << "Node 1: " << lyst[1] << endl;
	lyst.insertSort(LISTSIZE);
	cout << "The sorted list:  " << lyst << endl;

	//Extra credit bits.
	SLinkedList <string> quote;
	quote.addFront("minutes.");
	quote.addFront("5");
	quote.addFront("in");
	quote.addFront("back");
	quote.addFront("be");
	quote.addFront("-");
	quote.addFront("mind");
	quote.addFront("my");
	quote.addFront("of");
	quote.addFront("Out");

	cout << quote << endl;
	


}