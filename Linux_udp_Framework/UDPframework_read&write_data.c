/*
    Simple udp client
*/

#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
 
#define SERVER "192.168.43.228"
#define BUFLEN 1024  //Max length of buffer
#define PORT 4080   //The port on which to send data
 
    char buffer[1024];
    unsigned char start_Byte = '@';
    unsigned char No_of_Data = 0x00;
    unsigned char stop_Byte = '#';
    unsigned char Temp_Byte = 0x00;
    unsigned char Addr_Byte = 0x00;

void die(char *s)
{
    perror(s);
    exit(1);
}

/*********** Function To Print Binary value **************/

void bin(unsigned char n)
{
    /* step 1 */
    if (n > 1)
    bin(n/2);
 
    /* step 2 */
    printf("%d", n % 2);
}

int main(int argc, char* argv[])
{
    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    unsigned char buf[BUFLEN];
 
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
 
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
    while(1)
    {
	printf("\nEnter Read/Write: \n");
	scanf("%c",&Temp_Byte);

/********************** Function To Build Fram ****************************/	
	
	
	
        if(Temp_Byte == 'W' || Temp_Byte == 'w' || Temp_Byte == '1' )
	{
		printf("\nEnter message : \n");
		scanf("%s",buffer);

		do
		{
			printf("\nEnter Address between 0X00 - 0X7F : \n");
			scanf("%x",&Addr_Byte);
			
		}
		while(Addr_Byte > 0x7F);

		// 0b01010101<<1 | 0b00000001 i.e 0b10101011
		Addr_Byte = (Addr_Byte<<1) | 0x01;

		

		No_of_Data = strlen(buffer);

		char message[No_of_Data + 4];
		message[0] = start_Byte;
	
		message[1] = Addr_Byte;
	
		message[2] = No_of_Data;
		;
		for( i = 0; i <= No_of_Data ; i++ )
		{	
			//printf("%c",buffer[i]);
			message[3+i] = buffer[i];
		}
		message[i+2] = stop_Byte;
		
		printf("\n");
		for( i = 0; i <= No_of_Data +3 ; i++ )
		{
			//printf("%c \t ",Frame[i]);
			bin(message[i]);
			printf(" \t  %c\n",message[i]);
		
		}
		printf("\n");

	/*****************************************************************************/
		 printf("\n%d\n",strlen(message));
		//send the message
		if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
		{
		    die("sendto()");
		}
		 
		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf,'\0', BUFLEN);
		//try to receive some data, this is a blocking call
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
		{
		    die("recvfrom()");
		}
		 
		puts(buf);

		
		unsigned char R_message[] = {'@',0x02,20,'#'};
		
		if (sendto(s, R_message, strlen(R_message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
		{
		    die("sendto()");
		}
		 
		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf,'\0', BUFLEN);
		//try to receive some data, this is a blocking call
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
		{
		    die("recvfrom()");
		}
		 
		puts(buf);
	}
	else if(Temp_Byte == 'R' || Temp_Byte == 'r' || Temp_Byte == '0' )
	{
		printf("\nEnter No of Bytes to be Read : \n");
		scanf("%d",&No_of_Data);
		
		do
		{
			printf("\nEnter Address between 0X00 - 0X7F : \n");
			scanf("%x",&Addr_Byte);
			
		}
		while(Addr_Byte > 0x7F);


		// 0b01010101<<1 & 0b11111110 i.e 0b10101011
		Addr_Byte = (Addr_Byte<<1) & 0xFE;

		//No_of_Data = strlen(buffer);

		char message[4];
		message[0] = start_Byte;
	
		message[1] = Addr_Byte;
	
		message[2] = No_of_Data;
	
		message[3] = stop_Byte;
		
		printf("\n");
		for( i = 0; i < 4 ; i++ )
		{
			//printf("%c \t ",Frame[i]);
			bin(message[i]);
			printf(" \t  %c\n",message[i]);
		
		}
		printf("\n");

	/*****************************************************************************/
		printf("\n%d\n",strlen(message));
		//send the message
		if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
		{
		    die("sendto()");
		}
		 
		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf,'\0', BUFLEN);
		//try to receive some data, this is a blocking call
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
		{
		    die("recvfrom()");
		}
		 puts("hello");
		puts(buf);
	}
    }
 
    close(s);
    return 0;
}
