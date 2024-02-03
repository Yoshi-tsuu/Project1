#pragma once

#include "ChessPiece.h"

using namespace std;

class Chessboard {
public:
    vector<vector<ChessPiece*>> board;
    bool playerTurn;

    Chessboard();
    void initializeBoard();
    void initializeWhitePieces();
    void initializeBlackPieces();
    void displayBoard();
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol);
    void makeMove(int fromRow, int fromCol, int toRow, int toCol);
    bool isCheckmate(bool isWhiteKingInCheck);
    bool isKingInCheck(int kingRow, int kingCol) const;
    ~Chessboard();
};

