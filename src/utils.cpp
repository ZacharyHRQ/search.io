/**
 *
 * Utils file containing KMP and Navie searching 
 *
 * @author Zachary S10185319J
 * @since 02-06-2021
 */

#include <bits/stdc++.h>
using namespace std;
 

/**
*
* This method is used for preprocessing a pattern sting before searching for.  
* This involves the construction of a longest proper suffix array corressponding to the pattern of the same size.
* The lps will consist of the index of the char that was last seen 
*
* @param string pat : pattern , int patSize : length of the pattern  , int *lps : pointer to a lps array
*
* 
* */
void computeLPSArray(string pattern, int patSize, int *lps){
    int len = 0;
    lps[0] = 0; 
    int index = 1;

    // loop from 1 to size of pattern -1 
    while (index < patSize)
    {
        if (pattern[index] == pattern[len])
        {
            len++;
            lps[index] = len;
            index++;
        }
        else 
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else 
            {
                lps[index] = 0;
                index++;
            }
        }
    }
}

/**
*
* This method is used implement KMP searching , it uses helper function computeLPSArray to generate arrays to search from.
* KMP searching uses a the lps array for patterns with a string , using a two pointer techniques. Checking for mismatches.
* 
*
* @param string pattern : pattern to search for , string txt : word to search from
*
* @return int this returns the index of the found pattern
* 
* */
int KMPSearch(string pattern , string txt)
{
    int patSize = pattern.size();
    int wordSize = txt.size();

    // create lps[] that will hold the longest prefix suffix values for pattern
    int lps[patSize];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pattern, patSize, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < wordSize)
    {
        if (pattern[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == patSize)
        {
            return i - j;
            j = lps[j - 1];
        }

        else if (i < wordSize && pattern[j] != txt[i])
        {
            
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return -1;
}

/**
*
* This method is used return the result from KMP search function
* 
* @param vector<string> words : the words to search from , string pattern : pattern to search for
*
* @return vector<string> This returns the results from KMP search
* */
vector<string> search(vector<string> words ,string pattern){
    vector<string> results;

    auto start = chrono::high_resolution_clock::now();

    for (auto str : words)
    {
        // KMP search 
        if (KMPSearch(pattern, str) != -1)
            results.push_back(str);
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cerr << "\033[32m\n"
         << results.size() << " results in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";

    return results;
}

/**
*
* This method is used return the result from naive search , checking if the pattern existing in the word by constantly checking from past substrings
* 
* @param vector<string> words : the words to search from , string pattern : pattern to search for
*
* @return vector<string> This returns the results from naiveSearch
* */
vector<string> naiveSearch(vector<string> words , string pattern ){
    vector<string> results;

    auto start = chrono::high_resolution_clock::now();

    for (auto str : words)
    {
        int patSize = pattern.length(); 
        int wordSize = str.length(); 
    
        // looping one pattern by one pattern  
        for (int i = 0; i <= wordSize - patSize; i++) { 
            int j; // making accessable within the loop
            // at current index i, check for pattern match 
            for (j = 0; j < patSize; j++) 
                if (str[i + j] != pattern[j]) 
                    break; 
    
            if (j == patSize) // if pattern[0...M-1] = str[i, i+1, ...i+M-1] 
                results.push_back(str);
        } 
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cerr << "\033[32m\n"
         << results.size() << " results in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";

    return results; 
}