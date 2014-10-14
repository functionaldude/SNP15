#include <iostream>

using namespace std;

class Incomplete{
public:
    void getData(){
        cout << "Number: ";
        cin >> number;
        cout << endl;
    }
    virtual void display();
    int number;
};

class mno:public Incomplete{
public:
    void getData();
    void display(){
        cout << "Number: " << number << endl;
    }      
};

int main()
{
    class Incomplete *ref;
    class mno obj;
    
    ref = &obj;
    ref -> getData();
    ref -> display();
    
    return 0;
}

