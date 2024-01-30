#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <iostream>
#include <vector>
using namespace std;

class ChessPiece {
public:
    virtual char getSymbol() const = 0;
    virtual bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) const = 0;
    virtual ~ChessPiece() {}
};

class King : public ChessPiece {
public:
    char getSymbol() const override { return 'K'; }
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) const override;
};

class Queen : public ChessPiece {
public:
    char getSymbol() const override { return 'Q'; }
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) const override;
};

class Bishop : public ChessPiece {
public:
    char getSymbol() const override { return 'B'; }
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) const override;
};

class Knight : public ChessPiece {
public:
    char getSymbol() const override { return 'N'; }
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) const override;
};

class Rook : public ChessPiece {
public:
    char getSymbol() const override { return 'R'; }
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) const override;
};

class Pawn : public ChessPiece {
public:
    char getSymbol() const override { return 'P'; }
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) const override;
};

#endif
