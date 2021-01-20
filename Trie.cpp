// Trie.cpp - Implementation of Trie ADT using Pointers
#include "Trie.h"

Trie::Trie(){
    root = getNode();
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
        int index = CHAR_TO_INDEX(word[level]);

        if (curr->children[index] == nullptr)
            curr->children[index] = getNode();
        
        curr = curr->children[index];
    }

    // mark last node as leaf
    curr->isEndOfWord = true;
}

void Trie::search(ItemType word){
    int result = printAutoSuggestions(word);
    cout << result << endl;
    if (result == -1) 
        cout << "No other strings found with this prefix\n"; 

    else if (result == 0) 
        cout << "No string found with this prefix\n"; 
}

int Trie::printAutoSuggestions(ItemType word){
    TrieNode *curr = root;

    for (int level = 0; level < word.length(); level++){
        int index = CHAR_TO_INDEX(word[level]);

        if (curr->children[index] == nullptr) return 0;

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
        return -1; 
    } 
  
    // If there are are nodes below last 
    // matching character. 
    string prefix = word; 
    suggestionsRec(curr, prefix); 
    return 1; 
}

void Trie::suggestionsRec(Trie::TrieNode* node, ItemType word){

    if (node->isEndOfWord){
        cout << word << endl;
    }

    if (isLastNode(node)) return;

    for (int i = 0; i < MAX_SIZE; i++){
        if (node->children[i]){
            word.push_back(97 + i);

            suggestionsRec(node->children[i], word);

            // backtracking
            word.pop_back();
        }
    }
}