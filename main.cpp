#include <iostream>
#include "Trie.h"
using namespace std;

void displayMenu();
void initTrie(Trie* trie);

int main(){
    Trie *trie = new Trie;
    initTrie(trie);

    int option = -1;

    while (option != 0){
        displayMenu();
        cin >> option; cout << endl;

        if (option == 1){
	        cout << "[1] Insert a new keyword        \n";
            cout << "Enter a new keyword: ";
            string word;
            cin >> word;
            trie->insert(word);
        }

        else if (option == 3){
	        cout << "[3] Search                      \n";
            cout << "Enter a keyword for searching: ";
            string word;
            cin >> word;
            trie->search(word);
        }
    }

    return 0;
}

void displayMenu()
{
	cout << endl;
	cout << "Search.io \n";
	cout << "--------------------------------\n";
	cout << "[1] Insert a new keyword        \n";
	cout << "[2] Delete a new keyword        \n";
	cout << "[3] Search                      \n";
	cout << "[4] Display Trie                \n";
	cout << "[5] Reset Trie                  \n";
	cout << "[0] Exit                        \n";
	cout << "--------------------------------\n";
	cout << "Enter option : ";
}

void initTrie(Trie* trie){
    trie->insert("hi");
    trie->insert("hiichan");
    trie->insert("chaewon");
    trie->insert("chaeyeon");
    trie->insert("chaewonangel");
    trie->insert("chaewonismywife");
}

