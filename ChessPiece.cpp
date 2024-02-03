#include "ChessPiece.h"

using namespace std;

King::King(char a)
{
    color = a;
}

char King::getSymbol()
{
    return 'K';
}

bool King::isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol)
{
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    // Król mo¿e przesun¹æ siê o jedno pole w ka¿dym kierunku
    if ((rowDiff <= 1) && (colDiff <= 1)) {
        // SprawdŸ, czy na docelowym polu nie ma w³asnej figury lub jest figura przeciwnika
        if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() != playerSymbol){
            return true; // Ruch jest dozwolony
        }
    }
    return false; // Ruch jest nieprawid³owy
}

Queen::Queen(char a)
{
    color = a;
}

char Queen::getSymbol()
{
    return 'Q';
}
bool Queen::isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) {
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    // Królowa mo¿e przesuwaæ siê w pionie, poziomie lub na ukos
    if ((rowDiff == 0 && colDiff > 0) || (rowDiff > 0 && colDiff == 0) || (rowDiff == colDiff)) {
        // SprawdŸ, czy na docelowym polu nie ma w³asnej figury
        if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() != playerSymbol){
            return true; // Ruch jest dozwolony
        }
    }
    return false; // Ruch jest nieprawid³owy
}

Pawn::Pawn(char a)
{
    color = a;
}

char Pawn::getSymbol()
{
    return 'P';
}

bool Pawn::isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) 
{
    // SprawdŸ, czy ruch jest o jedno pole do przodu
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);

    if (rowDiff > 1 || colDiff > 1) 
    {
        return false; // Ruch nie jest o jedno pole do przodu lub na ukos
    }
    // SprawdŸ, czy nie ma innych figurek na drodze
    if (board[toRow][toCol] != nullptr) 
    {
        return false; // Jest figura na docelowym polu
    }
    // Ruch jest poprawny

    return true;
}


Knight::Knight(char a)
{
    color = a;
}

char Knight::getSymbol()
{
    return 'S';
}

bool Knight::isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) {
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    // Skoczek mo¿e przesuwaæ siê o 2 pola w jednym kierunku i 1 pole w drugim kierunku
    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
        // SprawdŸ, czy na docelowym polu nie ma w³asnej figury
        if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() != playerSymbol){
            return true; // Ruch jest dozwolony
        }
    }
    return false; // Ruch jest nieprawid³owy
}

Tower::Tower(char a)
{
    color = a;
}

char Tower::getSymbol()
{
    return 'T';
}

bool Tower::isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) {
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    // Wie¿a mo¿e przesuwaæ siê w pionie lub poziomie
    if ((rowDiff == 0 && colDiff > 0) || (rowDiff > 0 && colDiff == 0)) {
        // SprawdŸ, czy na docelowym polu nie ma w³asnej figury
        if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() != playerSymbol){
            return true; // Ruch jest dozwolony
        }
    }
    return false; // Ruch jest nieprawid³owy
}

Bishop::Bishop(char a)
{
    color = a;
}

char Bishop::getSymbol()
{
    return 'G';
}

bool Bishop::isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) {
    // SprawdŸ, czy ruch jest diagonalny
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    if (rowDiff != colDiff) {
        return false; // Ruch nie jest diagonalny
    }
    // SprawdŸ, czy nie ma innych figurek na drodze
    int rowDirection = (toRow > fromRow) ? 1 : -1;
    int colDirection = (toCol > fromCol) ? 1 : -1;
    int row = fromRow + rowDirection;
    int col = fromCol + colDirection;
    while (row != toRow) {
        if (board[row][col] != nullptr) {
            return false; // Jest figura na drodze
        }
        row += rowDirection;
        col += colDirection;
    }
    // Ruch jest poprawny
    return true;
}

char ChessPiece::getColor()
{
    return color;
}
