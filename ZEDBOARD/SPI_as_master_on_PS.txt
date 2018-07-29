#include <stdio.h>
#include "platform.h"
#include <xspips.h>
#include <xparameters_ps.h>
#include <sleep.h>

 static XSpiPs *spi1;
int main()
{
    init_platform();
    unsigned char i;
 u8 *k,*f;
k='p';

    XSpiPs_Config *spi_config;

    XSpiPs_LookupConfig(XPAR_PS7_SPI_1_DEVICE_ID);
    XSpiPs_CfgInitialize(&spi1,&spi_config,XPAR_PS7_SPI_1_BASEADDR);
    XSpiPs_SetClkPrescaler(&spi1,XSPIPS_CLK_PRESCALE_256);
    XSpiPs_SetOptions(&spi1,XSPIPS_MASTER_OPTION |XSPIPS_FORCE_SSELECT_OPTION );
    XSpiPs_Enable(&spi1);

print("salve input");

    while(1)
    {

    XSpiPs_SetSlaveSelect(&spi1,0x00);
    XSpiPs_PolledTransfer(&spi1,&k,f,1);

    xil_printf("___%c___",*f);


      sleep(1);

    }
    return 0;
}

