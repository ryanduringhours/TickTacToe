#include <stdio.h>

#include "tic-tac-toe.h"
#include "error.h"

/*
int main(int argc, char const *argv[])
{
    char board[9];
    clear_board(board);
    start_game(board);
    return 0;
}
*/

void clear_board(int *board)
{
    //set state to empty
    for(int i = 0;i<(int)sizeof(board);i++) board[i] = empty;
}

void display_board(int* board)
{
    /*
    0|1|2
    3|4|5
    6|7|8
    */
    for(int i = 0;i<3;i++)
    {
        printf("%c|%c|%c\n",number_to_char(board[i*3]),number_to_char(board[i*3+1]),number_to_char(board[i*3+2]));
    }
}

char number_to_char(int player)
{
    if(player == empty) return ' ';
    else if(player == player_1) return 'X';
    else if(player == player_2) return 'O';
    return 'E';
}

void start_game(int* board)
{
    int turn = 0, winner = empty;
    while(winner == empty)
    {
        turn ++;
        if (turn % 2 == 1) get_player_move(board, player_1);
        else if(turn %2 == 0) get_player_move(board, player_2);
        winner = check_win_con(board);
        display_board(board);
    }
    if (winner == 3) printf("It is a tie\n");
    else  printf("player %d wins\n",winner);

}

void get_player_move(int* board, int player)
{
    int move = 0, validity = 0;
    while(validity ==0)
    {
        printf("player %d make a move:",player);
        move = get_player_input();
        move--;
        //check move validity
        if(move>=0&&move<9&&board[move] == empty) validity = 1;
        else printf("invalid move\n");
    }
    board[move] = player;
}

int get_player_input(void)
{
  int integer;
  char buffer[50];
  while (fgets(buffer, sizeof(buffer), stdin)) 
  {
    if (sscanf(buffer, "%d", &integer) == 1 ) return integer;
    else printf("invalid response");
  }
  return -1;
}

int check_win_con(int *board)
{
    //horizontal check
    for (int i =0;i<3;i++)
    {
        if(board[i*3]==board[i*3+1] && board[i*3+1]==board[i*3+2])
        {
            if (board[i*3] == player_1) return player_1;
            if (board[i*3] == player_2) return player_2;
        }
    }
    //verticle check
    for (int i =0;i<3;i++)
    {
        if(board[i]==board[3+i] && board[3+i]==board[6+i])
        {
            if (board[i] == player_1) return player_1;
            if (board[i] == player_2) return player_2;
        }
    }
    //diagonal check
    for(int i = 0;i<2;i++)
    {
        if(board[4] == board[4+(i+1)*2] && board[4] == board[4-(i+1)*2])
        {
            if (board[4] == player_1) return player_1;
            if (board[4] == player_2) return player_2;
        }
    }
    //check for tie if all windonditoins weren't met
    int full =0;
    for(int i = 0;i<9;i++) if(board[i]!= empty) full++;
    if(full>=9) return 3;
    
    return empty;
}
