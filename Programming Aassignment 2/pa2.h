#include <string>
#include <cstring>
#include <iostream>
using namespace std;

struct Node{
    Node(string d) : data(d), next(NULL) {}            //Node constructor.
    string data;
    Node *next;
};

struct List{
    int best;                                          //Determines index to insert for best fit algorithm.
    int worst;                                         //Determines index to insert for worst fit algorithm.
    Node *head;
    Node *tail;
    
    List(string data){
        head = NULL;
        tail = NULL;
        head = new Node(data);
        tail = head;
    }
    
    List(){
        head = NULL;
        tail = NULL;
        for(int i = 0; i < 32; i++){                   //Adds 32 "FREE" nodes.
            push("Free");
        }
    };
    
    int size(){                                        //Confirms the size of the list.
        int count = 0;
        Node * currentPosition = head;
        while(currentPosition != NULL){                //Examines if current node is not null.
            currentPosition = currentPosition->next;   //Goes on to the next node.
            ++count;                                   //Increments the counter by 1.
        }
        return count;                                  //Returns the size of the list.
    }
    
    bool is_empty(){                                   //Sees if the list is empty.
        return size() == 0;
    }
    
    void push(string data){                            //Adds a new node.
        if(head == NULL){
            head = new Node(data);
            tail = head;
        }
        else{
            tail -> next = new Node(data);
            tail = tail->next;
        }
    }
    
    void printNumFragments(){                          //Prints the number of free memory fragments.
        Node * currentPosition = head;
        string name;                                   //Keeps record of the last name of a node that was unique.
        int count = 0;                                 //Counts the number of fragments.
        
        for(int i = 0; i < 32; i++){
            if(currentPosition -> data == "Free" && name != "Free"){
                name = "Free";
                count++;
            }
            else if(currentPosition->data != name){            //Determines if the last node is different from this one.
                name = currentPosition -> data;                //Name equals the new node if it is indeed different.
            }
            else if(currentPosition->next != NULL){            //Checks to see if there are more.
                currentPosition = currentPosition->next;       //Skips to the next one.
            }
        }
        cout << "There are " << count << " fragment(s)." << endl;      //Prints number of fragments in the memory.
    }
    
    void printNumList(){                                       //Prints the contents.
        if(head == NULL){
            cout << "List is empty" << endl;
            return;
        }
        
        Node * currentPosition = head;
        {
            
        }
        while(currentPosition != NULL){
            for(int i = 0; i < 8; i++){
                if(currentPosition != NULL){
                    if(currentPosition->data != "Free") {
                        cout << currentPosition -> data << "   ";
                    }
                    else{
                        cout << currentPosition -> data << " ";
                    }
                    currentPosition = currentPosition->next;
                }
            }
            cout << "\n \n";
        }
    }
    
    bool removePrograms(string data){                           //Removes program entries by their designated name.
        Node * currentPosition = head;
        bool programFound = false;                              //Continuously checking if program was found.
        
        for(int i = 0; i < 32; i++){
            if(currentPosition -> data == data){
                currentPosition -> data = "Free";
                programFound = true;
            }
            
            if(currentPosition->next != NULL){
                currentPosition = currentPosition->next;
            }
        }
        return programFound;
    }
    
    void replacePage(string data, int position){                //replacePage finds a node with new data at a certain position.
        
        Node * currentPosition = head;
        
        for(int i = 0; i < position; i++){
            currentPosition = currentPosition -> next;
        }
        currentPosition -> data = data;
    }
    
    bool getWorst(string name, int size){                       //Finds the optimal place to insert the entry.
        int maxNum = 0, count = 0, start;
        Node * currentPosition = head;
        
        for(int i = 0; i < 32; i++){
            if(currentPosition -> data == name){
                cout << "There is a program with that name";
                return false;
            }
            
            if(currentPosition->data == "Free"){
                start = i;
                while(currentPosition->data == "Free"){
                    if(currentPosition->next != NULL){
                        count++;
                        currentPosition = currentPosition -> next;
                    }
                    else{
                        break;
                    }
                }
                
                if(count > maxNum){                             //Checks if the number of spaces is greater than the largest one.
                    maxNum = count;
                    worst = start;                              //Updates the condition.
                }
                count = 0;
            }
            else if(currentPosition->next != NULL){
                currentPosition = currentPosition->next;
            }
        }
        return (maxNum >= size) ? true : false;                 //Determines the maxNum whether or not the program can fit in.
    }
    
    bool getBest(string name, int size){                        //Looks for index for the best algorithm.
        Node * currentPosition = head;
        int init = 0;
        int count = 0;
        int start = 0;
        int minNum = 0;
        
        for(int i = 0; i < 32; i++){
            if(currentPosition->data == name){
                cout << "Error, Program " << name << " already running.\n";
                return false;
            }
            if(currentPosition->data == "Free"){
                start = i;
                while(currentPosition -> data == "Free"){
                    if(currentPosition -> next != NULL){
                        count++;
                        currentPosition = currentPosition->next;
                    }
                    else{
                        break;
                    }
                }
                if(count >= size){
                    if(init == 0) {
                        minNum = count;
                        init++;
                        best = start;
                    }
                    if(count < minNum){                         //minNum checks if there is a smaller space that can hold data.
                        minNum = count;
                        best = start;
                    }
                }
                count = 0;
            }
            else if(currentPosition -> next != NULL){
                currentPosition = currentPosition -> next;
            }
        }
        return (minNum >= size) ? true : false;
    }
};
