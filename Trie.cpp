// Trie.cpp - Implementation of Trie ADT using Pointers
#include "Trie.h"

Trie::Trie(){
    root = NULL;
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