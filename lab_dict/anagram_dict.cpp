/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    string word;
    ifstream wordsFile(filename);
    
    if (wordsFile.is_open()) {
      while (getline(wordsFile, word)) {
        string st = word;
        std::sort(st.begin(), st.end());
        dict[st].push_back(word);
      }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (size_t i = 0; i < words.size(); i++){
    	string str = words[i];
    	std::sort(str.begin(), str.end());
    	dict[str].push_back(words[i]);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    if (word.size() < 3) 
        return vector<string>();
    string curr(word);
    std::sort(curr.begin(), curr.end());
    if (dict.count(curr) == false) 
        return vector<string>();
    return dict.at(curr);
    //return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    std::vector<std::vector<string>> a;
    for (std::pair<string, std::vector<std::string>> each : dict){
        vector<string> anagrams = each.second;
        if (anagrams.size() <= 1) 
            continue;
        a.push_back(anagrams);
    }
    return a;
}
