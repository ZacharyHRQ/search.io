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

int hashCharToIndex(char c){
    if (c == 32) // if the char is space
        return 26;
    else if (isdigit(c))
        return 27 + int(c) - 48;
    else
        return CHAR_TO_INDEX(c);
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
        int index = hashCharToIndex(word[level]);
        
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
        int index = hashCharToIndex(word[level]);

        if (curr->children[index] == nullptr) return false;

        curr = curr->children[index];
    }

    return (curr != nullptr && curr->isEndOfWord);
}

// search for a word in Trie
bool Trie::searchExact(ItemType word){
    auto start = chrono::high_resolution_clock::now();
    
    bool isExist = isWordExist(word);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
   cerr << "\033[32m\n"
         << int(isExist) << " result in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";
    return isExist;
}

// print the suggestions by the prefix given
vector<string> Trie::searchPrefix(ItemType word){
    auto start = chrono::high_resolution_clock::now();

    vector<string> result;

    searchPrefixHelper(word, result);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cerr << "\033[32m\n"
         << result.size() << " results in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";
 
    return result;
}

// helper funtions to print the auto suggestions
void Trie::searchPrefixHelper(ItemType word, vector<string> &result){
    TrieNode *curr = root;

    for (int level = 0; level < word.length(); level++){
        int index = hashCharToIndex(word[level]);

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
            if (i == 26)
                word.push_back(32);
            else if (i >= 27 && i <= 36)
                word.push_back(48 + i - 27);
            else
                word.push_back(97 + i);
                

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

    int index = hashCharToIndex(word[level]);

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
    auto start = chrono::high_resolution_clock::now();

    vector<string> result;

    searchR(root, "", result);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cerr << "\033[32m\n"
         << result.size() << " results in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";

    return result;
}

void Trie::display(){
    set<int> divider;

    displayR(root, 0, divider);
}

void Trie::displayR(Trie::TrieNode* node, int spacing, set<int> divider){

    int lastChildPos = findLastChildPos(node);

    bool isMoreThanOneChild = hasMoreThanOneChildAt(node, 0);
    if (isMoreThanOneChild){
        divider.insert(spacing);
    }
    
    if (node->isEndOfWord){
        cout << "*";
    }
    cout << endl;

    if (isLastNode(node)){
        return;
    }
    
    for (int i = 0; i < MAX_SIZE; i++){
        if (node->children[i]){

            if (lastChildPos == i){
                divider.erase(spacing);
            }

            string word;
            if (i == 26)
                word.push_back(32);
            else if (i >= 27 && i <= 36)
                word.push_back(48 + i - 27);
            else
                word.push_back(97 + i);

            bool lastChild = isLastChildAt(node, i+1);
            
            for (int space = 0; space < spacing; space++){

                if (divider.find(space) != divider.end())
                    cout << "│";
                else
                    cout << " ";
                
            }
            
            if (isMoreThanOneChild && !lastChild)
                cout << "├──";
            else
                cout << "└── ";
            
            cout << word;

            // if (hasMoreThanOneChildAt(node, 0)){
            //     divider.insert(spacing+4);
            // }

            displayR(node->children[i], spacing+4, divider);

            // backtracking
            word.pop_back();
        }
    }
}

int Trie::findLastChildPos(TrieNode *node){
    for (int i = MAX_SIZE-1; i > 0; i--)
        if (node->children[i]) return i;

    return 0;
}

bool Trie::isLastChildAt(TrieNode *node, int start){

    for (int i = start; i < MAX_SIZE; i++){
        if (node->children[i]) return false;
    }

    return true;
}

bool Trie::hasMoreThanOneChildAt(TrieNode* node, int start){
    int child = 0;

    for (int i = start; i < MAX_SIZE; i++){
        if (node->children[i]) child++;

    }

    return child > 1;
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