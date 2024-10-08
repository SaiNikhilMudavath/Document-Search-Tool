#include "dict.h"


Dict::Dict(){
    trie=new Trie();    
}

Dict::~Dict(){
   delete trie;   
}
TrieNode::TrieNode() {
    for (int i = 0; i < 256; i++) {
        children[i] = NULL;
    }
    count = 0;
    end_of_word=false;
}
TrieNode::~TrieNode(){
    for (int i = 0; i < 256; i++) {
            delete children[i]; 
    }
}
Trie:: Trie() {
    root = new TrieNode();
}
Trie::~Trie(){
    delete root;
}

bool isSeparator(char c) {
   static  const string separators = ".,-:!\"'()?—[]“”‘’˙;@ ";
    return separators.find(c) != string::npos;
}
string to_lower( string& result) {
    for (char& c : result) {
        c= towlower(c);
    }
    return result;
}
vector<string> split_sentence(const string& sentence) {
    vector<string> words;
    string word;
    for (char c : sentence) {
        if (isSeparator(c)) {
            if (!word.empty()) {
                words.push_back(to_lower(word));
            }
            word.clear();
        } else  {
            word += c;
        }
    }

    if (!word.empty()) {
        words.push_back(to_lower(word)); 
    }

    return words;
}


void traverseTrie(TrieNode* node, string word, ofstream& outputFile) {
    if (node->end_of_word) {
        outputFile << word << ", " << node->count << endl;
    }
    for (int i = 0; i < 256; i++) {
        if (node->children[i] != NULL) {
            traverseTrie(node->children[i], word + static_cast<char>(i), outputFile);
        }
    }
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){

    vector<string> words = split_sentence(sentence);
// traversing in words vector
    TrieNode* current =trie->root;
    int size;
    for (const string& word : words) {
        size =word.length();
        for (int i=0;i<size; i++) {
    // iterating over word
            unsigned int index = word[i];
            if(i==size-1){
                if (current->children[index] == NULL) {
                    current->children[index] = new TrieNode();
                }
                current->children[index]->end_of_word =true;
                current->children[index]->count=current->children[index]->count+1;
            }
            else{
                if (current->children[index] == NULL) {
                    current->children[index] = new TrieNode();
                }
                current = current->children[index];
            }
            
        }
        current=trie->root;
    } 
    return;
}

int Dict::get_word_count(string word){
    TrieNode* current = trie->root;
    for (char c : word) {
        unsigned int index = c;
        if (current->children[index] == NULL) {
            return 0; 
        }
        current = current->children[index];
    }
    return current->count; 

}

void Dict::dump_dictionary(string filename) {
    ofstream outputFile(filename);
    traverseTrie(trie->root, "", outputFile);
    outputFile.close(); 
}