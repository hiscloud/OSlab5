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
    int listenfd = 0, connfd = 0, n=0;
    struct sockaddr_in serv_addr; 
    char recvBuff[1024];
    char sendBuff[1025];
    char endC='@';
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
        memset(map[i],'1',sizeof(map[i]));
        for(int j=0;j<column;j++)
            printf("%c",map[i][j]);
        printf("\n");
    }
    
    
    printf("Server started...\n");
    
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, endC, sizeof(sendBuff)); 
    memset(recvBuff,endC,sizeof(recvBuff));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(6666); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
    listen(listenfd, 10); 
    
    //fflush(stdout);
    while(1)
    {   connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
     
        write(connfd, sendBuff, strlen(sendBuff));
     //char nextline[1];
     // nextline[0]='\n';
    // for (int i=0;i<row;i++)
     //   {   write(connfd,map[i],column);
      //      write(connfd,nextline,1);
       // }
     
        read(connfd, recvBuff, strlen(recvBuff));
        
    
   //  while ( (n = read(connfd, recvBuff, sizeof(recvBuff)-1)) > 0)
   // {
       // cout<<n<<endl;
   //     recvBuff[n] = 0;
 //       if(fputs(recvBuff, stdout) == EOF)
 //       {
  //          printf("\n Error : Fputs error\n");
   //     }
    //} 
        //matrix
        printf("connected with client ");
       // fputs(recvBuff, stdout);
    // char c=' ';
     int i=0;
        while (recvBuff[i]!=endC)
        {   
            printf("%c",recvBuff[i]);          
            i++;
            
        }
     printf("\n"); //ip address
     
     
     fflush(stdout);
       write(connfd, "sbbb", strlen("sbbb"));
        
     close(connfd);
        sleep(1);
     }
}
