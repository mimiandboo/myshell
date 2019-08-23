#include <iostream>
#include <string>

using namespace std;

string delimeter;

string parse(string s){
	for(int i = 0; i < s.length(); i++){
		if(s[i] == ';'){
			delimeter = ";";
			i += i;
		}
		else if(s[i] == '|'){
			delimeter = "|"; 
			i += i;
		}
	}

	return delimeter;
}

