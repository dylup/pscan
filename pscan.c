#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

// print help menu
void printHelp()
{
    printf("Usage: ./pscan <host> <start port> - <end port>\n");
    printf("[!] <host>\n");
    printf("\t- An IP address, anywhere between 0.0.0.0 - 255.255.255.255\n");
    printf("[!] <start port>\n");
    printf("\t- A beginning port, anywhere between 1 - 65535\n");
    printf("[!] <end port>\n");
    printf("\t- An end port, starting on or after <start port>\n");
    printf("[!] help/-h/--help\n");
    printf("\t- Display this help menu\n");
}

// check if user entered args are valid host and ports
int checkArgs(char host[16], char sPort[6], char ePort[6])
{
    int valid = 0;

    // check if IP address is a valid IPv4 address
    struct sockaddr_in sa;
    int ipValid = inet_pton(AF_INET, host, &(sa.sin_addr));

    // check if sPort is a valid port
    int sPortInt = atoi(sPort);
    int sPortValid = 0;
    if (sPortInt > 0 && sPortInt <= 65535)
        sPortValid = 1;

    // check if ePort is a valid port
    int ePortInt = atoi(ePort);
    int ePortValid = 0;
    if (ePortInt >= sPortInt && ePortInt <= 65535)
        ePortValid = 1;

    // set valid based on each variable

    if (ipValid && sPortValid && ePortValid)
        valid = 1;

    return valid;
}

// function to handle port scan
void portScan(char host[16], char sPort[6], char ePort[6])
{
    // intialize our socket 
    struct sockaddr_in sAddress;
    strncpy((char *)&sAddress, "", sizeof(sAddress));
    sAddress.sin_family = AF_INET;
    sAddress.sin_addr.s_addr = inet_addr(host);

    int ports[65535] = {0};
    int openPorts = 0;

    // convert ports to ints
    int start = atoi(sPort);
    int end = atoi(ePort);

    int i, sock, result;

    // loop through our ports and make a connection, checking
    // if the port is open
    for (i = start; i < end; i++)
    {
        sAddress.sin_port = htons(i);
        sock = socket(AF_INET, SOCK_STREAM, 0);

        // see if sock failed to create
        if (sock < 0)
        {
            printf("[-] Error creating socket\n");
            exit(1);
        }


        // connect to socket using provided information (host, port)
        result = connect(sock, (struct sockaddr*)&sAddress, sizeof(sAddress));

        // failed to connect
        if (result < 0)
        {
            // printf("[!] port %d closed on %s\n", i, host);
        }
        else
        {
            ports[i] = 1;
            openPorts = 1;
            printf("[!] port %d open on %s\n", i, host);
        }
        close(sock);
    }

    // if we have open ports, loop through and print the open ports
    if (openPorts)
    {
        int cnt = 0;
        fflush(stdout);
        printf("[+] Open ports on %s:\n", host);
        for (i = 0; i < 65535; i++)
        {
            if (ports[i])
            {
                printf("%5d ", i);
                cnt++;
            }
            // if we've printed 5 ports, insert a new line
            if (cnt == 5)
            {
                printf("\n");
                cnt = 0;
            }    
        }
        printf("\n");
        printf("[!] Done!\n");
    }
    else
    {
        printf("[-] No open ports on %s\n", host);
    }
}

int main (int argc, char *argv[])
{
    // check for correct arguments
    if ((argc > 1 && argc < 5) && (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
    {
        printHelp();
        exit(0);
    }
    else if (argc < 5)
    {
        printf("[-] Invalid arguments, see help:\n");
        printHelp();
        exit(0);
    }

    // set up our host and port variables
    char host[16] = {0};
    strncpy(host, argv[1], 16);

    char sPort[6] = {0};
    strncpy(sPort, argv[2], 5);

    char ePort[6] = {0};
    strncpy(ePort, argv[4], 5);

    // check our arguments
    if (!checkArgs(host, sPort, ePort))
    {
        printf("[-] Invalid arguments, see help:\n");
        printHelp();
        exit(0);
    }

    // scan our host for specified ports
    portScan(host, sPort, ePort);

    return 0;
}