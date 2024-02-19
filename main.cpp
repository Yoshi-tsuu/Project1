#include "Chessboard.h"
#include "ChessPiece.h"
#include <iostream>

using namespace std;

int main() {
    system("chcp 1250>>null");
    Chessboard chessboard;
    chessboard.displayBoard();
    int fromRow, fromCol{}, toRow, toCol;
    do {
        chessboard.startTurn();
        char fromColChar, toColChar;
        chessboard.isKingInCheck();
        cin >> fromColChar >> fromRow;
        if (fromColChar > 64 and fromColChar < 73)
            fromCol = int(fromColChar) - 65;
        else if (fromColChar > 96 and fromColChar < 105)
            fromCol = int(fromColChar) - 97;
        if(chessboard.select(8 - fromRow, fromCol)) {
            chessboard.showMoves(8 - fromRow, fromCol);
            chessboard.displayMessage("Możliwe ruchy: \n");
            chessboard.displayMoves();
            chessboard.displayMessage("Podaj ruch (np. A3): ");
            cin >> toColChar >> toRow;
            toCol = 0;
            if (toColChar > 64 and toColChar < 73)
                toCol = int(toColChar) - 65;
            else if (toColChar > 96 and toColChar < 105)
                toCol = int(toColChar) - 97;
            chessboard.makeMove(8 - fromRow, fromCol, 8 - toRow, toCol);
            chessboard.clear();
            chessboard.displayBoard();
        }
        else {
            chessboard.displayMessage("Błędny wybór \n");
        }
    } while (chessboard.endGame == false);
    chessboard.gameEnd();
    return 0;
}
