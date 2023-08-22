#include "bits/stdc++.h"

using namespace std;

class TrieNode {
    vector<int> next;
    bool isEndOfWord;
public:
    TrieNode() {
        next = vector<int> (26,-1);
        isEndOfWord = false;
    }

    int getNext(int ind) {
        return next[ind];
    }
    bool getIsEndOfWord() {
        return this->isEndOfWord;
    }

    void setNext(int ind, int val) {
        next[ind] = val;
    }
    void setIsEndOfWord(bool b) {
        this->isEndOfWord = b;
    }
};

class Trie {
    vector<TrieNode> trie;
public:
    Trie() {
        trie = vector<TrieNode> (1);
    }

    void insert(string word) {
        int v=0;

        for(char c : word) {
            int x = c-'a';
            if(trie[v].getNext(x) == -1) {
                trie[v].setNext(x,trie.size());
                trie.emplace_back();
            }
            v = trie[v].getNext(x);
        }
        trie[v].setIsEndOfWord(true);
    }

    bool search(string word) {
        int v=0;

        for(char c : word) {
            int x = c-'a';
            if(trie[v].getNext(x) == -1) {
                return false;
            }
            v = trie[v].getNext(x);
        }
        return trie[v].getIsEndOfWord();
    }

    bool startsWith(string prefix) {
        int v=0;
        for(char c : prefix) {
            int x = c-'a';
            if(trie[v].getNext(x) == -1) {
                return false;
            }
            v = trie[v].getNext(x);
        }
        return true;
    }

};


int main() {
    int option;
    string word;
    Trie trie;
    bool ans;

    while(1) {
        cout <<"Choose one of the below options\n";
        cout <<"Option-1 : Insert the string into the trie\n";
        cout <<"Option-2 : Search for the String presence in the trie\n";
        cout <<"Option-3 : Check  for the Prefix String presence\n";
        cin >> option;
        cout <<"Enter the word\n";
        cin >> word;
        switch (option) {
            case 1:
                trie.insert(word);
                cout <<"Inserted the word successfully\n";
                break;
            case 2:
                ans = trie.search(word);
                if(ans == true) {
                    cout <<"The Word provided is present in the Trie\n";
                } else {
                    cout <<"Word is not present\n";
                }
                break;
            case 3:
                ans = trie.startsWith(word);
                if(ans == true) {
                    cout <<"There are some word which starts with the given word\n";
                } else {
                    cout <<"There are no words which starts with the given word\n";
                }
                break;
            default:
                cout <<"Invalid options Selected\n";
        }
    }
    return 0;
}
