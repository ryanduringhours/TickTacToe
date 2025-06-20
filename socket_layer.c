/*
 * @file socket_layer.c
 * @brief socket binding for CS-202 project
 *
 */

 #include "socket_layer.h"
 #include "error.h"
 #include "macros.h"
 
 // ======================================================================
 int init_socket(time_t t)//t in seconds
 {
     const int fd = socket(AF_INET,SOCK_DGRAM,0);
     if(fd < 0)
     {
         printf("Socket creation failed\n");
         return ERR_SOCKET;
     }
     else
     {
         if (t > 0) 
         {
             // Set receive timeout
             struct timeval timeout;
             zero_var(timeout);//sets timeout to all zeroes
             timeout.tv_sec = t;
             //set timeout 
             if(setsockopt(fd,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout))<0)
             {//if failure or timeout is exceeded
                 close(fd);
                 return ERR_SOCKET;
             }
         }
         else if(t==0);
         else return ERR_SOCKET;
     }
     return fd;
 }
 
 // ======================================================================
 int insert_addr(const char *ip, uint16_t port,struct sockaddr_in *p_server_addr)
 {
     M_REQUIRE_NON_NULL(ip);
     M_REQUIRE_NON_NULL(p_server_addr);
     //assuming *p_server_addr is nalready allocated before this function
     if (inet_pton(AF_INET,ip,&p_server_addr->sin_addr) == 1)
     {
         p_server_addr->sin_family = AF_INET;
         p_server_addr->sin_port = htons(port);
     }
     else return ERR_ADDRESS;
     return ERR_NONE;
 }
 
 // ======================================================================
 int bind_server(int socket, const char *ip, uint16_t port)
 {
     struct sockaddr_in server_addr = {0};
     const struct sockaddr_in * server_addr_p = &server_addr;
     int err = insert_addr(ip,port, &server_addr);
      //initialize sockaddr values
     if(err == ERR_NONE)
     {
          if(bind(socket,(const struct sockaddr *)server_addr_p, sizeof(struct sockaddr_in))<0) err = ERR_NETWORK;
          else printf("successfully bound server\n");
     }
     else err = ERR_ADDRESS;
     return err;
 }
 
 // ======================================================================
 int udp_server_init(const char *ip, uint16_t port, time_t t)
 {
     M_REQUIRE_NON_NULL(ip);
 
     // Create a socket
     int socket = init_socket(t); // to be modified
     if (socket < 0) {
         perror("Error opening server socket");
         return ERR_NETWORK;
     }
     else
     {
         if(bind_server(socket, ip, port) == ERR_NONE) printf("Great success, server bound\n");
         else return ERR_NETWORK;
     }
     return socket;
 }
 
 /********************************************************************/
 ssize_t udp_read(int socket, char *buf, size_t buflen,
                  struct sockaddr_in *cli_addr)
 {
     ssize_t ret_bytes = -1;
     if(cli_addr != NULL) //retrive the senders address
     {
         socklen_t cli_addr_len = (socklen_t)sizeof(*cli_addr);
         ret_bytes = recvfrom(socket, buf, buflen,0, (struct sockaddr *)cli_addr, &cli_addr_len);
         //printf("recieved: %zd bytes\n",ret_bytes);
         //print_msg(buf,cli_addr,0);
     }
     else
     { //either the sender doesnt matter or is already known
         ret_bytes = recv(socket, buf, buflen,0);
         //printf("message: %s\n",buf);
     }
     
     return ret_bytes < 0 ? ERR_NETWORK: ret_bytes;
 
 }
 
 /********************************************************************/
 ssize_t udp_send(int socket, const char *response, size_t response_len,
                  const struct sockaddr_in *cli_addr)
 {
     M_REQUIRE_NON_NULL(response);
     struct sockaddr client_address = {0};
     memcpy(&client_address,cli_addr,sizeof(struct sockaddr_in));
     socklen_t cli_addr_len = (socklen_t)sizeof(*cli_addr);
     const ssize_t res = sendto(socket,response,response_len,0,&client_address,cli_addr_len);
     //print_msg(response,cli_addr,1);
     return res < 0 ? ERR_NETWORK : res;
 }
 
 int print_msg(ssize_t number, char* message, struct sockaddr_in* addr_p,int sendrec)
 {
     int error = ERR_NONE;
     if(message == NULL && addr_p == NULL) error = ERR_INVALID_ARGUMENT;
     else
     {
         //if 0 for receiving, 1 for sending
         if (sendrec == 0) printf("=======\nRecieved message from: ");
         else printf("=======\nSent message to: ");
         printf_ip_port(addr_p);
         printf("message: %s\n", message);
         printf("message length = %zd\n",number);
     }
     return error;
 }

 void printf_ip_port(struct sockaddr_in * address)
 {
    char* ip_add = inet_ntoa(address->sin_addr);
    int port = ntohs(address->sin_port);
    printf("%s:%i\n",ip_add,port);
 }
