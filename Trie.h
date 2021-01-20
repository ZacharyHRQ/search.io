#pragma once
#include <iostream>
using namespace std;

const int MAX_SIZE = 27; // (26 characters + empty space)
typedef string ItemType;

#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 

class Trie
{
    private:
        struct TrieNode
        {
            // TrieNode pointers list with size of 27 representing its children
            struct TrieNode *children[MAX_SIZE];

            // isWordEnd is true if the node represents end of a word 
            bool isEndOfWord;
        };
        
        // the root of Trie
        TrieNode *root;

        // helper functions

        // get a new TrieNode
        TrieNode* getNode();

        // check whether the TrieNode is the lastNode (no children)
        bool isLastNode(TrieNode* node);

        int printAutoSuggestions(ItemType word);

        void suggestionsRec(TrieNode* node, ItemType word);

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
        void search(ItemType word);

        // display the full structure of Trie
        void display();
};