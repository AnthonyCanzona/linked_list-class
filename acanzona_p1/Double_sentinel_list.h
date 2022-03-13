/*****************************************
 * UW User ID: acanzona
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission: Winter 2022
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

		// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

// Constructor of the Linked List Class that initializes and allocates memory for head and tail pointers and sets size var
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_head( new Double_node (Type {}, nullptr, nullptr) ),
list_tail( new Double_node (Type {}, nullptr, nullptr) ),
list_size( 0 )
{
	// Enter your implementation here
	list_head->next_node = list_tail;
	list_tail->previous_node = list_head;
}

// Constructor that copy one list onto a new list. Takes the address of list as an argument.
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head( new Double_node (Type {}, nullptr, nullptr) ),
list_tail( new Double_node (Type {}, nullptr, nullptr) ),
list_size( 0 )
{
	// Enter your implementation here
	list_head->next_node = list_tail;
	list_tail->previous_node = list_head;

	Double_node *holder { list.rbegin() };
	for(unsigned int x{0}; x < list.size(); x++ ){
		this->push_front(holder->value());
		holder = holder->previous();
	}
}

// Constructor that copy one list onto a new list. Takes a list as an argument.
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( new Double_node (Type {}, nullptr, nullptr) ),
list_tail( new Double_node (Type {}, nullptr, nullptr) ),
list_size( 0 )
{
	// Enter your implementation here
	list_head->next_node = list_tail;
	list_tail->previous_node = list_head;

	Double_node *holder { list->rbegin() };
	for(unsigned int x{0}; x < list.size(); x++ ){
		this->push_front(holder->value());
		holder = holder->previous();
	}
}

// Deconstructor that deletes all allocated memory used by object.
template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	while(list_head->next() != list_tail ){
		this->pop_back();
		}
	delete list_head;
	delete list_tail;
}

// Returns the lists size.
template <typename Type>
int Double_sentinel_list<Type>::size() const {
	// Enter your implementation here
	return this->list_size;
}

//Checks if the list is empty.
template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	// Enter your implementation here
	if (this->size() == 0){return true;}
	return false;
}

//Peaks at the first value in the list. Returns an underflow error if list is empty (no first element).
template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	// Enter your implementation here
	if (this->size() > 0) {return this->begin()->value();}
	throw std::underflow_error("Your list is empty!");
}

//Peaks at the last value in the list. Returns an underflow error if list is empty (no last element).
template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	// Enter your implementation here
	if (this->size() > 0) {return this->rbegin()->value();}
	throw std::underflow_error("Your list is empty!");
}

//Returns the address of the first element in the list. The start of the list. 
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
	// Enter your implementation here
	return this->list_head->next();
}

//Returns the address of the tail pointer. The last address in the list. 
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	// Enter your implementation here
	return this->list_tail;
}

//Returns the address of the last element in the list. The beginning of the list going in reverse. 
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	// Enter your implementation here
	return this->list_tail->previous();
}

//Returns the address of the first element in the list. The end of the list going in reverse.
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	// Enter your implementation here
	return this->list_head;
}

//Returns the address of a node in the list that has the same value as a given object. Takes an address of an object. Retruns the end of the list if no value matches.
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
	// Enter your implementation here
	Double_node *node{ begin() };
	for (unsigned int x{ 0 }; x < this->size() ; x++){ // can use a while loop instead with condition node != tail
		if (node->value() == obj ){return node;}
		node = node->next();
	}
	return end();
}

// Counts how many nodes have an equal value to a given object. Takes an address of an object. 
template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
	// Enter your implementation here
	unsigned int counter{0};
	Double_node *node{begin()};
	for (unsigned int x{0}; x < this->size() ; x++){ // can use a while loop instead with condition node != tail
		if (node->value() == obj ){counter++;}
		node = node->next();
	}
	return counter;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	// This is done for you
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

// The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

// The move operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

//Adds a node to the front of the list with given object value. Takes an address to an object value.
template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
	// Enter your implementation here
	Double_node *new_node (new Double_node( obj, rend(), begin() ));
	begin()->previous_node = new_node;
	list_head->next_node = new_node;
	list_size++;
}

//Adds a node to the end of the list with given object value. Takes an address to an object value.
template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
	// Enter your implementation here
	Double_node *new_node (new Double_node ( obj, rbegin(), end() ));
	rbegin()->next_node = new_node;
	list_tail->previous_node = new_node;
	list_size++;
}

//Deletes a node to the front of the list. Throws an underflow error if the list is empty. 
template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
	// Enter your implementation here
	if (this->empty()) {throw std::underflow_error("Your list is empty!");}
	Double_node *holder { begin() };
	begin()->next()->previous_node = list_head; 
	list_head->next_node = begin()->next();
	delete holder;
	list_size--;
}

//Deletes a node to the fend of the list. Throws an underflow error if the list is empty
template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
	// Enter your implementation here
	if (this->empty()) {throw std::underflow_error("Your list is empty!");}
	Double_node *holder { rbegin() };
	rbegin()->previous()->next_node = list_tail; 
	list_tail->previous_node = rbegin()->previous();
	delete holder;
	list_size--;
}

//Deletes all node equal to a given objects value. Takes the address to the object as a parameter. Retruns how many objects were deleted. 
template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	// Enter your implementation here
	unsigned int count{0};
	Double_node *node { begin() };
	while(node != this->list_tail){
		if (node->value() == obj ){
			Double_node *holder { node->previous() };
			node->previous()->next_node = node->next(); 
			node->next()->previous_node = node->previous();
			delete node;
			node = holder;
			--list_size;
			count++;	 
		}
		node = node->next(); 
	}
	return count;
}

// Constructor of the Node class. Initiates and sets the node value, previous node pointer and next node pointer. 
template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here	
node_value( nv ),
previous_node( pn ),
next_node( nn )
{
	// Enter your implementation here
}

// Retruns the Value at the current node.
template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	// Enter your implementation here
	return this->node_value; 
}

// Retunrs the previous node in the list
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	// Enter your implementation here
	return this->previous_node;
}

// Retunrs the next node in the list
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	// Enter your implementation here
	return this->next_node;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}

#endif