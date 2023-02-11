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
#include <error.h>
#include "tcp_common_data.h"

void tcp_setup_server_communication()
{
    // Step1: Initialize the variables
    // Step2: Create a master socket
    // Step3: Bind the master socket to the network layer
    // Step4: Listen from the master socket
    // Step5: Initialize and refill readfs
    // Step6: Select the socket for communication
    // Step7: Accept the connection from the client
    // Step8: Receive data from the client
    // Step9: Process the data from the client
    // Step10: Send the data back to the client
    // Step11: Close the connection with the client
    // Step12: Go back to Step 5
}

int main(int argc, char* argv[])
{
    printf("This is the TCP server summation program.\n");
    tcp_setup_server_communication();
}