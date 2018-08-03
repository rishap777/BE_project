/*
    Simple udp client
*/
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <sys/time.h>
 
#define SERVER "192.168.43.228"
#define BUFLEN 250  //Max length of buffer
//#define No_STR 10000  //Max length of buffer
#define PORT 4080   //The port on which to send data

long No_STR = 1;  //Max length of buffer

long Succes = 0;
long Fail = 0;
long Loop_Count = 0;
long getMicrotime();
long Start_Time = 0;
long Stop_Time    = 0;

void die(char *s)
{
    perror(s);
    exit(1);
}

void bin(unsigned char n)
{
    /* step 1 */
    if (n > 1)
    bin(n/2);
 
    /* step 2 */
    printf("%d", n % 2);
}
 
int main(void)
{
    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    unsigned char Recev_Message[BUFLEN+4];
    unsigned char Temp_Message[BUFLEN+4];
    unsigned char Send_Message[BUFLEN+4];
    unsigned long Time_Massage[No_STR];

    

    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
 
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
     
    if (inet_aton(SERVER , &si_other.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
    
    time_t t;
        for(Loop_Count = 0 ; Loop_Count < No_STR ; Loop_Count++)
    {
    /* Intializes random number generator */
        srand((unsigned) time(&t));
    
    Send_Message[0] = '@';
    Send_Message[1] = 0x03;
    Send_Message[2] = BUFLEN;
    
    
    
        /* Print 5 random numbers from 0 to 49 */
        for( i = 0 ; i < BUFLEN ; i++ )
        {
          Send_Message[i+3] = (rand() % 26)+'a';
      //printf("%d\t%c\n",i,Send_Message[i+3]);    
        }
        Send_Message[i+3] = '#';
    
    //printf("\nWe Are Started\n");
///////////////////////////////////////////////////////////////////////////////////////
    for( i = 0 ; i <BUFLEN+4 ; i++ )
        {
          //printf("\n%d\t%c\t",i+1,Send_Message[i]);
      //bin(Send_Message[i]);
      
      //printf("%c",Send_Message[i]);
      Temp_Message[i] = Send_Message[i];
      
        }
    //printf("\n");
///////////////////////////////////////////////////////////////////////////////////////
        //send the message
    //memset(Recev_Message,'\0',  BUFLEN);
    //Start_Time = getMicrotime();
        if (sendto(s, Send_Message, strlen(Send_Message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }
    
    //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data
        //Stop_Time = getMicrotime();
        //try to receive some data, this is a blocking call
        if (recvfrom(s, Recev_Message, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
        {
            die("recvfrom()");
        }
        
    //Time_Massage[Loop_Count] = Stop_Time - Start_Time;  
        //puts(Recev_Message);

        /* Print 5 random numbers from 0 to 49 */
        for( i = 0 ; i < BUFLEN+3 ; i++ )
        {
          Send_Message[i] = 0;
        }

    Send_Message[0] = '@';
    Send_Message[1] = 0x02;
    Send_Message[2] = BUFLEN;
    Send_Message[3] = '#';

    //send the message
        if (sendto(s, Send_Message, strlen(Send_Message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }
         
    
        //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data
        //memset(Recev_Message,'\0', BUFLEN+4);
    //try to receive some data, this is a blocking call
        if (recvfrom(s, Recev_Message, BUFLEN+4, 0, (struct sockaddr *) &si_other, &slen) == -1)
        {
            die("recvfrom()");
        }
         
        //puts(Recev_Message);
        //printf("Temp Message is \n");
    //puts(Temp_Message);
    
    char result = 0;
    int Loop = 0;
    //printf(".");
    
    //printf("\n No\t Rx\t Tx\n");
    /* Compare the two strings provided */
         for(Loop=3 ; Loop < BUFLEN+3; Loop++)
    {
        //printf("\n %d \t %c \t %c\t",Loop-2,Recev_Message[Loop],Temp_Message[Loop]);
        if(Recev_Message[Loop]  != Temp_Message[Loop])
        {
            //printf("Char are the Not same\n");
            result = 1;
            break;
        }
        else
        {
            //printf("Strings are  same\n");
        }
            
    }
    /* Compare the two strings provided */
        //char result = strcmp(Recev_Message, Send_Message);
        /* If the two strings are the same say so */
        if (result == 0)
    {
        //printf("\nStrings are the same\n");
        Succes ++;
        printf("\n%ld",Succes);
    }
    else
    {
        //printf("\nStrings are Not same\n");
        Fail ++;
	printf("\n%ld",Fail);
    }
	
    }
    printf("\n");
    printf("Length of String = %d\n",BUFLEN);
    printf("Number of String = %ld\n",No_STR);
    printf("Success Result = %ld\n",Succes);
    printf("Fail Result = %ld\n",Fail);
   // printf("Avg Time = %ld\n",);
    printf("\n");
    close(s);
    return 0;
}

long getMicrotime(){
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}
