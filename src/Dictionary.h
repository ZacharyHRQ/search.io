/**
*
* 	Dictionary header file
*   This is a hash table that has used dynamic resizing and has thresholds to how long the chains can be 
*
* 	@author Zachary S10185319J
* 	@since 01-21-2021
*/

#pragma once
#include<string>
#include<iostream>
using namespace std;

const int DEFAULT_TABLE_SIZE = 10000;
template<typename KeyType, typename ItemType> // setting template for generic type 

class Dictionary
{
private:
	struct Node
	{
		KeyType	 key;   // search key
		ItemType item;	// data item
		Node     *next;	// pointer pointing to next item with same search key
	};

	int size;			// number of items in the Dictionary
    float threshold;    // limit for the length of each chain
    int maxSize;        // limit for the size of the table with threshold
    int tableSize;      // the max size of the table 
	Node *items[DEFAULT_TABLE_SIZE]; // inital items arrays to store key-value pair
        


public:

	// constructor
	Dictionary();

	// destructor
	~Dictionary();

	// hash function
	int hash(KeyType key);

	// add a new item with the specified key to the Dictionary
	bool add(KeyType newKey, ItemType newItem);

	//remove an item with the specified key in the Dictionary
	void remove(KeyType key);

	// retrieve an item with the specified key in the Dictionary 
	ItemType get(KeyType key);

	// check if the Dictionary is empty
	bool isEmpty();

	// check the size of Dictionary
	int getLength();

	// display the items in the Dictionary
	void print();

	// resizing the Dictionary 
	void resize();

};
