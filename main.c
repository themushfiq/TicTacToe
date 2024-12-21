#include <stdio.h>
#include <stdlib.h>

// Mushfiqur Rahman
// Global variables
char board[3][3];

// Function prototypes
void initializeBoard();
void displayBoard();
int isBoardFull();
char checkWinner();
int minimax(int depth, int isMaximizing);
void computerMove();
void playerMove();

void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

int isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') return 0;
        }
    }
    return 1;
}

char checkWinner() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i];
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];

    return ' '; // No winner
}

int minimax(int depth, int isMaximizing) {
    char winner = checkWinner();
    if (winner == 'O') return 10 - depth;
    if (winner == 'X') return depth - 10;
    if (isBoardFull()) return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int score = minimax(depth + 1, 0);
                    board[i][j] = ' ';
                    if (score > bestScore) bestScore = score;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int score = minimax(depth + 1, 1);
                    board[i][j] = ' ';
                    if (score < bestScore) bestScore = score;
                }
            }
        }
        return bestScore;
    }
}

void computerMove() {
    int bestScore = -1000;
    int moveRow = -1, moveCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int score = minimax(0, 0);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    moveRow = i;
                    moveCol = j;
                }
            }
        }
    }

    if (moveRow != -1 && moveCol != -1) {
        board[moveRow][moveCol] = 'O';
    }
}

void playerMove() {
    int row, col;
    while (1) {
        printf("Enter row (0-2) and column (0-2): ");
        if (scanf("%d %d", &row, &col) != 2) {
            printf("Invalid input! Please enter two numbers.\n");
            while (getchar() != '\n'); // Clear invalid input
            continue;
        }

        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            board[row][col] = 'X';
            break;
        } else {
            printf("Invalid move! Cell is either occupied or out of bounds. Try again.\n");
        }
    }
}

int main() {
    initializeBoard();
    char winner = ' ';
    int isPlayerTurn = 1;

    printf("Welcome to Tic-Tac-Toe!\n");

    while (winner == ' ' && !isBoardFull()) {
        displayBoard();

        if (isPlayerTurn) {
            printf("Your turn (X):\n");
            playerMove();
            isPlayerTurn = 0;
        } else {
            printf("Computer's turn (O):\n");
            computerMove();
            isPlayerTurn = 1;
        }

        winner = checkWinner();
    }

    displayBoard();

    if (winner == 'X') {
        printf("Congratulations! You win!\n");
    } else if (winner == 'O') {
        printf("The computer wins. Better luck next time!\n");
    } else {
        printf("It's a draw!\n");
    }

    return 0;
}
