#include <iostream>
#include <fstream>
#include "Dictionary.h"
using namespace std;
 
int main() {
    Dictionary d;
    string data,word,define;
    ifstream file("data.txt");
    if(file.is_open()){ 
       while( getline(file,data)){
           int pos = data.find(":");
           word = data.substr(0,pos);
           define = data.substr(pos+1);
           d.add(word,define);
        }
       file.close();
    }

    d.print();
        
    


 return 0;
}

