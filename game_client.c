#include <stdio.h>

#include "tic-tac-toe.h"
#include "socket_layer.h"
#include "macros.h"

int main(int argc, char const *argv[])
{
    int sockfd = init_socket(10);
    char message[] = "join";
    size_t message_size = sizeof(message);
    struct sockaddr_in server = {0}, rec_addr = {0};
    insert_addr(DEFAULT_IP,DEFAULT_PORT, &server);
    udp_send(sockfd, message, message_size,&server);

    //clear message and recieve player position
    char buffer[MAX_MSG_SIZE]={0};
    udp_read(sockfd,buffer,sizeof(buffer),&rec_addr);
    printf("%s\n", buffer);

    return 0;
}
