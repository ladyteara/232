/*
Name:				Tara Walton
Date :				11/05/15
Program :			DEque from SLL
Platform / IDE :	Windows / VS2013
*/


/*
Name: Conrad Bell IV
Date: 10/28/15
Program: DEque from SLL
Platform/IDE: Windows/VS2015

Description:
Implements a double-ended queue ADT by inheritance using a singly linked
list ADT. Uses hierarchical exception handling similar to textbook,
incorporating various exception safety levels (per Stroustrup article)
where possible.

Uses preprocessor instructions to redefine NULL to the appropriate type and
as an example of conditional compilation for testing with different data
types.

Copyright 2015 CBell4. For sole personal use by Missouri State University
students in CSC232. All other uses prohibited.
*/
#include <iostream>
#include <string>
#include <exception>
#include <time.h>

/*	Global constants	*/
int LISTSIZE = 10;

// For cleaner code.
using std::cout;
using std::endl;
using std::ostream;
using std::string;

/*	Forward declarations for code compatibility between Visual Studio 2013 and Xcode 6.3. Always required for Xcode. VS doesn't normally
	need them but does here for SLinkedList due to the << overload (a templated friend function).	*/
template <typename E> class SLinkedList;


// Forward declarations required for << overload
template <typename E>
ostream& operator<< (ostream& out, const SLinkedList<E>& sll);


template<typename E> using SLL = SLinkedList<E>;



/***		Exceptions			***/
class SLLException : public std::exception {					//generic SLL exception
public:
	SLLException(const string& err) : errMsg(err) { }			//constructor
	string getError() { return errMsg; };						//get error message

private:
	string errMsg;												//error message
};

class SLLEmpty : public SLLException {							//for invalid operation on empty list
public:
	SLLEmpty(const string& err) : SLLException(err) { };		//constructor
};


/***		Template class for nodes.		***/
template <typename E>
class Node {
public:
	Node();														//default constructor
	Node(const Node<E>& node);									//copy constructor
	Node<E>* operator= (const Node<E>* rhs);					//override for = 

	//give SLinkedList and << access to private members
	template <typename E> friend class SLinkedList;
	friend ostream& operator<< <E>(ostream& out, const SLinkedList<E>& sll);
	friend void runAllTests();

private:
	E elem;														//datatype independent element
	Node<E>* next;												//next list item
};

// Default constructor.
template <typename E>
Node<E>::Node() {
	elem = NULL;												//using NULL is fine since we redefined it to the right type
	next = nullptr;
}

// Copy constructor. Does the equivalent of	Node<E>* node = new Node<E>;
template <typename E>
Node<E>::Node(const Node<E>& rhs) {
	elem = rhs->elem;
	next = rhs->next;
}

/*	Old style of overloading assignment operator. Superseded by copy and swap idiom - see SLL class. Return a pointer for
	assignment chaining (a = b = c). */
template <typename E>
Node<E>* Node<E>::operator= (const Node<E>* rhs) {
	if (this != rhs) {											//ignore self-assignment
		elem = rhs->elem;
		next = rhs->next;
	}
	return this;
}

/*		Template class for singly linked list.		*/
template <typename E>
class SLinkedList {
public:
	SLinkedList();												//constructor
	SLinkedList(const SLinkedList<E>& sll);						//copy constructor
	~SLinkedList();												//destructor

	// Basic Operations.
	bool empty() const;											//is list empty?
	const E front() const;										//get front element
	const E back() const;										//get last element
	void push_front(const E& e);								//add element to front
	void push_back(const E& e);									//add element to end
	E& pop_front();												//return and delete front element.
	E& pop_back();												//return and delete last element

	

	// For assignment and copy/assignment.
	void swap(SLinkedList<E> rhs);
	SLinkedList<E>& operator= (SLinkedList<E> rhs);				//override for = 

	// For output.
	void printDetails() const;									//for debugging
	friend ostream& operator<< <E>(ostream& out, const SLinkedList<E>& sll);
	friend void runAllTests();

protected:														//allow sublclasses access
	Node<E>* head;												//head of list
};

// Default constructor.
template <typename E>
SLinkedList<E>::SLinkedList()
{
	head = nullptr;
}

// Copy constructor; creates a deep copy.
template <typename E>
SLinkedList<E>::SLinkedList(const SLinkedList<E>& rhs):
head(nullptr)
{
	// head is set via initializer list so only one test needed - if rhs is empty.
	if (!rhs.empty()) {
		Node<E>* node = new Node < E > ;
		head = node;
		Node<E>* litr = head;									//iterators for each list
		Node<E>* ritr = rhs.head;

		while (ritr->next != nullptr) {							//do all but last node
			litr->elem = ritr->elem;
			Node<E>* node = new Node < E > ;
			litr->next = node;									//'link in' the new node
			litr = node;										//increment both itrs
			ritr = ritr->next;
		}
		litr->elem = ritr->elem;								//copy last node element
		litr->next = nullptr;									//set end of list
	}  //else rhs was empty & lhs set in initializer list so done
}

// Exception safe destructor because it doesn't call pop_front(), which can thrown an exception.
template <typename E>
SLinkedList<E>::~SLinkedList() 
{
	while (!empty()) {
		Node<E>* old = head;
		head = old->next;
		delete old;
	}
}

// Is list empty?
template <typename E>
bool SLinkedList<E>::empty() const 
{
	return head == nullptr;
}

// Get front element.  What's the effect of the first const?
template <typename E>
const E SLinkedList<E>::front() const
{
	E e = NULL;
	try {
		if (empty())											//empty list
			throw SLLEmpty("\nSLL:Error: attempted front() on empty list.");
		e = head->elem;
	}
	catch (SLLEmpty err) {
		cout << err.getError() << endl;
	}
	return e;
}

template <typename E>
E SLinkedList<E>::back()
{
	E e = NULL;
	try {
		if (empty())											//empty list
			throw SLLEmpty("\nSLL:Error: attempted front() on empty list.");
		e = head->elem;
	}
	catch (SLLEmpty err) {
		cout << err.getError() << endl;
	}
	return e;
}

// Add to front of list. 
template <typename E>
void SLinkedList<E>::push_front(const E& e) 
{
	Node<E>* node = new Node<E>;
	node->elem = e;
	node->next = head;
	head = node;
}

// Remove front element and delete it. 
template <typename E>
E& SLinkedList<E>::pop_front() 
{
	// Also, note that the complexity of nested exceptions here is due to return-by-address. 
	// Compare to LinkedDEque::pop_front() which is return-by-value.
	try {
		E* e = new E;
		*e = NULL;

		try {
			if (empty())
				throw SLLEmpty("\nSLL:Error: attempted pop_front() on empty list.");
			// else get element, update head, and delete old head
			Node<E>* tmp = head;
			*e = head->elem;
			head = head->next;
			delete tmp;
		}

		catch (SLLEmpty err) {
			cout << err.getError() << endl;
		}
	return *e;
	//````````````````````````````
	}
	catch (...) { //syntax for catching all other errors
		// In this case, only possibility is if new fails to allocate memory.
		throw SLLException("\nSLL:Error allocating memory in pop_front().");
	}
}


/*	Swap two lists. The lhs is the current object. Provides no-throw exception safety via std::swap(). */
template <typename E>
void SLinkedList<E>::swap(SLinkedList<E> rhs) {
	// head is from lhs
	std::swap(head, rhs.head);
}

/*	Assignment overload uses copy and swap idiom. Note it is passed in by value so copy constructor has already been called.
	Is no-throw exception safe, the strongest exception gaurantee.		*/
template <typename E>
SLinkedList<E>& SLinkedList<E>::operator= (SLinkedList<E> rhs) {
	swap(rhs);													//swaps lhs with rhs
	return *this;
}

// Print the list with node addresses for debugging.
template <typename E>
void SLinkedList<E>::printDetails() const {
	Node<E>* itr = SLL<E>::head;
	int i = 0;

	while (itr != nullptr) {
		cout << "index: " << i << "\tdata: " << itr->elem << "\tnode: "
			<< itr << "\tnode->next: " << itr->next << endl;
		itr = itr->next;
		i++;
		if (i > LISTSIZE)										//for debugging if list becomes circular
			break;
	}
}

/*			Non-class overloads.			*/
// Output operator overload. Print as {e1, e2, e3}.
template <typename E>
ostream& operator<< (ostream& out, const SLinkedList<E>& sll) {
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

void test(string message, bool b)
{
	cout.width(30);
	cout << message;
	cout.width(10);
	if (b)
		cout << " PASSED\n";
	else
		cout << " FAILED\n";
}

template <typename E>
void runAllTests(SLinkedList<E> & ll)
{
#if C_DT == 0												//if string

	test("Testing front()", ll.front() == "AA");
	ll.push_front("Test");
	test("Testing pop_front()", ll.pop_front() == "Test");
	cout << endl;
#elif C_DT == 1												//if int
#else														//else float
#endif
}

int main(int argc, char *argv[]) {

	/// These preprocessor instructions allow NULL to be declared differently depending on the selected data type. It is an example of how to do 
	/// conditional compilation. In VS, the inactive code is grayed out. C_DT stands for concrete data type.

#if C_DT == 0												///instantiate with string
	SLinkedList<string> ll;
	ll.push_front("CC");
	ll.push_front("BB");
	ll.push_front("AA");
	cout << "\n\nPushed 3 strings.\n";
	cout << "Front() is " << ll.front() << endl;
	cout << "With << overload, the deque is " << ll << endl;
	cout << "\nDetails of list:" << endl;
	ll.printDetails();
	cout << "\nld - Testing functions...\n";
	runAllTests(ll);

	SLinkedList<string> ll_empty;								//empty deque
	cout << "\nEmpty Linked List Created\n";
	cout << "\nll_empty - Testing functions...\n";
	runAllTests(ll_empty);

#elif C_DT == 1												///instantiate with int
	LinkedDEque<int> ld;
	ld.push_front(0);
	ld.push_back(1);
	ld.push_back(2);
	cout << "Pushed some ints. With << overload, the deque is " << ld;
	cout << ". Size is " << ld.size() << endl;
	cout << "Print details of deque:" << endl;
	ld.printDetails();

#else														///Instantiate with float
	LinkedDEque<float> ld;
	//ld.push_front(1.1);
	cout << "The deque is " << ld;
#endif

	// Keep window open, then exit on key press.
	//getchar();
	return(0);
}