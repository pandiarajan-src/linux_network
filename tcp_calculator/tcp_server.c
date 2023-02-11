/*
    tcp_server.c
    This is tcp server program

    The purpose of this server program is to find the sum of two numbers.
    Client will send two integer values in a data structure.
    This server computes the sum of two integer and returns the result.
    If client sends both the integer values as zero, then it is a indication to terminate the client.
    If clinet sends both integer values greater than zero, it computes the result and wait for the next client request.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <memory.h>
#include <error.h>
#include <limits.h>
#include "tcp_common_data.h"

void tcp_setup_server_communication()
{
    // Step1: Initialize the variables
    int master_socket_fd = 0;
    // Set of file descriptor on which select() polls. select() unlocks whenever data arries on any fd in this set.
    fd_set readfs; 

    // Step2: Create a master socket
    if( (master_socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
    {
        perror("ERROR: creating master socket with socket() API failed...\n");
        exit(EXIT_FAILURE);
    }
    // Step3: Bind the master socket to the network layer
    struct sockaddr_in server_sock_addr;
    int server_addr_len = 0;
    server_sock_addr.sin_family = AF_INET;
    server_sock_addr.sin_port = SERVER_PORT_4_COMMUNICATION;
    server_sock_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr_len = sizeof(struct sockaddr_in);
    
    if( bind(master_socket_fd, (const struct sockaddr*)(&server_sock_addr), server_addr_len) == -1)
    {
        perror("ERROR: binding master socket with bind() API failed...\n");
        exit(EXIT_FAILURE);
    }

    // Step4: Listen from the master socket
    if( listen(master_socket_fd, MAX_CLIENT_CONNECTION_ALLOWED) == -1)
    {
        perror("ERROR: listening master socket with listen() API failed...\n");
        exit(EXIT_FAILURE);
    }
    
    while (1)
    {
        // Step5: Initialize and refill readfs
        FD_ZERO(&readfs);
        FD_SET(master_socket_fd, &readfs);

        // Step6: Select the socket for communication
        // select() is blocking system call
        printf("calling select() to listen to the income request from the client...\n");
        select(master_socket_fd+1, &readfs, NULL, NULL, NULL);

        if(FD_ISSET(master_socket_fd, &readfs))
        {
            // Step7: Accept the connection from the client
            printf("new connection request received from client. server is going to accept the new request..\n");
            struct sockaddr_in client_sock_addr;
            socklen_t client_sock_addr_len;
            int client_socket_fd;
            if( (client_socket_fd = accept(master_socket_fd, (struct sockaddr*)(&client_sock_addr), &client_sock_addr_len)) == -1)
            {
                perror("ERROR: accepting new client connection error...\n");
                break;
            }
            printf("new connection accepted from %s:%u\n", inet_ntoa(client_sock_addr.sin_addr), ntohs(client_sock_addr.sin_port));

            // Step8: Receive data from the client
            char data_buffer[SCHAR_MAX];
            while(1)
            {
                printf("server is ready to receive data from client %d....\n", client_socket_fd);
                memset(data_buffer, 0, sizeof(data_buffer));
                int recv_bytes_len = 0 ;
                if((recv_bytes_len = recvfrom(client_socket_fd, data_buffer, sizeof(data_buffer),0, (struct sockaddr*)(&client_sock_addr), &client_sock_addr_len )) == 0)
                {
                    perror("ERROR: received byte length from the client is 0, hence exiting from client read operation...\n");
                    close(client_socket_fd);
                    break;
                }
                
                // Step9: Process the data from the client
                tcp_request_data_2_sum *client_request_data = (tcp_request_data_2_sum*)(data_buffer);                
                if(client_request_data != NULL)
                {
                    if(client_request_data->a == 0 && client_request_data->b == 0)
                    {
                        // Step11: Close the connection with the client
                        printf("client sends done with the connection, hence teriminating this client connection...\n");
                        close(client_socket_fd);
                        break;
                    }
                    // Step10: Send the data back to the client
                    tcp_response_data_2_sum response_data;
                    response_data.result = client_request_data->a + client_request_data->b;
                    int sent_resp_bytes = sendto(client_socket_fd, (const char*)(&response_data), sizeof(response_data), 0, (const struct sockaddr*)(&client_sock_addr), sizeof(struct sockaddr));
                    printf("server sending %d bytes of response to client..\n", sent_resp_bytes);
                }
            }
            //Step 12: Goto Step 6
        }
    }
    close(master_socket_fd);
    
}

int main(int argc, char* argv[])
{
    printf("This is the TCP server summation program.\n");
    tcp_setup_server_communication();
}