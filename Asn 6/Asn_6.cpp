/*
Name:	Tara Walton
Date:	11/27/2015
Assignment:	Asn 6 - Due Wed, Dec 1, 2015 @ 1700
Platform/IDE: Windows 10 - MS Visual Studio 2013

Description: Alter the SLinkedList ADT
*/

#include<iostream>
#include<ctime>
#include<iomanip>
#include<string>

using namespace std;

template <typename E> class Node;
template <typename E> class SLinkedList;

template <typename E>
ostream& operator<< (ostream& out, const SLinkedList<E>& sll);

template<typename E> using SLL = SLinkedList<E>;

/** This class implements a singly-linked list ADT. **/
template <typename E>
class SLinkedList
{

public:
	/*  Constructors & destructor  */
	SLinkedList();											//default
//	SlinkedList(const SlinkedList<E>& rhs);					//copy
	~SLinkedList();											//destructor

	/*  ADT methods  */
	bool empty() const;										//list empty?
	E front() const;										//return 1st element
	E back() const;											//return last element
	E pop_front();											//return 1st element & delete node  
	E pop_back();											//return last element & delete node
	void push_front(const E e);								//insert at front
	void push_back(const E e);								//append to end
	int size();												//return size of SLL

	/*  For overloads  */
	void swap(SLinkedList<E> rhs);							//for copy & swap
	SLinkedList& operator= (SLinkedList<E> rhs);
	E operator[] (const int index);
	friend ostream& operator<< <E>(ostream& out, const SLinkedList<E>& sll);

protected:
	Node<E>* head;
	int sllsize;
}; /* end SlinkedList class declaration */

// Definitions for SLinkedList go here as usual.
template <typename E>
SLinkedList<E>::SLinkedList()					// constructor
	: head(NULL) {}

template <typename E>
SLinkedList<E>::SLinkedList(const SLinkedList<E>& rhs) :
head(nullptr)
{
	// head is set via initializer list so only one test needed - if rhs is empty.
	if (!rhs.empty()) {
		Node<E>* node = new Node < E >;
		head = node;
		Node<E>* litr = head;									//iterators for each list
		Node<E>* ritr = rhs.head;

		while (ritr->next != nullptr) {							//do all but last node
			litr->elem = ritr->elem;
			Node<E>* node = new Node < E >;
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
E SLinkedList<E>::back() const			
{		// return last element
	Node<E> temp = head;
	try 
	{
		if (empty())					//empty list
			throw SLLEmpty("\nSLL:Error: attempted back() on empty list.");
		while (temp->next != NULL)	
		{	
			temp = temp->next;
		}
	}
	catch (SLLEmpty err) 
	{
		cout << err.getError() << endl;
	}
	return temp->elem;
}

template <typename E>
E SLinkedList<E>::pop_front()
{		// remove and return front item
	Node<E>* old = head;
	head = old->next;
	SLinkedList<E>::sllsize--;
	return old->elem;
	
}

template <typename E>
E SLinkedList<E>::pop_back()
{		// remove and return last item
	Node<E> temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	SLinkedList<E>::sllsize--;
	return temp->elem;
}

template <typename E>
void SLinkedList<E>::push_front(const E e)
{		// add to front of list
	Node<E>* v = new Node<E>;					// create new node
	v->elem = e;								// store data
	v->next = head;								// head now follows v
	head = v;									// v is now the head

	SLinkedList<E>::sllsize++;
}

template <typename E>
void SLinkedList<E>::push_back(const E e)
{		//add to end of list
	Node<E>* node = new Node < E >;
	node->elem = e;
	node->next = nullptr;								//since it becomes the last node

	if (SLL<E>::empty())
		SLL<E>::head = node;
	else
	{	//append to non-empty list
		Node<E>* itr = SLL<E>::head;					//list iterator
		while (itr->next != nullptr)					//get pointer to last node
			itr = itr->next;
		itr->next = node;								//point old last node to new last node
	}

	SLinkedList<E>::sllsize++;
}


template<typename E>
void SLinkedList<E>::swap(SLinkedList<E> rhs)
{		// Swaps the placement of two given nodes


	Node<E>* temp = head;

	while (temp != NULL && temo->next != NULL)
	{
		swap(&
	//while (temp->next != n1 && n1 != head)		//If n1 is not head or head->next...
	//	temp = temp->next;						//move to next node.
	//if (n1 == head)								//If n1 is head
	//{
	//	n1->next = n2->next;					//n1->next = n3
	//	n2->next = n1;
	//	head = n2;
	//}
	//else
	//{
	//	n1->next = n2->next;					//n1->next = n3
	//	n2->next = n1;
	//	temp->next = n2;						//head->next = n2
	//}
	}
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
/** End SLinkedList class **/

/**  List class **/
template <typename E>
class List: public SlinkedList<E>
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
		E operator* { }											//dereference the iterator and return a value
		Iterator<E> operator++ { }								//increment the iterator
		Iterator<E> operator-- { }								//decrement the iterator
		bool operator==  { }									//test equality of iterators
		bool operator!= { }										//test inequality of iterators

	private:
		// Constructors & destructor here since only want List class to access.

		// List constructor called from List::begin(). Use initializer list or create class copy constructor and assignment overload.
		Iterator(const List<E>* sl): llist(sl)
		{
			nodePosition = sl->head;
		}

		// Class fields.
		const List<E>* llist;									//give Iterator class a handle to the list
		Node<E>* nodePosition; 									//abstracted position is a pointer to a node

	}; /** end Iterator class **/

	/* The Iterator class is now fully defined. The rest of these statements must go AFTER the Iterator class or the compiler won’t have complete information about their data types.	*/
	E begin();
	E end();
	void insert(Iterartor<I> itr, E e);
	void erase(Iterator<I> itr);



	// REQUIRED: While not necessary for the code to work, my test suite needs this defined. Create a less cumbersome name for Iterator<E>. Use 
	// anywhere you would have used List<E>::Iterator<E> in class List. 
	// Allows this syntax in main() -- List<int>::iterator instead of List<int>::Iterator<int>.
	typedef typename List<E>::Iterator<E> iterator;

	/***	All method declarations and fields for the List class go here.
	Any method that returns an iterator must be defined here.	***/
	iterator begin() const
	{  //return an iterator of beginning of list
		// Call iterator constructor with pointer to List that begin() was called with.
		return iterator(this);
	}

}; /** end List class declaration **/


// Remaining definitions for List class 
template <typename E>
E List<E>::begin()
{	return head->elem }

template <typename E>
E List<E>::end()
{}

template <typename E>
void List<E>::insert(Iterator<I> itr, E e)
{}

template <typename E>
void List<E>::erase(Iterator<I> itr)
{}
/** End List class **/


/***	Exceptions	***/
//From Asn 5 - Deque
class SLLException: public std::exception
{					//generic SLL exception
public:
	SLLException(const string& err): errMsg(err) {}			//constructor
	string getError() { return errMsg; };						//get error message

private:
	string errMsg;												//error message
};

class SLLEmpty: public SLLException
{							//for invalid operation on empty list
public:
	SLLEmpty(const string& err): SLLException(err) {};		//constructor
};


void mergeSort()
{}

void binarySearch()
{}

