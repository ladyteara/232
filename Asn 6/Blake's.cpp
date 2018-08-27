/**
Name: Blake Kobel
Date: 11/08/15
Program: Asn6
Platform/IDE: Windows/Eclipse

Description:
This program implements the list and position ADT to help us better understand iterators.
**/

/** This class implements a singly-linked list ADT. **/

#include <iostream>
#include <string>
#include <exception>
#include <time.h>
#include<cstdio>
#include<cstdlib>
using namespace std;

template <typename E>
class SLinkedList;

template <typename E>
class List;

template <typename E>
ostream& operator <<(ostream& out, const SLinkedList<E>& v); // operator overloading

template <typename E>
class Node
{ // singly linked list node
private:
	E elem; // linked list element value
	Node<E>* next; // next item in the list
	friend class SLinkedList<E>; // provide SLinkedList access
	friend class List<E>;
	friend ostream& operator << <E>(ostream& out, const SLinkedList<E>& v); // operator overloading
};


template <typename E>
class SLinkedList
{

public:
	/*  Constructors & destructor  */
	SLinkedList();     //default
	SLinkedList(const SLinkedList<E>& sll);  //copy constructor
	~SLinkedList();  //destructor

	/*  ADT methods  */
	void removeFront(); // remove front item list
	bool empty() const;                                        //list empty?
	E front() const;                                  //return 1st element
	E pop_front();                                   //return 1st element & delete node
	void push_front(const E e);          //insert at front
	int size();                                                             //return size of SLL

	/*  For overloads  */
	void swap(SLinkedList<E> rhs);  //for copy & swap
	SLinkedList& operator= (SLinkedList<E> rhs);
	E operator[] (const int index);
	friend ostream& operator<< <E>(ostream& out, const SLinkedList<E>& sll);


protected:
	Node<E>* head;
	int sllsize;
}; /* end SlinkedList class declaration */

template <typename E>
SLinkedList<E>::SLinkedList() // constructor
	: head(nullptr)
{
	sllsize = 0;
}

template <typename E>
SLinkedList<E>::SLinkedList(const SLinkedList<E>& rhs):
head(nullptr)
{
	// head is set via initializer list so only one
	//  test needed - if rhs is empty.

	if (!rhs.empty()) {
		Node<E>* node = new Node<E>;
		head = node;
		Node<E>* litr = head;                    //iterators for each list
		Node<E>* ritr = rhs.head;            //

		while (ritr->next != nullptr) {  //do all but last node
			litr->elem = ritr->elem;
			Node<E>* node = new Node<E>;
			litr->next = node;                                                             //'link in' the new node
			litr = node;                                                                          //increment both itrs
			ritr = ritr->next;                                                //
		}
		litr->elem = ritr->elem;  //copy last node element
		litr->next = nullptr;                          //set end of list
	}
}

template <typename E>
SLinkedList<E>::~SLinkedList() // destructor
{ while (!empty()) removeFront(); }

template <typename E>
void SLinkedList<E>::removeFront()
{ // remove front item
	Node<E>* old = head;				// save current head
	head = old->next;					// skip over old head
	delete old;							// delete the old head
	sllsize--;
}

template <typename E>
bool SLinkedList<E>::empty() const		// is list empty?
{ return head == NULL; }

template <typename E>
E SLinkedList<E>::front() const			// return front element
{ return head->elem; }

template <typename E>
E SLinkedList<E>::pop_front()
{
	E* e = new E;
	*e = NULL;
	Node<E>* tmp = head;
	*e = head->elem;
	head = head->next;
	delete tmp;
	return *e;
	sllsize--;
}

template <typename E>
void SLinkedList<E>::push_front(const E e)
{
	Node<E>* node = new Node<E>;
	node->elem = e;
	node->next = head;
	head = node;

	sllsize++;
}

template <typename E>
int SLinkedList<E>::size()
{
	//returns the size of the linked list
	return sllsize;
}

template <typename E>
void SLinkedList<E>::swap(SLinkedList<E> rhs)
{
	// head is from lhs
	std::swap(head, rhs.head);
}

template <typename E>
SLinkedList<E>& SLinkedList<E>::operator= (SLinkedList<E> rhs)
{
	swap(rhs);  //swaps lhs with rhs
	return *this;
}

template <typename E>
E SLinkedList<E>::operator [](const int index)
{
	Node<E>*   itr = head;
	for (int i = 0; i<index; i++){
		itr = itr->next;
	}
	return itr->elem; //This returns the value at the specified index
}

template <typename E>
ostream& operator<< (ostream& out, const SLinkedList<E>& sll)
{
	cout << "{";
	Node<E>* itr = sll.head;
	if (sll.head == nullptr)  //empty list
		cout << "}";
	else   //print elements
		while (itr->next != nullptr) {  //print all but last
		cout << itr->elem << ", ";
		itr = itr->next;
		}
	cout << itr->elem << "}";  //print last and close
	return out;
}

template <typename E>
class List:public SLinkedList<E>
{
public:
	E back() const;                                 //return last element
	E pop_back();                                   //return last element & delete node
	void push_back(const E e);						//insert at back

private:
	int sllsize;
};

template <typename E>
E List<E>::back() const
{ // return front element
	E e = NULL;
	Node<E>* itr;   //list iterator
	itr = List<E>::head;
	while (itr->next != nullptr){  //get pointer to last node
		itr = itr->next;
	}
	e = itr->elem;

	return e;
}


template <typename E>
E List<E>::pop_back()
{
	E* e = new E;
	*e = NULL;
	if (sllsize == 1) {  //head is only node
		*e = List<E>::head->elem;
		delete List<E>::head;  //delete it
		List<E>::head = nullptr;
	}
	else {  //pop last node
		Node<E>* itr;   //list iterator
		itr = List<E>::head;
		while (itr->next->next != nullptr)  //stop at 2nd to last node
			itr = itr->next;
		*e = itr->next->elem;
		delete itr->next;     //delete last node
		itr->next = nullptr;  //current node is new last node
	}
	sllsize--;
	return *e;

}

template <typename E>
void List<E>::push_back(const E e)
{
	Node<E>* node = new Node < E >;
	node->elem = e;
	node->next = nullptr;  //since it becomes the last node

	if (List<E>::empty())
		List<E>::head = node;
	else {  //append to non-empty list
		Node<E>* itr = List<E>::head;   //list iterator
		while (itr->next != nullptr)  //get pointer to last node
			itr = itr->next;
		itr->next = node;  //point old last node to new last node
	}
	sllsize++;
}

int main()
{
	SLinkedList<float> a;
	srand(time(NULL));
	for (int i = 0; i<10; i++){
		float random = rand() % 999 + 1;
		float new_rand = random / 100;
		a.push_front(new_rand);
	}
	cout << a;
	cout << endl;
	//cout << a.back();
	cout << endl;
	//cout << a.pop_back();
	cout << endl;
	cout << a.size();
}