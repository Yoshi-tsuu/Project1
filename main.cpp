#include "Chessboard.h"
#include "ChessPiece.h"
#include <iostream>

using namespace std;

int main() {
    Chessboard chessboard;
    chessboard.displayBoard();

    int fromRow, fromCol, toRow, toCol;

    do {
        cout << (chessboard.playerTurn ? "Biały" : "Czarny") << ", podaj ruch (np. A2 A4): ";
        char fromColChar, toColChar;
        cin >> fromColChar >> fromRow >> toColChar >> toRow;


        fromCol = int(fromColChar) - 65;
        toCol = int(toColChar) - 65;


        chessboard.makeMove(8 - fromRow, fromCol, 8 - toRow, toCol);
        chessboard.displayBoard();

    } while (!chessboard.isCheckmate(chessboard.playerTurn));

    cout << (chessboard.playerTurn ? "Czarny" : "Biały") << " wygrywa!" << endl;

    return 0;
}
