#pragma once
#include<string>
#include<iostream>
using namespace std;

const int DEFAULT_TABLE_SIZE = 30;
template<typename KeyType, typename ItemType>

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
	Node *items[DEFAULT_TABLE_SIZE]; 
        


public:

	// constructor
	Dictionary();

	// destructor
	~Dictionary();

	// hash function
	int hash(KeyType key);

	bool add(KeyType newKey, ItemType newItem);

	void remove(KeyType key);

	ItemType get(KeyType key);

	bool isEmpty();

	int getLength();

	void print();

	void resize();

};
