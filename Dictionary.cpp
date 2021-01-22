#include <iostream>
#include "Dictionary.h" 
using namespace std;

Dictionary::Dictionary(){
  for(int i = 0; i < MAX_SIZE; i++){
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
	  total %= MAX_SIZE;
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
  int index = hash(key);
  Node *curr = items[index];
  if(!curr){
    return "";
  }else{
    Node *tmp = curr;
    while(tmp){
      if(tmp->key == key)return tmp->item;
      tmp = tmp->next;
    }
  }

  return "";
}



int Dictionary::getLength(){return size;}

void Dictionary::print(){ 
  for (int i = 0; i < MAX_SIZE ; i++)
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
