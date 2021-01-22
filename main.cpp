#include <iostream>
#include <fstream>
#include "Trie.h"
#include "Dictionary.h"
#include <string>

using namespace std;

void displayMenu();
void initTrie(Trie *trie);
void initDict(Dictionary &d);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Trie *trie = new Trie;
    initTrie(trie);

    Dictionary d;
    initDict(d);

    int option = -1;

    while (option != 0)
    {
        displayMenu();
        cin >> option;
        cout << endl;

        if (option == 1)
        {
            cin.ignore();
            cout << "[1] Insert a new keyword        \n";
            cout << "Enter a new keyword: ";
            string word;
            getline(cin, word);
            trie->insert(word);
        }

        else if (option == 2)
        {
            cin.ignore();
            cout << "[2] Delete a keyword           \n";
            cout << "Enter a keyword for deleting: ";
            string word;
            getline(cin, word);
            trie->remove(word);
        }

        else if (option == 3)
        {
            cin.ignore();
            cout << "[3] Search                      \n";
            cout << "Enter a keyword for searching: ";
            string word;
            getline(cin, word);
            trie->search(word);

            // when both trie and dict access word , it gives segmentation fault , hmmm 
            //trie->search(word);
            //cout << d.get(word) << endl;

            //if(trie->isWordExist(word)) cout << d.get(word) << endl;
        }

        else if (option == 4)
        {
            cin.ignore();
            cout << "[4] Auto-Suggestions            \n";
            cout << "Enter a keyword for auto-suggestions: ";
            string word;
            getline(cin, word);
            trie->printAutoSuggestions(word);
        }

        else if (option == 5)
        {
            cin.ignore();
            cout << "[5] Display Trie                \n";
            trie->display();
        }

        else if (option == 6)
        {
            cin.clear();
            cout << "[6] Reset Trie                  \n";
            trie->reset();
            cout << "The trie has been reset successfully. \n";
        }
    }

    cout << "[0] Exit                        \n";
    cout << "Exiting Search.io .......       \n";

    return 0;
}

void displayMenu()
{
    cout << endl;
    cout << "Search.io \n";
    cout << "--------------------------------\n";
    cout << "[1] Insert a new keyword        \n";
    cout << "[2] Delete a keyword            \n";
    cout << "[3] Search                      \n";
    cout << "[4] Auto-Suggestions            \n";
    cout << "[5] Display Trie                \n";
    cout << "[6] Reset Trie                  \n";
    cout << "[0] Exit                        \n";
    cout << "--------------------------------\n";
    cout << "Enter option : ";
}

void initTrie(Trie *trie)
{
    trie->insert("apple");
    trie->insert("apple iphone ten");
    trie->insert("apple m one");
    trie->insert("apple mac");
    trie->insert("apple m one chip");
    trie->insert("apple watch");
    trie->insert("apple imac");
    trie->insert("apple stocks");
    trie->insert("hello worldz");
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

void initDict(Dictionary &d)
{
    string data, word, define;
    ifstream file("data.txt");
    if (file.is_open())
    {
        while (getline(file, data))
        {
            int pos = data.find(":");
            word = data.substr(0, pos);
            define = data.substr(pos + 1);
            d.add(word, define);
        }
        file.close();
    }
}
