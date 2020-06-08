#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
//#include <iostream>
//using namespace std;



int main(int argc, char *argv[])
{   
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    char sendBuff[1025];
    time_t ticks; 
    
    int column=10;
    int row=10;
    
    if (argc==1)
    {   
        printf("column = %d, row=%d\n",column,row);
          
    }else if( argc ==3)
    {   
            column=atoi(argv[1]);
             row=atoi(argv[2]);
           printf("column = %d, row=%d\n",column,row);
    }else
    {
        printf("invalid input!\n");
        exit(1);
    }
    
    //map init
    char map[row][column];
    for(int i=0;i<row;i++){
        memset(map[i],'0',sizeof(map[i]));
        fputs(map[i], stdout);
        printf("\n");
    }
    
    
    printf("waiting for client...\n");
    
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
    listen(listenfd, 10); 
    
    //fflush(stdout);
    while(1)
    {   connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
       // ticks = time(NULL);
       // snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        //write(connfd, sendBuff, strlen(sendBuff)); 
        //matrix
        char nextline[1];
        nextline[0]='\n';
        printf("connected with client\n");
        for (int i=0;i<row;i++)
        {   write(connfd,map[i],column);
            write(connfd,nextline,1);
        }
        close(connfd);
        sleep(1);
     }
}
