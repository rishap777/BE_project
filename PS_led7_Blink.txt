#include <stdio.h>
#include "platform.h"
#include "xgpiops.h"
#include "xparameters_ps.h"
#include "sleep.h"



int main(void)
{
	XGpioPs led;
	XGpioPs_Config  *bb;

	bb= XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);
	XGpioPs_CfgInitialize(&led,bb,bb->BaseAddr);
	XGpioPs_SetDirectionPin(&led,7,1);
	XGpioPs_SetOutputEnablePin(&led,7,1);
    init_platform();

while(1)
{
	XGpioPs_WritePin(&led,7,0x00);
	sleep(1);
	XGpioPs_WritePin(&led,7,0x01);
		sleep(1);
   xil_printf("heloo worald");
}
    return 0;
}
