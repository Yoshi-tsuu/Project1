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
    // Kr�l mo�e przesun�� si� o jedno pole w ka�dym kierunku
    if ((rowDiff <= 1) && (colDiff <= 1)) {
        // Sprawd�, czy na docelowym polu nie ma w�asnej figury lub jest figura przeciwnika
        if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() != playerSymbol){
            return true; // Ruch jest dozwolony
        }
    }
    return false; // Ruch jest nieprawid�owy
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
    // Kr�lowa mo�e przesuwa� si� w pionie, poziomie lub na ukos
    if ((rowDiff == 0 && colDiff > 0) || (rowDiff > 0 && colDiff == 0) || (rowDiff == colDiff)) {
        // Sprawd�, czy na docelowym polu nie ma w�asnej figury
        if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() != playerSymbol){
            return true; // Ruch jest dozwolony
        }
    }
    return false; // Ruch jest nieprawid�owy
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
    // Sprawd�, czy ruch jest o jedno pole do przodu
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);

    if (rowDiff > 1 || colDiff > 1) 
    {
        return false; // Ruch nie jest o jedno pole do przodu lub na ukos
    }
    // Sprawd�, czy nie ma innych figurek na drodze
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
    // Skoczek mo�e przesuwa� si� o 2 pola w jednym kierunku i 1 pole w drugim kierunku
    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
        // Sprawd�, czy na docelowym polu nie ma w�asnej figury
        if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() != playerSymbol){
            return true; // Ruch jest dozwolony
        }
    }
    return false; // Ruch jest nieprawid�owy
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
    // Wie�a mo�e przesuwa� si� w pionie lub poziomie
    if ((rowDiff == 0 && colDiff > 0) || (rowDiff > 0 && colDiff == 0)) {
        // Sprawd�, czy na docelowym polu nie ma w�asnej figury
        if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() != playerSymbol){
            return true; // Ruch jest dozwolony
        }
    }
    return false; // Ruch jest nieprawid�owy
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
    // Sprawd�, czy ruch jest diagonalny
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    if (rowDiff != colDiff) {
        return false; // Ruch nie jest diagonalny
    }
    // Sprawd�, czy nie ma innych figurek na drodze
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
