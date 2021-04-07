#include <reg51.h>
#define dat P1
sbit sw1 = P0^2;                           //initializing pins
sbit in1 = P2^1;
sbit in2 = P2^7;
sbit in3 = P3^4;
sbit in4 = P3^5;
sbit in5 = P3^6;
sbit in6 = P3^7;
void ramp(int i, int j)                     //function to slowly ramp the motor
{
    unsigned int x, y, z;
    for (x = 1; x < 99; x++)                // to ramp up the motor using pulse width modulation
    {
        for (y = 0; y < a; y++)
        {
            in1 = i;
            in2 = j;
            for (z = 0; z < x; z++);
            in1 = 0;
            in2 = 0;
            for (z = 0; z < 99 - x; z++);
        }
    }
    in1 = i;
    in2 = j;
    for(x=0;x<2000;x++);                    //to run motor at full speed for 2 seconds
    for (x = 1; x < 99; x++)                // ramping down motor using pwm
    {
        for (y = 0; y < a; y++)
        {
            in1 = i;
            in2 = j;
            for (z = 0; z < 99 - x; z++);
            in1 = 0;
            in2 = 0;
            for (z = 0; z < x; z++);
        }
    }

}
void led(int a)
{
    int v=0;                        
    v=dat*0.02;                     //0.02 is the resolution of the adc
    v=v/0.2;                        //0.2 is the r2/(r1+r2) value of the voltage divider circuit in the voltage sensor
    if(v>9)                        // ie if the battery has more than 9 volts remaining light all 4 leds
    {
        in3 = in4 = in5 = in6 = 1;
    }
    else if ((v>6)&&(v<=9))     
    {
        in3=0;
        in4 = in5 = in6 = 1;
    }
    else if (v==6)                  // ie when only 6v remains light only 2 leds to show 50% power remaining
    {
        in3 = in4 = 0;
        in5 = in6 = 1;
    }
    else if ((v>2)&&(v<6))
    {
        in3 = in4 = in5 = 0;
        in6 = 1;
    }
    else if (v<=2)                      // ie shut the system when battery reaches less than 10% of battery life
    {
        sw1 = 1;
        in1 = in2 = in3 = in4 = in5 = in6 = 0 ;
    }
}
void main(void)
{
    sw1 = 1;                    //initializing switch
    in1 = in2 = in3 = in4 = in5 = in6 = 0;              //initializing output pins
    dat=0xff;
    while (1)
    {
        if (sw1 == 0)           //condition to see if switch is pressed
        {
            led(dat);           // to light leds depending upon how much battery is left
            ramp(1,0);          // to move the motor clockwise
            ramp(0,1);          // and anticlockwise
        }
    }
}