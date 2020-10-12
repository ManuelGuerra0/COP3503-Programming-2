#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <cstdio>
#include <string>
#include <cstring>
#include "pa2.h"
#include <iostream>
using namespace std;

int main(int argc, const char * argv[]){
    string algorithm = "FillerText";
    List list;
    bool isItTheBest;                              //If true, then it runs best fit. Vice versa.
    
    if(argv[1] != 0){                              //Checks if there is an argument present.
        algorithm = argv[1];                       //String algorithm to see for best or worse.
    }
    if(algorithm == "best"){
        isItTheBest = true;
        printf("Using best fit algorithm\n");
    }
    else if(algorithm == "worst"){
        isItTheBest = false;
        printf("Using worst fit algorithm\n");
    }
    else{
        isItTheBest = true;
        printf("Default: best fit algorithm\n");
    }
    cout << " " << endl;
    printf("  1. Add program\n");                  //Console menu for the user.
    printf("  2. Kill program\n");
    printf("  3. Fragmentation\n");
    printf("  4. Print memory\n");
    printf("  5. Exit\n\n");
    
    char option;
    
    do{
        printf("choice - ");
        cin >> option;
        
        switch(option){
            case '1':{                                              //Adds a program.
                string name;
                double size;
                cout << "Program name - ";
                cin >> name;                                        //Asks user input for the name of the program.
                cout << "Program size (KB) - ";
                cin >> size;                                        //Asks user input for the size of the program in KB.
                cout << " " << endl;
                
                int realSize = ceil(size/4.0);                      //Rounds up to the number of nodes for program.
                
                if(isItTheBest){                                    //If isItTheBest is true, then best fit algorithm is used.
                    if(list.getBest(name, realSize)){               //Calls getBest to put best.
                        for(int i = list.best; i < realSize + list.best; i++){
                            list.replacePage(name, i);
                        }
                        cout << "Program " << name << " added successfully: " << realSize << " page(s) used.\n";
                                                                    //Message to the user saying operation was a success.
                    }
                    else{
                        cout << "\nProgram " << name << " cannot be added.\n";
                    }
                }
                else{                                               //If isItTheBest is false, then worst fit algorithm is used.
                    if(list.getWorst(name, realSize)){
                        for(int i = list.worst; i < realSize + list.worst; i++){
                            list.replacePage(name, i);
                        }
                        cout << "Program " << name << " added successfully: " << realSize << " page(s) used.\n";
                    }
                    else{
                        cout << "\n Program " << name << " cannot be added.\n";
                    }
                }
                break;
            }
            case '2':{                                              //Deletes a program.
                string name;
                cout << "Program name to delete: ";
                cin >> name;
                
                if (list.removePrograms(name)){                     //Calling removePrograms to replace named program with FREE slots.
                    cout << "\nProgram " << name << " successfully killed, " << name.length() << " page(s) reclaimed.\n";
                                                                    //Prompts user that action was successful.
                }
                else{
                    cout << "\nNo program with the name " << name << " was found in the memory\n";  //Failure message.
                }
                break;
            }
            case '3':{                                              //Prints the number of fragments in the entire memory.
                printf("\n");
                list.printNumFragments();
                break;
            }
            case '4':{                                              //Prints what is in the entire memory.
                printf("\n");
                list.printNumList();
                break;
            }
            case '5':{                                              //Exists out of the program.
                printf("Exit \n");
                return 0;
            }
            default: cout << option << " It is invalid item.\n";    //Error message notifying the user when range is outside of 1 - 5.
        }
        cout << " " << endl;
    }
    while(option != 5);                                             //Executes the parameter from 1 - 5.
    
    return 0;
}
