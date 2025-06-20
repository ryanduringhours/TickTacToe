#pragma once

#include <stdio.h>

void display_board(int* board);
char number_to_char(int player);
void clear_board(int*board);
void start_game(int*board);
void get_player_move(int* board, int player);
int check_win_con(int*board);
int get_player_input(void);


enum state{
    empty = 0,
    player_1 = 1,
    player_2 = 2,
};
