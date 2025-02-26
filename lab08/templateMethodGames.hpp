// Games, Template Method example
// Mikhail Nesterenko
// 2/4/2014

#ifndef templateMethodGames_HPP
#define templateMethodGames_HPP

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>


using std::cout; using std::endl;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game{
public:
   Game():playersCount_(0), movesCount_(0), playerWon_(noWinner){}

   // template method
   void playGame(const int playersCount = 0) {
      playersCount_ = playersCount;
      movesCount_=0;

      initializeGame();

      for(int i=0; !endOfGame(); i = (i+1) % playersCount_ ){
	 makeMove(i);
	 if (i==playersCount_-1) 
	    ++movesCount_; 
      }
      printWinner();
   }

   virtual ~Game(){}

protected:
   // primitive operations
   virtual void initializeGame() = 0;
   virtual void makeMove(int player) = 0;
   virtual void printWinner() = 0;
   virtual bool endOfGame() { return playerWon_ != noWinner;} // this is a hook
                   // returns true if winner is decided
   static const int noWinner=-1;

   int playersCount_;
   int movesCount_;
   int playerWon_;
};

class Dice : public Game{
public:
   void initializeGame(){ 
      playersCount_ = 2;
      movesCount_ = 1;
      playerWon_ = -1;
   }

   void printWinner(){
      if(computerSum >= PlayerSum){std::cout << "You lose!" << std::endl;} else{std::cout << "You win!" << std::endl;}
   }

   int getRound(){
      return movesCount_;
   }

   void AIReset(){
        computerNumbers_.clear();
    }

   void PlayerReset(){
      playerNumbers_.clear();
    }

    void outPut(int i, bool reRolled){
        switch (i) {
            case 0: {
                std::cout << "Computer rolled: ";
                std::for_each(computerNumbers_.begin(), computerNumbers_.end(), [](int n) {
                    std::cout << n << " ";
                });
                
                computerSum = std::accumulate(computerNumbers_.begin(), computerNumbers_.end(), 0);
                std::cout << ", Computer's score: " << computerSum << std::endl;
                break;
            }
            case 1: {
                std::cout << "You rolled: ";
                if(reRolled){
                  std::for_each(playerNumbers_.begin(), playerNumbers_.end(), [](int n) {
                     std::cout << n << " ";
                  });
                }else{
                  std::cout << "passed,";
                }
                PlayerSum = std::accumulate(playerNumbers_.begin(), playerNumbers_.end(), 0);
                std::cout << ", your score = " << PlayerSum << std::endl;
               movesCount_ += 1;
                break;
            }
        }
    }

   void makeMove(int player){
      int rollAmount = 5;

      switch (player){
         case 0:
            for(int i = 0; i < rollAmount; ++i){int randomNumber = (rand()%6)+1; computerNumbers_.push_back(randomNumber);}
            break;
         case 1:
            for(int i = 0; i < rollAmount; ++i){int randomNumber = (rand()%6)+1; playerNumbers_.push_back(randomNumber);}
            break;
      }
   }

private: 
    std::vector<int> computerNumbers_;
    int computerSum;

    std::vector<int> playerNumbers_;
    int PlayerSum;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly: public Game {
public:  
   // implementing concrete methods
   void initializeGame(){
      playersCount_ = rand() % numPlayers_ + 1 ; // initialize players
   }

   void makeMove(int player) {
      if (movesCount_ > minMoves_){ 
	 const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Monopoly, player "<< playerWon_<< " won in "
	   << movesCount_<< " moves." << endl;
   }

private:
   static const int numPlayers_ = 8; // max number of players
   static const int minMoves_ = 20; // nobody wins before minMoves_
   static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess: public Game {
public:
   void initializeGame(){
      playersCount_ = numPlayers_; // initalize players
      for(int i=0; i < numPlayers_; ++i) 
	     experience_[i] = rand() % maxExperience_ + 1 ; 
   }

   void makeMove(int player){
      if (movesCount_ > minMoves_){
	 const int chance = (rand() % maxMoves_) / experience_[player];
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Chess, player " << playerWon_ 
	   << " with experience " << experience_[playerWon_]
	   << " won in "<< movesCount_ << " moves over"
	   << " player with experience " << experience_[playerWon_== 0 ? 1:0] 
           << endl;
   }

private:
   static const int numPlayers_ = 2;
   static const int minMoves_ = 5; // nobody wins before minMoves_
   static const int maxMoves_ = 100; // somebody wins before maxMoves_
   static const int maxExperience_ = 5; // player's experience
                              // the higher, the greater probability of winning
   int experience_[numPlayers_]; 
};

#endif