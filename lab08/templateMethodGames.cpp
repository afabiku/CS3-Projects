#include "templateMethodGames.hpp"

int main() {
    srand(time(nullptr));
    Dice* mode = new Dice;
    int computer = 0;
    int player = 1;

    char input = 'y';
    bool PlayerReroll = true;
    bool AIReroll = true;

    mode->initializeGame(); 

    // WHile round less than 3 and either players want to reroll
    while((mode->getRound() <= 3)){
        if(!PlayerReroll && !AIReroll){break;}
        std::cout << "Round " << mode->getRound() <<": ";

        // AI Turn
        mode->AIReset();
        mode->makeMove(computer);
        AIReroll = (rand()%2 == 0)? true : false;
        if(AIReroll){
            mode->AIReset(); 
            mode->makeMove(computer);
        }
        mode->outPut(computer,AIReroll);

        // Player's Turn
        if(PlayerReroll){
            mode->makeMove(player);
        }
        mode->outPut(player,PlayerReroll);   

        if(mode->getRound() <= 3){
            std::cout << "Roll again? [y/n] ";
            std::cin >> input;
            PlayerReroll = (input == 'y')? true:false;
            if(PlayerReroll){mode->PlayerReset();}
        }
    }
    mode->printWinner();
}