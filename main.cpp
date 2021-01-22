#include <iostream>
#include <fstream>
#include "Trie.h"
#include "Dictionary.h"
#include <string>

using namespace std;

void displayMenu();
void initTrie(Trie* trie);
void initDict(Dictionary& d);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Trie *trie = new Trie;
    initTrie(trie);

    Dictionary d;
    initDict(d);

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
            cout << word.length() << endl;
            trie->insert(word);
        }

        else if (option == 3){
            cin.ignore();
	        cout << "[3] Search                      \n";
            cout << "Enter a keyword for searching: ";
            string word;
            getline(cin, word);
            cout << word.length() << endl;
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
    trie->insert("hello worldz");
    trie->insert("hiichan");
    trie->insert("chaewon hii");
    trie->insert("chaewon angel");
    trie->insert("chaewon pretty");
    trie->insert("chaewon fairy");
    trie->insert("chaewon is my wife");
    trie->insert("apple");
    trie->insert("book");
    trie->insert("cup");
    trie->insert("red");
    trie->insert("wet");
    trie->insert("dog");
    trie->insert("big");
    trie->insert("fast");
    trie->insert("lunch");
    trie->insert("five");
    
}

void initDict(Dictionary& d){
    string data,word,define;
    ifstream file("data.txt");
    if(file.is_open()){
        while(getline(file,data)){
            int pos = data.find(":");
            word = data.substr(0,pos);
            define = data.substr(pos+1);
            d.add(word,define);
        }
        file.close();
    }
}
