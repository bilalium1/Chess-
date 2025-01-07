#include <iostream>
#include "chesslib.h"
#include <windows.h>
#include <conio.h>
#include <cstdlib>

int main(){

    Chess game;
    game.display();
    game.move(1, {1,2});



    

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
                    if (game.get_piece(game.cursor)!=-1){
                        if (game.select[0]==-1){
                            game.select[0]=game.cursor[0]; game.select[1]=game.cursor[1];
                        }
                        else {
                            if(game.cursor[0]==game.select[0] && game.cursor[1]==game.select[1]){
                                game.select={-1,-1};
                            }
                        }
                    } 
                    else {
                        if(game.select[0]==-1)cout<<"this is not a chess piece mate";
                        else {
                            game.move(game.get_piece(game.select), game.cursor);
                            game.select={-1,-1};
                        }
                    };
                    break;
                default: cout << "Unknown key: " << key << "\n"; break;
            }

            system("cls");
            game.display();
            cout<<"x ="<<game.cursor[0]<<", y ="<<game.cursor[1];


            if (key=='q'){
                cout << "game finished.";
                break;
            }
        }
    }

    return 0;
}