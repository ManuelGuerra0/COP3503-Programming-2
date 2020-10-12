/* 
Name: Manuel Guerra
UFID: 8811-2134
Section: 6773
Assignment: To program a Magic Square 
*/

#include <iostream>
using namespace std;

// Method that handles the Magic Square calculations separately
void letsMakeSomeMagic(int input) {
    
    for(int square = 1; square <= 4; square++) {
        
        // Takes care of exception handling by limiting the user to an odd number within 3 and 15
        while(input % 2 == 0 || input < 3 || input > 15) {
            int nAgain;
            cout << " " << endl;
            cout << "ERROR! Please enter an odd number within 3 and 15" << endl;
            cout << endl << "Enter the size of a magic square: ";
            cin >> nAgain;
            input = nAgain;
        }
        
        // Initializes 2-D array
        int magicSquare[input][input];
        
        // Sets all the 2-D array values to zero
        memset(magicSquare, 0, sizeof(magicSquare));
        
        // Establishes the location for number 1 in the Magic Square
        int row = input / 2;
        int column = input - 1;
        
        // Enters each number after 1 in the 2-D array
        for (int num = 1; num <= input * input; ) {
            
            // If row position is - 1 & column position equals input, then new position should be (0, n - 2)
            if (row == - 1 && column == input) {
                column = input - 2;
                row = 0;
            }
            else {
                
                // If the next number goes outside of the square's right side, column is set to zero
                if (column == input) {
                    column = 0;
                }
                
                // If the next number goes outside of the square's upper side, row is set to be 1 less from input
                if (row < 0) {
                    row = input - 1;
                }
            }
            
            // If a number already exists in the current position, column is decreased by 2 & row is increased by 1
            if (magicSquare[row][column]) {
                column = column - 2;
                row++;
                continue;
            }
            
            // Finds the position of the next number by decreasing row by 1 & increasing column by 1
            else {
                magicSquare[row][column] = num++;
                column++;
                row--;
            }
        }
        
        // Calculates the sum of each row, column, and diagonal depending on input
        int sum = input * (input * input + 1) / 2;
        
        // Prompts user which Magic Square they're looking at
        cout << " " << endl;
        cout << "Magic Square #" << square << " is: " << endl;
        cout << " " << endl;
        
        // Displays the Magic Square
        for(row = 0; row < input; row++) {
            for(column = 0; column < input; column++)
                printf("%3d ", magicSquare[row][column]);
            cout << " " << endl;
        }
        
        // Prompts the user the sum of each row, column, and diagonal
        cout << " " << endl;
        cout << "Checking the sums of every row:      " << sum << " " << sum << " " << sum << endl;
        cout << "Checking the sums of every column:   " << sum << " " << sum << " " << sum << endl;
        cout << "Checking the sums of every diagnoal: " << sum << " " << sum << endl;
        
    }
}

// The main function that executes the Magic Square program
int main(int argc, const char * argv[]) {
    
    // Initializes variable "input" which will be given a value by the user
    int input;
    
    // Prompts the user to enter an integer for the Magic Square
    cout << endl << "Enter the size of a magic square: ";
    
    // Takes the user's input and stores it in the variable "input"
    cin >> input;
    
    // Prints out results of the method
    letsMakeSomeMagic(input);
    
    cout << " " << endl;
    
    return 0;
}
