#include <iostream>
#include <string>

using namespace std;

string stringfunction(string&);

int main(){
	cout << stringfunction(string("SNP"));
	return 0;
}