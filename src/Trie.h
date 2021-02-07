/**
 *
 * Trie.h - Header file of Trie
 *
 * @author Hou Man S10197636F
 * @since 07-02-2021
**/

#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <chrono>
using namespace std;

const int MAX_SIZE = 37; // (26 characters + empty space + 10 digits(0-9))
typedef string ItemType;

class Trie
{
    private:
        // declaration of TrieNode
        struct TrieNode
        {
            // TrieNode pointers list with size of 37 representing its children
            struct TrieNode *children[MAX_SIZE];

            // a boolean variable which indicates whether if the node represents end of a word 
            bool isEndOfWord;
        };
        
        // the root of Trie
        TrieNode *root;

        // helper functions

        /**
         *
         * This method will create a new TrieNode and initialize all its children to NULLs.
         *
         * @return TrieNode* It will return a new TrieNode.
         *
         * */
        TrieNode* getNode();

        /**
         *
         * This method will check whether the TrieNode is the lastNode, meaning having 0 child.
         * 
         * @param node This parameter is to get the TrieNode pointer.
         *
         * @return bool It will return a boolean value which indicate whether the TrieNode is the lastNode.
         *
         * */
        bool isLastNode(TrieNode* node);

        /**
         *
         * This method is used when performing exact searching, by checking whether the word does exist in the TrieNode.
         * 
         * This method will traverse the Trie starting from the root,
         * by incrementing the level and accessing to that particular child node using hashed char index
         * until it reaches the last character.
         *  
         * @param word This parameter is to get the word.
         *
         * @return bool It will return a boolean value which indicate whether the word does exist in the TrieNode.
         *
         * */
        bool isWordExist(ItemType word);

        /**
         *
         * This method is a recursive helper funtion called by main remove function to renove the word from Trie.
         * 
         * This method will traverse the Trie starting from the root, 
         * by incrementing the level and accessing to that particular child node using hashed char index
         * until it reaches the last character to delete.
         *
         * It will have a early return to cancel the operation when the respective child node is NULL
         * 
         * @param word This parameter is to get the word.
         *
         * @return TrieNode* This will return the update TrieNode after the opration is performed.
         * */
        TrieNode* removeR(TrieNode* node, ItemType word, int level);

        /**
         *
         * This method is a search prefix helper function which perform the searching prefix task.
         * 
         * It will first traverse the node to the last level of characters (immediate return when the prefix does not exist),
         * and later call a search function to perform the searching task to get the available words.
         * 
         * @param key This parameter is to get the prefix.
         * @param result This parameter is to get the result list for appending result.
         * 
         * */
        void searchPrefixHelper(ItemType key, vector<string> &result);

        /**
         *
         * This method is a recursive helper function to print out all the keywords in Trie by reaching every end of node
         * 
         * It will perform a depth first search until it reached the end of a word.
         * Backtracking by popping the last character will also perform consecutively after the searching is ended.
         * 
         * @param node This parameter it to get the recurred node
         * @param word This parameter is to get the prefix.
         * @param result This parameter is to get the result list for appending result.
         * 
         * */
        void searchR(TrieNode* node, string word, vector<string> &result);

        /**
         *
         * This method is a display helper function to display the structure of Trie horizontally.
         * 
         * @param node This parameter is to get the node
         * @param spacing This parameter is to get the current spacing
         * @param divider This parmameter is to get the divider set which indicates which spacing should cout "|"
         * 
         * */
        void displayR(TrieNode* node, int spacing, set<int> divider);

        /**
         *
         * This method is find the last child pos from the current node
         * 
         * @param node This parameter is to get the node
         * 
         * @return int This will return the position of last child in the Trie Node
         * */
        int findLastChildPos(TrieNode *node);

        /**
         *
         * This method is find whether the current node is the last child of the node.
         * 
         * @param node This parameter is to get the node
         * @param start This parameter is to get the current position of the node
         * 
         * @return bool This will return whether the current node is the last child of the node
         * */
        bool isLastChildAt(TrieNode *node, int start);
        
        /**
         *
         * This method is find whether the node has more than 1 child at the given position.
         * 
         * @param node This parameter is to get the node
         * @param start This parameter is to get the current position of the node
         * 
         * @return bool This will return whether the the node has more than 1 child at the given position.
         * */
        bool hasMoreThanOneChildAt(TrieNode* node, int start);

        /**
         *
         * This method is a recursive helper function to preform mass deletion of all existing nodes
         * 
         * Starting from the root, it will keep recurring until it reaches the end of node
         * It will delete the node and free up the memory
         * 
         * @param node This parameter is to get the node
         * */
        void resetR(TrieNode* node);
        

    public:
        
        /**
         *
         * This method is the constructor of Trie
         *
         * It will initialise root to a new trie node
         *
         * */
        Trie();	

        /**
         *
         * This method is the deconstructor of Trie to free up the memory
         *
         * It will call the reset Trie method to deallocate and free up the memory
         *
         * */
        ~Trie();   

        /**
         *
         * This method is used to insert a word to Trie.
         * 
         * This method will traverse the Trie starting from the root, 
         * by incrementing the level and accessing to that particular child node using hashed char index
         * until it reaches the last character.
         * 
         * If the character does not exist in the child nodes, it will create a new node using getNode() method.
         * At the end, it will mark the current node as end of word.
         *  
         * @param word This parameter is to get the word.
         *
         * */
        void insert(ItemType word);

        /**
         *
         * This method is remove a word from Trie it the word does exist.
         * 
         * It will call a recursive helper function to perform the deletion task.
         * 
         * @param word This parameter is to get the word.
         *
         * */
        void remove(ItemType word);

        /**
         *
         * This method is search for a word in Trie.
         * 
         * It will call a isWordExisit helper function to perform the searching task.
         * 
         * @param word This parameter is to get the word.
         *
         * @return bool This will return a boolean value which indicate whether the key does exist in Trie.
         * */
        bool searchExact(ItemType word);

        // print the suggestions by the prefix given
        /**
         *
         * This method is search for all words in Trie which have the prefix starting with key which is input by user.
         * 
         * It will call a search prefix helper function to perform the searching task.
         * 
         * @param key This parameter is to get the prefix.
         *
         * @return vector<string> This will return a vector consisting of the prefix.
         * */
        vector<string> searchPrefix(ItemType key);

        /**
         *
         * This method is called to get all words in Trie.
         * 
         * It will call the searchR helper method to perform the depth first search from root.
         * 
         * @return vector<string> This will return a vector consisting of all words in Trie.
         * */
        vector<string> getAllWords();

        /**
         *
         * This method is to display the structure of Trie horizontally.
         * 
         * It will call the displayR helper method to perform the display task.
         * 
         * */
        void display();

        /**
         *
         * This method is to reset the Trie and initialise the Trie root to default node again.
         * 
         * This method will call a resetR helper function to perform the reset task.
         * */
        void reset();
};