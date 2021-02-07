/**
*
* 	Dictionary cpp file
*   This is a hash table that has used dynamic resizing and has thresholds to how long the chains can be 
*
* 	@author Zachary
* 	@since 01-21-2021
*/

#include "Dictionary.h"
#include <iostream>
using namespace std;

/**
*
* This is a constructor for the Dictionary class 
* It sets the threshold , maxSize and default table size
* It empties the items array
* 
* */
template <typename KeyType, typename ItemType>
Dictionary<KeyType, ItemType>::Dictionary() {
    threshold = 0.75f; // setting the threshold to 0.75%
    maxSize = 21; // setting max size
    tableSize = DEFAULT_TABLE_SIZE;
    size = 0;

    // empties items
    for (int i = 0; i < tableSize; i++) {
        items[i] = NULL;
    }
}


/**
*
* This is a destructor for the Dictionary class 
* It empties the items array and deletes every value in items
* 
* */
template <typename KeyType, typename ItemType>
Dictionary<KeyType, ItemType>::~Dictionary() {
    // deletes all indexes in items
    for (int i = 0; i < tableSize; i++){
        if (items[i]){
            Node *temp = items[i];
            temp->next = NULL;

            delete temp;
        }
        items[i] = NULL;
    }
}

/**
*
* This is a helper method for converting a letter to the Assci numbers used in the hash function
* 
* @param char c : charactor to convert
* @return int This returns the assci number 
* */
int charvalue(char c){
	if (isalpha(c)) // checks if it a alphabet 
	{
		if (isupper(c))
			return (int)c - (int) 'A'; // A = 65 
		else
			return (int)c - (int) 'a' + 26; // adding 26 for lowercase letters
    }
    
    return -1; 
}

/**
*
* This is the hash function method that takes a key and hashes it into an index
* 
* @param KeyType key : key to hash
* 
* @return int This returns the index to place into items array
*
* */

template <typename KeyType, typename ItemType>
int Dictionary<KeyType, ItemType>::hash(KeyType key) {

    int total = charvalue(key[0]);

    for (int i = 1; i < key.length(); i++) {
        if (charvalue(key[i]) < 0) // not an alphabet
            continue;

        total = total * 52 + charvalue(key[i]);  // horner's rule
        total %= tableSize; 
    }

    return total;
}

/**
*
* This method is used to add a new key value pair to the dictionary , it resize the dictionary if the size exceeds the threshold size
* 
* @param KeyType newKey : key to hash , ItemType newItem : the item to newKey is mapped to 
* 
* @return bool This returns if the method worked
*
* */
template <typename KeyType, typename ItemType>
bool Dictionary<KeyType, ItemType>::add(KeyType newKey, ItemType newItem) {
    // hashing key
    int index = hash(newKey);
    // creating new node to be inserted 
    Node *curr = items[index];
    Node *newNode = new Node;
    newNode->item = newItem;
    newNode->key = newKey;
    newNode->next = NULL;

    // if hashed index is empty
    if (items[index] == NULL) {
        items[index] = newNode;
    } else {
        // duplicated key , return false 
        if (curr->key == newKey) {
            return false;
        }
        // loops down the chain to add to 
        while (curr->next) {
            curr = curr->next;
            if (curr->key == newKey) return false;
        }

        curr->next = newNode;
    }

    size++;
    // if current size is greater or equal to maxsize (threshold * tableSize) , resize
    if (size >= maxSize) {
        resize();
    }

    return true;
}

/**
*
* This method is used to remove a key value pair from the dictionary
* 
* @param KeyType key : key to find from the dictionary
* 
*
* */
template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::remove(KeyType key) {

    int index = hash(key);
    Node *curr = items[index];
    
    if (curr) {
        // first node of the chain to be deleted , delete and set next node to be head 
        if (curr->key == key) {
            Node *temp = curr->next;
            delete curr->next;
            items[index] = temp;
        } else {
            // loop til the node is found 
            while (curr->next) {
                if (curr->next->key == key) {
                    Node *temp = curr->next->next;
                    curr->next->next = NULL;
                    delete curr->next;
                    curr->next = temp;
                }

                curr = curr->next;
            }
        }

        size--;
    }
}

/**
*
* This method is used to retrive the value from the input key
* 
* @param KeyType key : key to find from the dictionary
* 
* @return ItemType This returns the value associated to the key from @param
* */
template <typename KeyType, typename ItemType>
ItemType Dictionary<KeyType, ItemType>::get(KeyType key) {
    ItemType item;
    int index = hash(key);

    if (items[index]) {
        Node *curr = items[index];
        while (curr) {
            if (curr->key == key)
                return curr->item;
            curr = curr->next;
        }
    }

    return item;
}

/**
*
* This method is used to retrieve the size of the dictionary
* 
* @return int This returns the size of the dictionary
* */
template <typename KeyType, typename ItemType>
int Dictionary<KeyType, ItemType>::getLength() {
    return size;
}


/**
*
* This method is used to display the contents of the dictionary
* 
* */
template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::print() {
    for (int i = 0; i < tableSize; i++) {
        Node *curr = items[i];
        if (curr) {
            while (curr) {
                cout << curr->key << " : " << curr->item << endl;
                curr = curr->next;
            }
        }
    }
}

/**
*
* This method is used to check if the dictionary is empty
* 
* @return bool This returns if the dictionary is empty
* */
template <typename KeyType, typename ItemType>
bool Dictionary<KeyType, ItemType>::isEmpty() {
    return bool(size);
}

/**
*
* This method is used to dyanmically resize the dictionary
* It doubles the size of the current tablesize 
* Creates a new array and rehashes the current array key-value pairs
* adding it into the new array. It deletes the old array.
* 
* 
* */
template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::resize() {
    int oldTableSize = tableSize;
    tableSize *= 2; // double the size 
    maxSize = (int)(tableSize * threshold); // calculate 


    Node **oldItems = items; // copy of old items
    Node *newItems[tableSize]; // new array to store the new table 
    for (int i = 0; i < tableSize; i++)
        newItems[i] = NULL;

    // rehashing and transfering into new table 
    size = 0;
    for (int hash = 0; hash < oldTableSize; hash++){
        if (newItems[hash] != NULL) {
            Node *oldentry;
            Node *entry = oldItems[hash];
            
            while (entry != NULL) {
                add(entry->key, entry->item);
                oldentry = entry;
                entry = entry->next;
                delete oldentry;
            }
        }
    }

    delete[] oldItems;
}