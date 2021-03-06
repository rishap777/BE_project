#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include<SPI.h>

const char* ssid = "Rishap";
const char* password = "87654321";

char Receive_Slave[255];
char j = 0 , Num =0;

WiFiUDP Udp;
unsigned int localUdpPort = 4080;  // local port to listen on
char incomingPacket[512];  // buffer for incoming packets
char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back

char buff[]="Hello Slave\n";

void setup()
{                                    //configure the line as output
  Serial.begin(115200);              //Set UART baud rate                                 //Initialize the CS line to HIGH
  
  Serial.println();
  pinMode(D8,OUTPUT);
  
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
 
    SPI.begin();  /* begin SPI */
  
    for(int i=0; i<sizeof buff; i++)  /* transfer buff data per second */
    SPI.transfer(buff[i]);                                 //Pull CS Line High
}


void loop()
{
  j=0;
  Num=0;
       
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    //delay(100);
   // Serial.printf("\nReceived %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 512);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
      
    //SPI.transfer('\n');
    //Serial.println('\n');
    
    digitalWrite(D8,HIGH);
    
    if( strlen(incomingPacket) == 4)
     {
      //Serial.println("Enter in Read Mode");
      
      digitalWrite(D8,LOW);
      for( int i=0 ; i< strlen(incomingPacket); i++)
      {
        SPI.transfer(incomingPacket[i]);
        Serial.print(incomingPacket[i]);
        if(incomingPacket[i] == '#')
        {
          break;
        }
      }
      SPI.transfer('\n');
      //Serial.println('\n');
      digitalWrite(D8,HIGH);


      for(int count=0 ; count < strlen(Receive_Slave) ; count++)
      {
        Receive_Slave[Num] = 0;
      }
       digitalWrite(D8,LOW);
       do
       {
          j = SPI.transfer('r');
          Receive_Slave[Num] = j;
          Serial.print(Receive_Slave[Num]);
          Num++;
       }while(j!='#');
       
       digitalWrite(D8,HIGH);
       
      // send back a reply, to the IP address and port we got the packet from
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.write(Receive_Slave);
      Udp.endPacket();
    }
    else
    {
      digitalWrite(D8,LOW);
      for( int i=0 ; i< strlen(incomingPacket); i++)
      {
        SPI.transfer(incomingPacket[i]);
        Serial.print(incomingPacket[i]);
        if(incomingPacket[i] == '#')
        {
          break;
        }
      }
      Serial.print("\n");
      SPI.transfer('\n');
      digitalWrite(D8,HIGH);
       
      // send back a reply, to the IP address and port we got the packet from
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.write(replyPacket);
      Udp.endPacket();
    }
    
  }
}
