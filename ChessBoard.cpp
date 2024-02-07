#include "Chessboard.h"

using namespace std;

Chessboard::Chessboard() {
    board.resize(8, vector<ChessPiece*>(8, nullptr));
    initializeBoard();
    playerTurn = true;
}

void Chessboard::initializeBoard() {
    initializeWhitePieces();
    initializeBlackPieces();
    for (int i = 0; i < 8; i++)
        cout << board[6][i]->getSymbol() << endl;
    cout << board[7][4]->getSymbol() << endl;
    cout << board[7][2]->getSymbol() << endl;
}

void Chessboard::initializeWhitePieces() {
    board[7][4] = new King('w');
    board[7][3] = new Queen('w');
    board[7][2] = new Bishop('w');
    board[7][5] = new Bishop('w');
    board[7][6] = new Knight('w');
    board[7][1] = new Knight('w');
    board[7][7] = new Tower('w');
    board[7][0] = new Tower('w');
    for (int col = 0; col < 8; col++) {
        board[6][col] = new Pawn('w');
    }
}

void Chessboard::initializeBlackPieces() {
    board[0][4] = new King('b');
    board[0][3] = new Queen('b');
    board[0][2] = new Bishop('b');
    board[0][5] = new Bishop('b');
    board[0][6] = new Knight('b');
    board[0][1] = new Knight('b');
    board[0][7] = new Tower('b');
    board[0][0] = new Tower('b');
    for (int col = 0; col < 8; col++) {
        board[1][col] = new Pawn('b');
    }
}

void Chessboard::displayBoard() {
    system("cls");
    cout << "   A B C D E F G H" << endl;
    for (int row = 0; row < 8; ++row) {
        cout << 8 - row << "  ";
        for (int col = 0; col < 8; ++col) {
            if (board[row][col]) {
                if (board[row][col]->getColor() == 'w' and board[row][col]->marked != true)
                    cout << "\033[1;37m" << board[row][col]->getSymbol() << "\033[0m "; 
                if (board[row][col]->getColor() == 'b' and board[row][col]->marked != true)
                    cout << "\033[1;30m" << board[row][col]->getSymbol() << "\033[0m ";
                if (board[row][col]->marked == true)
                    cout << "\033[1;32m" << board[row][col]->getSymbol() << "\033[0m ";
            } 
            else {
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
    if (playerSymbol != piece->getColor())
        return false;
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    // Sprawdź, czy docelowe pole nie jest poza planszą
    if (toRow < 0 || toRow > 7 || toCol < 0 || toCol > 7) {
        return false; // Pole docelowe jest poza planszą
    }
    // Sprawdź, czy ruch jest dozwolony zgodnie z zasadami konkretnej figury
    if (!piece->isValidMove(fromRow, fromCol, toRow, toCol, board, playerSymbol)) {
        return false; // Ruch nie jest dozwolony
    }
    return true; // Ruch jest dozwolony
}

bool Chessboard::select(int fromRow, int fromCol) {
    if (board[fromRow][fromCol] == nullptr) {
        cout << "Błąd: brak figury na pozycji początkowej." << endl;
        return false;
    }
    char playerSymbol = playerTurn ? 'w' : 'b';
    if (playerSymbol != board[fromRow][fromCol]->getColor())
        return false;
    board[fromRow][fromCol]->marked = true; // zmarkuj figure do podświetlenia
    displayBoard();
    return true;
}

void Chessboard::showMoves(int fromRow, int fromCol)    // row - cyfra 
                                                        // col - symbol
{
    char playerSymbol = (playerTurn) ? 'w' : 'b';
    char foo = board[fromRow][fromCol]->getSymbol();
    switch (foo) {
        case 'P': //skanowanie pola przed pionkiem (z rozroznieniem białego od czarnego)
            if (playerTurn == true) {
                for (int i = 2; i >= 1; i--)
                    for (int j = 1; j >= -1; j--) {
                        if (isValidMove(fromRow, fromCol, fromRow - i, fromCol + j)) {
                            coords.push_back(Coord(fromRow - i, fromCol + j));
                        }
                    }   
            }
            else {
                for (int i = 2; i >= 1; i--)
                    for (int j = 1; j >= -1; j--) {
                        if (isValidMove(fromRow, fromCol, fromRow + i, fromCol + j)) {
                            coords.push_back(Coord(fromRow + i, fromCol + j));
                        }
                    }
            }
            break;
        case 'S': //sknaowanie pól skoczka
            for (int i = -2; i < 3; i++)
                for (int j = -2; j < 3; j++)
                    if (isValidMove(fromRow, fromCol, fromRow + i, fromCol + j)) {
                        coords.push_back(Coord(fromRow + i, fromCol + j));
                    }
            break;
        case 'T': // skanowanie pól w lew, góra, dól, prawo (zaczynamy od pierwszej pozycji od wiezy po czym idziemy dalej, w momencie wystapienia figur, break petli)
            for (int i = 1; i < 8; i++) {
                if (isValidMove(fromRow, fromCol, fromRow + i, fromCol)) {
                    coords.push_back(Coord(fromRow + i, fromCol));
                    if (board[fromRow + i][fromCol] != nullptr && board[fromRow + i][fromCol]->getColor() != playerSymbol)
                        break;
                }
                else
                    break;
            }
            for (int i = -1; i > -8; i--) {
                if (isValidMove(fromRow, fromCol, fromRow + i, fromCol)) {
                    coords.push_back(Coord(fromRow + i, fromCol));
                    if (board[fromRow + i][fromCol] != nullptr && board[fromRow + i][fromCol]->getColor() != playerSymbol)
                        break;
                }
                else
                    break;
            }
            for (int i = 1; i < 8; i++) {
                if (isValidMove(fromRow, fromCol, fromRow, fromCol + i)) {
                    coords.push_back(Coord(fromRow, fromCol + i));
    
                    if (board[fromRow][fromCol + i] != nullptr && board[fromRow][fromCol + i]->getColor() != playerSymbol)
                        break;
                }
                else
                    break;
            }
            for (int i = -1; i > -8; i--) {
                if (isValidMove(fromRow, fromCol, fromRow, fromCol + i)) {
                    coords.push_back(Coord(fromRow, fromCol + i));
                    if (board[fromRow][fromCol + i] != nullptr && board[fromRow][fromCol + i]->getColor() != playerSymbol)
                        break;
                }
                else
                    break;
            }
            break;
        case 'G': // skanowanie diaganoalne, zasada ta samo co dla wiezy
            for (int i = 1; i < 8; i++) {
                if (isValidMove(fromRow, fromCol, fromRow + i, fromCol + i)) {
                    coords.push_back(Coord(fromRow + i, fromCol + i));
                    if (board[fromRow + i][fromCol + i] != nullptr && board[fromRow + i][fromCol + i]->getColor() != playerSymbol)
                        break;
                }
                else
                    break;
            }
            for (int i = -1; i > -8; i--) {
                if (isValidMove(fromRow, fromCol, fromRow + i, fromCol + i)) {
                    coords.push_back(Coord(fromRow + i, fromCol + i));
                    if (board[fromRow + i][fromCol + i] != nullptr && board[fromRow + i][fromCol + i]->getColor() != playerSymbol)
                        break;
                }
                else
                    break;
            }
            for (int i = 1; i < 8; i++) {
                if (isValidMove(fromRow, fromCol, fromRow + i, fromCol - i)) {
                    coords.push_back(Coord(fromRow + i, fromCol - i));
                    if (board[fromRow + i][fromCol - i] != nullptr && board[fromRow + i][fromCol - i]->getColor() != playerSymbol)
                        break;
                }
                else
                    break;
            }
            for (int i = -1; i > -8; i--) {
                if (isValidMove(fromRow, fromCol, fromRow + i, fromCol - i)) {
                    coords.push_back(Coord(fromRow + i, fromCol - i));
                    if (board[fromRow + i][fromCol - i] != nullptr && board[fromRow + i][fromCol - i]->getColor() != playerSymbol)
                        break;
                }
                else
                    break;
            }
            break;
        case 'Q': // polaczeni gonca i wiezy
            for (int i = 1; i < 8; i++) {
                if (isValidMove(fromRow, fromCol, fromRow + i, fromCol)) {
                    coords.push_back(Coord(fromRow + i, fromCol));
                    if (board[fromRow + i][fromCol] != nullptr && board[fromRow + i][fromCol]->getColor() != playerSymbol)
                        break;
                }
                else
                    break;
            }
            for (int i = -1; i > -8; i--) {
                if (isValidMove(fromRow, fromCol, fromRow + i, fromCol)) {
                    coords.push_back(Coord(fromRow + i, fromCol));
                    if (board[fromRow + i][fromCol] != nullptr && board[fromRow + i][fromCol]->getColor() != playerSymbol)
                        break;
                }
                else
                    break;
            }
            for (int i = 1; i < 8; i++) {
                if (isValidMove(fromRow, fromCol, fromRow, fromCol + i)) {
                    coords.push_back(Coord(fromRow, fromCol + i));
                    if (board[fromRow][fromCol + i] != nullptr && board[fromRow][fromCol + i]->getColor() != playerSymbol)
                        break;
                }
                else
                    break;
            }
            for (int i = -1; i > -8; i--) {
                if (isValidMove(fromRow, fromCol, fromRow, fromCol + i)) {
                    coords.push_back(Coord(fromRow, fromCol + i));
                    if (board[fromRow][fromCol + i] != nullptr && board[fromRow][fromCol + i]->getColor() != playerSymbol)
                        break;
                }
                else
                    break;
            }
            for (int i = 1; i < 8; i++) {
                if (isValidMove(fromRow, fromCol, fromRow + i, fromCol + i)) {
                    coords.push_back(Coord(fromRow + i, fromCol + i));
                    if (board[fromRow + i][fromCol + i] != nullptr && board[fromRow + i][fromCol + i]->getColor() != playerSymbol)
                        break;
                }
                else
                    break;
            }
            for (int i = -1; i > -8; i--) {
                if (isValidMove(fromRow, fromCol, fromRow + i, fromCol + i)) {
                    coords.push_back(Coord(fromRow + i, fromCol + i));
                    if (board[fromRow + i][fromCol + i] != nullptr && board[fromRow + i][fromCol + i]->getColor() != playerSymbol)
                        break;
                }
                else
                    break;
            }
            for (int i = 1; i < 8; i++) {
                if (isValidMove(fromRow, fromCol, fromRow + i, fromCol - i)) {
                    coords.push_back(Coord(fromRow + i, fromCol - i));
                    if (board[fromRow + i][fromCol - i] != nullptr && board[fromRow + i][fromCol - i]->getColor() != playerSymbol)
                        break;
                }
                else
                    break;
            }
            for (int i = -1; i > -8; i--) {
                if (isValidMove(fromRow, fromCol, fromRow + i, fromCol - i)) {
                    coords.push_back(Coord(fromRow + i, fromCol - i));
    
                    if (board[fromRow + i][fromCol - i] != nullptr && board[fromRow + i][fromCol - i]->getColor() != playerSymbol)
                        break;
                }
                else
                    break;
            }
            break;
        case 'K': // skanowanie pol dookola krola oraz sprawdznie warunkow roszady
            for (int i = 1; i > -2; i--)
                for(int j = 1; j > -2; j--)
                    if(!(i == 0 and j == 0))
                        if (isValidMove(fromRow, fromCol, fromRow + i, fromCol + j)) {
                            coords.push_back(Coord(fromRow + i, fromCol + j));
                        }
            if(board[fromRow][fromCol]->firstMove == true) {
                if(board[fromRow][fromCol]->getColor() == 'w') {
                    if (isValidMove(fromRow, fromCol, 7, 7)) {
                        coords.push_back(Coord(7, 7));
                    }
                    if (isValidMove(fromRow, fromCol, 7, 0)) {
                        coords.push_back(Coord(7, 0));
                    }
                }
                if (board[fromRow][fromCol]->getColor() == 'b') {
                    if (isValidMove(fromRow, fromCol, 0, 0)) {
                        coords.push_back(Coord(0, 0));
                    }
                    if (isValidMove(fromRow, fromCol, 0, 7)) {
                        coords.push_back(Coord(0, 7));
                    }
                }
            }
        default:
            break;
    }
}

void Chessboard::displayMoves() {
    char playerSymbol = (playerTurn) ? 'w' : 'b';
    for (int i = 0; i < coords.size(); i++) {
        if (board[coords[i].row][coords[i].col] != nullptr and board[coords[i].row][coords[i].col]->getColor() != playerSymbol) //sprawdzanie bicia
            cout << "Bicie - ";
        cout << char(coords[i].col + 65) << 8 - coords[i].row << endl; // wyswietlanie mozliwych ruchow
    }
}

void Chessboard::makeMove(int fromRow, int fromCol, int toRow, int toCol) {

    char playerSymbol = (playerTurn) ? 'w' : 'b';
    if (board[toRow][toCol] != nullptr and board[toRow][toCol]->getColor() == playerTurn) { // sprawdznie czy wybrano wlasciwego pionka
        cout << "Błąd: Nieprawidłowy ruch." << endl;
        return;
    }
    if (fromRow == toRow && fromCol == toCol) {
        cout << "Błąd: Nieprawidłowy ruch. Figura musi się przemieszczać." << endl;
        return;
    }
    if (!isValidMove(fromRow, fromCol, toRow, toCol)) { // sprawdzanie czy ruch jest prawidlowy dla danej figure
        cout << "Błąd: Nieprawidłowy ruch." << endl;
        return;
    }
    bool can = false; 
    for (int i = 0; i < coords.size(); i++) { // walidacja czy wskazane pole jest w zakresie mozliwych ruchow
        if (coords[i].row == toRow and coords[i].col == toCol) {
            can = true;
            break;
        }
    }
    if (can == false) { // walidacja czy wskazane pole jest w zakresie mozliwych ruchow
        cout << "Błąd: Nieprawidłowy ruch." << endl;
        return;
    }
    coords.clear(); // czyszczenie tablicy mozliwych ruchow
    if(board[fromRow][fromCol]->getSymbol() == 'K' and board[fromRow][fromCol]->firstMove == true) { // sprawdzanie czy wskazany ruch jest roszadą
        if (playerSymbol == 'w') {
            if (toRow == 7 and toCol == 7) {
                if (board[7][6] == nullptr and board[7][5] == nullptr and board[fromRow][fromCol]->firstMove == true and board[toRow][toCol] != nullptr and board[toRow][toCol]->getSymbol() == 'T') {
                    board[fromRow][fromCol]->firstMove = false;
                    board[7][6] = board[fromRow][fromCol];
                    board[7][5] = board[7][7];
                    board[7][4] = nullptr;
                    board[7][7] = nullptr;
                    playerTurn = !playerTurn; // Zmiana tury po udanym ruchu
                    return;
                }
            }
            if (toRow == 7 and toCol == 0) {
                if (board[7][1] == nullptr and board[7][2] == nullptr and board[7][3] == nullptr and board[fromRow][fromCol]->firstMove == true and board[toRow][toCol] != nullptr and board[toRow][toCol]->getSymbol() == 'T') {
                    board[fromRow][fromCol]->firstMove = false;
                    board[7][2] = board[fromRow][fromCol];
                    board[7][3] = board[7][0];
                    board[7][4] = nullptr;
                    board[7][0] = nullptr;
                    playerTurn = !playerTurn; // Zmiana tury po udanym ruchu
                    return;
                }
            }
        }
        else if (playerSymbol == 'b') {
            if (toRow == 0 and toCol == 7) {
                if (board[0][6] == nullptr and board[0][5] == nullptr and board[fromRow][fromCol]->firstMove == true and board[toRow][toCol] != nullptr and board[toRow][toCol]->getSymbol() == 'T') {
                    board[fromRow][fromCol]->firstMove = false;
                    board[0][6] = board[fromRow][fromCol];
                    board[0][5] = board[0][7];
                    board[0][4] = nullptr;
                    board[0][7] = nullptr;
                    playerTurn = !playerTurn; // Zmiana tury po udanym ruchu
                    return;
                }
            }
            if (toRow == 0 and toCol == 0) {
                if (board[0][1] == nullptr and board[0][2] == nullptr and board[0][3] == nullptr and board[fromRow][fromCol]->firstMove == true and board[toRow][toCol] != nullptr and board[toRow][toCol]->getSymbol() == 'T') {
                    board[fromRow][fromCol]->firstMove = false;
                    board[0][2] = board[fromRow][fromCol];
                    board[0][3] = board[0][0];
                    board[0][4] = nullptr;
                    board[0][0] = nullptr;
                    playerTurn = !playerTurn; // Zmiana tury po udanym ruchu
                    return;
                }
            }
        }
    }
    board[fromRow][fromCol]->firstMove = false; // kazdy ruch wybranego pionka ustawiamy na false
    if (board[toRow][toCol] != nullptr and board[toRow][toCol]->getSymbol() == 'K') // sprawdzanie czy krol został zbity
        endGame = true;
    board[toRow][toCol] = board[fromRow][fromCol]; // zmiana pola figury na wskazany
    board[fromRow][fromCol] = nullptr; // zmiana poprzedniego pola figury na nullptr
    if (board[toRow][toCol]->getSymbol() == 'P' and (toRow == 0 or toRow == 7)) { // awans pionka
        if (board[toRow][toCol]->getColor() == 'w') {
            spag:
            char aw;
            cout << "Wybierz figure do awansu: ";
            cin >> aw;
            switch (aw) {
            case 'Q':
                board[toRow][toCol] = new Queen('w');
                break;
            case 'T':
                board[toRow][toCol] = new Tower('w');
                break;
            case 'S':
                board[toRow][toCol] = new Knight('w');
                break;
            case 'G':
                board[toRow][toCol] = new Bishop('w');
                break;
            default:
                goto spag;
                break;
            }
        }
        else
        {
        spag2:

            char aw;
            cout << "Wybierz figure do awansu: ";
            cin >> aw;
            switch (aw) {
            case 'Q':
                board[toRow][toCol] = new Queen('b');
                break;
            case 'T':
                board[toRow][toCol] = new Tower('b');
                break;
            case 'S':
                board[toRow][toCol] = new Knight('b');
                break;
            case 'G':
                board[toRow][toCol] = new Bishop('b');
                break;
            default:
                goto spag2;
                break;
            }
        }
    }
    playerTurn = !playerTurn; // Zmiana tury po udanym ruchu

}

void Chessboard::clear() {
    for (int row = 0; row < 8; ++row)
        for (int col = 0; col < 8; ++col)
            if(board[row][col] != nullptr)
                board[row][col]->marked = false;
}

bool Chessboard::isKingInCheck() {
    if (playerTurn == true) { // generowanie tablicy ze wszystkimi mozliwymi ruchami figur (z rozroznieniem czarnych od białych)
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (board[i][j] != nullptr) {
                    showMoves(i, j);
                }
        playerTurn = false;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (board[i][j] != nullptr) {
                    showMoves(i, j);
                }
        playerTurn = true;
    }
    else {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (board[i][j] != nullptr) {
                    showMoves(i, j);
                }
        playerTurn = true;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (board[i][j] != nullptr) {
                    showMoves(i, j);
                }
        playerTurn = false;
    }

    int WK_row;
    int WK_col;
    int BK_row;
    int BK_col;

    for (int i = 0; i < 8; i++) // skanowanie w poszukiwanie króla
        for (int j = 0; j < 8; j++)
            if (board[i][j] != nullptr) {
                if (board[i][j]->getSymbol() == 'K' and board[i][j]->getColor() == 'w') {
                    WK_row = i;
                    WK_col = j;
                }
                if (board[i][j]->getSymbol() == 'K' and board[i][j]->getColor() == 'b') {
                    BK_row = i;
                    BK_col = j;
                }
            }

    for (int i = 0; i < coords.size(); i++) { // jeżeli pozucja krola znajduje się w tablicy możliwych ruchow przeciwnika wyświetl komunikat
        if (coords[i].col == WK_col and coords[i].row == WK_row) {
            cout << "(Uwaga!!! Biału w szachu)" << endl;
        }
        if (coords[i].col == BK_col and coords[i].row == BK_row) {
            cout << "(Uwaga!!! Czarny w szachu)" << endl;
        }

    }
    coords.clear();
    return 0;
}

Chessboard::~Chessboard() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            delete board[row][col];
        }
    }
}
