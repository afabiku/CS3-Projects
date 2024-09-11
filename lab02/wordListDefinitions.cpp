#include "wordListMain.hpp"


WordList::WordList(const WordList&input){
    size_ = input.size_;
    wordArray_ = new WordOccurrence[size_];
    for(int i = 0; i < size_; ++i){
        wordArray_[i] = input.wordArray_[i];
    }
}


WordList& WordList::operator=(const WordList&input){
    if(this != &input){
        size_ = input.size_;
        delete[] wordArray_;
        wordArray_ = new WordOccurrence[size_];
        for(int i = 0; i < size_; ++i){
            wordArray_[i] = input.wordArray_[i];
        }
    }
    return *this;
}

void WordList::print(){
    int value = 0;
    for(int i = 0; i < size_; ++i){
        wordArray_[i].print();
    }
}

int WordList::locateWord(const string&input) const{
    for(int i = 0; i < size_; ++i){
        bool result = wordArray_[i].matchWord(input);
        if(result) return i;       
    }
    return -1;
}

void WordList::addWord(const string & input){
    int index = locateWord(input);
    if(index == -1){
        int prevSize = size_;
        int newSize = size_ + 1;
        WordOccurrence * temp = new WordOccurrence[newSize];
        for(int i = 0; i < prevSize; ++i){
            temp[i] = wordArray_[i];
        }
        size_ = newSize;
        temp[size_- 1] = WordOccurrence(input,1);
        delete [] wordArray_;
        wordArray_ = temp;
    }else{
        wordArray_[index].increment();
    }
}

bool equal(const WordList&lhs, const WordList&rhs){
    if(lhs.size_ != rhs.size_){return false;}
    for(int i = 0; i < lhs.size_; ++i){
        bool result = lhs.wordArray_[i].matchWord(rhs.wordArray_[i].getWord());
        return result;        
    }
    return true;
}

void WordOccurrence::print(){
    std::cout << word_ << std::endl;
}

string WordOccurrence::getWord() const {
    return word_;
}

int WordOccurrence::getNum() const {
    return num_;
}

bool WordOccurrence::matchWord(const string&input){
    if(word_.length() != input.length()){return false;}
    for(int i = 0; i < input.length(); ++i){
        if(input[i] != word_[i])
            return false;
    }
    return true;
}