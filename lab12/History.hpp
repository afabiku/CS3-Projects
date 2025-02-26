#ifndef MAIN_HPP
#define MAIN_HPP
#include <iostream>
#include <string>
#include <vector>
#include <stack>

class Document{
public:
    Document(std::vector<std::string>& Obj): list_(Obj){}    
    void insert(int l,const std::string&str){
        int index = l -1;
        if(index <= list_.size()){
            list_.insert(list_.begin()+index,str);
        }
    }
    const std::string remove(int l){
        std::string deleted = "";
        int index = l -1;
        if(l <= list_.size()){
            deleted = *(list_.begin()+index);
            list_.erase(list_.begin()+index);
        }
        return deleted;
    }

    void show(){
        int v = 1;
        for(auto&i:list_){
            std::cout << v++ << " " <<i << std::endl;
        }
    }

    class Momento * checkpoint();
    void rollback(class Momento*obj);
private:
    std::vector<std::string>  list_;
};


class Command{
public:
    Command(Document*obj): doc_(obj){}
    virtual void execute() = 0;
    virtual void unexecute() = 0;
    virtual int getLine()=0;
    virtual std::string getString() = 0;
    virtual std::string operation() = 0;
    virtual Command* clone() = 0;
protected:
    Document* doc_;
};


class InsertCommand: public Command{
public:
    InsertCommand(Document*obj, int l, const std::string &string): Command(obj), line_(l),str_(string) {};
    virtual void execute() override{doc_->insert(line_,str_);}
    virtual void unexecute() override{doc_->remove(line_);}
    virtual int getLine() override{return line_;}
    virtual std::string getString() override{return str_;}
    virtual std::string operation() override{return "insert";}
    virtual Command* clone() override{ return new InsertCommand(doc_,line_,str_); }

private:
    int line_;
    std::string str_;
};

class DeleteCommand: public Command{
public:
    DeleteCommand(Document*obj, int l): Command(obj), line_(l),str_("") {};
    virtual void execute() override{str_ = doc_->remove(line_);}
    virtual void unexecute() override{doc_->insert(line_,str_);}
    virtual int getLine() override{return line_;}
    virtual std::string getString() override{return str_;}
    virtual std::string operation() override{return "erase";}
    virtual Command* clone() override{ return new DeleteCommand(doc_,line_); }

private:
    int line_;
    std::string str_;
};


class DocumentHistory {
public:
    DocumentHistory(Document*doc): doc_(doc){}

    void remove(int line){
        Command*obj = new DeleteCommand(doc_,line);
        obj->execute();
        commands_.push_back(obj);
    }

    void insert(int line, const std::string& s){
        Command*obj = new InsertCommand(doc_,line,s);
        obj->execute();
        commands_.push_back(obj);
    }

    void undo(){
        if(!commands_.empty()){
            Command*obj = *(commands_.end()-1);
            obj->unexecute();
            commands_.erase(commands_.end()-1);
        }else{
            std::cout << "No commands to undo" << std::endl;
        }
    }

    void show(){
        doc_->show();
    }

    class Momento* checkpoint(){
        return doc_->checkpoint();
    }

    void rollback(class Momento*obj){
        doc_->rollback(obj);
    }


    // clone the command using the prototype design pattern
    // then execte the clone and add it to the commands structure
    void redo(int i){
        // add a check for i out of range
        Command* selected = commands_[i - 1]->clone();
        selected->execute();
        commands_.push_back(selected);
        // insert(selected->getLine(), selected->getString());
    }

    std::vector<Command*> getHistory(){
        return commands_;
    }
private:
    Document*doc_;
    std::vector<Command*> commands_;
};

class Momento {
public:
    Momento(const std::vector<std::string>& state): state_(state) {}
    const std::vector<std::string>& getState() const { return state_; }
private:
    std::vector<std::string> state_; 
};


Momento* Document::checkpoint() {
    return new Momento(list_); 
}


void Document::rollback(Momento* obj) {
    list_ = obj->getState(); 
}



#endif