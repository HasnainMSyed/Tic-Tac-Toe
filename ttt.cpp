#include <iostream>
#include <string>
#include <limits>
using namespace std;

// g++ ttt.cpp -std=c++17 -o ttt
// ttt


// Set up a game state with an array of integers
// The even-number-th item on the array store the location that player 1 placed a piece
// The odd-number-th item on the array store the location that player 2 placed a piece
class gameState{
    public:
        int gameLength = 1; // Length of current game (length of game array)
        int gameState[9]; // Current game in a string
        char player1Choice; // 'x' or 'o', player 1 plays first
        char player2Choice; // 'o' or 'x', player 2 plays second
        bool turn = true; // true for player 1's turn, false for player 2's turn
};

void pieceAssignment(gameState g){
    int choice;
    cout << "Which piece does player 1 want?\n";
    cout << "Please choose from one of the following.\n";
    cout << "Note: Player 2 will get the other one.\n\n";

    cout << "Type 0 if you want \'x\'.\n";
    cout << "Type 1 if you want \'o\'.\n";
    cout << "Choice:";

    while (!(cin >> choice)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nExpected 0 or 1. Try again: ";
    }

    if (choice != 0 && choice != 1){
        cout << "\nOut of range.\n\n";
        return pieceAssignment(g);
    }

    g.player1Choice = (choice == 0) ? 'x' : 'o';
    g.player2Choice = (choice == 0) ? 'o' : 'x';

    cout << "Your pieces are set up!\n";
}

void print_input_board(){
    string top = "0|1|2\n";
    string middle = "3|4|5\n";
    string bottom = "6|7|8\n";

    cout << top + "-+-+-\n" + middle + "-+-+-\n" + bottom;
}

string set_up_board(gameState g){
    string top = " | | \n";
    string middle = " | | \n";
    string bottom = " | | \n";

    for (int i = 0; i < g.gameLength; i++){
        switch (g.gameState[i] / 3){ // check top, middle, or bottom; 0 => top, 1 => middle, 2 => bottom
            case 0:
                // Use the remainder after division with 3 to check location
                // Turn checking with (i % 2). If even, player 1. Else, player 2.
                top[2 * (g.gameState[i] % 3)] = (i % 2 == 0) ? g.player1Choice : g.player2Choice;
            case 1:
                middle[2 * (g.gameState[i] % 3)] = (i % 2 == 0) ? g.player1Choice : g.player2Choice;
            case 2:
                bottom[2 * (g.gameState[i] % 3)] = (i % 2 == 0) ? g.player1Choice : g.player2Choice;
        }
    }

    return top + "-+-+-\n" + middle + "-+-+-\n" + bottom;
}

bool check_win(gameState g){
    // Horizontal => 012,345,678
    // Vertical => 036,147,258
    // Diagonal => 048,246

    // All the winning conditions
    int win[8][3] = {{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8},{2,4,6}};

    int player[5]; // Only need to check once for the player that just played
    int len;

    // Turn resets after get_input() is called, so it would be player 2's turn when checking if player 1 won
    // Player 1 has one more piece than player 2
    // Odd number of pieces on the board
    if (!g.turn){
        len = g.gameLength / 2 + 1;
        if (len < 3){
            return false;
        }
        for (int i = 0; i < g.gameLength; i++){
            if (i % 2 == 0){
                player[i/2] = g.gameState[i];
                // Player 1 occupies all the even-number-th int
            }
        }
    }
    // Even number of pieces on the board
    // Player 1 and player 2 have the same amount of pieces
    else{
        len = g.gameLength / 2;
        if (len < 3){
            return false;
        }
        for (int i = 0; i < g.gameLength; i++){
            if (i % 2 == 1){
                player[i/2] = g.gameState[i];
                // Player 1 occupies all the even-number-th int
            }
        }
    }

    // check
    int connect = 0;
    // Looping through all the cases
    for (int i = 0; i < 8; i++){
        // Looping through the individual cell in every case
        for (int j = 0; j < 3; j++){
            // Looping through all the currently occupied cell
            connect = 0; // Reset connect to 0 when checking every case
            for (int k = 0; k < len; k++){
                if (player[k] == win[i][j]){
                    connect++;
                }
            }
            if (connect == 3){
                return true; // When there are three connecting pieces, return true
            }
        }
    }

    return false;
}

void get_input(gameState g){
    int output;
    cout << "Type an integer from 0 to 8:";
    while (!(cin >> output)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "An integer input expected. Try again: ";
    }
    
    if (output > 8 || output < 0){
        cout << "\nOut of range.\n\n";
        return get_input(g);
    }

    g.gameState[g.gameLength-1] = output;
    g.gameLength++;
    g.turn = !g.turn;
}

int main(){
    bool over = false;
    gameState ttt;

    cout << "####################### \n";
    cout << "Welcome to Tic Tac Toe! \n";
    cout << "####################### \n\n\n";

    pieceAssignment(ttt);

    cout << "\nYour game starts now!\n\n";

    while (!over){
        if (ttt.gameLength == 9){
            over = true;
        }

        if (ttt.turn){
            cout << "Player 1's turn.\n";
            cout << "Current Board: \n";
            cout << set_up_board(ttt) + "\n";
            print_input_board();
            get_input(ttt);
            if (check_win(ttt) == true){
                over = true;
                cout << "Player 1 won! Thanks for playing!\n";
                cout << "Final Board: \n";
                cout << set_up_board(ttt);
            }
        }
        else{
            cout << "Player 2's turn.\n";
            cout << "Current Board: \n";
            cout << set_up_board(ttt) + "\n";
            print_input_board();
            get_input(ttt);
            if (check_win(ttt) == true){
                over = true;
                cout << "Player 2 won! Thanks for playing!\n";
                cout << "Final Board: \n";
                cout << set_up_board(ttt);
            }
        }
    }

    cout << "The game was drawn. Thanks for playing!\n";
    cout << "Final Board: \n";
    cout << set_up_board(ttt);
    
    return 0;
}



