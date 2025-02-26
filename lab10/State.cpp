#include "State.hpp"
#include <queue>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    std::srand(std::time(nullptr)); // Seed for random number generation

    std::queue<Process*> Queue;
    std::queue<Process*> blockQueue;

    Process* running = new Process();
    Process* readyOne = new Process();
    Process* readyTwo = new Process();
    Process* readyThree = new Process();

    Queue.push(running);
    Queue.push(readyOne);
    Queue.push(readyTwo);
    Queue.push(readyThree);

    while(!Queue.empty()){
        int chance = rand()%3;
        Process* front = Queue.front();
        front->Dispatch();
        Queue.pop();

        switch(chance){
            case 0:
                front->exit();
                break;
            case 1:
                front->suspend();
                Queue.push(front);
                break;
            case 2:
                front->block();
                blockQueue.push(front);
                break;
        }

        if(Queue.empty() && !blockQueue.empty()){
            std::cout << "The ready queue is empty" << std::endl;
            Process * front = blockQueue.front();
            blockQueue.pop();
            front->unBlock();
            Queue.push(front);
        }

    }

    std::cout << "all processes exited." << std::endl;
    return 0;
}
