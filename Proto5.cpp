#include <iostream>
#include <cstdlib>

using namespace std;


bool isValidMove(char board[8][8], int X, int Y, char A, char B);
bool isValidDirection(char board[8][8], int X, int Y, int deltaX, int deltaY, char A, char B);
void applyMove(char board[8][8], int X, int Y, char A, char B);
void markValidMoves(char board[8][8], char A, char B, char validBoard[8][8]);
int countFlipsInDirection(char board[8][8], int X, int Y, int deltaX, int deltaY, char A, char B);



void Display(char board[8][8], char A, char B, char currentPlayer) {
    char validBoard[8][8];
    markValidMoves(board, currentPlayer, (currentPlayer == A) ? B : A, validBoard); 


    for (int i = 0; i < 8; i++) {
        cout << "\t\t\t\t\t  +---+---+---+---+---+---+---+---+" << endl;
        cout << "\t\t\t\t\t" << i + 1 << " | ";
        for (int j = 0; j < 8; j++) {
            cout << validBoard[i][j] << " | ";
        }
        cout << endl;
    }
    cout << "\t\t\t\t\t  +---+---+---+---+---+---+---+---+" << endl;
    cout << "\t\t\t\t\t    A   B   C   D   E   F   G   H  " << endl;
}



bool isBoardFull(char board[8][8]) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[i][j] == ' ')
                return false;
    return true;
}

bool isValidDirection(char board[8][8], int X, int Y, int deltaX, int deltaY, char A, char B) {
    int i = Y + deltaY;
    int j = X + deltaX;
    bool opponentFound = false;

    
    while (i >= 0 && i < 8 && j >= 0 && j < 8 && board[i][j] == B) {
        opponentFound = true;
        i += deltaY;
        j += deltaX;
    }

    
    return opponentFound && i >= 0 && i < 8 && j >= 0 && j < 8 && board[i][j] == A;
}


bool isValidMove(char board[8][8], int X, int Y, char A, char B) {
    
    if (board[Y][X] != ' ') return false; 

    
    return isValidDirection(board, X, Y, -1, 0, A, B) || // Left
           isValidDirection(board, X, Y, 1, 0, A, B) ||  // Right
           isValidDirection(board, X, Y, 0, -1, A, B) || // Up
           isValidDirection(board, X, Y, 0, 1, A, B) ||  // Down
           isValidDirection(board, X, Y, -1, -1, A, B) || // Up-Left Diagonal
           isValidDirection(board, X, Y, 1, -1, A, B) ||  // Up-Right Diagonal
           isValidDirection(board, X, Y, -1, 1, A, B) ||  // Down-Left Diagonal
           isValidDirection(board, X, Y, 1, 1, A, B);     // Down-Right Diagonal
}


void applyMove(char board[8][8], int X, int Y, char A, char B) {
    int i, j;
    board[Y][X] = A;

    
    // Left
    if (isValidDirection(board, X, Y, -1, 0, A, B)) {
        for (j = X - 1; board[Y][j] == B; j--)
            board[Y][j] = A;
    }
    // Right
    if (isValidDirection(board, X, Y, 1, 0, A, B)) {
        for (j = X + 1; board[Y][j] == B; j++)
            board[Y][j] = A;
    }
    // Up
    if (isValidDirection(board, X, Y, 0, -1, A, B)) {
        for (i = Y - 1; board[i][X] == B; i--)
            board[i][X] = A;
    }
    // Down
    if (isValidDirection(board, X, Y, 0, 1, A, B)) {
        for (i = Y + 1; board[i][X] == B; i++)
            board[i][X] = A;
    }
    // Up-Left Diagonal
    if (isValidDirection(board, X, Y, -1, -1, A, B)) {
        i = Y - 1; j = X - 1;
        while (board[i][j] == B)
            board[i--][j--] = A;
    }
    // Up-Right Diagonal
    if (isValidDirection(board, X, Y, 1, -1, A, B)) {
        i = Y - 1; j = X + 1;
        while (board[i][j] == B)
            board[i--][j++] = A;
    }
    // Down-Left Diagonal
    if (isValidDirection(board, X, Y, -1, 1, A, B)) {
        i = Y + 1; j = X - 1;
        while (board[i][j] == B)
            board[i++][j--] = A;
    }
    // Down-Right Diagonal
    if (isValidDirection(board, X, Y, 1, 1, A, B)) {
        i = Y + 1; j = X + 1;
        while (board[i][j] == B)
            board[i++][j++] = A;
    }
}


void markValidMoves(char board[8][8], char A, char B, char validBoard[8][8]) {
    memcpy(validBoard, board, sizeof(char) * 64);

    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (isValidMove(board, j, i, A, B)) {
                int flips = 0;
                
                
                for (int deltaY = -1; deltaY <= 1; deltaY++) {
                    for (int deltaX = -1; deltaX <= 1; deltaX++) {
                        if (deltaY == 0 && deltaX == 0) continue;
                        flips += countFlipsInDirection(board, j, i, deltaX, deltaY, A, B);
                    }
                }
                
                validBoard[i][j] = '0' + flips;
            }
        }
    }
}


int countFlipsInDirection(char board[8][8], int X, int Y, int deltaX, int deltaY, char A, char B) {
    int flips = 0;
    int i = Y + deltaY;
    int j = X + deltaX;

    
    while (i >= 0 && i < 8 && j >= 0 && j < 8 && board[i][j] == B) {
        flips++;
        i += deltaY;
        j += deltaX;
    }

    
    if (i >= 0 && i < 8 && j >= 0 && j < 8 && board[i][j] == A) {
        return flips;
    }

    return 0;
}

void randomMove(char board[8][8], char A, char B) {
    int X, Y;
    while (true) {
        X = rand() % 8;
        Y = rand() % 8;
        if (board[Y][X] == ' ' && isValidMove(board, X, Y, B, A)) {
            applyMove(board, X, Y, B, A);
            break;
        }
    }
}

void mediumMove(char board[8][8], char A, char B) {
    int bestX = -1, bestY = -1, maxFlips = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == ' ' && isValidMove(board, j, i, B, A)) {
                int flips = 0;
                
                for (int deltaY = -1; deltaY <= 1; deltaY++) {
                    for (int deltaX = -1; deltaX <= 1; deltaX++) {
                        if (deltaY == 0 && deltaX == 0) continue;
                        int iTemp = i + deltaY, jTemp = j + deltaX;
                        while (iTemp >= 0 && iTemp < 8 && jTemp >= 0 && jTemp < 8 && board[iTemp][jTemp] == A) {
                            flips++;
                            iTemp += deltaY;
                            jTemp += deltaX;
                        }
                    }
                }
                if (flips > maxFlips) {
                    maxFlips = flips;
                    bestX = j;
                    bestY = i;
                }
            }
        }
    }

    
    if (bestX != -1 && bestY != -1) {
        applyMove(board, bestX, bestY, B, A);
    } else {
        cout << "No valid moves available." << endl;
    }
}


int evaluateBoard(char board[8][8], char A, char B) {
    int score = 0;
    

    int weights[8][8] = {
        {100, -20, 10, 10, 10, 10, -20, 100},
        {-20, -50, 1, 1, 1, 1, -50, -20},
        {10, 1, 5, 5, 5, 5, 1, 10},
        {10, 1, 5, 5, 5, 5, 1, 10},
        {10, 1, 5, 5, 5, 5, 1, 10},
        {10, 1, 5, 5, 5, 5, 1, 10},
        {-20, -50, 1, 1, 1, 1, -50, -20},
        {100, -20, 10, 10, 10, 10, -20, 100}
    };
    
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == A) {
                score += weights[i][j];
            } else if (board[i][j] == B) {
                score -= weights[i][j];
            }
        }
    }
    
    return score;
}



int minimax(char board[8][8], int depth, bool isMaximizing, char A, char B) {
    if (depth == 0 || isBoardFull(board)) {
        return evaluateBoard(board, A, B);
    }

    if (isMaximizing) {
        int maxEval = -1000;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j] == ' ' && isValidMove(board, j, i, A, B)) {
                    char tempBoard[8][8];
                    memcpy(tempBoard, board, sizeof(tempBoard));
                    applyMove(tempBoard, j, i, A, B);
                    int eval = minimax(tempBoard, depth - 1, false, A, B);
                    maxEval = max(maxEval, eval);
                }
            }
        }
        return maxEval;
    } else {
        int minEval = 1000;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j] == ' ' && isValidMove(board, j, i, B, A)) {
                    char tempBoard[8][8];
                    memcpy(tempBoard, board, sizeof(tempBoard));
                    applyMove(tempBoard, j, i, B, A);
                    int eval = minimax(tempBoard, depth - 1, true, A, B);
                    minEval = min(minEval, eval);
                }
            }
        }
        return minEval;
    }
}


void minimaxMove(char board[8][8], char A, char B) {
    int bestX = -1, bestY = -1;
    int bestValue = -1000;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == ' ' && isValidMove(board, j, i, A, B)) {
                char tempBoard[8][8];
                memcpy(tempBoard, board, sizeof(tempBoard));
                applyMove(tempBoard, j, i, A, B);
                int moveValue = minimax(tempBoard, 3, false, A, B); 

                if (moveValue > bestValue) {
                    bestValue = moveValue;
                    bestX = j;
                    bestY = i;
                }
            }
        }
    }

    if (bestX != -1 && bestY != -1) {
        applyMove(board, bestX, bestY, A, B);
    } else {
        cout << "No valid moves available." << endl;
    }
}


bool hasValidMoves(char board[8][8], char player, char opponent) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == ' ' && isValidMove(board, j, i, player, opponent)) {
                return true;
            }
        }
    }
    return false;
}

int countValidMoves(char board[8][8], char player, char opponent) {
    int count = 0;

    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            if (isValidMove(board, x, y, player, opponent)) {
                count++;
            }
        }
    }
    return count;
}


int countTokens(char board[8][8], char token) {
    int count = 0;
    for(int i = 0; i < 8; i++) 
        for(int j = 0; j < 8; j++) 
            if(board[i][j] == token) 
                count++;
    return count;
}

int main() 
{ 
    char p1_sy, p2_sy, pos[2], board[8][8]; 
    int X, Y, mode;

    cout << "\t\t\t\t\t WELCOME TO REVERSI GAME !!!!!!" << "\n\n"; 
    cout << "Enter Your Token Symbol: "; 
    cin >> p1_sy; 
    cout << "Enter Opponent's Token Symbol: "; 
    cin >> p2_sy;
    
    char A = p1_sy, B = p2_sy;
    if(A == B) 
    {
        cout << endl << "\t\t\t\t\t LOL !!! Both symbols are the same. Restarting the game." << endl;
        return main();
    }

    cout << "\t\t\t\tSelect mode : " << endl << "1 for Two Players: " << endl << "2 for Player vs Computer-Random: " << endl << "3 for Player vs Computer-Medium: " << endl << "4 for Player vs Computer-Hard" << endl;
    cin >> mode;

    if(mode > 4){
        cout << " -_- Enter a Mode which is present in the menu!! Restarting the game." << endl; 
        return main();
    }

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        { 
            board[i][j] = ' '; 
        }
    }


    board[3][3] = A; board[3][4] = B; 
    board[4][3] = B; board[4][4] = A;

    while (!isBoardFull(board)) 
    {
        Display(board, A, B, A);

        int validMovesCount_A = countValidMoves(board, A, B);
        if (validMovesCount_A != 0) 
        {
            
            cout << endl << "Your (" << A << ") Turn -_- " << endl;
            cout << "Enter Position: ( Like A1, B6, C3, G7 etc. ) "; 
            cin >> pos;

            if(pos[0] >= 'A' && pos[0] <= 'H') X = pos[0] - 'A';
            else { cout << "\t\t\t\t\tInvalid input. Enter again." << endl; continue; }

            if(pos[1] >= '1' && pos[1] <= '8') Y = pos[1] - '1';
            else { cout << "\t\t\t\t\tInvalid input. Enter again." << endl; continue; }

            if(!isValidMove(board, X, Y, A, B)) 
            {
                cout << "\t\t\t\t\tInvalid move! Enter again." << endl;
                continue;
            }

            applyMove(board, X, Y, A, B);
        }
        else 
        {
            cout << "Your (" << A << ") has no valid moves left. Skipping turn." << endl;
            
        } 
           

        
        int validMovesCount = countValidMoves(board, B, A);
        if (validMovesCount == 0) 
        {
            cout << "Opponent (" << B << ") has no valid moves left. Skipping turn." << endl;
            continue;
        } 
        else 
        {
            
            if (mode == 2) 
            {
                cout << "Computer's (" << B << ") Turn." << endl;
                Display(board, A, B, B);
                randomMove(board, A, B);
            }
            else if (mode == 3)
            {
                cout << "Computer's (" << B << ") Turn." << endl;
                Display(board, A, B, B);
                mediumMove(board, A, B);
            }
            else if (mode == 4) 
            { 
                cout << "Computer's (" << B << ") Turn." << endl;
                Display(board, A, B, B);
                minimaxMove(board, B, A);
            }
            else if (mode == 1)
            {
                while (true) {
                    cout << endl << "Opponent's (" << B << ") Turn -_- " << endl;
                    Display(board, A, B, B);
                    cout << "Enter Position: ( Like A1, B6, C3, G7 etc. ) "; 
                    cin >> pos;

                    if(pos[0] >= 'A' && pos[0] <= 'H') X = pos[0] - 'A';
                    else { cout << "\t\t\t\t\tInvalid input. Enter again." << endl; continue; }

                    if(pos[1] >= '1' && pos[1] <= '8') Y = pos[1] - '1';
                    else { cout << "\t\t\t\t\tInvalid input. Enter again." << endl; continue; }

                    if(!isValidMove(board, X, Y, B, A)) 
                    {
                        cout << "\t\t\t\t\tInvalid move! Enter again." << endl;
                        continue;
                    }

                    applyMove(board, X, Y, B, A);
                    break;
                }
                
            }
        
        }
    }



    Display(board, A, B, B);
    int p1_count = countTokens(board, A);
    int p2_count = countTokens(board, B);
    
    cout << endl << "Final Score - Player 1 (" << A << "): " << p1_count << ", Player 2 (" << B << "): " << p2_count << endl;
    if(p1_count > p2_count)
    {
        cout << "Player 1 Wins!" << endl;
    } 
    else if(p1_count < p2_count)
    {
        cout << "Player 2 Wins!" << endl;
    }
    else
    {
        cout << "It's a Draw!" << endl;
    }
    cout << "\t\t\t\t\tThank You For Playing!!" << endl;
    return 0;
}