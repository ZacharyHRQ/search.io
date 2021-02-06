// Trie.cpp - Implementation of Trie ADT using Pointers
#include "Trie.h"

// constructor of Trie
Trie::Trie(){
    root = getNode();
}

// deconstructor of Trie to free up the memory
Trie::~Trie(){
    reset();
}

// Returns new trie node (initialized to NULLs) 
Trie::TrieNode* Trie::getNode(){
    TrieNode *node = new TrieNode;
    node->isEndOfWord = false;

    for (int i = 0; i < MAX_SIZE; i++){
        node->children[i] = NULL;
    }

    return node;
}

// check whether the TrieNode is the lastNode (no children)
bool Trie::isLastNode(Trie::TrieNode* node){
    for (int i = 0; i < MAX_SIZE; i++){
        if (node->children[i] != NULL) return false;
    }
    
    return true;
}

// If not present, inserts key into trie.  If the 
// key is prefix of trie node, just marks leaf node 
void Trie::insert(ItemType word){
    TrieNode *curr = root;

    for (int level = 0; level < word.length(); level++){
        int index = (word[level] != 32) ? CHAR_TO_INDEX(word[level]) : 26;

        if (curr->children[index] == nullptr)
            curr->children[index] = getNode();
        
        curr = curr->children[index];
    }

    // mark last node as leaf
    curr->isEndOfWord = true;
}

bool Trie::isWordExist(ItemType word){
    TrieNode *curr = root;

    for (int level = 0; level < word.length(); level++){
        int index = (word[level] != 32) ? CHAR_TO_INDEX(word[level]) : 26;

        if (curr->children[index] == nullptr) return false;

        curr = curr->children[index];
    }

    return (curr != nullptr && curr->isEndOfWord);
}

// search for a word in Trie
bool Trie::searchExact(ItemType word){
    bool isExist = isWordExist(word);

    return isExist;
}

// print the suggestions by the prefix given
vector<string> Trie::searchPrefix(ItemType word){
    vector<string> result;

    searchPrefixHelper(word, result);
 
    return result;
}

// helper funtions to print the auto suggestions
void Trie::searchPrefixHelper(ItemType word, vector<string> &result){
    TrieNode *curr = root;

    for (int level = 0; level < word.length(); level++){
        int index = (word[level] != 32) ? CHAR_TO_INDEX(word[level]) : 26;

        if (curr->children[index] == nullptr) return;

        curr = curr->children[index];
    }

    // If prefix is last node of tree (has no children)
    bool isLast = isLastNode(curr);

    // If prefix is present as a word, but 
    // there is no subtree below the last 
    // matching node. 
    if (isLast) 
    { 
        cout << word << endl; 
        return;
    } 
  
    // If there are are nodes below last 
    // matching character. 
    string prefix = word; 
    searchR(curr, prefix, result); 
}

// recursive helper function to print out all the keywords in Trie by reaching every end of node
void Trie::searchR(TrieNode* node, string word, vector<string> &result){
    if (node->isEndOfWord){
        result.push_back(word);
    }

    if (isLastNode(node)) return;

    for (int i = 0; i < MAX_SIZE; i++){
        if (node->children[i]){
            if (i != 26)
                word.push_back(97 + i);
            else
                word.push_back(32);

            searchR(node->children[i], word, result);

            // backtracking
            word.pop_back();
        }
    }
}

// removal of a keyword from trie if existed
void Trie::remove(ItemType word){
    root = removeR(root, word, 0);
}

// recursive helper funtion to access and remove the word by incrementing the level
Trie::TrieNode* Trie::removeR(Trie::TrieNode *node, ItemType word, int level){
    if (root == nullptr) return NULL;

    if (level == word.length()){
        if (node->isEndOfWord)
            node->isEndOfWord = false;
        
        if (isLastNode(node)){
            delete (node);
            node = NULL;
        }

        return node;
    }

    int index = (word[level] != 32) ? CHAR_TO_INDEX(word[level]) : 26;

    // if the word not found, then cancel the operations and return
    if (node->children[index] == nullptr) return node;

    node->children[index] = removeR(node->children[index], word, level + 1);

    if (isLastNode(node) && node->isEndOfWord){
        delete (node);
        node = NULL;
    }

    return node;
}

// get all words in trie
vector<string> Trie::getAllWords(){
    vector<string> result;

    searchR(root, "", result);

    return result;
}

// reset the trie and initialise the trie to default again
void Trie::reset(){
    resetR(root);
    root = getNode();
}

// mass deletion of all existing nodes
// Starting from the root, it will keep recurring until it reaches the end of node
// it will delete the node and free up the memory
void Trie::resetR(TrieNode *node){

    if (isLastNode(node)){
        node = NULL;
        delete (node);
        return;
    }

    for (int level = 0; level < MAX_SIZE; level++){
        if (node->children[level]){
            resetR(node->children[level]);
        }
    }

    // free up the current node as well after removing all its children
    node = NULL;
    delete (node);
}