/*Name:				Tara Walton
Date :				11/05/15
Program :			DEque from SLL
Platform / IDE :	Windows / VS2013

1)	Explain preprocessor commands for redefining NULL.I understand why it is necessary, but not what is actually happening in this section of code.
a.Not necessary - this actually is a “quick and dirty method” for instantiating several different data types for the first node set to NULL.NULL becomes the appropriate data type.
b.This section of code being run can be modified by changing just Line 31 :
#define C_DT 1
2)	Line 79. If err is the string being passed in for the specific error that is being thrown, then it is acting as a parameter in errMsg, which is declared as a string in the SLLException class.Is this simply exception syntax ? Hard to follow – first time I’ve seen exception handling in code.
	a.The err message is passes to the METHOD for errMsg, which is defined inside the class itself.The constructor is an initializer list.
3)	Line 235 – NOTE – What made you include option 2 if you were going to comment it out and note why it is not the best option.Could this have been covered in a review or simply excluded ? Will we ever need the option ?
	a.Just used to clarify code and see the two differences.Teaching moment vs.standardized coding.
4)	Line 278. Why use the return-by address method if it is not as robust and causes complications in the exceptions ?
	a.Depends on if you know the context of when the program will be used.If we KNOW the values are small, we’re good, but if we don’t know, then we need to use references.
5)	Line 384. Style question.Why the underscore ? It is the only variable named in such a way.Why not just use size ?
	a.This is to differentiate from the METHOD size().
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

///* Conditional compilation. Redefine NULL depending on the data type we want to test. Look in main() for the effect of these prepocessor commands.*///
#define C_DT 0		//C_DT stands for concrete data type

#if C_DT == 0		//string
#define NULL ""
#elif C_DT == 1		//int
#define NULL 0
#else
#define NULL 0.0	//float
#endif

// For cleaner code.
using std::cout;
using std::endl;
using std::ostream;
using std::string;

/*
	Forward declarations for code compatibility between Visual Studio 2013 and Xcode 6.3. Always required for Xcode. VS doesn't normally
	need them but does here for SLinkedList due to the << overload (a templated friend function).
*/
template <typename E> class SLinkedList;
template <typename E> class LinkedDEque;

// Forward declarations required for << overload
template <typename E>
ostream& operator<< (ostream& out, const SLinkedList<E>& sll);

/*
	Xcode requires that inherited class members be fully qualified with	their class names. This can make for cumbersome code, especially
	with templates. These alias template names help clean up some of that.
*/
template<typename E> using SLL = SLinkedList<E>;
template<typename E> using LD = LinkedDEque<E>;


/***		Exceptions			***/

/*	Good practice for custom exceptions dictates inheriting from an STL exception class like std::exception. Didn't do it here
	to simplify technique and since book uses a string error message. */
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

/* It's a best practice to have a separate exception class for each real class. If the deque exception class had to do some completely different type of
exception handling, you would make it independent from SLLException rather than deriving from it. */
class DEqueException : public SLLException {					//generic DEque exception
public:
	DEqueException(const string& err) : SLLException(err) { };  //constructor
};

class DEqueEmpty : public DEqueException {						//invalid operation on empty DEque
public:
	DEqueEmpty(const string& err) : DEqueException(err) { }		//constructor
};
/*****   End Exceptions   *****/


/***		Template class for nodes.		***/
template <typename E>
class Node {
public:
	Node();														//default constructor
	Node(const Node<E>& node);									//copy constructor
	Node<E>* operator= (const Node<E>* rhs);					//override for = 

	//give SLinkedList and << access to private members
	template <typename E> friend class SLinkedList;
	template <typename E> friend class LinkedDEque;
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
	void push_front(const E& e);								//add element to front
	E& pop_front();												//return and delete front element.

	// For assignment and copy/assignment.
	void swap(SLinkedList<E> rhs);
	SLinkedList<E>& operator= (SLinkedList<E> rhs);				//override for = 

	// For output.
	void printDetails() const;									//for debugging
	friend ostream& operator<< <E>(ostream& out, const SLinkedList<E>& sll);
	friend void runAllTests();

protected:													//allow sublclasses access
	Node<E>* head;												//head of list
};

// Default constructor.
template <typename E>
SLinkedList<E>::SLinkedList() {
	head = nullptr;
}

// Copy constructor; creates a deep copy.
template <typename E>
SLinkedList<E>::SLinkedList(const SLinkedList<E>& rhs) :
	head(nullptr) {
	// head is set via initializer list so only one test needed - if rhs is empty.

	if (!rhs.empty()) {
		Node<E>* node = new Node<E>;
		head = node;
		Node<E>* litr = head;									//iterators for each list
		Node<E>* ritr = rhs.head;	

		while (ritr->next != nullptr) {							//do all but last node
			litr->elem = ritr->elem;
			Node<E>* node = new Node<E>;
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
SLinkedList<E>::~SLinkedList() {
	while (!empty()) {
		Node<E>* old = head;
		head = old->next;
		delete old;
	}
}

// Is list empty?
template <typename E>
bool SLinkedList<E>::empty() const {
	return head == nullptr;
}

// Get front element.  What's the effect of the first const?
template <typename E>
const E SLinkedList<E>::front() const {
	/* Note: Two options for code in this method are shown. opt1 is better than op2:
		1) It exits method in only one place
		2) Even if exceptions occur, correct result returned and it "cleans up"
			after itself - e is destroyed when it goes out of scope.

	Only advantage to opt2 is it does not require creating and assigning
	a new variable of type E. Insignificant compared to opt1's benefits.		*/
	E e = NULL; //opt1
	try {
		if (empty())											//empty list
			throw SLLEmpty("\nSLL:Error: attempted front() on empty list.");
		e = head->elem;											//opt1
		//return head->elem;									//opt2
	}
	catch (SLLEmpty err) {
		cout << err.getError() << endl;
		//return NULL;											//opt2
	}

	return e;													//opt1
}


// Add to front of list. 
template <typename E>
void SLinkedList<E>::push_front(const E& e) {
	Node<E>* node = new Node<E>;
	node->elem = e;
	node->next = head;
	head = node;
}

// Remove front element and delete it. 
/*	As an example, return-by-address is used here - shown by E& as the return type. In contrast, for return-by-value the return type is just E.
	Return-by-value is easier to understand because no pointers are involved. Also, it's ok to use in this program because we know elements are
	small in size. If each element was a million-item array, we would have to deal with the pointers and use return-by-address everywhere.	*/
template <typename E>
E& SLinkedList<E>::pop_front() {
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

/***		Template class for DEque. Inherits from Singly Linked List.			***/
template <typename E>
class LinkedDEque : public SLinkedList <E> {
public:
	LinkedDEque();												//constructor
	virtual ~LinkedDEque();										//destructor
	int size() const;											//get number of elements
	virtual const E front();									//get front element
	virtual const E pop_front();								//return and delete front element
	virtual void push_front(const E e);							//insert at front of the list
	const E back() const;										//get last element
	const E pop_back();											//return and delete back element
	void push_back(const E e);									//append to end of list

private:
	int size_;													//size of list

	friend void runAllTests();
};

// Constructor.
template <typename E>
LinkedDEque<E>::LinkedDEque() {									//: SLinkedList(SLinkedList<E>::head = nullptr) {
	SLinkedList<E>();											//call SLL default constructor
	size_ = 0;
}

// Destructor.
template <typename E>
LinkedDEque<E>::~LinkedDEque() {
	SLL<E>::~SLinkedList();
	//while (SLL<E>::head != nullptr)
	//	SLL<E>::pop_front();
}

// Return list size
template <typename E>
int LinkedDEque<E>::size() const {
	return size_;
}

// Return first element
template <typename E>
const E LinkedDEque<E>::front() {
	E e = NULL;
	try {
		if (SLL<E>::empty())
			throw DEqueEmpty("\nLD:Error: attempted front() on empty DEque.");
		e = SLL<E>::front();
	}
	catch (DEqueException err) {
		cout << err.getError() << endl;
	}
	return e;
}

// Remove and return front element and delete it. Need this child method to manage list size.
template <typename E>
const E LinkedDEque<E>::pop_front() {
	E e = NULL;

	try {
		if (SLL<E>::empty())
			throw DEqueEmpty("\nLD:Error: attempted pop_front() on empty DEque.");
		e = SLL<E>::pop_front();
		LD<E>::size_--;
	}
	catch (DEqueException err) {
		cout << err.getError() << endl;
	}
	return e;
}

// Push new node at front. Need this child method to manage list size.
template <typename E>
void LinkedDEque<E>::push_front(const E e) {
	SLL<E>::push_front(e);
	LD<E>::size_++;
}

// Get last element.
template <typename E>
const E LinkedDEque<E>::back() const {
	E e = NULL;
	Node<E>* itr;												//list iterator
	try {
		if (SLL<E>::empty())
			throw DEqueEmpty("\nLD:Error: attempted back() on empty DEque.");
		itr = SLL<E>::head;
		while (itr->next != nullptr)							//get pointer to last node 
			itr = itr->next;
		e = itr->elem;
	}
	catch (DEqueEmpty err) {
		cout << err.getError() << endl;
	}
	return e;
}

// Remove and return back element and delete its node.
template <typename E>
const E LinkedDEque<E>::pop_back() {
	E e = NULL;
	try {
		if (SLL<E>::empty())
			throw DEqueEmpty("\nLD:Error: attempted pop_back() on empty DEque.");
		if (size() == 1) {										//head is only node
			e = SLL<E>::head->elem;
			delete SLL<E>::head;								//delete it
			SLL<E>::head = nullptr;
		}
		else {													//pop last node
			Node<E>* itr;										//list iterator
			itr = SLL<E>::head;
			while (itr->next->next != nullptr)					//stop at 2nd to last node
				itr = itr->next;
			e = itr->next->elem;
			delete itr->next;									//delete last node
			itr->next = nullptr;								//current node is new last node
		}
	}
	catch (DEqueEmpty err) {
		cout << err.getError() << endl;
	}
	catch (...) {												//any other error
		throw DEqueException("\nDEque: Unknown error in pop_back().");
	}

	LD<E>::size_--;
	return e;
}

// Append new node to end of list. 
template <typename E>
void LinkedDEque<E>::push_back(const E e) {
	Node<E>* node = new Node < E >;
	node->elem = e;
	node->next = nullptr;										//since it becomes the last node

	if (SLL<E>::empty())
		SLL<E>::head = node;
	else {														//append to non-empty list
		Node<E>* itr = SLL<E>::head;							//list iterator
		while (itr->next != nullptr)							//get pointer to last node
			itr = itr->next;
		itr->next = node;										//point old last node to new last node
	}

	LD<E>::size_++;
}

// Print the list with node addresses for debugging template 
//<typename E> 
//void LinkedDEque<E>::printDetails() const {
//	SLL<E>::printDetails();
//}

/* End LinkedDEque class ----------------------------------*/



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
void runAllTests(LinkedDEque<E> & ld)
{
#if C_DT == 0												//if string
	test("Testing size()", ld.size() == 4 /*ld.size_*/);
	test("Testing front()", ld.front() == "AA"); 
	ld.push_front("Test");
	test("Testing pop_front()", ld.pop_front() == "Test");
	test("Testing back()", ld.back() == "ZZ");
	ld.push_back("Test");
	test("Testing pop_back()", ld.pop_back() == "Test");
	cout << endl;

#elif C_DT == 1												//if int
	test("Testing size()", ld.size() == 3);
	test("Testing front()", ld.front() == 0);
	ld.push_front(0);
	test("Testing pop_front()", ld.pop_front() == 0);
	test("Testing back()", ld.back() == 2);
	ld.push_back(0);
	test("Testing pop_back()", ld.pop_back() == 0);

#else														//else float
	test("Testing size()", ld.size() == 0);
	test("Testing front()", ld.front() == NULL);
	ld.push_front(0);
	test("Testing pop_front()", ld.pop_front() == 5);
	test("Testing back()", ld.back() == 2);
	ld.push_back(0);
	test("Testing pop_back()", ld.pop_back() == 5);

#endif
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
	LinkedDEque<string> ld;
	ld.push_back("OO");
	ld.push_front("MM");
	ld.push_back("ZZ");
	ld.push_front("AA");
	cout << "Pushed 4 strings.\n";
	cout << "Front() is " << ld.front() << " and back() is " << ld.back() << endl;
	cout << "With << overload, the deque is " << ld << " and size is " << ld.size() << endl;
	cout << "\nDetails of deque:" << endl;
	ld.printDetails();
	cout << "\nld - Testing functions...\n";
	runAllTests(ld);

	LinkedDEque<string> ld_empty;								//empty deque
	cout << "\nEmpty Linked Deque Created\n";
	//ld_empty.printDetails();
	cout << "\nld_empty - Testing functions...\n";
	runAllTests(ld_empty);

	LinkedDEque<string> ld_copy;
	ld_copy = ld;
	//ld_copy.printDetails();
	cout << "\nld_copy - Testing functions...\n";
	runAllTests(ld_copy);

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
	//ll_empty.printDetails();
	cout << "\nll_empty - Testing functions...\n";
	runAllTests(ll_empty);

	//LinkedDEque<string> ll_copy;
	//ll_copy = ll;
	////ll_copy.printDetails();
	//cout << "\nld_copy - Testing functions...\n";
	//runAllTests(ll_copy);

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