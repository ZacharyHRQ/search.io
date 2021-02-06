#include <iostream>
#include <fstream>
#include "Trie.cpp"
#include "Dictionary.cpp"
#include <string>

using namespace std;

void displayMenu();
void initTrie(Trie *trie);
void initDict(Dictionary &d);
string convertStringToLower(string s);

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
            trie->insert(convertStringToLower(word));
        }

        else if (option == 2)
        {
            cin.ignore();
            cout << "[2] Delete a keyword           \n";
            cout << "Enter a keyword for deleting: ";
            string word;
            getline(cin, word);
            trie->remove(convertStringToLower(word));
        }

        else if (option == 3)
        {
            cin.ignore();
            cout << "[3] Exact Search                \n";
            cout << "Enter a keyword for exact searching: ";
            string word;
            getline(cin, word);
            bool isFound = trie->searchExact(convertStringToLower(word));

            if (isFound){
                string definition = d.get(word);
                if (definition.length() > 0)
                    cout << "The definition of " << word << " is " << definition << endl;
                else
                    cout << "Oops. The definition is not available in the dictionary at the moment.\n";
            } else{
                cout << "The word is not found in the Trie.\n";
            }

        }

        else if (option == 4)
        {
            cin.ignore();
            cout << "[4] Prefix Search               \n";
            cout << "Enter a keyword for prefix searching: ";
            string word;
            getline(cin, word);

            vector<string> result = trie->searchPrefix(convertStringToLower(word));
            if (result.size() == 0){
                cout << "No string found with this prefix\n";
            } else {
                for (string w: result)
                    cout << w << endl;
            }
        }

        else if (option == 5){
            cout << "[5] Display Trie                \n";

            for (string w: trie->getAllWords()){
                cout << w << endl;
            }
        }

        else if (option == 6){
            cout << "[6] Universal search             \n";

            // search();
        }

        else if (option == 7){
        	cout << "[7] Reset Trie                  \n";
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
    cout << "[3] Exact Search                \n";
    cout << "[4] Prefix Search               \n";
    cout << "[5] Display Trie                \n";
    cout << "[6] Reset Trie                  \n";
    cout << "[0] Exit                        \n";
    cout << "--------------------------------\n";
    cout << "Enter option : ";
}

void initTrie(Trie *trie)
{
    trie->insert("apple m1");
    trie->insert("apple iphone 10");
    trie->insert("apple iphone 12");
    trie->insert("apple macbook pro 2019");
    trie->insert("apple macbook pro 2020");
    trie->insert("apple mac");
    trie->insert("apple m1 chip");
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
    trie->insert("5");
}

// reading from data file , loading into dictionary
void initDict(Dictionary &d)
{
    string data, word, define;
    ifstream file("../data/data.txt");
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

string convertStringToLower(string s){
    string res;

    for (char c: s){
        res.push_back(tolower(c));
    }
    cout << res << endl;
    return res;
}

void search(){ 

}

vector<string> 