#include <iostream>
#include <sstream>
#include <fstream>
#include <deque>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#include "pa3.h"

int main(int argc, const char * argv[]){
    vector<string> fileLines;
    string fileName;
    
    //Prompts user to type in a text file
    do{
        cout << "INPUT> Please enter the name of the input file:" << endl;
        cin >> fileName;
        ifstream file;
        file.open(fileName.c_str());
        string cLine;
        while(getline(file, cLine)){
            fileLines.push_back(cLine);
        }
    }
    while(fileLines.size() <= 1);
    
    cout << endl;
    
    //Performs Lexical Analysis from the .h file
    LexicalAnalysis LA(fileLines);
    
    //After the text file has been typed in, user will see the contents of the file
    cout << "Syntax Error(s): ";
    LA.check();
    
    cout << endl;
    cout << "OUTPUT> The depth of nested loop(s) is " << LA.nestedLoops << endl;
    cout << endl;
    cout << "Keywords: ";
    print(LA.foundKeywords);
    cout << "Identifiers: ";
    print(LA.foundIdentifiers);
    cout << "Constants: ";
    print(LA.foundConstants);
    cout << "Operators: ";
    print(LA.foundOperators);
    cout << "Delimiters: ";
    print(LA.foundDelimiters);
    
    cout << endl;
    return 0;
}
