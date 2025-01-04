#include <iostream>
#include "chesslib.h"
#include <windows.h>

int main(){

    Chess game;
    game.display();
    game.move(1, {1,2});
    game.see_moves(1);
    game.is_check();
    game.is_checkmate();
    

    //game loop
    while (1) {
        Sleep(2000);
    }

    return 0;
}