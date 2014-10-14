#include <iostream>

using namespace std;

const int &getNumber(const int &input_number){
    int foo = input_number;
    return foo;
}

int main(){
    int i = getNumber(2);
    return 0;
}
