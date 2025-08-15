#include <iostream>
#include "chesslib.h"
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

// Clears the screen using ANSI escape codes
void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

// Set terminal to raw mode to read keypresses without enter
void setRawMode(bool enable) {
    static struct termios oldt, newt;

    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

// Checks if a key was pressed
bool kbhit() {
    struct termios oldt, newt;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    int ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }

    return false;
}

// Reads one character from stdin
char getch() {
    char buf = 0;
    read(STDIN_FILENO, &buf, 1);
    return buf;
}

int main() {
    Chess game;
    game.display();

    setRawMode(true); // enable raw input

    int mv;

    while (1) {
        if (kbhit()) {
            char key = getch();

            // Handle arrow keys (they come as a 3-byte sequence)
            if (key == 27) { // ESC
                if (getch() == 91) { // [
                    char arrow = getch();
                    switch (arrow) {
                        case 'A': if (game.cursor[1] > 0) --game.cursor[1]; break; // up
                        case 'B': if (game.cursor[1] < 7) ++game.cursor[1]; break; // down
                        case 'D': if (game.cursor[0] > 0) --game.cursor[0]; break; // left
                        case 'C': if (game.cursor[0] < 7) ++game.cursor[0]; break; // right
                    }
                }
            } else if (key == '\n' || key == '\r') {
                if (game.select_piece == -1) {
                    if (game.get_piece(game.cursor) != -1 && (game.get_piece(game.cursor) <= 15) == game.turn) {
                        game.select[0] = game.cursor[0];
                        game.select[1] = game.cursor[1];
                        game.select_piece = game.get_piece(game.cursor);
                    }
                } else {
                    mv = game.move(game.get_piece(game.select), game.cursor);
                    game.select = {-1, -1};
                    game.select_piece = -1;

                    if (mv > -1)
                        game.turn = !game.turn;
                }
            } else if (key == 'q') {
                std::cout << "game finished.\n";
                break;
            } else {
                std::cout << "Unknown key: " << (int)key << "\n";
            }

            clearScreen();
            game.display();
        }
    }

    setRawMode(false); // restore terminal
    return 0;
}
