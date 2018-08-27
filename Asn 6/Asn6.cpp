/*
Name:	Tara Walton
Date:	11/29/2015
Assignment:	Asn 6 - Due Tues, Dec 3, 2015 @ 2359
Platform/IDE: Windows 10 - MS Visual Studio 2013

Description: Assignment from hell.
			 Still have no idea how to throw an exception, so the code breaks when it increments off the end or decrements from the beginning, but at least an error message is thrown out before it crashes.
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
	E elem;											// linked list element value
	Node<E>* next;									// next item in the list

	template <typename E> friend class SLinkedList;	// provide SLinkedList access
	template <typename E> friend class List;
	friend ostream& operator<< <E>(ostream& out, const SLinkedList<E>& l);
};

/** This class implements a singly-linked list ADT. **/
template <typename E>
class SLinkedList
{
public:
	/*  Constructors & destructor  */
	SLinkedList();									//default
	SLinkedList(const SLinkedList<E>& sll);			//copy
	~SLinkedList();									//destructor

	/*  ADT methods  */
	bool empty() const;								//list empty?
	E front() const;								//return 1st element
	E back() const;									//return last element
	E pop_front();									//return 1st element & delete node  
	E pop_back();									//return last element & delete node
	void push_front(const E e);						//insert at front
	void push_back(const E e);						//append to end
	int size();										//return size of SLL

	/*  For overloads  */
	void swap(SLinkedList<E> rhs);					//for copy & swap
	SLinkedList& operator= (SLinkedList<E> rhs);
	E operator[] (const int index);
	friend ostream& operator<< <E>(ostream& out, const SLinkedList<E>& sll);

protected:
	Node<E>* head;
	int sllsize;
}; /* end SlinkedList class declaration */

// Definitions for SLinkedList go here as usual.
		/*ADT*/

template <typename E>
SLinkedList<E>::SLinkedList()						// constructor
	: head(NULL) {}

template <typename E>
SLinkedList<E>::SLinkedList(const SLinkedList<E>& rhs) : head(nullptr)
{
	// head is set via initializer list so only one test needed - if rhs is empty.
	if (!rhs.empty()) {
		Node<E>* node = new Node < E >;
		head = node;
		Node<E>* litr = head;						//iterators for each list
		Node<E>* ritr = rhs.head;

		while (ritr->next != nullptr) {				//do all but last node
			litr->elem = ritr->elem;
			Node<E>* node = new Node <E>;
			litr->next = node;						//'link in' the new node
			litr = node;							//increment both itrs
			ritr = ritr->next;
		}
		litr->elem = ritr->elem;					//copy last node element
		litr->next = nullptr;						//set end of list
	}  //else rhs was empty & lhs set in initializer list so done
}

template <typename E>
SLinkedList<E>::~SLinkedList()						// destructor
{
	while (!empty())
		pop_front();
}

template <typename E>
bool SLinkedList<E>::empty() const				
{		// is list empty?
	return head == NULL; 
}

template <typename E>
E SLinkedList<E>::front() const
{		// return front element
	E e = head->elem;
	return e;
}

template <typename E>
E SLinkedList<E>::back() const
{		// return last element
	Node<E>* temp = head;
		while (temp->next != NULL)
			temp = temp->next;
	return temp->elem;
}

template <typename E>
E SLinkedList<E>::pop_front()
{		// remove and return front item
	E* e = new E;
	Node<E>* tmp = head;
	*e = head->elem;
	head = head->next;
	delete tmp;
	return *e;
}

template <typename E>
E SLinkedList<E>::pop_back()
{		// remove and return last item
	E e = NULL;
		if (size() == 1) 
		{		//head is only node
			e = SLinkedList<E>::head->elem;
			delete SLinkedList<E>::head;			//delete it
			SLinkedList<E>::head = nullptr;
		}
		else 
		{		//pop last node
			Node<E>* itr;							//list iterator
			itr = SLinkedList<E>::head;
			while (itr->next->next != nullptr)		//stop at 2nd to last node
				itr = itr->next;
			e = itr->next->elem;
			delete itr->next;						//delete last node
			itr->next = nullptr;					//current node is new last node
		}
	sllsize--;
	return e;
}

template <typename E>
void SLinkedList<E>::push_front(const E e)
{		// add to front of list
	Node<E>* v = new Node<E>;						// create new node
	v->elem = e;									// store data
	v->next = head;									// head now follows v
	head = v;										// v is now the head

	sllsize++;
}

template <typename E>
void SLinkedList<E>::push_back(const E e)
{		//add to end of list
	Node<E>* node = new Node < E >;
	node->elem = e;
	node->next = nullptr;							//since it becomes the last node

	if (SLinkedList<E>::empty())
		SLinkedList<E>::head = node;
	else
	{	//append to non-empty list
		Node<E>* itr = SLinkedList<E>::head;		//list iterator
		while (itr->next != nullptr)				//get pointer to last node
			itr = itr->next;
		itr->next = node;							//point old last node to new last node
	}
	sllsize++;
}

template <typename E>
int SLinkedList<E>::size()
{
	return sllsize;
}


		/*OVERLOADS*/

template <typename E>
void SLinkedList<E>::swap(SLinkedList<E> rhs)
{		//swaps two lists, head is from lhs
	swap(head, rhs.head);
}

template <typename E>
SLinkedList<E>& SLinkedList<E>::operator =(SLinkedList<E> rhs)
{		//copy & swap to provide no-throw guarantee
	swap(rhs);										//swaps lhs with rhs
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

	if (sll.head == nullptr)						//empty list
		cout << "}";
	else											//print elements
		while (itr->next != nullptr) {				//print all but last
		cout << itr->elem << ", ";
		itr = itr->next;
		}
	cout << itr->elem << "}";						//print last and close

	return out;
}
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

		E operator* ()
		{	//dereference the iterator and return a value
			return nodePosition->elem;
		} 

		Iterator<E> operator++ ()
		{	//increment the iterator 
			if (nodePosition->next != nullptr)
			{
				nodePosition = nodePosition->next;
			}
			else
				cout << "Cannot increment off end of list.\n";
			return *this;
		}  

		Iterator<E> operator-- ()
		{	//decrement the iterator 
			Node<E>* temp = llist->head;
			if (nodePosition != llist->head)
			{
				while (temp->next != nodePosition)
					temp = temp->next;
				nodePosition = temp;
				return *this;
			}					
			else
			{
				cout << "Cannot decrement from beginning of list.\n";
				return *this;						//no change made
			}
		}  

		bool operator==(iterator rhs)
		{	//test equality of iterators
			return nodePosition == rhs.nodePosition;
		}  

		bool operator!= (iterator rhs)
		{	//test inequality of iterators
			return !(this==rhs)
		}   

		
	private:
		// Constructors & destructor here since only want List class to access.
		// List constructor called from List::begin(). Use initializer list or create class copy constructor and assignment overload.

		Iterator(const List<E>* sl): llist(sl)
		{		//constructor with list
			nodePosition = sl->head;
		}

		Iterator()
		{		//default constructor
			nodePosition = nullptr;
		}

		// Class fields.
		const List<E>* llist;						//give Iterator class a handle to the list
		Node<E>* nodePosition; 						//abstracted position is a pointer to a node

	}; /** end Iterator class **/

	/* The Iterator class is now fully defined. The rest of these statements must go AFTER the Iterator class or the compiler
	won’t have complete information about their data types.  */

	// REQUIRED: While not necessary for the code to work, my test suite needs this defined. 
	// Create a less cumbersome name for Iterator<E>. Use anywhere you would have used List<E>::Iterator<E> in class List. 
		// Allows this syntax in main() -- List<int>::iterator instead of List<int>::Iterator<int>.
	typedef typename List<E>::Iterator<E> iterator;
	//using iterator = List<E>::Iterator <E>;

	/***	All method declarations and fields for the List class go here.
	Any method that returns an iterator must be defined here.	***/

	iterator begin() const
	{  //return an iterator of beginning of list
		// Call iterator constructor with pointer to List that begin() was called with.
		return iterator(this);
	}

	iterator end() const
	{		//return next to last node in list
		iterator temp = iterator(this);
		/*while (temp.nodePosition != nullptr)
			temp++;*/
		return temp;
	}

	void insert(iterator itr, E elem);
	void erase(iterator itr);
}; /** end List class declaration **/

// Remaining definitions for List class 

template <typename E>
void List<E>::insert(iterator itr, E elem)
{		//Insert element into the list before itr
	Node<E>* n = new Node<E>;			//create a new Node
	n->elem = elem;						//assign element

	n->next = itr.nodePosition;			//link new to next node
	iterator previous = itr--;			//find the previous node from itr
	previous.nodePosition->next = n;	//link previous node to new node
	
}

template <typename E>
void List<E>::erase(iterator itr)
{		//Remove the element at itr
	Node<E>* previous = itr.nodePosition--;
	oldNext = itr.nodePosition->next;
	previous->next = oldNext;	//prevous relinks to next node, skipping current
	delete itr;
}
/** End List class **/

int main()
{
	SLinkedList<float> sll;
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		float random = rand() % 999 + 1;
		float new_rand = random / 100;
		sll.push_front(new_rand);
	}
	cout << "Testing SLL functions:\n";
	cout << sll << endl;
	cout << sll.back() << endl;
	cout << sll.pop_back() << endl;
	cout << sll.size() << endl;
	cout << sll << endl;

	List<int> lyst;
	for (int i = 0; i < 5; i++)
	{
		lyst.push_back(i);
	}
	List<int> lyst2;
	for (int i = 5; i < 10; i++)
	{
		lyst2.push_back(i);
	}
	cout << "Testing iterator functions:\n";
	List<int>::iterator itr = lyst.begin();
	List<int>::iterator itr2 = lyst2.begin();
	cout << *(itr++) << endl;
	cout << lyst << endl;
	cout << boolalpha << (itr == itr2) << endl;
	
	
	cout << "Testing list functions:\n";
	lyst.insert(itr, 10);
	cout << lyst << endl;
	lyst.insert(itr2, 5);
	List<int>::iterator itrE = lyst.end();
	cout << *(itrE) << endl << *(itrE++) << endl;



	cout << "done";





	return 0;
}