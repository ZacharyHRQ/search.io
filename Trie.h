#pragma once
#include <iostream>
#include <vector>
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
        void searchPrefixHelper(ItemType word, vector<string> &result);

        // recursive helper function to print out all the keywords in Trie by reaching every end of node
        void searchR(TrieNode* node, string word, vector<string> &result);

        // recursive helper funtion to access and remove the word by incrementing the level
        TrieNode* removeR(TrieNode* node, ItemType word, int level);

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
        bool searchExact(ItemType word);

        // print the suggestions by the prefix given
        vector<string> searchPrefix(ItemType word);

        // get all words in trie
        vector<string> getAllWords();

        // reset the trie to default
        void reset();
};