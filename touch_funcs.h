
#ifndef TOUCH_FUNCS_H_
#define TOUCH_FUNCS_H_





#endif /* TOUCH_FUNCS_H_ */


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



extern tPushButtonWidget SINE;
void touch_SINE(tWidget *psWidget);

extern tPushButtonWidget TRIANGLE;
void touch_TRIANGLE(tWidget *psWidget);

extern tPushButtonWidget SQUARE;
void touch_SQUARE(tWidget *psWidget);

extern tPushButtonWidget freq_plus;
void touch_freq_plus(tWidget *psWidget);

extern tPushButtonWidget freq_minus;
void touch_freq_minus(tWidget *psWidget);

extern tPushButtonWidget generate;
void touch_generate(tWidget *psWidget);

extern tPushButtonWidget back;
void touch_back(tWidget *psWidget);

extern tPushButtonWidget left;
void touch_left(tWidget *psWidget);

extern tPushButtonWidget right;
void touch_right(tWidget *psWidget);


void display_fun(void);
void clr_scrn(void);
void generate_sine(void);

