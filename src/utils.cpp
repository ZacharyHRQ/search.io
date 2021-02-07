/**
 *
 * Utils file containing KMP and Navie searching 
 *
 * @author Zachary
 * @since 02-06-2021
 */

#include <bits/stdc++.h>
using namespace std;
 

/**
*
* This method is used for preprocessing a pattern sting before searching for.  
* This involves the construction of a longest proper suffix array corressponding to the pattern of the same size.
*   
* @param string pat : pattern , int M : length of the pattern  , int *lps : pointer to a lps array
*
* 
* */
void computeLPSArray(string pat, int M, int *lps){
    int len = 0;
    lps[0] = 0; 
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else 
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

/**
*
* This method is used implement KMP searching , it uses helper function computeLPSArray to generate arrays to search from.
* KMP searching uses a the lps array together with a sliding window method search for patterns with a string 
*
* @param string pat : pattern to search for , string txt : word to search from
*
* @return int 
* 
* */
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

        else if (i < N && pat[j] != txt[i])
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
* @param vector<string> w : the words to search from , string pat : pattern to search for
*
* @return vector<string> This returns the results from KMP search
* */
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

/**
*
* This method is used return the result from navie search , checking if the pattern existing in the word
* 
* @param vector<string> w : the words to search from , string pat : pattern to search for
*
* @return vector<string> This returns the results from navieSearch
* */
vector<string> navieSearch(vector<string> w , string pat){
    vector<string> results;

    auto start = chrono::high_resolution_clock::now();

    for (auto str : w)
    {
        if(str.find(pat) != string::npos)
            results.push_back(str);
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cerr << "\033[32m\n"
         << results.size() << " results in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";

    return results; 
}