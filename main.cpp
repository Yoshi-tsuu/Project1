#include "Chessboard.h"
#include "ChessPiece.h"
#include <iostream>

using namespace std;

int main() {
    system("chcp 1250>>null");
    Chessboard chessboard;
    chessboard.displayBoard();
    int fromRow, fromCol, toRow, toCol;
    do {
        cout << (chessboard.playerTurn ? "Biały" : "Czarny") << ", wybierz bierke (np. A2): ";
        char fromColChar, toColChar;
        chessboard.isKingInCheck();
        cin >> fromColChar >> fromRow;
        fromCol = int(fromColChar) - 65;
        if(chessboard.select(8 - fromRow, fromCol)) {
            chessboard.showMoves(8 - fromRow, fromCol);
            cout << "Możliwe ruchy: " << endl;
            chessboard.displayMoves();
            cout << "Podaj ruch (np. A3): ";
            cin >> toColChar >> toRow;
            toCol = int(toColChar) - 65;
            chessboard.makeMove(8 - fromRow, fromCol, 8 - toRow, toCol);
            chessboard.clear();
            chessboard.displayBoard();
        }
        else {
            cout << "Błędny wybór \n";
        }
    }
    while (chessboard.endGame == false);
    cout << (chessboard.playerTurn ? "Czarny" : "Biały") << " wygrywa!" << endl;
    return 0;
}
