#pragma once
#include <iostream>
using namespace std;

const int MAX_SIZE = 27; // (26 characters + empty space)
typedef string ItemType;

struct TrieNode
{
    struct TrieNode *children[MAX_SIZE];

    bool isEndOfWord;
};

class Trie
{
    private:
        TrieNode *root;

    public:
        // constructor
        Trie();	

        // destructor
        ~Trie();   

        // insertion of new keyword
        void insert(ItemType word);

        // removal of a keyword
        bool remove(ItemType word);

        // search for a word in Trie
        bool search(ItemType word);

        // display the full structure of Trie
        void display();

};