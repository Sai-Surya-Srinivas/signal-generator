#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_nvic.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/flash.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "driverlib/udma.h"
#include "driverlib/rom.h"
#include "grlib/grlib.h"
#include "grlib/widget.h"
#include "grlib/canvas.h"
#include "grlib/checkbox.h"
#include "grlib/container.h"
#include "grlib/pushbutton.h"
#include "grlib/radiobutton.h"
#include "grlib/slider.h"
#include "lcd_tools/Kentec320x240x16_ssd2119_spi.h"
#include "lcd_tools/touch.h"


#include "cordic.h"
#include "touch_funcs.h"






uint32_t ui32SysClock;
tContext sContext;




void system_init(void)
{


    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);



    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    IntMasterEnable();
}

int main(void){

    system_init();

    ui32SysClock = SysCtlClockGet();

    Kentec320x240x16_SSD2119Init(ui32SysClock);
    GrContextInit(&sContext, &g_sKentec320x240x16_SSD2119);

    TouchScreenInit(ui32SysClock);
    TouchScreenCallbackSet(WidgetPointerMessage);
    FPUEnable();
    FPUStackingDisable();
    while(1)
     display_fun();

    return 0;
}


