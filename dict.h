// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class TrieNode
{
public:
    TrieNode *children[256];
    int count; // Count of occurrences of the word
    bool end_of_word;
    TrieNode();
    ~TrieNode();
};
class Trie
{
public:
    TrieNode *root;
    Trie();
    ~Trie();
};
class Dict
{

public:
    // You can add attributes/helper functions here
    Trie *trie;
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};

