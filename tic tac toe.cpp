#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

// Global variables for board size
const int BOARD_SIZE = 3;
char player = 'X', computer = 'O'; // player and computer marks

// Function to display the Tic-Tac-Toe board
void displayBoard(vector<vector<char>>& board) {
    cout << "\nTic-Tac-Toe Board:\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if a player has won
bool checkWin(vector<vector<char>>& board, char currentPlayer) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer)
            return true;
        if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)
            return true;
    }
    if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer)
        return true;
    if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)
        return true;

    return false;
}

// Function to check if the board is full
bool isBoardFull(vector<vector<char>>& board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

// Minimax algorithm to find the best move for the computer
int minimax(vector<vector<char>>& board, int depth, bool isMaximizing) {
    // Base cases: Check for a win or draw
    if (checkWin(board, computer)) return 10 - depth;
    if (checkWin(board, player)) return depth - 10;
    if (isBoardFull(board)) return 0;

    // Maximizing for computer (O)
    if (isMaximizing) {
        int best = INT_MIN;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = computer;
                    best = max(best, minimax(board, depth + 1, false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
    // Minimizing for player (X)
    else {
        int best = INT_MAX;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = player;
                    best = min(best, minimax(board, depth + 1, true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// Function to find the best move for the computer using Minimax
pair<int, int> findBestMove(vector<vector<char>>& board) {
    int bestVal = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = computer;
                int moveVal = minimax(board, 0, false);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

// Function to prompt for valid input (row and column) from the player
bool isValidMove(int row, int col, vector<vector<char>>& board) {
    // Check if the row and column are within bounds and the cell is empty
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == ' ') {
        return true;
    }
    return false;
}

// Function for the single-player mode
void singlePlayerMode(vector<vector<char>>& board) {
    int row, col;
    cout << "Single Player Mode: You are X and the computer is O.\n";
    while (true) {
        // Player's move
        displayBoard(board);
        cout << "Your Move (Row and Column): ";
        while (true) {
            cin >> row >> col;
            if (isValidMove(row, col, board)) {
                break;  // Valid move
            } else {
                // Provide more specific error message for filled cells
                if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
                    cout << "Invalid input! Please enter row and column between 0 and 2.\n";
                } else {
                    cout << "Cell already filled! Please choose an empty cell.\n";
                }
            }
        }

        board[row][col] = player;
        if (checkWin(board, player)) {
            displayBoard(board);
            cout << "You win!" << endl;
            break;
        }
        if (isBoardFull(board)) {
            displayBoard(board);
            cout << "It's a draw!" << endl;
            break;
        }

        // Computer's move using Minimax
        pair<int, int> bestMove = findBestMove(board);
        board[bestMove.first][bestMove.second] = computer;
        if (checkWin(board, computer)) {
            displayBoard(board);
            cout << "Computer wins!" << endl;
            break;
        }
        if (isBoardFull(board)) {
            displayBoard(board);
            cout << "It's a draw!" << endl;
            break;
        }
    }
}

// Function for the two-player mode
void twoPlayerMode(vector<vector<char>>& board) {
    int row, col;
    while (true) {
        displayBoard(board);
        // Player 1's move (X)
        cout << "Player 1's (X) Move (Row and Column): ";
        while (true) {
            cin >> row >> col;
            if (isValidMove(row, col, board)) {
                break;  // Valid move
            } else {
                // Provide more specific error message for filled cells
                if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
                    cout << "Invalid input! Please enter row and column between 0 and 2.\n";
                } else {
                    cout << "Cell already filled! Please choose an empty cell.\n";
                }
            }
        }

        board[row][col] = player;
        if (checkWin(board, player)) {
            displayBoard(board);
            cout << "Player 1 wins!" << endl;
            break;
        }
        if (isBoardFull(board)) {
            displayBoard(board);
            cout << "It's a draw!" << endl;
            break;
        }

        displayBoard(board);
        // Player 2's move (O)
        cout << "Player 2's (O) Move (Row and Column): ";
        while (true) {
            cin >> row >> col;
            if (isValidMove(row, col, board)) {
                break;  // Valid move
            } else {
                // Provide more specific error message for filled cells
                if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
                    cout << "Invalid input! Please enter row and column between 0 and 2.\n";
                } else {
                    cout << "Cell already filled! Please choose an empty cell.\n";
                }
            }
        }

        board[row][col] = computer;
        if (checkWin(board, computer)) {
            displayBoard(board);
            cout << "Player 2 wins!" << endl;
            break;
        }
        if (isBoardFull(board)) {
            displayBoard(board);
            cout << "It's a draw!" << endl;
            break;
        }
    }
}

// Main function
int main() {
    vector<vector<char>> board(BOARD_SIZE, vector<char>(BOARD_SIZE, ' '));
    int choice;

    cout << "Welcome to Tic-Tac-Toe Game!\n";
    cout << "1. Single Player\n";
    cout << "2. Two Player\n";
    cout << "Choose your mode: ";
    cin >> choice;

    if (choice == 1) {
        singlePlayerMode(board);
    } else if (choice == 2) {
        twoPlayerMode(board);
    } else {
        cout << "Invalid choice, exiting game.\n";
    }

    return 0;
}
