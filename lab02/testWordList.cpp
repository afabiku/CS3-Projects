#include "wordListMain.hpp"

void testfunc(WordList, WordList&); // function to test pass-by-value for WordList class

int main(int argc, char *argv[]){
    // std::ifstream file(argv[1]);
    // if(argc != 1){
    //     return 0;
    // }

    // std::string text;
    // while(std::getline(file,text)){
    //     std::cout << text << std::endl;
    // }

    WordList w;

   // testing regular member functions
   w.addWord("two");
   w.addWord("one"); 
   w.addWord("one"); // adding duplicate
   w.addWord("three");

   // check the size and contents of w
   assert(w.getSize() == 3);
   WordOccurrence* words = w.getWords();
   for (int i = 0; i < 3; i++) {
      if (words[i].getWord() == "one") {
        assert(words[i].getNum() == 2);
      } else if (words[i].getWord() == "two") {
        assert(words[i].getNum() == 1);
      } else if (words[i].getWord() == "three") {
        assert(words[i].getNum() == 1);
      }
   }

    cout << "sorted word list is:" << endl;
    w.print(); // printed list should be in decreasing order
    cout << endl;

    WordList w2, w3;

    w3=w2=w; // testing stacked overloaded assignment
    w3=w3; // testing protection against self-assingment

    assert(equal(w,w2));
    assert(equal(w,w3));

    testfunc(w, w2); // testing copy constructor

    cout << "word list after copy and destroy:" << endl;
    w.print(); // if destructor is implemented correctly
                // this should print properly after testfunc completes
   
    assert(equal(w,w2));
    assert(equal(w,w3));

}

// tests pass-by-value for object of class varArray
void testfunc(WordList myList, WordList& myList2){ // copy constructor is invoked on "myList"
   
   assert(equal(myList,myList2));
   
   cout << "word list in testfunc: " << endl;
   myList.print();
   cout << endl;
} // destructor is invoked when "myList" goes out of scope