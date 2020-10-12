const string KEYWORDS[] = {"BEGIN", "END", "FOR"}; //Keywords (size 3)
const unsigned int KEYWORDS_SIZE = 3;

const string OPERATORS[] = {"+", "-", "*", "/", "++", "="}; //Operators (size 7)
const unsigned int OPERATORS_SIZE = 7;

const string DELIMITERS[] = {",", ";"}; //Delimiters (size 2)
const unsigned int DELIMITERS_SIZE = 2;

void print(const vector<string> &s){
    for(unsigned int i = 0; i < s.size(); i++){
        cout << s[i];
        if(i < s.size() - 1) cout << " ";
    }
    cout << endl;
}

class LexicalAnalysis{
private:
    vector<string> *fileLines;
    
public:
    int nestedLoops;
    int loops;
    vector<string> foundIdentifiers, foundConstants, foundOperators, foundDelimiters, foundKeywords;
    LexicalAnalysis(vector<string> &fileLines) : nestedLoops(0) {
        this->fileLines = &fileLines;
    }
    
    //Checks vector for preexisting elements and adds one
    void addToVector(vector<string> &v, string s){
        for(unsigned int i = 0; i < v.size(); i++){
            if(v[i] == s) return;
        }
        v.push_back(s);
    }
    //Returns vector of split substrings
    vector<string> splitStringVec(const string &s, string what){
        unsigned int i = 0;
        vector<string> hold;
        size_t pos = s.find(what);
        while(pos != string::npos){
            addToVector(foundOperators, what);
            if(s.substr(i, pos - i) != "") hold.push_back(s.substr(i, pos - i));
            i = ++pos;
            pos = s.find(what, pos);
        }
        if(pos == string::npos){
            if(s.substr(i, s.length()) != "") hold.push_back(s.substr(i, s.length()));
        }
        return hold;
    }
    
    //Returns string w/o "what"
    string splitString(const string &s, string what){
        unsigned int i = 0;
        string hold = "";
        size_t pos = s.find(what);
        while(pos != string::npos){
            addToVector(foundOperators, what);
            hold += " " + (s.substr(i, pos - i));
            i = ++pos;
            pos = s.find(what, pos);
        }
        if(pos == string::npos){
            hold += " " + (s.substr(i, s.length()));
        }
        return hold;
    }
    
    //Returns string w/ all operators split
    string splitStringOperators(const string &s){
        string hold;
        hold = s;
        for(unsigned int i =  0; i < OPERATORS_SIZE; i++){
            hold = splitString(hold, OPERATORS[i]);
        }
        return hold;
    }
    
    //Finds string occurance
    unsigned int numOfOccurence(const string &main, string what){
        size_t fPos = main.find(what);
        unsigned int c = 0;
        while(fPos != string::npos){
            c++;
            fPos = main.find(what, fPos + 1);
        }
        return c;
    }
    
    //Deletes ' ' whitespace
    string removeSpaces(string s){
        s.erase(remove(s.begin(), s.end(), '\t'), s.end());
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        return s;
    }
    
    //Checks for one instance in string
    bool justFound(const string &main, string what){
        if (removeSpaces(main).size() == what.size() && found(main, what)) return true;
        return false;
    }
    
    //Checks string as a number
    bool isNumber(const string &s){
        std::string::const_iterator it = s.begin();
        while(it != s.end() && std::isdigit(*it)) ++it;
        bool hold = !s.empty() && it == s.end();
        return hold;
    }
    
    //Checks OPERATOR is in a string
    bool isOperator(const string &s, unsigned int amount = 1){
        for(unsigned int i =  0; i < OPERATORS_SIZE; i++){
            if(found(s, OPERATORS[i], amount)) return true;
        }
        return false;
    }
    
    //Checks for string in another string
    bool found(string main, string what, unsigned int amount = 1){
        if(amount == 0){
            if(main.find(what) != string::npos) return true;
        }
        else if(numOfOccurence(main, what) == amount) return true;
        return false;
    }
    
    //Checks string is an identifier
    bool isIdentifier(const string &s){
        for(unsigned int i = 0; i < s.size(); i++){
            if(!islower(s.at(i))) return false;
        }
        if(isNumber(s) || isOperator(s)) return false;
        return true;
    }
    
    //Checks string is an keyword
    bool isKeyword(const string &s, unsigned int amount = 0){
        for(unsigned int i =  0; i < KEYWORDS_SIZE; i++){
            if(found(s, KEYWORDS[i], amount)) return true;
        }
        return false;
    }
    
    //Main loop that checks for errors in the text file
    void check(){
        unsigned int line = 1;
        deque < deque<string> >fKeywords; //Checks for nested loops
        for(vector<string>::iterator it = fileLines->begin(); it != fileLines->end(); it++, line++){
            *it = removeSpaces(*it);
            bool reg = true;
            if(found(*it, "FOR")){
                if(!process(*it, line)){
                    cout << "Error within FOR statment" << endl;
                }
                reg = false;
                deque<string> temp;
                temp.push_back("FOR");
                fKeywords.push_back(temp);
                if(!justFound(*(it + 1), "BEGIN")){
                    cout << "Expected BEGIN: " << removeSpaces(*(it + 1)) << endl;
                }
            }
            if(found(*it, "BEGIN")){
                reg = false;
                if(fKeywords.back().back() == "FOR") fKeywords.back().push_back("BEGIN");
                else{
                    fKeywords.pop_back();
                    cout << "Error no BEGIN for FOR" << endl;
                }
            }
            if(found(*it, "END")){
                if(fKeywords.back().back() == "BEGIN"){
                    fKeywords.pop_back();
                    nestedLoops ++ ;
                    reg = false;
                }
                else{
                    fKeywords.pop_back();
                    cout << "Did not find BEGIN" << endl;
                }
            }
            
            //Checks for regular expressions
            if(reg && found(*it, "=")){
                if(!found(*it, ";")){
                    cout << "(Line " << line << ") Expected semicolon" << endl;
                }
                size_t b = (*it).find(";");
                addToVector(foundDelimiters, ";");
                string noSemi = (*it).substr(0, b);
                
                vector<string> m = splitStringVec(splitStringOperators(noSemi), " ");
                for(unsigned int i = 0; i < m.size(); i++){
                    if(isNumber(m[i])) addToVector(foundConstants, m[i]);
                    if(isIdentifier(m[i])) addToVector(foundIdentifiers, m[i]);
                }
            }
        }
        if(fKeywords.size() != 0) cout << "Missing END statements" << endl;
    }
    
    //Checks for for-loop containments
    bool checkStack(const deque<string> &stack, unsigned int line){
        bool hold = true;
        if(!isNumber(stack.at(1))){
            cout << "(Line " << line << ") \"" << stack.at(1) << "\" is not a constant" << endl;
            hold = false;
        }
        if(!isOperator(stack.back())){
            cout << "(Line " << line << ") \"" << stack.back() << "\" is not an operator" << endl;
            hold = false;
        }
        if(!isIdentifier(stack.front())){
            cout << "(Line " << line << ") \"" << stack.front() << "\" not an identifier" << endl;
            hold = false;
        }
        if(stack.back() != "++") cout << "(Line " << line << ") Warning \"" << stack.back() << "\" is an operator but does not make sense" << endl;
        if(hold){
            addToVector(foundIdentifiers, stack.front());
            addToVector(foundConstants, stack.at(1));
            addToVector(foundOperators, stack.back());
            addToVector(foundKeywords, stack.at(0));
            
        }
        return hold;
    }
    
    //Parses for-loop containments
    bool process(string it, unsigned int line){
        deque<string> oPerDel;
        size_t par1 = (it).find("(");
        size_t par2 = (it).find(")", par1);
        if(par2 == string::npos || par1 == string::npos || par1 >= par2){
            cout << "(Line " << line << ") Error with Parenthesis" << endl;
            return false;
        }
        
        string lim = (it).substr(par1 + 1, par2 - par1 - 1);
        lim.erase(remove(lim.begin(), lim.end(), ' '), lim.end());
        if(numOfOccurence(lim, ",") != 2){
            cout << "(Line " << line << ") Error with delimiters " << endl;
            return false;
        }
        
        else addToVector(foundDelimiters, string(","));
        size_t firstPosC = lim.find_first_of(",");
        size_t lastPosC = lim.find_last_of(",");
        string var = lim.substr(0, firstPosC);
        string con = lim.substr(firstPosC + 1, lastPosC - firstPosC - 1);
        string oper = lim.substr(lastPosC + 1, lim.size() - 1);
        oPerDel.push_back(var);
        oPerDel.push_back(con);
        oPerDel.push_back(oper);
        return (checkStack(oPerDel, line));
    }
};
