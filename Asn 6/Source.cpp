/*
Name:	Tara Walton
Date:	11/29/2015
Assignment:	Asn 6 - Due Tues, Dec 1, 2015 @ 1700
Platform/IDE: Windows 10 - MS Visual Studio 2013

Description: 
*/


#include<iostream>
#include<ctime>
#include<iomanip>
#include<string>
using namespace std;

template <typename E>
class Node
{	//!Best practice dictates an assignment overload and a copy constructor
private:
	E elem;										// linked list element value
	Node<E>* next;								// next item in the list

	template <typename E> friend class SLinkedList;				// provide SLinkedList access
	template <typename E> friend class List;
	friend ostream& operator<< <E>(ostream& out, const SLinkedList<E>& l);
};

/** This class implements a singly-linked list ADT. **/
template <typename E>
class SLinkedList
{
public:
	/*  Constructors & destructor  */
	SLinkedList();								//default
	SLinkedList(const SLinkedList<E>& sll);		//copy
	~SLinkedList();								//destructor

	/*  ADT methods  */
	bool empty() const;							//list empty?
	E front() const;							//return 1st element
	E pop_front();								//return 1st element & delete node  
	void push_front(const E e);					//insert at front
	int size();									//return size of SLL

	/*  For overloads  */
	void swap(SLinkedList<E> rhs);				//for copy & swap
	SLinkedList& operator= (SLinkedList<E> rhs);
	E operator[] (const int index);

	friend ostream& operator << <E>(ostream& out, const SLinkedList<E>& sll);

protected:
	Node<E>* head;
	int sllsize;
}; /* end SlinkedList class declaration */

// Definitions for SLinkedList go here as usual.

		/*ADT*/
template <typename E>
SLinkedList<E>::SLinkedList()					// constructor
	: head(NULL) {}

template <typename E>
SLinkedList<E>::SLinkedList(const SLinkedList<E>& rhs) : head(nullptr)
{
	// head is set via initializer list so only one test needed - if rhs is empty.
	if (!rhs.empty()) {
		Node<E>* node = new Node < E >;
		head = node;
		Node<E>* litr = head;									//iterators for each list
		Node<E>* ritr = rhs.head;

		while (ritr->next != nullptr) {							//do all but last node
			litr->elem = ritr->elem;
			Node<E>* node = new Node <E>;
			litr->next = node;									//'link in' the new node
			litr = node;										//increment both itrs
			ritr = ritr->next;
		}
		litr->elem = ritr->elem;								//copy last node element
		litr->next = nullptr;									//set end of list
	}  //else rhs was empty & lhs set in initializer list so done
}

template <typename E>
SLinkedList<E>::~SLinkedList()					// destructor
{
	while (!empty())
		pop_front();
}

template <typename E>
bool SLinkedList<E>::empty() const				// is list empty?
{ return head == NULL; }

template <typename E>
E SLinkedList<E>::front() const
{		// return front element
	E e = NULL; //opt1
	try {
		if (empty())									//empty list
			throw SLLEmpty("\nSLL:Error: attempted front() on empty list.");
		e = head->elem;
	}
	catch (SLLEmpty err) {
		cout << err.getError() << endl;
	}

	return e;
}

template <typename E>
E SLinkedList<E>::pop_front()
{		// remove and return front item
	Node<E>* old = head;
	head = old->next;
	sllsize--;
	return old->elem;
}

template <typename E>
void SLinkedList<E>::push_front(const E e)
{		// add to front of list
	Node<E>* v = new Node<E>;					// create new node
	v->elem = e;								// store data
	v->next = head;								// head now follows v
	head = v;									// v is now the head

	sllsize++;
}

template <typename E>
int SLinkedList<E>::size()
{
	return size;
}


		/*OVERLOADS*/
template <typename E>
void SLinkedList<E>::swap(SLinkedList<E> rhs)
{		//swaps two lists
	// head is from lhs
	swap(head, rhs.head);
}

template <typename E>
SLinkedList<E>& SLinkedList<E>::operator =(SLinkedList<E> rhs)
{		//copy & swap to provide no-throw guarantee
	swap(rhs);													//swaps lhs with rhs
	return *this;
}

template <typename E>
E SLinkedList<E>::operator [](int index)
{		//indexing operator overload
	Node<E>* temp = head;
	for (int i = 0; i < index - 1; i++)
	{
		temp = temp->next;
	}
	return temp->elem;
}

template <typename E>
ostream& operator <<(ostream& out, const SLinkedList<E>& sll)
{
	cout << "{";
	Node<E>* itr = sll.head;

	if (sll.head == nullptr)									//empty list
		cout << "}";
	else														//print elements
		while (itr->next != nullptr) {							//print all but last
		cout << itr->elem << ", ";
		itr = itr->next;
		}
	cout << itr->elem << "}";									//print last and close

	return out;
}

/** End SLinkedList class **/


/**  List class **/
template <typename E>
class List: public SLinkedList<E>
{

public:

	// NOTE THE DIFFERENT LETTER – IT IS ONLY USED HERE! Use E everywhere else!
	// For a nested class, methods are declared and defined *INSIDE* the class declaration.
	template <typename I>
	class Iterator
	{
	public:
		// Give List access to Iterator private fields.
		friend class List<E>;

		// These are the minimum methods needed.
		E operator* ()
		{		//dereference the iterator and return a value
			return *this;
		}			

		Iterator<E> operator++ ()
		{		//increment the iterator
			return this->next;
		}	

		Iterator<E> operator-- ()
		{		//decrement the iterator
			Node<E>* temp = llist;
			while (temp->next != this)
				temp = temp->next;
			return temp;
		}	

		bool operator==  (iterator rhs)
		{		//test equality of iterators
			return this == rhs;
		}		

		bool operator!= (iterator rhs)
		{		//test inequality of iterators 
			return this != rhs
		}						

	private:
		// Constructors & destructor here since only want List class to access.

		// List constructor called from List::begin(). Use initializer list or create class copy constructor and assignment overload.
		Iterator(const List<E>* sl): llist(sl)
		{
			nodePosition = sl->head;
		}

		// Class fields.
		const List<E>* llist;						//give Iterator class a handle to the list
		Node<E>* nodePosition; 						//abstracted position is a pointer to a node

	}; /** end Iterator class **/
	/* The Iterator class is now fully defined. The rest of these statements must go AFTER the Iterator class or the compiler
	won’t have complete information about their data types.		*/

	// REQUIRED: While not necessary for the code to work, my test suite needs this defined. 
	//Creates a less cumbersome name for Iterator<E>. Use anywhere you would have used List<E>::Iterator<E> in class List. 
		//Allows this syntax in main() -- List<int>::iterator instead of List<int>::Iterator<int>.
	typedef typename List<E>::Iterator<E> iterator;
	//using iterator = List<E>::Iterator<I>;

	/***	All method declarations and fields for the List class go here.
	Any method that returns an iterator must be defined here.	***/
	iterator begin() const
	{  //return an iterator of beginning of list
		// Call iterator constructor with pointer to List that begin() was called with.
		return iterator(this);
	}

	iterator end() const
	{	//Return an iterator to the end of the list*
		Node<E>* temp = this.begin();
		while (temp != NULL)
			temp = temp->next;
		return temp;
	}

	void insert(iterator itr, E elem);
	void erase(iterator itr);

}; /** end List class declaration **/

// Remaining definitions for List class 
template <typename E>
void List<E>::insert(iterator itr, E elem)
{	//Insert element into the list before itr
	return 0;
}

template <typename E>
void List<E>::erase(iterator itr)
{	//Remove the element at itr
	return 0;
}
/** End List class **/

