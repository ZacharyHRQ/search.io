/**
 *
 * @brief Trie.cpp - Implementation of Trie ADT using Pointers
 *
 * @author Hou Man 
 * StudentID: S10197636F
 * Group: P04 Group 4
 * @since 07-02-2021
**/

#include "Trie.h"

/**
 *
 * This method is the constructor of Trie
 *
 * It will initialise root to a new trie node
 *
 * */
Trie::Trie(){
    root = getNode();
}


/**
 *
 * This method is the deconstructor of Trie to free up the memory
 *
 * It will call the reset Trie method to deallocate and free up the memory
 *
 * */
Trie::~Trie(){
    reset();
}

/**
 *
 * This method will create a new TrieNode and initialize all its children to NULLs.
 *
 * @return TrieNode* It will return a new TrieNode.
 *
 * */
Trie::TrieNode* Trie::getNode(){
    TrieNode *node = new TrieNode;
    // mark the current node is not the end of word.
    node->isEndOfWord = false;

    for (int i = 0; i < MAX_SIZE; i++){
        node->children[i] = NULL;
    }

    return node;
}

/**
 *
 * This method will hash a character to an index.
 * There is only 37 possibilities for the children nodes:
 * Alphabet Letters ('a' - 'z') will return 0 - 25 respectively.
 * Empty space ('') will return 26.
 * Digits ('0' - '9') will return 27 - 36 respetively.
 * 
 * @param c This paramater is to get the character which is being hashed and processed.
 *
 * @return int It will return an index which indicates the hashed character.
 *
 * */
int hashCharToIndex(char c){
    if (c == 32)  // if the char is empty space ('')
        return 26;
    else if (isdigit(c)) // if the char is digit ('0' - '9')
        return 27 + int(c) - 48;
    else // if the char is alphabet letter ('a' - 'z')
        return (int) c - (int) 'a'; 
}

/**
 *
 * This method will check whether the TrieNode is the lastNode, meaning having 0 child.
 * 
 * @param node This parameter is to get the TrieNode pointer.
 *
 * @return bool It will return a boolean value which indicate whether the TrieNode is the lastNode.
 *
 * */
bool Trie::isLastNode(Trie::TrieNode* node){
    for (int i = 0; i < MAX_SIZE; i++){
        if (node->children[i] != NULL) return false;
    }
    
    return true;
}

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
bool Trie::isWordExist(ItemType word){
    TrieNode *curr = root;

    for (int level = 0; level < word.length(); level++){
        int index = hashCharToIndex(word[level]);

        // It will have an early "false" return, when the child node does not exist while traversing.
        if (curr->children[index] == nullptr) return false;
        
        // accessing to the child node
        curr = curr->children[index];
    }

    // After the traversing, it will check whether the current node is not null and it is the end of word.
    return (curr != nullptr && curr->isEndOfWord);
}


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
void Trie::insert(ItemType word){
    TrieNode *curr = root;

    for (int level = 0; level < word.length(); level++){
        int index = hashCharToIndex(word[level]);
        
        // If the character does not exist in the child nodes, it will create a new node using getNode() method.
        if (curr->children[index] == nullptr)
            curr->children[index] = getNode();
        
        curr = curr->children[index];
    }

    // mark the current node as end of word
    curr->isEndOfWord = true;
}

/**
 *
 * This method is remove a word from Trie it the word does exist.
 * 
 * It will call a recursive helper function to perform the deletion task.
 * 
 * @param word This parameter is to get the word.
 *
 * */
void Trie::remove(ItemType word){
    root = removeR(root, word, 0);
}

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
 * @param node This parameter is to get the node recurred.
 * @param word This parameter is to get the word.
 * @param level This parameter is to get the current level.
 *
 * @return TrieNode* This will return the update TrieNode after the opration is performed.
 * */
Trie::TrieNode* Trie::removeR(Trie::TrieNode *node, ItemType word, int level){
    // immediate return when the root is empty
    if (root == nullptr) return NULL;

    // If last character of key is being processed
    if (level == word.length()){

        // Unmark the node as it is no more end of word after removal of given key
        if (node->isEndOfWord)
            node->isEndOfWord = false;
        
        // delete the current node and free up memory space if the node does not have child (not prefix of other word)
        if (isLastNode(node)){
            delete (node);
            node = NULL;
        }

        return node;
    }

    int index = hashCharToIndex(word[level]);

    // if the word not found, then cancel the operations and return
    if (node->children[index] == nullptr) return node;

    // incrementing the level to recur and access its node child
    node->children[index] = removeR(node->children[index], word, level + 1);

    // If root does not have any child (its only child got deleted),
    // and it is not end of another word.
    if (isLastNode(node) && !node->isEndOfWord){
        delete (node);
        node = NULL;
    }

    return node;
}

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
bool Trie::searchExact(ItemType word){
    // get the start time when the searching task is performed
    auto start = chrono::high_resolution_clock::now();
    
    bool isExist = isWordExist(word);

    // calculate the duration of the task and display them in terminal console.
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cerr << "\033[32m\n"
         << int(isExist) << " result in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";

    return isExist;
}

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
vector<string> Trie::searchPrefix(ItemType key){
    auto start = chrono::high_resolution_clock::now();

    vector<string> result;

    searchPrefixHelper(key, result);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cerr << "\033[32m\n"
         << result.size() << " results in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";
 
    return result;
}

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
void Trie::searchPrefixHelper(ItemType key, vector<string> &result){
    TrieNode *curr = root;

    for (int level = 0; level < key.length(); level++){
        int index = hashCharToIndex(key[level]);

        // It will have an early "false" return, when the child node does not exist while traversing.
        if (curr->children[index] == nullptr) return;

        // access the child node
        curr = curr->children[index];
    }

    // If prefix is last node of tree (has 0 child node)
    bool isLast = isLastNode(curr);

    // If prefix is present as a word, but 
    // there is no subtree below the last 
    // matching node. 
    if (isLast) 
    {  
        return;
    } 
  
    // If there are are nodes below last matching character,
    // perform the searching task to get the available words.
    string prefix = key; 
    searchR(curr, prefix, result); 
}

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
void Trie::searchR(TrieNode* node, string word, vector<string> &result){
    // found a string in Trie with the given prefix 
    if (node->isEndOfWord){
        result.push_back(word);
    }

    // All children struct node pointers are NULL 
    if (isLastNode(node)) return;

    // loop over all children nodes
    for (int i = 0; i < MAX_SIZE; i++){
        if (node->children[i]){

            // append current character to currPrefix string 
            if (i == 26)
                word.push_back(32);
            else if (i >= 27 && i <= 36)
                word.push_back(48 + i - 27);
            else
                word.push_back(97 + i);
                
            // recur over the rest 
            searchR(node->children[i], word, result);

            // backtracking and remove last character (ready for another prefix searching)
            word.pop_back();
        }
    }
}

/**
 *
 * This method is called to get all words in Trie.
 * 
 * It will call the searchR helper method to perform the depth first search from root.
 * 
 * @return vector<string> This will return a vector consisting of all words in Trie.
 * */
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

/**
 *
 * This method is to display the structure of Trie horizontally.
 * 
 * It will call the displayR helper method to perform the display task.
 * 
 * */
void Trie::display(){
    set<int> divider;

    displayR(root, 0, divider);
}

/**
 *
 * This method is a display helper function to display the structure of Trie horizontally.
 * 
 * @param node This parameter is to get the node
 * @param spacing This parameter is to get the current spacing
 * @param divider This parmameter is to get the divider set which indicates which spacing should cout "|"
 * 
 * */
void Trie::displayR(Trie::TrieNode* node, int spacing, set<int> divider){

    // to find the position of last child (for later removal the spacing of divider set)
    int lastChildPos = findLastChildPos(node);

    // add the current spacing to divider when there is more than one child to cout "|" on the below nodes
    bool isMoreThanOneChild = hasMoreThanOneChildAt(node, 0);
    if (isMoreThanOneChild){
        divider.insert(spacing);
    }
    
    // put a "*" sign to indicate the current node forms a word
    if (node->isEndOfWord){
        cout << "*";
    }
    cout << endl;

    // immediate return when the current has no children nodes (no point of continue traversal it anymore)
    if (isLastNode(node)){
        return;
    }
    
    // loop over all children nodes
    for (int i = 0; i < MAX_SIZE; i++){
        if (node->children[i]){

            // remove the "|" starting from current child node as this is already the last child
            if (lastChildPos == i){
                divider.erase(spacing);
            }

            // append the word
            string word;
            if (i == 26)
                word.push_back(32);
            else if (i >= 27 && i <= 36)
                word.push_back(48 + i - 27);
            else
                word.push_back(97 + i);

            bool lastChild = isLastChildAt(node, i+1);
            
            // cout "|" to indicate there is still child node below the current node
            for (int space = 0; space < spacing; space++){
                if (divider.find(space) != divider.end())
                    cout << "│";
                else
                    cout << " ";
            }
            
            // cout "├──" to indicate the is more than one child 
            if (isMoreThanOneChild && !lastChild)
                cout << "├──";
            else
                cout << "└── ";
            
            cout << word;

            // call the recursive function to continue its traversal to child nodes
            displayR(node->children[i], spacing+4, divider);

            // backtracking and remove last character (ready for another dfs)
            word.pop_back();
        }
    }
}

/**
 *
 * This method is find the last child pos from the current node
 * 
 * @param node This parameter is to get the node
 * 
 * @return int This will return the position of last child in the Trie Node
 * */
int Trie::findLastChildPos(TrieNode *node){
    for (int i = MAX_SIZE - 1; i > 0; i--)
        if (node->children[i]) return i;

    return 0;
}

/**
 *
 * This method is find whether the current node with given position is the last child of the node.
 * 
 * @param node This parameter is to get the node
 * @param start This parameter is to get the current position of the node
 * 
 * @return bool This will return whether the current node is the last child of the node
 * */
bool Trie::isLastChildAt(TrieNode *node, int start){

    for (int i = start; i < MAX_SIZE; i++){
        if (node->children[i]) return false;
    }

    return true;
}

/**
 *
 * This method is find whether the node has more than 1 child at the given position.
 * 
 * @param node This parameter is to get the node
 * @param start This parameter is to get the current position of the node
 * 
 * @return bool This will return whether the the node has more than 1 child at the given position.
 * */
bool Trie::hasMoreThanOneChildAt(TrieNode* node, int start){
    int child = 0;

    for (int i = start; i < MAX_SIZE; i++){
        if (node->children[i]) child++;

    }

    return child > 1;
}

/**
 *
 * This method is to reset the Trie and initialise the Trie root to default node again.
 * 
 * This method will call a resetR helper function to perform the reset task.
 * */
void Trie::reset(){
    resetR(root);
    root = getNode();
}

/**
 *
 * This method is a recursive helper function to preform mass deletion of all existing nodes
 * 
 * Starting from the root, it will keep recurring until it reaches the end of node
 * It will delete the node and free up the memory
 * 
 * @param node This parameter is to get the node
 * */
void Trie::resetR(TrieNode *node){

    // return when it reaches the last node
    if (isLastNode(node)){
        node = NULL;
        delete (node);
        return;
    }

    // loop over all of its children
    for (int level = 0; level < MAX_SIZE; level++){
        if (node->children[level]){
            resetR(node->children[level]);
        }
    }

    // free up the current node as well after removing all its children
    node = NULL;
    delete (node);
}