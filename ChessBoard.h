#pragma once

#include "ChessPiece.h"

using namespace std;

struct Coord {
    Coord(float x, float y) : row(x), col(y) {};
    float row;
    float col;
};

class Chessboard {
public:
    vector<vector<ChessPiece*>> board; // tablica zawierajaca plansze
    vector<Coord> coords; // tablica zawierajaca mozliwe ruchy
    bool playerTurn;
    bool endGame = false;
    Chessboard(); // konstruktor
    void initializeBoard(); // inicjalizacja
    void initializeWhitePieces(); // inicjalizcja białych pionków
    void initializeBlackPieces(); // inicjalizcja czarnych pionków
    void displayBoard(); // wyświetlanie planszy oraz aktualnych pionków
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol); // sprawdzanie ruchu dla konkretnej figury
    bool select(int fromRow, int fromCol); // podświetlenie wybranego pionka
    void showMoves(int fromRow, int fromCol); // generowanie możliwych ruchów dla figur
    void displayMoves(); // wiświtlanie możliwych ruchów figur
    void makeMove(int fromRow, int fromCol, int toRow, int toCol); // zmiana pozycji pionka
    void clear(); // czysczenie zaznaczenia
    bool isKingInCheck(); // sprawdzanie czy któryś z królów jest w szachu
    ~Chessboard(); // destruktor
};
