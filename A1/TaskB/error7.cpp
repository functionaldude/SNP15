#include <iostream>
using namespace std;
class bar{
public:
    int funbar();
};

int bar::funbar(){
    cout << "SNP" << endl;
}

int main(){
    bar::funbar();
    return 0;
}
