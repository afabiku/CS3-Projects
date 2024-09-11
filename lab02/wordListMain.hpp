#ifndef COUNT_HPP
#define COUNT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cctype>


using std::cout; using std::endl; using std::string;

class WordOccurrence {
public:
    WordOccurrence(const string& word="", int num=0): word_(word), num_(num) {}; // done
    bool matchWord(const string &); // returns true if word matches stored done
    void increment(){++num_;} // increments number of occurrences done
    string getWord() const;  // done
    int getNum() const; // done
    void print(); // done

private:
    string word_;
    int num_;
};



class WordList{
public:
    // add copy constructor, destructor, overloaded assignment done
    WordList(): size_(0),wordArray_(0) {};
    WordList(const WordList&);
    ~WordList(){ delete [] wordArray_;}
    WordList& operator=(const WordList&);
    
    // checks if word in array
    int locateWord(const string&) const;
    // implement comparison as friend
    friend bool equal(const WordList&, const WordList&);

    void addWord(const string &);
    void print(); // done

    // Only use for testing purposes
    WordOccurrence * getWords() const {return wordArray_;}; // done
    int getSize() const {return size_;}; // done
private:
    WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
                                // may or may not be sorted
    int size_;
};

#endif
