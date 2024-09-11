#include "List.hpp"

template<typename T>
void idk(Collection<T> col) {
    col.print();  //
}

int main(){
    Collection<int> a,b;
    a.add(1);
    b.add(1);
    

    std::cout << (a == b) ;

}
