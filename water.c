#include <stdint.h>

#include "../mstimer.h"

#include "dplus.h"

#define VALID_MS 5000

static int16_t _litres = 0;
static uint32_t _msLastReceived = (uint32_t)VALID_MS; //On start up set last received to not be valid

void WaterSetLitres(int16_t litres)
{
    static int8_t _hundreths = 0;
    if (Dplus) //Driving along so smooth out any changes and limit to -10 to +110
    {
        if (litres > _litres) _hundreths++;
        if (litres < _litres) _hundreths--;
        if (_hundreths >  100)
        {
            if (_litres < 110) _litres++;
            _hundreths = 0;
        }
        if (_hundreths < -100)
        {
            if (_litres > -10) _litres--;
            _hundreths = 0;
        }
    }
    else //Not driving so use value as is.
    {
        _litres = litres;
    }
    _msLastReceived = MsTimerCount;
}
int16_t WaterGetLitres()
{
    return _litres;
}

char WaterGetLitresValid()
{
    return MsTimerCount - _msLastReceived < VALID_MS;
}