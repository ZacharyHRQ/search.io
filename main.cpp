#include <iostream>
#include "Trie.h"
#include <string>

using namespace std;

void displayMenu();
void initTrie(Trie* trie);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Trie *trie = new Trie;
    initTrie(trie);

    int option = -1;

    while (option != 0){
        displayMenu();
        cin >> option; cout << endl;

        if (option == 1){
            cin.ignore();
	        cout << "[1] Insert a new keyword        \n";
            cout << "Enter a new keyword: ";
            string word;
            getline(cin, word);
            trie->insert(word);
        }

        else if (option == 2){
            cin.ignore();
            cout << "[2] Delete a new keyword        \n";
            cout << "Enter a keyword for deleting: ";
            string word;
            getline(cin, word);
            trie->remove(word);
        }

        else if (option == 3){
            cin.ignore();
	        cout << "[3] Search                      \n";
            cout << "Enter a keyword for searching: ";
            string word;
            getline(cin, word);
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
    trie->insert("apple iphone ten");
    trie->insert("apple m one");
    trie->insert("apple mac");
    trie->insert("apple m one chip");
    trie->insert("apple watch");
    trie->insert("apple imac");
    trie->insert("apple stocks");
}

