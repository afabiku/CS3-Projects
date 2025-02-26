#include "History.hpp"


int main(){

    std::vector<std::string> vec;
    Document * obj = new Document(vec);
    DocumentHistory * Doc = new DocumentHistory(obj);
    Momento * checkpoint = nullptr;


    while(true){

        char input;
        std::cout << "Enter option (i)nsert line (e)rase line (u)undo last command (c)heckpoint roll(b)ack (h)history (r)edo command: ";
        std::cin >> input;

        int line;
        std::string str;
        switch(input){
            case 'i':
                std::cout << "Line number: ";
                std::cin >> line;

                std::cout << "Input text:";
                std::getline(std::cin >> std::ws, str); // `std::ws` discards leading whitespace

                Doc->insert(line,str);
                break;
            case 'e':
                std::cout << "Line number: ";
                std::cin >> line;

                Doc->remove(line);
                break;
            case 'u':
                Doc->undo();
                break;
            case 'c':
                checkpoint = Doc->checkpoint();
                break;
            case 'b':
                if(checkpoint != nullptr){
                    Doc->rollback(checkpoint);
                    Doc->getHistory().clear();
                }else{
                    std::cout << "No checkpoint saved" << std::endl;
                }
                break;

            case 'h':
                for(int i = 0; i < Doc->getHistory().size();++i){
                    std::cout << i+1 << " " << Doc->getHistory()[i]->operation() << " " << Doc->getHistory()[i]->getString() << " at Line " << Doc->getHistory()[i]->getLine() << std::endl;
                }
                std::cout << std::endl;
                break;
            case 'r': {
                int historyNumber;
                std::cout << "History number: ";
                std::cin >> historyNumber;
                if (historyNumber <= 0 || historyNumber > Doc->getHistory().size()) {
                    std::cout << "Invalid history number!" << std::endl;
                    break;
                }
                Doc->redo(historyNumber);

                break;
            }

        }
        Doc->show();
        
    }
}