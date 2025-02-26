#ifndef STATE_HPP
#define STATE_HPP

#include <iostream>
#include <queue>

class State;

class Process{
public:
    Process();
    virtual void Dispatch();
    virtual void unBlock();
    virtual void suspend();
    virtual void block();
    virtual void exit();

    Process* clone();
    std::string print();
    void changeState(State*);
    int getID() const{return ID_;}
private:
    //Process(int i,State*s): ID_(i),currentState_(s){};
    State* currentState_;
    int ID_;
    static int nextID_;
};

int Process::nextID_ = 0;


class State{
public:
    virtual void changeState(Process*p,State*s){ p->changeState(s);}
    virtual std::string print() = 0;
    virtual void Dispatch(Process*){};
    virtual void suspend(Process*){};
    virtual void unBlock(Process*){};
    virtual void block(Process*){};
    virtual void exit(Process*p){};
protected:
    State(){};
    State* currentState;
};

class Ready: public State{
public:
    static State* Instance(){
        static Ready* obj = new Ready;
        return obj;
    }
    virtual void Dispatch(Process*) override;
    virtual std::string print() override{ return "Ready";}
private:
    Ready(){};
};

class Blocked: public State{
public:
    static State* Instance(){
        static Blocked* obj = new Blocked;
        return obj;
    }
    virtual std::string print() override{ return "Blocked";}
    virtual void unBlock(Process*p) override{
        std::cout << "UnBlocking..." << std::endl;
        changeState(p,Ready::Instance());
    }
private:
    Blocked(){};
};

class Running: public State{
public:
    static State* Instance(){
        static Running* obj = new Running;
        return obj;
    }
    virtual std::string print() override{ return std::string("Running");}
    virtual void block(Process*p) override{
        std::cout << "Blocking..." << std::endl;
        changeState(p,Blocked::Instance());
    }
    virtual void suspend(Process*p) override{
        std::cout << "Suspended..." << std::endl;
        changeState(p,Ready::Instance());
    };
    void exit(Process*p) override{
        std::cout << "Exiting... " << std::endl;
        std::cout << "PID " << p->getID() << ":" << " exited" << std::endl;
    }
private:
    Running(){};
};

Process* Process::clone(){return new Process();}
Process::Process(): currentState_(Ready::Instance()), ID_(nextID_++) {
    std::cout << "PID " << ID_ << ":" << " created" << std::endl;
};

void Process::changeState(State*s){currentState_ = s; std::cout << "PID " << ID_ << " state: " << currentState_->print() << std::endl;}
std::string Process::print(){return "Process " + std::to_string(ID_) + " is " + currentState_->print();}
void Process::Dispatch(){currentState_->Dispatch(this);}
void Process::unBlock(){currentState_->unBlock(this);}
void Process::block(){currentState_->block(this);}
void Process::exit(){currentState_->exit(this);}
void Process::suspend(){currentState_->suspend(this);}

void Ready::Dispatch(Process*p){ std::cout << "Dispatching..." << std::endl; changeState(p,Running::Instance());}
#endif