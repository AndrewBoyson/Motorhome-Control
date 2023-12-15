#include <xc.h>
#include <stdint.h>

#define BIT0     RA0
#define TRI0     TRISA0

#define DEBOUNCE_MS  50

char Dplus = 0;

void DplusInit()
{
    ANSEL0 = 0; //Set pin to be RA0 rather than AN0
    TRI0 = 1;
}

void DplusTickHandler()
{
    static int8_t debounceMs0 = 0;

    if ( BIT0 && debounceMs0 <  DEBOUNCE_MS) debounceMs0++;
    if (!BIT0 && debounceMs0 >            0) debounceMs0--;
    if (         debounceMs0 == 0          ) Dplus = 0;
    if (         debounceMs0 == DEBOUNCE_MS) Dplus = 1;
}
