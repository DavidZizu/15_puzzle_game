#include <iostream>
#include <stdio.h>
#include <map>
#include <set>
#include <time.h>

using namespace std;

class Puzzle{
public:
    int length;
    
    Puzzle();
    //key is the value of a square tile; value is a position on the board
    //value 0 represents space
    map<int, int>numbers;
    //key represents the value of the tile and value represents its direction
    pair<int, int> user_move;
    
    //represents by how much space the tile should be moved
    int move_by;
    
    //an array of tile positons
    int temp_numbers[17];
    
    //initial game board
    void initial();
    //mix the game board (should be modified)
    void mix();
    
    //take the command from the user
    bool user_command();
    //determine the direction where to move the tile
    bool move_direct();
    //perform the movement
    void make_move();
    
    //print the rules of the game
    void print_rules();
    //print the game board
    void print_game();
    
    //check for winning
    bool win_check();
    
    //ask if user wants to play
    bool play_game();
};

Puzzle::Puzzle() {
    length = 16;
    move_by = 0;
    mix();
}

void Puzzle::initial() {
    numbers[0] = 16;
    for (int i = 1; i < length; i++)
        numbers[i] = i;
}

void Puzzle::mix() {
    set<int> used_numbers;
    srand(time(NULL));
    int rand_numb = rand() % 16 + 1;
    
    for (int i = 0; i < length; i++) {
        
        while (!used_numbers.insert(rand_numb).second)
            rand_numb = rand() % 16 + 1;
        numbers[i] = rand_numb;
    }
}

bool Puzzle::user_command() {
    string user_input[2];
    int index = 0;
    char char_taken, prev_char_taken = ' ';
    
    user_input[0] = "";
    user_input[1] = "";
    
    bool valid = true;
    
    cout << "> ";
    
    while ((char_taken = getchar()) != '\n') {
        if (char_taken == ' ' && prev_char_taken != ' ')
            index++;
        else if (index > 2 || (char_taken != ' ' && !isdigit(char_taken)))
            valid = false;
        else
            user_input[index] += char_taken;
        prev_char_taken = char_taken;
    }
    
    if (valid && index >= 1) {
        user_move.first = stoi(user_input[0]);
        user_move.second = stoi(user_input[1]);
    }
    
    return valid;
}

bool Puzzle::move_direct() {
    if (user_move.second <= 0 || user_move.second > 4)
        return false;
    
    if (user_move.second == 1) {
        if (numbers[user_move.first] == 4 || numbers[user_move.first] == 8 || numbers[user_move.first] == 12)
            return false;
        move_by = 1;
    }
    else if (user_move.second == 2)
        move_by = 4;
    else if (user_move.second == 3) {
        if (numbers[user_move.first] == 5 || numbers[user_move.first] == 9 || numbers[user_move.first] == 13)
            return false;
        move_by = -1;
    }
    else
        move_by = -4;
    
    return true;
}

void Puzzle::make_move() {
    if (user_command() && user_move.first > 0 && user_move.first < 16 && move_direct() && numbers[user_move.first] + move_by == numbers[0] ) {
        int temp_pos;
        temp_pos = numbers[user_move.first];
        numbers[user_move.first] = numbers[0];
        numbers[0] = temp_pos;
    }
    else
        //display an error
        fprintf(stderr, "Error: Invalid command\n\n");
}

bool Puzzle::win_check() {
    
    if (temp_numbers[16] != 0)
        return false;
    
    for (int i = 1; i < length; i++)
        if (temp_numbers[i] != i)
            return false;
    
    return true;
}

bool Puzzle::play_game() {
    
    char user_input[10];
    
    cout << "Do You Want to Play Again (\"Yes\", \"No\")?" << endl;
    
    while(true) {
        cout << "> ";
        fgets(user_input, 100, stdin);
        user_input[strlen(user_input) - 1] = '\0';
        if (strcasecmp(user_input, "yes") == 0)
            return true;
        else if (strcasecmp(user_input, "No") == 0)
            return false;
    }
    
}

void Puzzle::print_game() {
    
    for (int i = 0; i < length; i++)
        temp_numbers[numbers[i]] = i;
    
    cout << "-------------------------" << endl;
    
    for (int i = 1; i < length + 1; i++) {
        temp_numbers[i] == 0 ? cout << "|   " : cout << "|  " << temp_numbers[i];
        temp_numbers[i] > 9 ? cout << " " : cout << "  ";
        (i % 4 == 0 && i != 16) ? cout << "|" << endl << "|" << "-----" << "|" << "-----" << "|" << "-----" << "|" << "-----" << "|" << endl : cout << "";
    }
    
    cout << "|" << endl << "-------------------------" << endl;
}

void Puzzle::print_rules() {
    
    cout << "Reference:" << endl;
    
    cout << "\t1 : ->" << endl
    << "\t2 :  |" << endl
    << "\t    \\/" << endl
    << "\t3 : <-" << endl
    << "\t4 :  ^" << endl
    << "\t     |" << endl;
    
    cout << "Usage: " << endl;
    cout << "\t12" << " - " << "2" << " = " << "move 12 down" << endl;
}