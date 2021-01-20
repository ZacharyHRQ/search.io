#pragma once

#include<string>
#include<iostream>
using namespace std;

const int MAX_SIZE = 101;
typedef string KeyType;
typedef string ItemType;


class Dictionary
{
private:
	struct Node
	{
		KeyType	 key;   // search key
		ItemType item;	// data item
		Node     *next;	// pointer pointing to next item with same search key
	};

	Node *items[MAX_SIZE];
	int  size;			// number of items in the Dictionary

public:

	// constructor
	Dictionary();

	// destructor
	~Dictionary();

	int hash(KeyType key);

	bool add(KeyType newKey, ItemType newItem);

	void remove(KeyType key);

	ItemType get(KeyType key);

	bool isEmpty();

	int getLength();

	void print();

};
