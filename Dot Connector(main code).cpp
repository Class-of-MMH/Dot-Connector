#include <iostream>  
#include <vector>    
#include <map>       // Include map container for scores

using namespace std;  

const int SIZE = 3;  // Set the default size of the grid to 3, can be changed

// Define a structure representing a move with row, column, and direction
struct Move {
    int row, col;
    char direction;
};

// Define a class for the Dots and Boxes game
class DotsAndBoxes {
private:
    int gridSize;               // Size of the grid
    vector<vector<char>> grid;  // 2D vector to represent the game grid
    vector<Move> moves;          // Vector to store moves made

public:
    map<char, int> scores;  // Map to store scores for players

    // Constructor to initialize the game with a given size
    DotsAndBoxes(int size) : gridSize(size) {
        grid.resize(2 * size + 1, vector<char>(2 * size + 1, ' '));  // Resize the grid
        scores['1'] = 0;  // Initialize scores for Player 1
        scores['2'] = 0;  // Initialize scores for Player 2
    }

    // Function to print the current state of the grid
    void printGrid() {
        cout << "  ";
        for (int j = 1; j <= gridSize; j++) {
            cout << j << "   ";
        }
        cout << endl;

        for (int i = 1; i <= gridSize; i++) {
            cout << i;
            for (int j = 1; j <= gridSize; j++) {
                cout << " ";
                if (grid[2 * i - 1][2 * j - 1] == '|') {
                    cout << "|";
                } else if (grid[2 * i - 1][2 * j - 1] == '-') {
                    cout << "-";
                } else {
                    cout << " ";
                }
                cout << " ";
            }
            cout << endl;

            if (i < gridSize) {
                cout << "  ";
                for (int j = 1; j <= gridSize; j++) {
                    if (grid[2 * i - 1][2 * j - 1] == '|') {
                        cout << " |  ";
                    } else {
                        cout << "    ";
                    }
                }
                cout << endl;
            }
        }
    }

    // Function to check if a move is valid
    bool isValidMove(const Move& move) {
        if (move.row < 1 || move.row > gridSize || move.col < 1 || move.col > gridSize) {
            return false;
        }

        if (move.direction != 'H' && move.direction != 'V') {
            return false;
        }

        if (move.direction == 'H' && grid[2 * move.row - 1][2 * move.col - 1] == '-') {
            return false;
        }

        if (move.direction == 'V' && grid[2 * move.row - 1][2 * move.col - 1] == '|') {
            return false;
        }

        // Check if the move has already been made
        for (const Move& pastMove : moves) {
            if (pastMove.row == move.row && pastMove.col == move.col && pastMove.direction == move.direction) {
                return false;
            }
        }

        return true;
    }

    // Function to make a move on the grid
    void makeMove(const Move& move, char player) {
        if (move.direction == 'H') {
            grid[2 * move.row - 1][2 * move.col - 1] = '-';
        } else {
            grid[2 * move.row - 1][2 * move.col - 1] = '|';
        }

        checkForBoxes(move, player);
        // Add the move to the list of made moves
        moves.push_back(move);
    }

    // Function to check if a move completes a box and update scores
    void checkForBoxes(const Move& move, char player) {
        bool boxCompleted = false;

        if (move.direction == 'H') {
            if (grid[2 * move.row - 2][2 * move.col - 1] == '|' &&
                grid[2 * move.row][2 * move.col - 1] == '|' &&
                grid[2 * move.row - 1][2 * move.col - 2] == '-') {
                boxCompleted = true;
            }
            if (grid[2 * move.row - 1][2 * move.col - 1] == '|' &&
                grid[2 * move.row + 1][2 * move.col - 1] == '|' &&
                grid[2 * move.row][2 * move.col - 2] == '-') {
                boxCompleted = true;
            }
        } else {
            if (grid[2 * move.row - 1][2 * move.col - 2] == '-' &&
                grid[2 * move.row - 1][2 * move.col] == '-' &&
                grid[2 * move.row - 2][2 * move.col - 1] == '|') {
                boxCompleted = true;
            }
            if (grid[2 * move.row - 1][2 * move.col - 1] == '-' &&
                grid[2 * move.row - 1][2 * move.col + 1] == '-' &&
                grid[2 * move.row - 2][2 * move.col] == '|') {
                boxCompleted = true;
            }
        }

        if (boxCompleted) {
            grid[2 * move.row - 1][2 * move.col - 1] = player;
            scores[player]++;
        }
    }

    // Function to check if the game is over
    bool isGameOver() {
        return scores['1'] + scores['2'] == gridSize * gridSize;
    }

    // Function to print scores
    void printScores() {
        cout << "Player 1: " << scores['1'] << "  Player 2: " << scores['2'] << endl;
    }
};

// Function to print game instructions
void printInstructions() {
    cout << "Welcome to Dot Connector!" << endl;
    cout << "Players take turns connecting dots to form squares." << endl;
    cout << "Enter your move in the format: row column direction (e.g., 1 2 H)" << endl;
    cout << "Rows and columns are numbered from 1 to " << SIZE << "." << endl;
}

// Main function
int main() {
    printInstructions();  // Print game instructions

    int gridSize;
    cout << "Enter the size of the grid (3 or more): ";
    cin >> gridSize;

    if (gridSize < 3) {
        cout << "Invalid grid size. Exiting." << endl;
        return 1;
    }

    DotsAndBoxes game(gridSize);  // Create a DotsAndBoxes game object with the specified size

    while (!game.isGameOver()) {
        system("clear");  // Clear the console screen (use "cls" instead of "clear" for Windows)
        game.printGrid();  // Print the current state of the grid
        game.printScores();  // Print the scores

        int row, col;
        char direction;
        cout << "Player 1, enter your move: ";
        cin >> row >> col >> direction;

        Move move1 = {row, col, direction};  // Create a move object

        while (!game.isValidMove(move1)) {
            cout << "Invalid move! Try again: ";
            cin >> row >> col >> direction;
            move1 = {row, col, direction};
        }

        game.makeMove(move1, '1');  // Make the move for Player 1

        if (game.isGameOver()) {
            break;
        }

        system("clear");  // Clear the console screen
        game.printGrid();  // Print the current state of the grid
        game.printScores();  // Print the scores

        cout << "Player 2, enter your move: ";
        cin >> row >> col >> direction;

        Move move2 = {row, col, direction};  // Create a move object

        while (!game.isValidMove(move2)) {
            cout << "Invalid move! Try again: ";
            cin >> row >> col >> direction;
            move2 = {row, col, direction};
        }

        game.makeMove(move2, '2');  // Make the move for Player 2
    }

    system("clear");  // Clear the console screen
    game.printGrid();  // Print the final state of the grid
    game.printScores();  // Print the final scores
    cout << "Game over! ";

    // Determine the winner or declare a tie
    if (game.scores['1'] > game.scores['2']) {
        cout << "Player 1 wins!" << endl;
    } else if (game.scores['2'] > game.scores['1']) {
        cout << "Player 2 wins!" << endl;
    } else {
        cout << "It's a tie!" << endl;
    }

    return 0;
}
