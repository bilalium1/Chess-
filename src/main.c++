#include <iostream>
#include "chesslib.h"
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

class Stockfish {
    HANDLE hChildStdinWr = NULL;
    HANDLE hChildStdoutRd = NULL;
    PROCESS_INFORMATION pi{};

public:
    bool start(const std::string& path) {
        SECURITY_ATTRIBUTES saAttr{};
        saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
        saAttr.bInheritHandle = TRUE;
        saAttr.lpSecurityDescriptor = NULL;

        // Create pipes for STDOUT
        HANDLE hChildStdoutWr = NULL;
        if (!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 0)) return false;
        SetHandleInformation(hChildStdoutRd, HANDLE_FLAG_INHERIT, 0);

        // Create pipes for STDIN
        HANDLE hChildStdinRd = NULL;
        if (!CreatePipe(&hChildStdinRd, &hChildStdinWr, &saAttr, 0)) return false;
        SetHandleInformation(hChildStdinWr, HANDLE_FLAG_INHERIT, 0);

        STARTUPINFO si{};
        si.cb = sizeof(STARTUPINFO);
        si.hStdError = hChildStdoutWr;
        si.hStdOutput = hChildStdoutWr;
        si.hStdInput = hChildStdinRd;
        si.dwFlags |= STARTF_USESTDHANDLES;

        if (!CreateProcess(
            path.c_str(),
            NULL, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
            std::cerr << "Failed to launch Stockfish. Error: " << GetLastError() << "\n";
            return false;
        }

        CloseHandle(hChildStdoutWr);
        CloseHandle(hChildStdinRd);
        return true;
    }

    void send(const std::string& cmd) {
        std::string data = cmd + "\n";
        DWORD written;
        WriteFile(hChildStdinWr, data.c_str(), (DWORD)data.size(), &written, NULL);
    }

    string read() {
        DWORD dwRead;
        CHAR buffer[4096];
        std::string output;

        for (;;) {
            BOOL success = ReadFile(hChildStdoutRd, buffer, sizeof(buffer) - 1, &dwRead, NULL);
            if (!success || dwRead == 0) break;

            buffer[dwRead] = '\0';
            output += buffer;

            // Stop once Stockfish prints "bestmove"
            if (output.find("bestmove") != std::string::npos) break;
        }

        // Extract the move
        size_t pos = output.find("bestmove");
        if (pos != std::string::npos) {
            // skip the word "bestmove " (9 chars)
            size_t start = pos + 9;
            size_t end = output.find(' ', start);
            std::string move = output.substr(start, end - start);
            return move; // e.g. "e2e4"
        }

        return ""; // fallback if not found
    }

    void drainStockfishOutput() {
        DWORD dwRead;
        CHAR buffer[4096];

        for (;;) {
            BOOL success = ReadFile(hChildStdoutRd, buffer, sizeof(buffer) - 1, &dwRead, NULL);
            if (!success || dwRead == 0) break;
            // discard data
        }
    }



    void stop() {
        TerminateProcess(pi.hProcess, 0);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        CloseHandle(hChildStdinWr);
        CloseHandle(hChildStdoutRd);
    }
};

void clearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD charsWritten;

    // Get the number of characters in the console
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the console with spaces
    FillConsoleOutputCharacter(hConsole, ' ', consoleSize, coord, &charsWritten);

    // Reset the cursor to the top left corner
    SetConsoleCursorPosition(hConsole, coord);
}

int main(){

    Chess game;
    Stockfish bot;

    int mv;
    int game_mode = 0;

    cout << "\n\n" <<"| Choose Game mode : " << "\n\n" << " -> 0 : PLAYER VS PLAYER" << "\n\n" << " -> 1 : PLAYER VS CPU" << "\n\n";
    cin >> game.gamemode;

    if (game.gamemode > 0)
    {
        if (!bot.start("stockfish/stockfish.exe"))
        return 1;
    }

    clearScreen();
    game.display();

    //game loop
    while (1) {
        if (_kbhit()){
            char key = _getch();

            switch (key) {
                case 72: if(game.cursor[1]>0)--game.cursor[1]; break; //up
                case 80: if(game.cursor[1]<7)++game.cursor[1]; break; //down 
                case 75: if(game.cursor[0]>0)--game.cursor[0]; break; //left
                case 77: if(game.cursor[0]<7)++game.cursor[0]; break; //right
                case 13:
                    if (game.select_piece==-1){
                        // select piece
                        if (game.get_piece(game.cursor)!=-1 && (game.get_piece(game.cursor) <= 15) == game.turn){
                            game.select[0]=game.cursor[0]; game.select[1]=game.cursor[1];
                            game.select_piece=game.get_piece(game.cursor);
                        }
                    } else {
                        // move piece
                        mv = game.move(game.get_piece(game.select), game.cursor);
                        game.select={-1,-1};
                        game.select_piece=-1;
                        if (mv > -1)
                            game.turn = !game.turn;

                    }
                    break;
                default: break;
            }
            //cout<<"x ="<<game.cursor[0]+1<<", y ="<<game.cursor[1]+1;

            if (game.is_checkmate() != 0)
                break;  
        
            if (game.gamemode > 0 && game.turn)
            {
                bot.stop();
                bot.start("stockfish/stockfish.exe");
                string fen = game.get_FEN();
                cout << "Hold on let me think...\n";
                bot.send("position fen " + fen);
                bot.send("go movetime 1000");

                string res = bot.read();

                char *buffer = new char[res.size() + 1];
                strcpy(buffer, res.c_str());

                game.bot_move(buffer);
                game.turn = !game.turn;

                delete[] buffer;
            }
              
            clearScreen();
            game.display();

            if (key=='q'){
                cout << "game finished.";
                break;
            }
        }
    }

    if (game.is_checkmate() == 1) cout << "PLAYER 2 WINS";
    if (game.is_checkmate() == -1) cout << "PLAYER 1 WINS";
    if (game.is_checkmate() == 0) cout << "GAME OVER"; 

    return 0;
}