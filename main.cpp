#include "ChessBoard.h"
#include <iostream>

using namespace std;

int main() {
    Chessboard chessboard;
    chessboard.displayBoard();
    int fromRow, fromCol, toRow, toCol;
    do {
        chessboard.startTurn();
        chessboard.isKingInCheck();
        fromCol = chessboard.getColFromPlayer();
        fromRow = chessboard.getRowFromPlayer();
        if(chessboard.select(8 - fromRow, fromCol)){
            chessboard.showMoves(8 - fromRow, fromCol);
            chessboard.displayMessage("Możliwe ruchy: \n");
            chessboard.displayMoves();
            chessboard.displayMessage("Podaj ruch (np. A3): ");
            toCol = chessboard.getColFromPlayer();
            toRow = chessboard.getRowFromPlayer();
            chessboard.makeMove(8 - fromRow, fromCol, 8 - toRow, toCol);
            chessboard.clear();
            chessboard.displayBoard();
        }
        else
            chessboard.invalidMove();
    } while (chessboard.endGame == false);
    chessboard.gameEnd();
    return 0;
}
