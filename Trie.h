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

        bool isWordExist(ItemType word);

        // helper funtions to print the auto suggestions
        int autoSuggestionsHelper(ItemType word);

        // recursive helper function to print out all the keywords in Trie by reaching every end of node
        void displayR(TrieNode* node, string word);

        // recursive helper funtion to access and remove the word by incrementing the level
        TrieNode* removeR(TrieNode* node, ItemType word, int level);

        // recursive helper funtion to display the contents of the Trie
        void displayTrieR(TrieNode* node, char str[] , int level);

        // recursive helper function to reset the trie
        void resetR(TrieNode* node);


        

    public:
        // constructor
        Trie();	

        // destructor
        ~Trie();   

        // insertion of new keyword
        void insert(ItemType word);

        // removal of a keyword
        void remove(ItemType word);

        // search for a word in Trie
        bool search(ItemType word);

        // print the suggestions by the prefix given
        void printAutoSuggestions(ItemType word);

        // display the full structure of Trie
        void display();

        // reset the trie to default
        void reset();
};
