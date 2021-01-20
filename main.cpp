#include <iostream>
#include "Trie.h"
using namespace std;

int main(){
    Trie *trie = new Trie;

    trie->insert("hi");
    trie->insert("hiichan");
    trie->insert("chaewon");
    trie->insert("chaeyeon");
    trie->insert("chaewonangel");

    trie->search("chae");

    return 0;
}


