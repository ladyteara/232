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
	friend ostream& operator<< <E>(ostream& out, const SLinkedList<E>& sll);

protected:
	Node<E>* head;
	int sllsize;
}; /* end SlinkedList class declaration */

// Definitions for SLinkedList go here as usual.

/** End SLinkedList class **/

/**  List class **/
template <typename E>
class List: public SLinkedList<E>
{

public:
	// NOTE THE DIFFERENT LETTER – IT IS ONLY USED HERE! 
	// Use E everywhere else! For a nested class, methods are declared and defined *INSIDE* the class declaration.
	template <typename I>
	class Iterator
	{
	public:
		// Give List access to Iterator private fields.
		friend class List<E>;

		// These are the minimum methods needed.
		E operator* { }							//dereference the iterator and return a value
		Iterator<E> operator++ { }				//increment the iterator
		Iterator<E> operator-- { }				//decrement the iterator
		bool operator==  { }					//test equality of iterators
		bool operator!= { }						//test inequality of iterators

	private:
		// Constructors & destructor here since only want List class to access.

		// List constructor called from List::begin(). Use initializer list or create class copy constructor and assignment overload.
		Iterator(const List<E>* sl): llist(sl)
		{
			nodePosition = sl->head;
		}

		// Class fields.
		const List<E>* llist;					//give Iterator class a handle to the list
		Node<E>* nodePosition; 					//abstracted position is a pointer to a node

	}; /** end Iterator class **/

	/* The Iterator class is now fully defined. The rest of these
	statements must go AFTER the Iterator class or the compiler
	won’t have complete information about their data types.
	*/

	// REQUIRED: While not necessary for the code to work, my test suite needs
	// this defined. Create a less cumbersome name for Iterator<E>. Use 
	// anywhere you would have used List<E>::Iterator<E> in class List. Allows 
	// this syntax in main() -- List<int>::iterator instead of List<int>::Iterator<int>.
	typedef typename List<E>::Iterator<E> iterator;

	/***	All method declarations and fields for the List class go here.
	Any method that returns an iterator must be defined here.
	***/
	iterator begin() const
	{  //return an iterator of beginning of list
		// Call iterator constructor with pointer to List that begin() was called with.
		return iterator(this);
	}

}; /** end List class declaration **/


// Remaining definitions for List class 

/** End List class **/

