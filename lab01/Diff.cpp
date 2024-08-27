// reads command line arguments and prints them one per line
// Mikhail Nesterenko
// 1/16/2014

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

int main(int argc, char* argv[]){
    const int argRequired = 3;
    if(argc != argRequired){
        std::cout << "Invalid input" << std::endl;
        return 0;
    }

    std::ifstream fileOne(argv[1]);
    std::ifstream fileTwo(argv[2]);

    std::string textOne;
    std::string textTwo;

    int lineNumber = 1;
    while(!fileOne.eof() || !fileTwo.eof()){
        if(fileOne.eof()){
            textOne = "";
        }else{
            std::getline(fileOne,textOne);
        }
        
        if(fileTwo.eof()){
            textTwo = "";
        }else{
            std::getline(fileTwo,textTwo);
        }
        
        if(textOne != textTwo){

            int index = 0;
            int textLength = textOne.length() > textTwo.length() ? textOne.length() : textTwo.length();

            for(int i = 0; i < textLength; ++i){
                int space = strlen(argv[1])+3;
                int lineNumberLength = std::to_string(lineNumber).length()+1;
                

                if(textOne[index] != textTwo[index]){
                    std::string spaceString;
                    spaceString.assign(space + lineNumberLength + index,' ');
                    std::cout << argv[1]<<":" << ' ' << lineNumber << ":"<< " " << textOne << std::endl;
                    std::cout << argv[2]<<":" << ' ' << lineNumber << ":"<< ' ' <<textTwo << std::endl;
                    std::cout << spaceString << "^"; 
                    if(!fileOne.eof() || !fileTwo.eof()){
                        std::cout << std::endl;
                    }
                    break;
                }                
                index+=1;
            }
        }
        lineNumber+=1;
    }
}