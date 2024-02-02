#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define FIRST_INDEX 0
#define NUMBER_INIT 1
#define LAST_INDEX 2
#define LINE 3
#define COLUMN 3

using namespace std;

class Player {
    public:
        string name;
        char symbol;

    public: Player(string name, char symbol) {
        this->name = name;
        this->symbol = symbol;
    }

    string getName() {
        return name;
    }

    char getSymbol() {
        return symbol;
    }

    void makeMove(char board[LINE][COLUMN], int line, int column) {
        board[line][column] = getSymbol();
        cout << "Move made by " << getName() << " in the position " << line << " " << column << endl;
    }
};

void welcomeGame();
void createBoard(char board[LINE][COLUMN]);
void createPlayers(string *nameA, string *nameB);
void drawBoard(char board[LINE][COLUMN]);
void informationPlayers(Player playerA, Player playerB);
void turnPlayer(Player player, char board[LINE][COLUMN]);
int sortedPlayer();
bool checkWin(char board[LINE][COLUMN]);
bool checkTie(char board[LINE][COLUMN]);

int main() {
    char board[LINE][COLUMN];
    string nameA, nameB;
    int line, column;
    
    welcomeGame();
    createBoard(board);
    createPlayers(&nameA, &nameB);

    Player playerA(nameA, 'X');
    Player playerB(nameB, 'O');

    informationPlayers(playerA, playerB);
    int firstPlayer = sortedPlayer();
    int turn = firstPlayer;

    while (true) {
        drawBoard(board);
        turnPlayer((!turn ? playerA : playerB), board);

        if(checkWin(board)) {
            drawBoard(board);
            cout << "Player " << (!turn ? playerA.getName() : playerB.getName()) << " is winner!" << endl;
            cout << "Game over\n";
            break;
        } else if(checkTie(board)) {
            drawBoard(board);
            cout << "Empate!" << endl;
            cout << "Game over\n";
            break;
        } else {
            cout << "Game continues...\n";
            turn = !turn;
            continue;
        }
    }

    return 0;
}

void welcomeGame() {
    cout << "Welcome to the game noughts and crosses\n";
    cout << "Inicializing the board...\n\n";
    cout << "===BOARD===\n";
}

void createBoard(char board[LINE][COLUMN]) {
    int number = NUMBER_INIT;

    for (int i = FIRST_INDEX; i < LINE; i++) {
        for (int j = FIRST_INDEX; j < COLUMN; j++) {
            board[i][j] = number + '0';
            cout << " " << board[i][j];
            if (j < LAST_INDEX) cout << " |";
            number++;
        }

        cout << endl;
        if (i < LAST_INDEX) cout << "-----------" << endl;
    }

    delete &number;
}

void createPlayers(string *nameA, string *nameB) {
    cout << "\nInicializing the players...\n";
    cout << "Player 1, type your name: ";
    cin >> *nameA;

    cout << "Player 2, type your name: ";
    cin >> *nameB;
}

void drawBoard(char board[LINE][COLUMN]) {
    cout << "-----------" << endl;
    
    for (int i = FIRST_INDEX; i < LINE; i++) {
        for (int j = FIRST_INDEX; j < COLUMN; j++) {
            cout << " " << board[i][j];
            if (j < LAST_INDEX) cout << " |";
        }

        cout << endl;
        if (i < LAST_INDEX) cout << "-----------" << endl;
    }

    cout << "-----------" << endl;
}

void informationPlayers(Player playerA, Player playerB) {
    cout << "\nPlayer 1: " << playerA.getName() << " - Symbol: " << playerA.getSymbol() << endl;
    cout << "Player 2: " << playerB.getName() << " - Symbol: " << playerB.getSymbol() << endl;  
}

void turnPlayer(Player player, char board[LINE][COLUMN]) {
    int line, column;

    cout << "It's your turn " << player.getName() << endl;
    cout << "Type the line and column: ";
    cin >> line >> column;

    if(board[line][column] == 'X' || board[line][column] == 'O' || line < 0 || line > 2 || column < 0 || column > 2) {
        cout << "Invalid move, try again\n";
        turnPlayer(player, board);
    }

    player.makeMove(board, line, column);
}

int sortedPlayer() {
    cout << "Sorting the first player...\n";

    srand(static_cast<unsigned int>(time(nullptr)));
    int randomValue = rand();
    double normalizedValue = static_cast<double>(randomValue)/RAND_MAX;
    int result = round(normalizedValue);

    return result;
}

bool checkWin(char board[LINE][COLUMN]) {
    for (int i = FIRST_INDEX; i < LINE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
    }

    if(board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;
    
    return false;
}

bool checkTie(char board[LINE][COLUMN]) {
    for (int i = FIRST_INDEX; i < LINE; i++) {
        for (int j = FIRST_INDEX; j < COLUMN; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') return false;
        }
    }

    return true;
}
