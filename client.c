/* CHANGES FROM UNIX VERSION                                                   */
/*                                                                             */
/* 1.  Changed header files.                                                   */
/* 2.  Added WSAStartUP() and WSACleanUp().                                    */
/* 3.  Used closesocket() instead of close().                                  */

// Don't forget to include "wsock32" in the library list.

#include <stdio.h>      /* for printf(), fprintf() */
#include <winsock.h>    /* for socket(),... */
#include <stdlib.h>
#include <winsock2.h>     /* for exit() */
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#define ECHOMAX 255     /* Longest string to echo */

    char *sendBuff;
    int sock;                        /* Socket descriptor */
    struct sockaddr_in ServerAddr; /* Echo server address */
    struct sockaddr_in fromAddr;     /* Source address of echo */
    unsigned short ServerPort;     /* Echo server port */
    unsigned int fromSize;           /* In-out of address size for recvfrom() */
    char recvBuff[255];        /* Buffer for echo string */
    WSADATA wsaData;                 /* Structure for WinSock setup communication */
    int sendRes;
    int i; /*index*/
    int option;/* The option user click */
    float delays[100]={0.0}; /* Array of option 4 - delay from server */
    float diff[101]={0.0};/* Array of option 5 - diff the delays from server */
    double avgDelay=0;/* For option 4 - to calculate the avg */
    int sumDiffDelays=0;/* For option 4 - to calculate the avg */
    float sum =0; /*for option 5 to caculate the sum*/
    int size_of_buff=0;
    int j=0; /*index*/
    float temp = 0; /*for option 4*/



void DieWithError(char *errorMessage)
{
    fprintf(stderr,"%s: %d\n", errorMessage, WSAGetLastError());
    exit(1);
}  /* External error handling function */

int printMenu() /*prints the menu and check if the input is valid or not */
{
    int option = 0 ;
    int flag = 1; /*for testing the input from the user*/
    printf("\nPlease insert an option :\n");
	printf("\n 1 : Get the current time.");
	printf("\n 2 : Get time without year.");
	printf("\n 3 : Get time since epoch.");
	printf("\n 4 : Get client to server delay estimation.");
	printf("\n 5 : Measure RTT.");
	printf("\n 6 : Get day and month.");

    printf("\n Your option : ");
    if(scanf("%d",&option)==1)
    {
        if(option <=6 && option >= 1)
        {
            flag=0;
        }
        else
        {
            puts("Invalid Input. The program will terminate");
            exit(1);
        }
    }
    else
    {
        puts("Invalid Input. The program will terminate");
        exit(1);
    }
	return option;
}

void doAll (int option)
{
     if(option == 1)
    {
        sendBuff = "What's the time?";
            if (sendRes = sendto(sock, sendBuff, strlen(sendBuff), 0, (struct sockaddr *)
               &ServerAddr, sizeof(ServerAddr)) < 0)
               {
                   DieWithError("Error at sendto()");
               }

             fromSize = sizeof(fromAddr);

    if (recvfrom(sock, recvBuff, 255, 0, (struct sockaddr *) &fromAddr,&fromSize) < 0)
    {
            DieWithError("Error at recvfrom()");
    }
    size_of_buff = strlen(recvBuff);
    recvBuff[size_of_buff] = '\0';
    printf("\nClient Received : %s\n",recvBuff);
    printf("Closing Connection.");
    closesocket(sock);
    WSACleanup();  /* Cleanup Winsock */

    }
    else if(option == 2)
    {
        sendBuff = "What's the time2";
        if (sendRes = sendto(sock, sendBuff, strlen(sendBuff), 0, (struct sockaddr *)
               &ServerAddr, sizeof(ServerAddr)) < 0)
               {
                   DieWithError("Error at sendto()");
               }

        fromSize = sizeof(fromAddr);

    if (recvfrom(sock, recvBuff, 255, 0, (struct sockaddr *) &fromAddr,&fromSize) < 0)
    {
            DieWithError("Error at recvfrom()");
    }
    size_of_buff = strlen(recvBuff);
    recvBuff[size_of_buff ] = '\0';
    printf("\nClient Received : %s\n",recvBuff);
    printf("Closing Connection.");
    closesocket(sock);
    WSACleanup();  /* Cleanup Winsock */

    }

    else if(option == 3)
    {
        sendBuff = "What's the time3";
        if (sendRes = sendto(sock, sendBuff, strlen(sendBuff), 0, (struct sockaddr *)
               &ServerAddr, sizeof(ServerAddr)) < 0)
               {
                   DieWithError("Error at sendto()");
               }

        fromSize = sizeof(fromAddr);

    if (recvfrom(sock, recvBuff, 255, 0, (struct sockaddr *) &fromAddr,&fromSize) < 0)
    {
            DieWithError("Error at recvfrom()");
    }
    size_of_buff = strlen(recvBuff);
    recvBuff[size_of_buff]='\0';
    printf("\nClient Received : %s\n",recvBuff);
    printf("Closing Connection.");
    closesocket(sock);
    WSACleanup();  /* Cleanup Winsock */
    }

     else if(option == 4)
    {
        sendBuff="What's the time4";
        for(i=0;i<100;i++)
        {
            if (sendRes = sendto(sock, sendBuff, strlen(sendBuff), 0, (struct sockaddr *)
               &ServerAddr, sizeof(ServerAddr)) < 0)
               {
                   DieWithError("Error at sendto()");
               }
        }

       for(j=0;j<100;j++)
        {
            fromSize = sizeof(fromAddr);
            if (recvfrom(sock, recvBuff, 255, 0, (struct sockaddr *) &fromAddr,&fromSize) < 0)
            {
                DieWithError("Error at recvfrom()");
            }

            recvBuff[strlen(recvBuff)]='\0';
            temp = atof(recvBuff);
            delays[j]=temp;

            if(j>0)
            {
                sum+=(delays[j]-delays[j-1]);/*sum of the diffs*/
            }
        }

            printf("Delay average is : %lf\n",sum/99.0);
            printf("Closing Connection.");
            closesocket(sock);
            WSACleanup();  /* Cleanup Winsock */
            exit(0);

        }

    else if(option == 5)
    {
        sendBuff="What's the time5";
        for(i=0;i<100;i++)
        {
            DWORD theTime = GetTickCount();

            if (sendRes = sendto(sock, sendBuff, strlen(sendBuff), 0, (struct sockaddr *)
                   &ServerAddr, sizeof(ServerAddr)) < 0)
                {
                       DieWithError("Error at sendto()");
                }

            diff[i] = theTime;
            fromSize = sizeof(fromAddr);


            if (recvfrom(sock, recvBuff, 255, 0, (struct sockaddr *) &fromAddr,&fromSize) < 0)
            {
                DieWithError("Error at recvfrom()");
            }

            theTime = GetTickCount();
            diff[i] = theTime - diff[i]; /* to caculate the diff*/

            sumDiffDelays += diff[i];/*the sum to caculate the avarage*/

        }/*end for*/
        printf("\nThe avarage is %f", (float)(sumDiffDelays/100.0));

    }

    /*option 6*/
    else if(option == 6)
    {
        sendBuff="What's the time6";

        if (sendRes = sendto(sock, sendBuff, strlen(sendBuff), 0, (struct sockaddr *)
                   &ServerAddr, sizeof(ServerAddr)) < 0)
            {
                DieWithError("Error at sendto()");
            }

        fromSize = sizeof(fromAddr);


        if (recvfrom(sock, recvBuff, 255, 0, (struct sockaddr *) &fromAddr,&fromSize) < 0)
        {
                DieWithError("Error at recvfrom()");
        }
        size_of_buff = strlen(recvBuff);
        recvBuff[size_of_buff]='\0';
        printf("\nClient Received: %s",recvBuff);
    }

    closesocket(sock);
    WSACleanup();  /* Cleanup Winsock */
    exit(0);
}


void main(int argc, char *argv[])
{

     if ((argc < 2))    /* Test for correct number of arguments */
    {
        fprintf(stderr, "Error: no server port provided\n");
        exit(1);
    }
    ServerPort = atoi(argv[1]);
    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) /* Load Winsock 2.0 DLL */
    {
        fprintf(stderr, "WSAStartup() failed");
        exit(1);
    }

    /* Create a best-effort datagram socket using UDP */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        DieWithError("socket() failed");

    /* Construct the server address structure */
    memset(&ServerAddr, 0, sizeof(ServerAddr));    /* Zero out structure */
    ServerAddr.sin_family = AF_INET;                 /* Internet address family */
    ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  /* Server IP address */

    ServerAddr.sin_port = htons(ServerPort);     /* Server port */

    /* Send the string, including the null terminator, to the server */
    option = printMenu(); /*print the menu for the user*/
    doAll(option); /*sending to the option that user chose*/

    printf("Closing Connection.");

    return 0;
}
