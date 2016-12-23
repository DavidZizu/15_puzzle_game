#include "15_puzzle.h"

int main(int argc, char ** argv) {
    
    Puzzle game;
    
    //display the rules
    game.print_rules();
    cout << endl;
    game.mix();
    game.print_game();
    cout << endl;
    
    while (true) {
        //take the input from the user and make the movement
        game.make_move();
        //print the game board
        game.print_game();
        cout << endl;
        //check for winning
        if (game.win_check()) {
            cout << "You Won!" << endl;
            if (game.play_game()) {
                Puzzle game;
                cout << endl << "---------New Game--------" << endl << endl;
                game.print_game();
                cout << endl;

            }
            else
                exit(0);
        }
    }

    game.print_game();
    cout << endl;
    
    return 0;
}