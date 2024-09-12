#include <xc.h>
#include <stdint.h>

#define BIT0     RA6
#define TRI0     TRISA6

#define SAMPLE_SIZE  100
#define MAX_GLITCHES_PER_SAMPLE 2

char Ehu = 0;

void EhuInit()
{
    TRI0 = 1;
}

/*
 Over 10ms
 ehu off - input is true all the time               > 99%
 ehu on  - input is true for 2ms and false for 8ms  < 20%
 Sample over 100ms - ehu = count < 99 
*/

void EhuTickHandler()
{
    static uint8_t ms = 0;
    static uint8_t count = 0;
    
    if (BIT0) count++;
    
    ms++;
    if (ms >= SAMPLE_SIZE)
    {
        Ehu = count <= (SAMPLE_SIZE - MAX_GLITCHES_PER_SAMPLE);
        ms = 0;
        count = 0;
    }
}
