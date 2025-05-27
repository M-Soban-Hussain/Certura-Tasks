//Including all the necessary libraries
#include <iostream>
#include < fstream>
#include <string >
using namespace  std;

//Making a 2-Dimensional  Array to act like the board
char board[3][3];
//Storing scores of both   Players
int scoreX = 0, scoreO = 0;

//This function resets the Board t o its initial state
void resetBoard() {
    char ch = '1';           
    for (int i=0;i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ch++;
	//Initial State=>
    //1 2 3
	//4 5 6         
    //7 8 9
}            

//This function prints the board onto the Console
void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3;i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
			if (j < 2) cout << " | ";// Print vertical separator for making a grid
        }
		if (i < 2) cout << "\n-----------\n";// Print horizontal separator of the Grid
    }
    cout << "\n\n";
}

//This function checks if there is a winner
char checkWin() {
    // Rows & columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
			return board[0][i];//Thsi is the condition when there is a winner in the column
    }
    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
		return board[0][2];// This is the condition when there is a winner in the diagonal
	return ' ';//This is the condition when there is no winner yet
}

//This function checks if the game is a draw
bool isDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')//Checking if all cells are filled
                return false;
    return true;
}

//This function saves the scores of both players to an external file
void saveScores() {
	ofstream file("scores.txt");// Open store.txt in write mode
    file << "Player X: " << scoreX << endl;
    file << "Player O: " << scoreO << endl;
    file.close();
}

int main() {//This is the main function from where the game starts
    string playerX, playerO;// Initializing Player Variables and asking user to Enter Values
    cout << "Enter Player X name: ";
    cin >> playerX;
    cout<< "Enter Player O name: ";
    cin>> playerO;

    char playAgain =  'y';//Check to see if game should run or not
    while (playAgain ==   'y' || playAgain   == 'Y') {//Checking for uppercase and lowerCase letter "y"
        resetBoard();//Calling the Reset Function
        char currentPlayer = 'X';
        int move;
        bool gameOver = false;

        while (!gameOver) {//Checking if Game is not Over
            printBoard();//Printing the Board
            cout<<"Player "<<currentPlayer << ", enter cell (1-9): ";//Asking user to enter Place no. to mark
            cin >> move;

            if (move < 1 || move > 9) {//Checking if the slot is pre-occupied
                cout << "Invalid move. Try again.\n";
                continue;
            }

            int row = (move - 1) / 3;
            int col = (move - 1) % 3;

            if (board[row][col] == 'X' || board[row][col] == 'O') {
                cout << "Cell already taken. Try again.\n";//Checking if the slot is pre-occupied
                continue;
            }

            board[row][col] = currentPlayer;
            char winner = checkWin();

            if (winner == 'X') {//Declaring Player X as winner
                printBoard();
                cout << playerX << " (X) wins!\n";
                scoreX++;
                gameOver = true;
            }
            else if (winner == 'O') {//Declaring Player X as winner
                printBoard();
                cout << playerO << " (O) wins!\n";
                scoreO++;
                gameOver = true;
            }
            else if (isDraw()) {//Declaring Draw
                printBoard();
                cout << "It's a draw!\n";
                gameOver = true;
            }
            else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }

        saveScores();//Calling the function to Save the Scores
        cout << "\nScores:\n" << playerX << " (X): " << scoreX << "\n" << playerO << " (O): " << scoreO << "\n";
        cout << "Play another round? (y/n): ";//Asking user if he wants to play again
        cin >> playAgain;
    }

    cout << "\nFinal Scores saved to scores.txt\n";
    return 0;
}
