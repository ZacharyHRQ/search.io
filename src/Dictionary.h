/**
*
* 	@brief Trie.h - Header file of Dictionary
*   @brief This is a hash table that has used dynamic resizing and has thresholds to how long the chains can be 
*
* 	@author Zachary S10185319J
*   Group: P04 Group 4
* 	@since 21-01-2021
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

	/**
	*
	* This is a constructor for the Dictionary class 
	* It sets the threshold of load factor , maxSize and default table size
	* It empties the items array
	* 
	* */
	Dictionary();

	/**
	*
	* This is a destructor for the Dictionary class 
	* It empties the items array and deletes every value in items
	* 
	* */
	~Dictionary();

	/**
	*
	* This is the hash function method that takes a key and hashes it into an index
	* 
	* @param KeyType key : key to hash
	* 
	* @return int This returns the index to place into items array
	*
	* */
	int hash(KeyType key);

	/**
	*
	* This method is used to add a new key value pair to the dictionary , it resize the dictionary if the size exceeds the threshold size
	* 
	* @param KeyType newKey : key to hash , ItemType newItem : the item to newKey is mapped to 
	* 
	* @return bool This returns if the method worked
	*
	* */
	bool add(KeyType newKey, ItemType newItem);

	/**
	*
	* This method is used to remove a key value pair from the dictionary
	* 
	* @param KeyType key : key to find from the dictionary
	* 
	*
	* */
	void remove(KeyType key);

	/**
	*
	* This method is used to retrive the value from the input key
	* 
	* @param KeyType key : key to find from the dictionary
	* 
	* @return ItemType This returns the value associated to the key from @param
	* */
	ItemType get(KeyType key);

	/**
	*
	* This method is used to check if the dictionary is empty
	* 
	* @return bool This returns if the dictionary is empty
	* */
	bool isEmpty();

	/**
	*
	* This method is used to retrieve the size of the dictionary
	* 
	* @return int This returns the size of the dictionary
	* */
	int getLength();

	/**
	*
	* This method is used to display the contents of the dictionary
	* 
	* */
	void print();

	/**
	*
	* This method is used to dyanmically resize the dictionary
	* It doubles the size of the current tablesize 
	* Creates a new array and rehashes the current array key-value pairs
	* adding it into the new array. It deletes the old array.
	* 
	* 
	* */
	void resize();

};
