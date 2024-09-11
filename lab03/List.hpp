// node class tempate used to contruct lists
// Mikhail Nesterenko
// 5/01/00

#ifndef LIST_HPP_
#define LIST_HPP_
#include <iostream>
#include <string>


using std::cout; using std::endl;using std::string;

// the pointer part of every list is the same
// lists differ by data part
template <typename T>
class node{
public:
  node(): next_(nullptr) {}
  node(const T&);

  // functions can be inlined
  T getData() const {return data_;}
  void setData(const T& data){data_=data;}

  // or can be defined outside
  node<T>* getNext() const;
  void setNext(node<T> *const);

private:
  T data_;
  node<T> *next_;
};

//
// member functions for node
//

template<typename T>
node<T>::node(const T& input){
  data_ = input;
  next_ = nullptr;
}

template <typename T>
node<T>* node<T>::getNext() const {
  return next_;
}

template<typename T>
void node<T>::setNext(node<T> *const next){
  next_=next;
}

// collection

template<typename T>
class Collection;

template<typename T>
bool equal(const Collection<T>&,const Collection<T>&);

template<typename T>
class Collection{
public:
  Collection();
  Collection(const Collection<T>&);
  ~Collection();

  bool operator==(const Collection<T>&);

  T last(){return last_->getData();}
  void add(const T&);
  void remove(const T&);

  friend bool equal<T>(const Collection<T>&,const Collection<T>&);

  void print();
private:
  node<T> * last_;
  node<T> * beginning_;
};

template<typename T>
bool Collection<T>::operator==(const Collection<T>&input){
  return equal(*this,input);
}


template<typename T>
Collection<T>::Collection(const Collection<T>&input):Collection(){
  node<T>* current = input.beginning_;
  while(current){
    add(current->getData());
    current = current->getNext();
  }
}



template<typename T>
Collection<T>::~Collection(){
  node<T> * current = beginning_;
  while(current){
    node<T>*temp = current;
    current = current->getNext();
    delete temp;
  }
}

template<typename T>
bool equal(const Collection<T>&lhs,const Collection<T>&rhs){
  node<T> * currentLHS = lhs.beginning_;
  node<T> * currentRHS = rhs.beginning_;
  while(currentLHS || currentRHS){
    if((currentLHS != nullptr && currentRHS == nullptr) ||(currentLHS == nullptr && currentRHS != nullptr)){return false;}
    if(currentLHS->getData() != currentRHS->getData()){return false;}

    currentLHS = currentLHS->getNext();
    currentRHS = currentRHS->getNext();
  }
  return true;
}

template<typename T>
void Collection<T>::remove(const T&input){
  node<T> * current = beginning_;
  node<T>* previous = nullptr;

  while(current != nullptr){
    node<T> * temp = current;

    if(temp->getData() == input){

      if(temp == beginning_){
        if(temp->getNext() != nullptr){
          beginning_ = temp->getNext();
        }else{
          beginning_ = nullptr;
          last_ = nullptr;
        }
        current = current->getNext();
        delete temp;
      }
      else if(temp == last_){
        previous->setNext(nullptr);
        last_ = previous;
        delete temp;
        current = previous;
      }
      else{
        previous->setNext(current->getNext());
        current = current->getNext();
        delete temp;
      }
    }
    else{
      previous = current;
      current = current->getNext();
    }
  }
}

template<typename T>
Collection<T>::Collection(){
  last_ = nullptr;
  beginning_ = nullptr;

}


template<typename T>
void Collection<T>::print(){
  node<T> * current = beginning_;
  while(current != nullptr){
    std::cout << current->getData() << std::endl;
    current = current->getNext();
  }
}

template<typename T>
void Collection<T>::add(const T&input){
  node<T> * temp = new node<T>(input);
  if(last_ == nullptr){
    beginning_ = temp;
    last_ = temp;
  }else{
    last_->setNext(temp);
    last_ = temp;
  }
}


#endif // LIST_HPP_