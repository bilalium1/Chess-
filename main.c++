#include <iostream>
#include "chesslib.h"
#include <windows.h>
#include <conio.h>
#include <cstdlib>

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
                        if (game.get_piece(game.cursor)!=-1){
                            game.select[0]=game.cursor[0]; game.select[1]=game.cursor[1];
                            game.select_piece=game.get_piece(game.cursor);
                        }
                    } else {
                        // move piece
                        game.move(game.get_piece(game.select), game.cursor);
                        game.select={-1,-1};
                        game.select_piece=-1;
                    }
                    break;
                default: break;
            }

            system("cls");
            game.display();
            //cout<<"x ="<<game.cursor[0]+1<<", y ="<<game.cursor[1]+1;


            if (key=='q'){
                cout << "game finished.";
                break;
            }
        }
    }

    return 0;
}