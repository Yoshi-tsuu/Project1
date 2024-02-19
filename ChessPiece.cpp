#include "ChessPiece.h"

using namespace std;

King::King(char a) {
    color = a;
}

char King::getSymbol() {
    return 'K';
}

bool King::isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) {
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    // Król może przesunąć się o jedno pole w każdym kierunku
    if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() != playerSymbol) { //bicie
        return true;
    }
    if (playerSymbol == 'w') {
        if (toRow == 7 and toCol == 7) {
            if (board[7][6] == nullptr and board[7][5] == nullptr and board[fromRow][fromCol]->firstMove == true and board[toRow][toCol] != nullptr and board[toRow][toCol]->getSymbol() == 'T') {
                return true;
            }
        }
        if (toRow == 7 and toCol == 0) {
            if (board[7][1] == nullptr and board[7][2] == nullptr and board[7][3] == nullptr and board[fromRow][fromCol]->firstMove == true and board[toRow][toCol] != nullptr and board[toRow][toCol]->getSymbol() == 'T') {
                return true;
            }
        }
    }
    if (playerSymbol == 'b') {
        if (toRow == 0 and toCol == 7) {
            if (board[0][6] == nullptr and board[0][5] == nullptr and board[fromRow][fromCol]->firstMove == true and board[toRow][toCol] != nullptr and board[toRow][toCol]->getSymbol() == 'T') {
                return true;
            }
        }
        if (toRow == 0 and toCol == 0) {
            if (board[0][1] == nullptr and board[0][2] == nullptr and board[0][3] == nullptr and board[fromRow][fromCol]->firstMove == true and board[toRow][toCol] != nullptr and board[toRow][toCol]->getSymbol() == 'T') {
                return true;
            }
        }
    }
    if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() == playerSymbol) {
        return false;
    }
    if (board[toRow][toCol] == nullptr) {
        return true;
    }
    return false; // Ruch jest nieprawidłowy
}

Queen::Queen(char a) {
    color = a;
}

char Queen::getSymbol() {
    return 'Q';
}

bool Queen::isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) {
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    // Królowa może przesuwać się w pionie, poziomie lub na ukos
    if ((rowDiff == 0 && colDiff > 0) || (rowDiff > 0 && colDiff == 0) || (rowDiff == colDiff)) {
        if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() != playerSymbol) { //bicie
            return true;
        }
        else if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() == playerSymbol) {
            return false;
        }
        else if (board[toRow][toCol] == nullptr) {
            return true;
        }
    }
    return false; // Ruch jest nieprawidłowy
}

Pawn::Pawn(char a) {
    color = a;
}

char Pawn::getSymbol() {
    return 'P';
}

bool Pawn::isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) {
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    // Sprawdź, czy ruch jest o jedno pole do przodu
    if (playerSymbol == 'w' and toRow - fromRow >= 0)
        return false;
    if (playerSymbol == 'b' and toRow - fromRow <= 0)
        return false;
    if (playerSymbol == 'w') {
        if (colDiff == 0 and ((rowDiff == 1 and board[toRow][toCol] == nullptr) or (rowDiff == 2 and board[fromRow][fromCol]->firstMove == true and board[toRow][toCol] == nullptr)))
            return true; // Ruch jest o jedno pole do przodu lub na ukos
        if(colDiff == 1 and rowDiff == 1)
            if (board[toRow][toCol] != nullptr)
                if (char c = board[toRow][toCol]->getColor() == 'b') { //bicie
                    return true;
                }
        if(colDiff == 1 and rowDiff == 1)
            if(board[toRow][toCol] != nullptr)
                if(char c = board[toRow][toCol]->getColor() == 'b') { //bicie
                    return true;
                }
    }
    else {
        if (colDiff == 0 and ((rowDiff == 1 and board[toRow][toCol] == nullptr) or (rowDiff == 2 and board[fromRow][fromCol]->firstMove == true and board[toRow][toCol] == nullptr)))
            return true; // Ruch jest o jedno pole do przodu lub na ukos
        if (colDiff == 1 and rowDiff == 1)
            if (board[toRow][toCol] != nullptr)
                if (char c = board[toRow][toCol]->getColor() == 'w') { //bicie
                    return true;
                }
        if (colDiff == 1 and rowDiff == 1)
            if (board[toRow][toCol] != nullptr)
                if (char c = board[toRow][toCol]->getColor() == 'w') { //bicie
                    return true;
                }
    }
    return false;
}

Knight::Knight(char a) {
    color = a;
}

char Knight::getSymbol() {
    return 'S';
}

bool Knight::isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) {
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    // Skoczek może przesuwać się o 2 pola w jednym kierunku i 1 pole w drugim kierunku
    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
        if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() != playerSymbol) { //bicie
            return true;
        }
        else if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() == playerSymbol) {
            return false;
        }
        else if (board[toRow][toCol] == nullptr) {
            return true;
        }
    }
    return false; // Ruch jest nieprawidłowy
}

Tower::Tower(char a) {
    color = a;
}

char Tower::getSymbol() {
    return 'T';
}

bool Tower::isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) {
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    // Wieża może przesuwać się w pionie lub poziomie
    if ((rowDiff == 0 && colDiff > 0) || (rowDiff > 0 && colDiff == 0)) {
        if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() != playerSymbol) {
            return true; // Ruch jest dozwolony
        }
        else if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() == playerSymbol) {
            return false;
        }
        else if (board[toRow][toCol] == nullptr) {
            return true;
        }
    }
    return false; // Ruch jest nieprawidłowy
}

Bishop::Bishop(char a) {
    color = a;
}

char Bishop::getSymbol() {
    return 'G';
}

bool Bishop::isValidMove(int fromRow, int fromCol, int toRow, int toCol, const vector<vector<ChessPiece*>>& board, char playerSymbol) {
    // Sprawdź, czy ruch jest diagonalny
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    if (rowDiff != colDiff) {
        return false; // Ruch nie jest diagonalny
    }
    if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() != playerSymbol) {
        return true; // Ruch jest dozwolony
    }
    else if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() == playerSymbol) {
        return false;
    }
    else if (board[toRow][toCol] == nullptr) {
        return true;
    }
    return true;
}

char ChessPiece::getColor() {
    return color;
}
