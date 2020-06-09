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
    char man;
    struct sockaddr_in serv_addr; 

    if(argc != 4)
    {
        printf("\n Usage: %s <ip of server> <portnumber(5000)><manual/automatic> \n",argv[0]);
        return 1;
    } else if(strcmp(argv[2], "5000") != 0){
        printf("please enter 5000 as port number!\n");
        return 1;
    } else if(strcmp(argv[3], "manual") != 0&&strcmp(argv[3], "automatic") != 0){
        printf("enter either manual or automatic!\n");
            return 1;
    }
    if (strcmp(argv[3], "manual") == 0){
        man='1';
    }else
        man='0';
    
    
    
    memset(sendBuff,endC,sizeof(sendBuff));
    memset(recvBuff,endC,sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr,'0',sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); 

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
    char cc[2];
    cc[0]=man;
    
    strcat(argv[1],cc);
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
    if(man=='1')
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
    //read the reply
     memset(recvBuff,endC,sizeof(recvBuff));
     read(sockfd, recvBuff, strlen(recvBuff));
     i=0; 
     while(recvBuff[i]!=endC)
    {  cout<<recvBuff[i];
        i++;
    }
    }else
    {   while(1){
            srand(time(0));
            userCol=rand()%column;
            userRow=rand()%row;
            printf("you randomed column=%d, row= %d\n",userCol,userRow);
             //send numbers
            sprintf(userRowC,"%ld",userRow);
            sprintf(userColC,"%ld",userCol);
            char ch[2];
            ch[0]=sepC;
            strcat(userColC,ch);
            strcat(userColC,userRowC);
            write(sockfd, userColC,strlen(userColC));
            //read the reply
            memset(recvBuff,endC,sizeof(recvBuff));
            read(sockfd, recvBuff, strlen(recvBuff));
            i=0; 
            while(recvBuff[i]!=endC)
            {  cout<<recvBuff[i];
                i++;
            }
        sleep(3);
        }
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
