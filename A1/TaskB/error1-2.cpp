#include <iostream>
#include <string>

class Object
{
public:
    Object(std::string name);
private:
    std::string mName;
}

Object::Object(std::string name) {
    mName = name;
}

int main() {    
    Object obj1("SNP");
    return 0;
}