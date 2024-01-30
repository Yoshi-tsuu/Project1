#include "Chessboard.h"
#include "ChessPiece.h"
#include <iostream>
using namespace std;

Chessboard::Chessboard() {
    board.resize(8, vector<ChessPiece*>(8, nullptr));
    initializeBoard();
    playerTurn = true;
}

void Chessboard::initializeBoard() {
    initializeWhitePieces();
    initializeBlackPieces();
}

void Chessboard::initializeWhitePieces() {
    board[7][4] = new King;
    board[7][3] = new Queen;
    board[7][2] = new Bishop;
    board[7][5] = new Bishop;
    board[7][6] = new Knight;
    board[7][1] = new Knight;
    board[7][7] = new Rook;
    board[7][0] = new Rook;
    for (int col = 0; col < 8; col++) {
        board[6][col] = new Pawn;
    }
}

void Chessboard::initializeBlackPieces() {
    board[0][4] = new King;
    board[0][3] = new Queen;
    board[0][2] = new Bishop;
    board[0][5] = new Bishop;
    board[0][6] = new Knight;
    board[0][1] = new Knight;
    board[0][7] = new Rook;
    board[0][0] = new Rook;
    for (int col = 0; col < 8; col++) {
        board[1][col] = new Pawn;
    }
}

void Chessboard::displayBoard() {
    cout << "   A B C D E F G H" << endl;
    for (int row = 0; row < 8; ++row) {
        cout << 8 - row << "  ";
        for (int col = 0; col < 8; ++col) {
            if (board[row][col]) {
                cout << board[row][col]->getSymbol() << " ";
            } else {
                cout << ". ";
            }
        }
        cout << 8 - row << endl;
    }
    cout << "   A B C D E F G H" << endl;
}

bool Chessboard::isValidMove(int fromRow, int fromCol, int toRow, int toCol) {
    ChessPiece* piece = board[fromRow][fromCol];
    if (piece == nullptr) {
        return false; // Brak figury na starcie
    }
    char playerSymbol = playerTurn ? 'w' : 'b';
    // Sprawdź, czy to jest ruch gracza na jego turze
    if ((islower(piece->getSymbol()) && playerSymbol == 'w') ||
        (isupper(piece->getSymbol()) && playerSymbol == 'b')) {
        int rowDiff = abs(toRow - fromRow);
        int colDiff = abs(toCol - fromCol);
        // Sprawdź, czy docelowe pole nie jest poza planszą
        if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
            return false; // Pole docelowe jest poza planszą
        }
        // Sprawdź, czy ruch jest dozwolony zgodnie z zasadami konkretnej figury
        if (!piece->isValidMove(fromRow, fromCol, toRow, toCol, board, playerSymbol)) {
            return false; // Ruch nie jest dozwolony
        }
        // Sprawdź, czy na docelowym polu nie ma własnej figury
	    ChessPiece* targetPiece = board[toRow][toCol];
        if (targetPiece != nullptr &&
            ((targetPiece->getSymbol() && playerSymbol == 'w') ||
             (targetPiece->getSymbol() && playerSymbol == 'b'))) {
            return false; // Na docelowym polu jest własna figura
        }
        return true; // Ruch jest dozwolony
    }
    return false; // To nie jest tura gracza
}

void Chessboard::makeMove(int fromRow, int fromCol, int toRow, int toCol) {
    if (board[fromRow][fromCol] == nullptr) {
        cout << "Błąd: brak figury na pozycji początkowej." << endl;
        return;
    }

    ChessPiece* targetPiece = board[toRow][toCol];
    if (targetPiece != nullptr &&
        ((islower(targetPiece->getSymbol()) && playerTurn) ||
        (isupper(targetPiece->getSymbol()) && !playerTurn))) {
        cout << "Błąd: Nieprawidłowy ruch." << endl;
        return;
    }

    if (fromRow == toRow && fromCol == toCol) {
        cout << "Błąd: Nieprawidłowy ruch. Figura musi się przemieszczać." << endl;
        return;
    }

    if (!isValidMove(fromRow, fromCol, toRow, toCol)) {
        cout << "Błąd: Nieprawidłowy ruch." << endl;
        return;
    }

    if (targetPiece != nullptr) {
        delete targetPiece; // Zwolnij pamięć przed nadpisaniem
    }

    board[toRow][toCol] = board[fromRow][fromCol];
    board[fromRow][fromCol] = nullptr;
    playerTurn = !playerTurn; // Zmiana tury po udanym ruchu
}

bool Chessboard::isCheckmate(bool isWhiteKingInCheck) {
    // Pobierz aktualną sytuację na planszy
    vector<vector<ChessPiece*>>& currentBoard = board;
    // Przeszukaj planszę w poszukiwaniu króla gracza, którego jest teraz tura
    char kingSymbol = isWhiteKingInCheck ? 'K' : 'k';
    int kingRow = -1;
    int kingCol = -1;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board[row][col] != nullptr && currentBoard[row][col]->getSymbol() == kingSymbol) {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
        if (kingRow != -1) {
            break;
        }
    }
    // Sprawdź, czy król jest szachowany
    if (isKingInCheck(kingRow, kingCol)) {
        // Sprawdź, czy król ma dostęp do jakichkolwiek pól
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                if (isValidMove(kingRow, kingCol, row, col) && !isKingInCheck(row, col)) {
                    return false; // Król ma dostęp do co najmniej jednego pola
                }
            }
        }
        // Jeśli król nie ma dostępu do żadnego pola, to jest szach-mat
        return true;
    }
    return false; // Król nie jest szachowany
}

bool Chessboard::isKingInCheck(int kingRow, int kingCol) const {
    // Przeszukaj planszę w poszukiwaniu możliwych ruchów przeciwnych figur
    char opponentKingSymbol = (playerTurn) ? 'k' : 'K';
    char playerSymbol = (playerTurn) ? 'w' : 'b';
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board[row][col] != nullptr) {
                // Jeśli figura przeciwnika, sprawdź, czy może zaatakować króla
                if (((playerTurn && islower(board[row][col]->getSymbol())) ||
                     (!playerTurn && isupper(board[row][col]->getSymbol()))) &&
                    board[row][col]->isValidMove(row, col, kingRow, kingCol, board, playerSymbol)) {
                    return true; // Król jest szachowany
                }
            }
        }
    }
    return false; // Król nie jest szachowany
}

Chessboard::~Chessboard() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            delete board[row][col];
        }
    }
}
