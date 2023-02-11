/*
    tcp_client.c
    This is tcp client program

    The puprose of this program is to send two integer values to server and get sum of its results
    This client has to keep on send the request to get the sum values
    If this client wants to teriminate the connection then send the two integer values as zero in the request.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <error.h>
#include <memory.h>
#include "tcp_common_data.h"

void tcp_client_request_response_setup()
{  

    // Step1: Initialize 
    int socket_fd = 0;
    struct sockaddr_in server_socket_addr;
    server_socket_addr.sin_family = AF_INET;
    server_socket_addr.sin_port = SERVER_PORT_4_COMMUNICATION;
    struct hostent *host = (struct hostent*)gethostbyname(SERVER_IP_ADDRESS);
    server_socket_addr.sin_addr = *((struct in_addr*)host->h_addr);

    // Step2: Create a socket connection
    if((socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
    {
        perror("ERROR: creating socket for the client...\n");
        exit(EXIT_FAILURE);
    }
    printf("client socket creation is successful...\n");

    // Step3: Connect with the server
    if( connect(socket_fd, (const struct sockaddr*)(&server_socket_addr), sizeof(struct sockaddr_in)) == -1)
    {
        perror("ERROR: connecting server socket from the client...\n");
        exit(EXIT_FAILURE);
    }
    printf("connected with the server ip: %s port: %u\n", host->h_name, SERVER_PORT_4_COMMUNICATION);


    unsigned int get_user_input = 0;
    do
    {
        // Step4: Get the input from the customer
        tcp_request_data_2_sum request_data;
        printf("\nEnter a: ");
        int a_result = scanf("%u", &request_data.a);
        printf("\nEnter b: ");
        int b_result = scanf("%u", &request_data.b);
        if(a_result != 1 && b_result != 1)
        {
            perror("ERROR: reading input data from user ...\n");            
            break;
        }

        // Step5: Send the data to server
        int bytes_sent = sendto(socket_fd, (char*)(&request_data), sizeof(request_data), 0, (const struct sockaddr*)(&server_socket_addr), sizeof(struct sockaddr));
        if(bytes_sent <= 0)
        {
            perror("ERROR: sending data is not complete ...\n");            
            break;
        }
        printf("\nsent %u bytes of data successfully to the server...\n", bytes_sent);
        
        // Step6: Receive the response from the server
        tcp_response_data_2_sum response_data;

        socklen_t addr_len = sizeof(struct sockaddr);
        int received_bytes = recvfrom(socket_fd, (&response_data), sizeof(response_data), 0, (struct sockaddr*)(&server_socket_addr), &addr_len);
        if(received_bytes <= 0)
        {
            perror("ERROR: receiving data is not complete...\n");
            break;
        }
        printf("received %u bytes as result from server...\n", received_bytes);
        printf("\nReturn result from server: %u \n", response_data.result);

        printf("\ndo you want to send another request? Yes: 1 No: 0\nEnter your choice: ");
        int cont_result = scanf("%u", &get_user_input);
        if(cont_result != 1 || get_user_input <=0 )
        {
            break;
        }
        printf("\n");

    }while(get_user_input);

    // Close the socket connection.
    close(socket_fd);
    printf("\nclosing connection and exiting from the client...\n");

}

int main(int argc, char* argv[])
{
    printf("This is the TCP client summation program\n");
    tcp_client_request_response_setup();
    printf("Ending client running on pid: %d \n", getpid());
}