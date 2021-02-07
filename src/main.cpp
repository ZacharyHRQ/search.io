#include <iostream>
#include <fstream>
#include "Trie.cpp"
#include "Dictionary.cpp"
#include <string>
#include <vector>

using namespace std;

void displayMenu();
void initTrie(Trie *trie);
void initDict(Dictionary<string,string> &d);
string convertStringToLower(string s);
vector<string> getWordsFromFile();
vector<string> search(vector<string> w,string pat);
vector<string> navieSearch(vector<string> w,string pat);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Trie *trie = new Trie;
    initTrie(trie);

    Dictionary<string,string> d;
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
            cin.ignore();
            cout << "[6] Universal search             \n";
            cout << "Enter a keyword for universal searching: ";
            string word;
            getline(cin, word);

            vector<string> words = getWordsFromFile();
            vector<string> result = search(words,word);
            if(result.size() == 0){ 
               cout << "No results were found \n"; 
            }else{
                for(string w : result)
                    cout << w << endl;
            }
            
            
        }

        else if (option == 7){
            cin.ignore();
            cout << "[7] Navie search        \n";
            cout << "Enter a keyword for Navie Search: ";
            string word;
            getline(cin, word);

            vector<string> words = getWordsFromFile();
            vector<string> result = navieSearch(words,word);
            if(result.size() == 0){ 
               cout << "No results were found \n"; 
            }else{
                for(string w : result)
                    cout << w << endl;
            }
            
        }

        else if (option == 8){
        	cout << "[8] Reset Trie                  \n";
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
    cout << "[6] Universal Search            \n";
    cout << "[7] Navie Search                \n";
    cout << "[8] Reset Trie                  \n";
    cout << "[0] Exit                        \n";
    cout << "--------------------------------\n";
    cout << "Enter option : ";
}

void initTrie(Trie *trie)
{
    vector<string> words = getWordsFromFile();
    for(string word : words){ 
        trie->insert(convertStringToLower(word));
    }
}

// reading from data file , loading into dictionary
void initDict(Dictionary<string,string> &d)
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
            d.add(convertStringToLower(word), define);
        }
        file.close();
    }
}

string convertStringToLower(string s){
    string res;

    for (char c: s){
        res.push_back(tolower(c));
    }
    return res;
}

vector<string> getWordsFromFile(){
   string data, word;
   vector<string> words;
   ifstream file("../data/data.txt");
   if (file.is_open())
   {
        while (getline(file, data))
        {
            int pos = data.find(":");
            word = data.substr(0, pos);
            if(word.size()) 
                words.push_back(word);
        }
        file.close();
   } 
   return words;
}

// Fills lps[] for given patttern pat[0..M-1]
void computeLPSArray(string pat, int M, int *lps){
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else 
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Prints occurrences of txt[] in pat[]
int KMPSearch(string pat, string txt)
{
    int M = pat.size();
    int N = txt.size();

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            return i - j;
            j = lps[j - 1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i])
        {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return -1;
}

// KMP algorithm
vector<string> search(vector<string> w,string pat){
    vector<string> results;

    auto start = chrono::high_resolution_clock::now();

    for (auto str : w)
    {
        if (KMPSearch(pat, str) != -1)
            results.push_back(str);
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cerr << "\033[32m\n"
         << results.size() << " results in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";

    return results;
}

// navie searching checking if a word matches 
vector<string> navieSearch(vector<string> w , string pat){
    vector<string> results;

    auto start = chrono::high_resolution_clock::now();

    for (auto str : w)
    {
        if(str == pat)
            results.push_back(str);
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cerr << "\033[32m\n"
         << results.size() << " results in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";

    return results; 
}
