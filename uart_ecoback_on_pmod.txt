/*
 * uart.c
 *
 *  Created on: 24-Dec-2017
 *      Author: Rishap
 */


#include<xparameters.h>
#include <xuartps.h>
#include <xil_printf.h>


XUartPs uartps;

int main(void)
{
	unsigned char i=0;
	XUartPs_Config *config;
 XUartPsFormat ccc;

	config = XUartPs_LookupConfig(XPAR_XUARTPS_0_DEVICE_ID);
XUartPs_CfgInitialize(&uartps,config,XPAR_XUARTPS_0_BASEADDR);
//XUartPs_SetBaudRate(&uartps,9600);
XUartPs_SetOperMode(&uartps,XUARTPS_OPER_MODE_NORMAL);

  XUartPs_EnableUart(&uartps);
ccc.BaudRate=9600;
  ccc.DataBits=0;
     ccc.Parity=4;
      ccc.StopBits=0;
      XUartPs_SetDataFormat(&uartps,&ccc);
while(1)

{

	XUartPs_SendByte(XPAR_XUARTPS_0_BASEADDR,i);
  i=XUartPs_RecvByte(XPAR_XUARTPS_0_BASEADDR);
}

return(0);
}
