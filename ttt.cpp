#include <iostream>
#include <string>
#include <limits>
using namespace std;

// g++ ttt.cpp -std=c++17 -o ttt
// ttt

// All the winning conditions
// Initialized for the check_win() function
const int win[8][3] = {{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8},{2,4,6}};


// Set up a game state with a 2D array of integers
// First layer represent player, second layeer the position they put on the board
class gameState{
    public:
        int gameState[2][5] = {{9,9,9,9,9}, {9,9,9,9,9}}; // Current game in a string
        // Starting with 9 since it doesn't exist as a position

        // board to represent the current board
        char board[3][3] = {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
        };
        string playerChoice; // "xo" or "ox", and player 1 chooses the first character
        bool turn = true; // true for player 1's turn, false for player 2's turn
};



void pieceAssignment(gameState& g){
    int choice;
    cout << "\nWhich piece does player 1 want?\n";
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

    g.playerChoice = (choice == 0) ? "xo" : "ox";
    cout << "Your pieces are set up!\n";
}


void print_input_board(){
    string top = "0|1|2\n";
    string middle = "3|4|5\n";
    string bottom = "6|7|8\n";

    cout << top + "-+-+-\n" + middle + "-+-+-\n" + bottom;
}

string set_up_board(gameState& g){
    string editor(6, ' ');
    string out = "";

    // "X|X|X\n"
    for (int i = 0; i < 3; i++){ // 3 rows
        for (int j = 0; j < 6; j++){ // 6 is the length of each row of board
            if (j == 5){
                editor[j] = '\n';
            }
            else if (j == 1 || j == 3){
                editor[j] = '|';
            }
            else{
                editor[j] = g.board[i][j/2]; // getting values from the g.board 2D array
            }
        }
        out += editor;

        if (i != 2){
            out += "-+-+-\n"; // add separation
        }
    }
    return out;
}


bool check_win(gameState& g){
    // Horizontal => 012,345,678
    // Vertical => 036,147,258
    // Diagonal => 048,246


    // Turn resets after get_input() is called, so it would be player 2's turn when checking if player 1 won
    // Player 1 has one more piece than player 2
    // Odd number of pieces on the board

    int player = (g.turn) ? 0 : 1; // avoids a big if statement
    int connect;

    // Looping through all the 8 winning cases
    for (int i = 0; i < 8; i++){
        // Reset connect to 0 to check length of connections
        connect = 0;

        // check
        for (int j = 0; j < 3; j++){
            // Looping through all the currently occupied cell
            for (int k = 0; k < 5; k++){
                // Check if reached the end of the array
                // if the current length of the array is smaller than 3, return false
                if (g.gameState[player][k] == 9 && k < 2){ 
                    return false;
                }
                connect += (g.gameState[player][k] == win[i][j]);
            }

            if (connect == 3){
                return true; // When there are three connecting pieces, return true
            }
        }
    }

    return false;
}


void get_input(gameState& g){
    int input;
    int player = (g.turn) ? 0 : 1;
    cout << "Type an integer from 0 to 8:";
    while (!(cin >> input)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "An integer input expected. Try again: ";
    }


    if (input > 8 || input < 0){
        cout << "\nOut of range.\n\n";
        return get_input(g);
    }

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 5; j++)
            if (g.gameState[i][j] == input){ 
                cout << "That square is occupied! Try again!\n";
                return get_input(g);
            }
    }

    //Update g.gameState
    for (int i = 0; i < 5; i++){
        if (g.gameState[player][i] == 9){
            g.gameState[player][i] = input;
            break;
        }
    }

    //Update g.board
    g.board[input / 3][input % 3] = g.playerChoice[player];

    //Update g.turn
    g.turn = !g.turn;
}

int moveCount(const gameState& g){
    int cnt = 0;
    for (int p = 0; p < 2; ++p)
        for (int j = 0; j < 5; ++j)
            if (g.gameState[p][j] != 9) ++cnt;
    return cnt;
}

int main(){
    gameState ttt;
    for (auto& row : ttt.gameState)        // 1. init to 9
        fill(begin(row), end(row), 9);

    cout << "####################### \n"
         << "Welcome to Tic Tac Toe! \n"
         << "####################### \n\n";

    pieceAssignment(ttt);
    cout << "\nYour game starts now!\n\n";

    while (true){
        int moves = moveCount(ttt);
        if (moves == 9 || check_win(ttt)) break;

        cout << "Player " << (ttt.turn ? 1 : 2) << "'s turn.\n"
             << "Current Board:\n"
             << set_up_board(ttt) << '\n';
        print_input_board();
        get_input(ttt);
    }

    // final messages
    if (check_win(ttt))
        cout << "Player " << (ttt.turn ? 2 : 1) << " won!\n";
    else
        cout << "The game was drawn.\n";

    cout << "Final Board:\n" << set_up_board(ttt);
    return 0;
}