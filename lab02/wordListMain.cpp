#include "wordListMain.hpp"


int main(int argc, char *argv[]){
    if(argc != 2){
        return 0;
    }

    std::ifstream file(argv[1]);
    // std::ofstream out(argv[2]);

    std::string text;
    WordList Object;

    while(!file.eof() && std::getline(file,text)){
        std::string word;
        for(int i = 0; i < text.length();++i){
            if(isalnum(text[i]) || isalpha(text[i])){
                word += text[i];
            }
            if(ispunct(text[i]) || isspace(text[i]) || (i == text.length()-1)){
                if(word != ""){Object.addWord(word);}
                word = "";
            }
        }
    }

    WordOccurrence* wordList = Object.getWords();
    for(int i = 1; i < Object.getSize(); ++i) {
        WordOccurrence key = wordList[i];
        int previous = i - 1;
        while(previous >= 0 && wordList[previous].getNum() > key.getNum() || (wordList[previous].getNum() == key.getNum() &&  wordList[previous].getWord() > key.getWord())) {
            wordList[previous + 1] = wordList[previous];
            previous = previous - 1;
        }
        wordList[previous + 1] = key;
    }

    for(int i = 0;i <Object.getSize();++i){
        cout << wordList[i].getWord() << " " << wordList[i].getNum();
        if(i != Object.getSize()-1){
            cout << std::endl;
        }
    }
}

