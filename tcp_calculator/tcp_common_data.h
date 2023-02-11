/*
    tcp_commondata.h
    This header files holds the common data structures and values used by both client and server
*/

typedef struct _tcp_request_data_2_sum
{
    unsigned int a;
    unsigned int b;
} tcp_request_data_2_sum;

typedef struct _tcp_response_data_2_sum_struct
{
    unsigned int result;
} tcp_response_data_2_sum;

#define SERVER_IP_ADDRESS "127.0.0.1"
#define SERVER_PORT_4_COMMUNICATION 2000
#define MAX_CLIENT_CONNECTION_ALLOWED 20


