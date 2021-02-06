#include <iostream>
#include "Dictionary.h" 
using namespace std;


Dictionary::Dictionary(){
  threshold = 0.75f;
  maxSize = 96;
  tableSize = DEFAULT_TABLE_SIZE;
  size = 0;
  for(int i = 0; i < tableSize; i++){
    items[i] = NULL;
  }
}

Dictionary::~Dictionary(){}

int charvalue(char c)
{
	if (isalpha(c))
	{
		if (isupper(c))
			return (int)c - (int) 'A';
		else
			return (int)c - (int) 'a' + 26;
	}
	else
		return -1;
}



int Dictionary::hash(KeyType key)
{
	int total = charvalue(key[0]);

	for (int i = 1; i < key.length(); i++)
	{
		if (charvalue(key[i]) < 0)  // not an alphabet
			continue;
		total = total * 52 + charvalue(key[i]);
	  total %= tableSize;
	}

  return total;
}

bool Dictionary::add(KeyType newKey, ItemType newItem){  
  int index = hash(newKey);
  Node* curr = items[index];
  Node *newNode = new Node;
  newNode->item = newItem;
  newNode->key = newKey;
  newNode->next = NULL;
  if (items[index] == NULL){ 
    items[index] = newNode;
  }
  else{
    if (curr->key == newKey){
      return false;
    }
    while(curr->next){
      curr = curr->next;
      if (curr->key== newKey){ 
        return false;
      }
    }
    curr->next = newNode;
  }
  size++;
  if(size >= maxSize) {
    cout << "resize" << endl; 
    resize();
  }
  return true;
}

void Dictionary::remove(KeyType key){
  int index = hash(key);
  Node *curr = items[index]; 
  if(curr){
    if(curr->key == key){
      Node* temp = curr->next;
      delete  curr->next;
      items[index] = temp;
    }else{
      while(curr->next){
        if(curr->next->key == key){
          Node* temp = curr->next->next;
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

ItemType Dictionary::get(KeyType key){
    ItemType item;
    int index = hash(key);
    if (items[index]){
        Node *curr = items[index];
        while(curr){
            if(curr->key == key) return curr->item;
            curr = curr->next; 
        }
    }
    return item;
}



int Dictionary::getLength(){return size;}

void Dictionary::print(){ 
  for (int i = 0; i < tableSize; i++)
    {
        Node* curr = items[i];
        if(curr){
            while(curr){
                cout << curr->key << " : " << curr->item << endl;
                curr = curr->next;
            }
        }

    }
}

bool Dictionary::isEmpty(){return bool(size);}

void Dictionary::resize(){
		int oldTableSize = tableSize;
		tableSize *= 2;
		maxSize = (int) (tableSize * threshold);
		Node **oldItems = items;
		Node *newItems[tableSize];
		for (int i = 0; i < tableSize; i++)
			newItems[i] = NULL;
		size = 0;
		for (int hash = 0; hash < oldTableSize; hash++)
		if (newItems[hash] != NULL) {
			Node* oldentry;
			Node * entry = oldItems[hash];
			while (entry != NULL) {
					add(entry->key, entry->item);
					oldentry = entry; 
					entry = entry->next; 
					delete oldentry;
			}
		}
		delete[] oldItems;
}	