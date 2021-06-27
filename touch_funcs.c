#include "cordic.h"
#include "touch_funcs.h"
#include "grlib/pushbutton.h"

int back_flag;
extern tContext sContext;
tRectangle sRect,Rect_M,Rect_freq;
float sine_of_teta[1201];
float triangle[1201];
float square[1201];
float freq =1000;
int back_flag;
int value;
int sel;


RectangularButton(SINE, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 40, 50,
                  200, 30, PB_STYLE_FILL | PB_STYLE_TEXT|PB_STYLE_RELEASE_NOTIFY, ClrDarkBlue, ClrDarkRed, 0, ClrSilver,
                  &g_sFontCm20, "SINE", 0, 0, 0, 0,
                  touch_SINE);

RectangularButton(TRIANGLE, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 40, 100,
                  200, 30, PB_STYLE_FILL | PB_STYLE_TEXT|PB_STYLE_RELEASE_NOTIFY, ClrDarkBlue, ClrDarkRed, 0, ClrSilver,
                  &g_sFontCm20, "TRIANGLE", 0, 0, 0, 0,
                  touch_TRIANGLE);

RectangularButton(SQUARE, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 40, 150,
                  200, 30, PB_STYLE_FILL | PB_STYLE_TEXT|PB_STYLE_RELEASE_NOTIFY, ClrDarkBlue, ClrDarkRed, 0, ClrSilver,
                  &g_sFontCm20, "SQUARE", 0, 0, 0, 0,
                  touch_SQUARE);

RectangularButton(freq_plus, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 240, 50,
                  50, 50, PB_STYLE_FILL | PB_STYLE_TEXT, ClrDarkBlue, ClrDarkRed, 0, ClrSilver,
                  &g_sFontCm30, "+", 0, 0, 0, 0,
                  touch_freq_plus);

RectangularButton(freq_minus, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 30, 50,
                  50, 50, PB_STYLE_FILL | PB_STYLE_TEXT, ClrDarkBlue, ClrDarkRed, 0, ClrSilver,
                  &g_sFontCm30, "-", 0, 0, 0, 0,
                  touch_freq_minus);

RectangularButton(generate, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 100, 180,
                  120, 30, PB_STYLE_FILL | PB_STYLE_TEXT|PB_STYLE_RELEASE_NOTIFY, ClrDarkBlue, ClrDarkRed, 0, ClrSilver,
                  &g_sFontCm20, "GENERATE", 0, 0, 0, 0,
                  touch_generate);

RectangularButton(back, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 269, 200,
                  40, 30, PB_STYLE_FILL | PB_STYLE_TEXT|PB_STYLE_RELEASE_NOTIFY, ClrDarkBlue, ClrDarkRed, 0, ClrSilver,
                  &g_sFontCm14, "Back", 0, 0, 0, 0,
                  touch_back);

RectangularButton(left, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 19, 200,
                  40, 30, PB_STYLE_FILL | PB_STYLE_TEXT|PB_STYLE_RELEASE_NOTIFY, ClrDarkBlue, ClrDarkRed, 0, ClrSilver,
                  &g_sFontCm14, "L", 0, 0, 0, 0,
                  touch_left);

RectangularButton(right, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 200, 200,
                  40, 30, PB_STYLE_FILL | PB_STYLE_TEXT|PB_STYLE_RELEASE_NOTIFY, ClrDarkBlue, ClrDarkRed, 0, ClrSilver,
                  &g_sFontCm14, "R", 0, 0, 0, 0,
                  touch_right);




void clr_scrn(void){
    sRect.i16XMin = 0;
      sRect.i16YMin = 0;
      sRect.i16XMax = 319;
      sRect.i16YMax = 239;
      GrContextForegroundSet(&sContext, ClrBlack);
      GrRectFill(&sContext, &sRect);
}


void touch_freq_plus(tWidget *psWidget)
{
        Rect_freq.i16XMin = 100;
        Rect_freq.i16YMin = 50;
        Rect_freq.i16XMax = 220;
        Rect_freq.i16YMax = 100;
        GrContextForegroundSet(&sContext, ClrGreen);
        GrRectFill(&sContext, &Rect_freq);

    if(freq < 100000){
            freq=freq+1000;
        }
    char freq_str[10];
    char * freq_str_ptr=&freq_str;
    itoa(freq,freq_str_ptr,10);
    char Hz[3] = {'H','z'};
    strcat(freq_str,Hz);
    GrContextFontSet(&sContext, &g_sFontCm20);
           GrContextForegroundSet(&sContext, ClrWhite);
            GrStringDrawCentered(&sContext,freq_str_ptr ,10,140,75 ,0);

}
void touch_freq_minus(tWidget *psWidget)
{
    Rect_freq.i16XMin = 100;
        Rect_freq.i16YMin = 50;
        Rect_freq.i16XMax = 220;
        Rect_freq.i16YMax = 100;
        GrContextForegroundSet(&sContext, ClrGreen);
        GrRectFill(&sContext, &Rect_freq);

       if(freq > 100){
               freq=freq-50;
           }
       char freq_str[10];
       char * freq_str_ptr=&freq_str;
       itoa(freq,freq_str_ptr,10);
       char Hz[3] = {'H','z'};
       strcat(freq_str,Hz);
       GrContextFontSet(&sContext, &g_sFontCm20);
       GrContextForegroundSet(&sContext, ClrWhite);
       GrStringDrawCentered(&sContext,freq_str_ptr ,10,140,75 ,0);

}

void freq_sel(void)
{
    clr_scrn();
           WidgetRemove((tWidget *)&SINE);
           WidgetRemove((tWidget *)&TRIANGLE);
           WidgetRemove((tWidget *)&SQUARE);
           WidgetAdd(WIDGET_ROOT, (tWidget *)&freq_plus);
                    WidgetPaint((tWidget *)&freq_plus);
               WidgetAdd(WIDGET_ROOT, (tWidget *)&freq_minus);
                    WidgetPaint((tWidget *)&freq_minus);
               WidgetAdd(WIDGET_ROOT, (tWidget *)&generate);
                    WidgetPaint((tWidget *)&generate);
                Rect_freq.i16XMin = 100;
                Rect_freq.i16YMin = 50;
                Rect_freq.i16XMax = 220;
                Rect_freq.i16YMax = 100;
                GrContextForegroundSet(&sContext, ClrGreen);
                GrRectFill(&sContext, &Rect_freq);
      char freq_str[10];
      char * freq_str_ptr=&freq_str;
      itoa(freq,freq_str_ptr,10);
      char Hz[3] = {'H','z'};
      strcat(freq_str,Hz);
      GrContextFontSet(&sContext, &g_sFontCm20);
             GrContextForegroundSet(&sContext, ClrWhite);
              GrStringDrawCentered(&sContext,freq_str_ptr ,10,140,75 ,0);
}


void touch_SINE(tWidget *psWidget){ sel=1; freq_sel(); }

void touch_TRIANGLE(tWidget *psWidget){ sel=2;freq_sel(); }

void touch_SQUARE(tWidget *psWidget){ sel=3;freq_sel(); }


void display_fun()
{
    clr_scrn();
    back_flag=0;
    WidgetAdd(WIDGET_ROOT, (tWidget *)&SINE);
    WidgetPaint((tWidget *)&SINE);

    WidgetAdd(WIDGET_ROOT, (tWidget *)&TRIANGLE);
    WidgetPaint((tWidget *)&TRIANGLE);

    WidgetAdd(WIDGET_ROOT, (tWidget *)&SQUARE);
    WidgetPaint((tWidget *)&SQUARE);

    while(1)
        {
             WidgetMessageQueueProcess();
             if(back_flag==1) break;

        }

}
void print_sine(int a)
{

    int i=0;
    int step;
    int pixx1=18;
    int pixy1=120;
    int pixx2=18;
    int pixy2=120;
    for(i=a+0;i<=a+300;i++)
    {
        step=(sine_of_teta[i])/0.01;
        pixx1=pixx1+1;
        pixy1=120-step;
        GrContextForegroundSet(&sContext, ClrGreen);
        GrLineDraw(&sContext,pixx1,pixy1,pixx2,pixy2);
        pixx2=pixx1;
        pixy2=pixy1;
    }

}

void touch_back(tWidget *psWidget)
{
    WidgetRemove((tWidget *)&back);
    WidgetRemove((tWidget *)&left);
    WidgetRemove((tWidget *)&right);
    back_flag=1;
}

void generate_triangle()
{


    float T = 1/freq;
    float time=0;
    float tri;
    int i=0;
    while(i<1000)
    {
        while(time<=T/2)
        {
            tri=((4/T)*time) -1;
            triangle[i]=tri;
            i++;
            time=time+0.000001;
            if(i>=1000) break;
        }

        while(time>=T/2 && time<T)
        {
            tri=-((4/T)*(time-T)) -1;
            triangle[i]=tri;
            i++;
            time=time+0.000001;
            if(i>=1000) break;
            if(time>=T){time = 0; break;}
        }
    }

}

void print_triangle(int a)
{
    int pixx1=18;
    int pixy1=120;
    int pixx2=18;
    int pixy2=120;
    int step;
    int i;
    for(i=a+0;i<=a+300;i++)
        {
            step=(triangle[i]/0.01);
            pixx1=pixx1+1;
            pixy1=120-step;
            GrContextForegroundSet(&sContext, ClrGreen);
            GrLineDraw(&sContext,pixx1,pixy1,pixx2,pixy2);
            pixx2=pixx1;
            pixy2=pixy1;
        }
}

void generate_square(void)
{
    float T = 1/freq;
    float time=0;
    int i=0;
    while(i<1000)
       {
           while(time<=T/2)
           {
               square[i]=1;
               i++;
               time=time+0.000001;
               if(i>=1000) break;
           }
           while(time>=T/2 && time<T)
           {
               square[i]=-1;
               i++;
               time=time+0.000001;
               if(i>=1000) break;
               if(time>=T){time = 0; break;}
           }
       }

}

void print_square(int a)
{
     int pixx1=18;
     int pixy1=120;
     int pixx2=18;
     int pixy2=120;
     int i;
     float diff;
     int step;
     for(i=a+0;i<=a+300;i++)
        {
            diff=square[i];
            step=(diff/0.01);
            pixx1=pixx1+1;
            pixy1=120-step;
            GrContextForegroundSet(&sContext, ClrGreen);
            GrLineDraw(&sContext,pixx1,pixy1,pixx2,pixy2);
            pixx2=pixx1;
            pixy2=pixy1;
        }



}


void touch_left(tWidget *psWidget)
{
        int a;
        clr_scrn();
        WidgetRemove((tWidget *)&back);
        value--;
        a=5*(value);
        switch(sel)
           {
           case 1:print_sine(a);
           WidgetAdd(WIDGET_ROOT, (tWidget *)&back);
           WidgetPaint((tWidget *)&back);
               break;

           case 2:
           print_triangle(a);
           WidgetAdd(WIDGET_ROOT, (tWidget *)&back);
           WidgetPaint((tWidget *)&back);
               break;

           case 3:print_square(a);
                  WidgetAdd(WIDGET_ROOT, (tWidget *)&back);
                  WidgetPaint((tWidget *)&back);
               break;

           default:
               break;
           }
        GrContextForegroundSet(&sContext, ClrWhite);

                  GrLineDrawV(&sContext, 18, 15, 225);
                   GrLineDrawH(&sContext, 18, 319, 120);
}

void touch_right(tWidget *psWidget)
{
    int a;
    clr_scrn();
    WidgetRemove((tWidget *)&back);

    value++;
    a=5*(value);


    switch(sel)
       {
       case 1:
           print_sine(a);
       WidgetAdd(WIDGET_ROOT, (tWidget *)&back);
       WidgetPaint((tWidget *)&back);
           break;

       case 2:
       print_triangle(a);
       WidgetAdd(WIDGET_ROOT, (tWidget *)&back);
       WidgetPaint((tWidget *)&back);
           break;

       case 3:print_square(a);
              WidgetAdd(WIDGET_ROOT, (tWidget *)&back);
              WidgetPaint((tWidget *)&back);
           break;

       default:
           break;
       }
    GrContextForegroundSet(&sContext, ClrWhite);

              GrLineDrawV(&sContext, 18, 15, 225);
               GrLineDrawH(&sContext, 18, 319, 120);
}


void generate_sine(void)
{
double x,y;
double t;
double teta;
x=1;
y=0;
int i=0;
for(t=0;t<=0.001;t=t+0.000001)
{

    teta = 360*freq*t;
    sine_of_teta[i]=cordic(x,y,teta);
    i=i+1;
}

}



void touch_generate(tWidget *psWidget)
{
    value=0x0000;
    clr_scrn();
    WidgetRemove((tWidget *)&freq_plus);
    WidgetRemove((tWidget *)&freq_minus);
    WidgetRemove((tWidget *)&generate);

    switch(sel)
    {
    case 1:
        generate_sine();
        print_sine(0);
        break;
    case 2:
        generate_triangle();
        print_triangle(0);
        break;

    case 3:
        generate_square();
        print_square(0);
        break;

    default:
        break;
    }
    WidgetAdd(WIDGET_ROOT, (tWidget *)&left);
                WidgetPaint((tWidget *)&left);
                WidgetAdd(WIDGET_ROOT, (tWidget *)&right);
                WidgetPaint((tWidget *)&right);
                WidgetAdd(WIDGET_ROOT, (tWidget *)&back);
                WidgetPaint((tWidget *)&back);
                GrContextForegroundSet(&sContext, ClrWhite);
                GrLineDrawV(&sContext, 18, 15, 225);
                GrLineDrawH(&sContext, 18, 319, 120);



}



