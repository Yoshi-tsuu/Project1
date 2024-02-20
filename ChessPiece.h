#pragma once

#include <iostream>
#include <vector>

using namespace std;

class ChessPiece {
public:
    virtual char getSymbol() = 0;
    char getColor();
    virtual bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) = 0;
    char color;
    bool marked = false;
    bool firstMove = true;
};

class King : public ChessPiece {
public:
    King(char a);
    char getSymbol();
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol);
};

class Queen : public ChessPiece {
public:
    Queen(char a);
    char getSymbol();
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol);
};

class Bishop : public ChessPiece {
public:
    Bishop(char a);
    char getSymbol();
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol);
};

class Knight : public ChessPiece {
public:
    Knight(char a);
    char getSymbol();
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol);
};

class Tower : public ChessPiece {
public:
    Tower(char a);
    char getSymbol();
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol);
};

class Pawn : public ChessPiece {
public:
    Pawn(char a);
    char getSymbol();
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol);
};
