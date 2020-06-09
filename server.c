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
#include <iostream>
using namespace std;

//if start another server right after ending one, connection issue may happen. Wait about 20s after close one server.


int main(int argc, char *argv[])
{   
    int listenfd = 0, connfd = 0, n=0,i=0;
    struct sockaddr_in serv_addr; 
    char recvBuff[1024];
    char sendBuff[1025];
    char r[11],c[11]; //initial 
    char endC='@';
    char sepC='~';
    time_t ticks; 
    char man;
    
    int column=10;//init
    int row=10;//init
    int userCol,userRow;
    char userColC[11],userRowC[11];
    
    if (argc==1)
    {   
        printf("column = %d, row=%d\n",column,row);
          
    }else if( argc ==3)
    {   
            column=atoi(argv[1]);
             row=atoi(argv[2]);
            if (column<=0||row<=0){
                printf("input numbers larger than 0");
                exit(1);
            }
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
        for(int j=0;j<column;j++)
            printf("%c",map[i][j]);
        printf("\n");
    }
    
    printf("Server started...\n");
    
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
    listen(listenfd, 10); 
    
    
    while(1)
    {   connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); //connected
        memset(sendBuff, endC, sizeof(sendBuff)); 
        memset(recvBuff,endC,sizeof(recvBuff));
     //read the ip address
        read(connfd, recvBuff, strlen(recvBuff));
     //send n of columns and rows
        sprintf(r,"%ld", row);
        sprintf(c,"%ld",column);
     char ch[2];
     ch[0]=sepC;
     strcat(c,ch);
     strcat(c,r);
        write(connfd, c,strlen(c));
        
    //client info
     printf("connected with client ");
     int i=0;
        while (recvBuff[i+1]!=endC)
        {   
            printf("%c",recvBuff[i]);          
            i++;
        }
     man=recvBuff[i];
     printf("\n"); //ip address finished 
     //diverge
     if(man=='1')
     {//read user's number
        memset(userColC,endC,sizeof(userColC));
        memset(userRowC,endC,sizeof(userRowC));
        memset(recvBuff,endC,sizeof(recvBuff));
        read(connfd, recvBuff, strlen(recvBuff));

        i=0;
        while(recvBuff[i]!=sepC)
        {
            userColC[i]=recvBuff[i];
            i++;
        }
        i++;
        int k=0;
        while(recvBuff[i]!=endC)
        {   userRowC[k]=recvBuff[i];
            k++;
            i++;    
        }
        userCol=atoi(userColC);
        userRow=atoi(userRowC);
        printf("The user choose the seat on column =%d and row= %d \n",userCol,userRow);
        if(map[userRow][userCol]=='0')//avilable 
        {   map[userRow][userCol]='1';
            printf("user booked a seat.\n");
            write(connfd,"You successfully booked a seat!\n",sizeof("You successfully booked a seat!\n"));
            for(int i=0;i<row;i++)
            {
                for(int j=0;j<column;j++)
                    printf("%c",map[i][j]);
                printf("\n");
            }
        }else//unavailiable
        {   printf("user failed to book that seat\n");
         write(connfd,"That seat is unavailable!\n",sizeof("That seat is unavailable!\n"));
        }
     }else{//auto
        bool full=false;
        while(!full){
            full=true;
            for( int i=0;i<row;i++)
                for(int j=0;j<column;j++)
                    if (map[i][j]=='0')
                        full=false;
            
        //read user's number
        memset(userColC,endC,sizeof(userColC));
        memset(userRowC,endC,sizeof(userRowC));
        memset(recvBuff,endC,sizeof(recvBuff));
        read(connfd, recvBuff, strlen(recvBuff));

        i=0;
        while(recvBuff[i]!=sepC)
        {
            userColC[i]=recvBuff[i];
            i++;
        }
        i++;
        int k=0;
        while(recvBuff[i]!=endC)
        {   userRowC[k]=recvBuff[i];
            k++;
            i++;    
        }
        userCol=atoi(userColC);
        userRow=atoi(userRowC);
        printf("The user choose the seat on column =%d and row= %d \n",userCol,userRow);
        if(map[userRow][userCol]=='0')//avilable 
        {   map[userRow][userCol]='1';
            printf("user booked a seat.\n");
            write(connfd,"You successfully booked a seat!\n",sizeof("You successfully booked a seat!\n"));
            for(int i=0;i<row;i++)
            {
                for(int j=0;j<column;j++)
                    printf("%c",map[i][j]);
                printf("\n");
            }
        }else//unavailiable
        {   printf("user failed to book that seat\n");
         write(connfd,"That seat is unavailable!\n",sizeof("That seat is unavailable!\n"));
        }
        }
     }
     
     fflush(stdout);
     close(connfd);
     sleep(1);
     }
}
