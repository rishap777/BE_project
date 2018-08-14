#include <stdio.h>
#include "platform.h"
#include <xspips.h>
#include<xparameters.h>
#include <xgpiops.h>
#include <xparameters_ps.h>
#include <sleep.h>
#include <string.h>



 static XSpiPs *spi1;
int main()
{
    init_platform();
   // unsigned int const buff_len=260;
    unsigned int i=0,j=0,flag=0,k=0,l=0;
 unsigned char data[260],temp[260],r,s1[260],s2[260],s3[260],dummy='*',test[5]="rishi";
 unsigned char s=0,stop=0,adrr=0,rw=0,len=0,start_byte='@',stop_byte='#';

 XGpioPs led;
 XGpioPs_Config  *bb;
 bb= XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);
 XGpioPs_CfgInitialize(&led,bb,bb->BaseAddr);
XGpioPs_SetDirectionPin(&led,9,1);
 XGpioPs_SetDirectionPin(&led,7,1);
 XGpioPs_SetOutputEnablePin(&led,7,1);
 XGpioPs_SetOutputEnablePin(&led,9,1);

 XSpiPs_Config *spi_config;


    XSpiPs_LookupConfig(XPAR_PS7_SPI_1_DEVICE_ID);
    XSpiPs_CfgInitialize(&spi1,&spi_config,XPAR_PS7_SPI_1_BASEADDR);
    //XSpiPs_SetClkPrescaler(&spi1,XSPIPS_CLK_PRESCALE_256);
   // XSpiPs_SetOptions(&spi1,XSPIPS_);//XSPIPS_MASTER_OPTION |XSPIPS_FORCE_SSELECT_OPTION );
    XSpiPs_Enable(&spi1);

print("MASTER input");
i=0;
//XGpioPs_WritePin(&led,9,0);
    while(1)
    {


    		XSpiPs_PolledTransfer(&spi1,&dummy,&r,1);

			//xil_printf("%c",r);
    		s=r;
    		//xil_printf("_up_");
			if(s=='@')
			{
				i=0;
				while(stop!='#')
				{
				XSpiPs_PolledTransfer(&spi1,&dummy,&r,1);
				stop=r;

				temp[i]=r;

				//xil_printf("_%c_",temp[i]);

				i++;

				}
				// XGpioPs_WritePin(&led,7,1);

				adrr=temp[0];  //transferring (address+r/w) byte
				rw=adrr & 0x01; // checking the r/w bit and storing in rw
				adrr=(adrr>>1); // assigning the address no as it is of 7 bit only
				//xil_printf("_adrr=%c_",adrr);
				len=temp[1];
				//xil_printf("_len=%c_",len);

				if(rw==1) 		// rw=1 indicates write operation
				{
					if(adrr<0x7F)
					{
						for(j=2,k=adrr;j<len+2;j++,k++)
						{
							s1[k]=temp[j];
							xil_printf("_%c_",s1[k]);
						}
//						for(l=0;l<len;l++)
//						{
//						xil_printf("_%c_",s1[l]);
//						}
					}


					else
					{
						xil_printf("invalid address\n");
					}// invalid address

				}// rw==1 termination

				else if(rw==0) //   rw==0 read operation
				{
					i=0;
					if(adrr<0x7F)
					{
						XSpiPs_PolledTransfer(&spi1,&start_byte,&r,1);
						XSpiPs_PolledTransfer(&spi1,&adrr,&r,1);
						XSpiPs_PolledTransfer(&spi1,&len,&r,1);
						for(l=adrr;l<(len+adrr);l++)
						{
							XSpiPs_PolledTransfer(&spi1,&s1[l],&r,1);
							//test=test+1;
						}
						XSpiPs_PolledTransfer(&spi1,&stop_byte,&r,1);
					}// address 1 write

					else
					{
						xil_printf("invalid address\n");
					}// invalid address
					rw=1;
				}//rw==0 termination
				s=0,stop=0;
			}//start byte termination
			else
			{
				//xil_printf("invalid frame\n");
			}


			//XGpioPs_WritePin(&led,7,0);

    }//while(1) termination
    return 0;
}
