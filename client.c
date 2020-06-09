#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0,i=0;
    int column,row;
    int userCol,userRow;
    char userColC[11],userRowC[11];
    char c[11],r[11];
    char recvBuff[1024];
    char sendBuff[1025];
    char endC='@';
    char sepC='~';
    int man=1;
    struct sockaddr_in serv_addr; 

    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    } 
    memset(sendBuff,endC,sizeof(sendBuff));
    memset(recvBuff,endC,sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr,'0',sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(6666); 

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    
    } 
   //////////////////////////////////////////////////////////////////////
     write(sockfd,argv[1],strlen(argv[1])); //pass the ip address
  /*  
    while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
       // cout<<n<<endl;
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
    } 
      if(n < 0)
    {
        printf("\n Read error \n");
    } */
    //reading the number in the buffer
    read(sockfd, recvBuff, strlen(recvBuff));
      i=0;
        while (recvBuff[i]!=endC)
        {   
            printf("%c",recvBuff[i]);          
            i++;
        }
    //extract the numbers from the buffer
    i=0;
    while(recvBuff[i]!=sepC)
    {
        c[i]=recvBuff[i];
        i++;
    }
    i++;
    int k=0;
    while(recvBuff[i]!=endC)
    {   r[k]=recvBuff[i];
        k++;
        i++;    
    }
    column=atoi(c);
    row=atoi(r);
    printf("The map has %d columns and %d rows.\n",column,row);
    //diverge
    if(man)
    {   printf("enter the column number of the seat you want to book: ");
        cin>>userCol;  
        printf("enter the row number: ");
        cin>>userRow;
     //send numbers
        sprintf(userRowC,"%ld",userRow);
        sprintf(userColC,"%ld",userCol);
        char ch[2];
     ch[0]=sepC;
     strcat(userColC,ch);
     strcat(userColC,userRowC);
     write(sockfd, userColC,strlen(userColC));
     //   write(sockfd, &sepC,1);
      //  write(sockfd, userRowC, strlen(userRowC));
    }else
    {   
    }
    //snprintf(sendBuff, sizeof(sendBuff),  argv[1]);
     
    
 /*   
     memset(recvBuff,endC,sizeof(recvBuff));
     read(sockfd, recvBuff, strlen(recvBuff));
      i=0;
        while (recvBuff[i]!=endC)
        {   
            printf("%c",recvBuff[i]);          
            i++;
            
        }
   */ 
    //for (int i=0;i<strlen(recvBuff);i++)
   //     cout<<recvBuff[i];
    return 0;
}
