#include <stdio.h>
#include <string.h>

#include "tic-tac-toe.h"
#include "socket_layer.h"
#include "macros.h"

enum server_state{
    w2join, //waiting for 2 clients to join
    w1join, //waiting for 1 client to join
    waiting_turn,    
};


int main(int argc, char const *argv[])
{
    //create board
    int board[9];
    clear_board(board);
    //set up networking 
    int sockfd = udp_server_init(DEFAULT_IP,DEFAULT_PORT, 10);
    struct sockaddr_in cli_addr1 = {0}, cli_addr2 = {0};
    char buffer[MAX_MSG_SIZE] = {0};
    //game state
    int state = w2join, same = -1;
    ssize_t recieved = -1, sent = -1;
    while(1)
    {
        if(state == w2join)
        {//waiting for any player to join
            same = -1;
            while(recieved < 0 || same != 0)
            {
                recieved = udp_read(sockfd,buffer,sizeof(buffer),&cli_addr1);
                if(recieved >0) 
                {
                    //print_msg(recieved,buffer,&cli_addr1,0);
                    same = strcmp(buffer,"join");
                }
                zero_ptr(buffer);
            }
            //saved client 1 as player 1, tell client it is player 1
            snprintf(buffer,sizeof(buffer),"1");           
            sent = udp_send(sockfd,buffer,strlen(buffer)+1,&cli_addr1);
            state = w1join;
            printf("player one has joined\n");
        }
        else if(state == w1join)
        {
            same = -1;
            while(recieved < 0 || same != 0)
            {
                recieved = udp_read(sockfd,buffer,sizeof(buffer),&cli_addr2);
                if(recieved >0) 
                {
                    //print_msg(recieved,buffer,&cli_addr1,0);
                    same = strcmp(buffer,"join");
                }
                zero_ptr(buffer);
            }
            //saved client 2 info and tell client 2 to wait
            snprintf(buffer,sizeof(buffer),"2");           
            sent = udp_send(sockfd,buffer,strlen(buffer)+1,&cli_addr2);  
            printf("player two has joined\n");
            break;         
        }
    }
    printf("game start\n");
    

    return 0;
}
