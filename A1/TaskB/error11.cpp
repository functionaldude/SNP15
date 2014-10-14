#include <iostream>

class Incomplete{
public:
    Incomplete();
    ~Incomplete();
    int number;
};

Incomplete::Incomplete(){
    number = 0;
}

int main(){
	Incomplete object_name;
    return 0;
}
