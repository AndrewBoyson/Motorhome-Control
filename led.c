
#include <xc.h>
#include <stdint.h>

#include "../mstimer.h"

#define BIT1     LATAbits.LA1 //Use LAT not PORT to avoid the read modify write problem
#define BIT2     LATAbits.LA2
#define BIT3     LATAbits.LA3
#define BIT4     LATAbits.LA5
#define TRI1     TRISA1
#define TRI2     TRISA2
#define TRI3     TRISA3
#define TRI4     TRISA5

#define NUMBER_OF_FLASHES 10
#define FLASH_TIME_MS     100

void LedInit()
{
    TRI1 = 0;
    TRI2 = 0;
    TRI3 = 0;
    TRI4 = 0;
    BIT1 = 0;
    BIT2 = 0;
    BIT3 = 0;
    BIT4 = 0;
}

static char _on1 = 0;
static char _on2 = 0;
static char _on3 = 0;
static char _on4 = 0;

static int8_t _flash1Count = 0;
static int8_t _flash2Count = 0;
static int8_t _flash3Count = 0;
static int8_t _flash4Count = 0;

void Led1Set(char state) { _on1 = state; }
void Led2Set(char state) { _on2 = state; }
void Led3Set(char state) { _on3 = state; }
void Led4Set(char state) { _on4 = state; }

void Led1Flash() { _flash1Count = NUMBER_OF_FLASHES * 2; }
void Led2Flash() { _flash2Count = NUMBER_OF_FLASHES * 2; }
void Led3Flash() { _flash3Count = NUMBER_OF_FLASHES * 2; }
void Led4Flash() { _flash4Count = NUMBER_OF_FLASHES * 2; }

void LedMain()
{
    static char _flash = 0;
    static uint32_t _msTimerFlash = 0;
    if (MsTimerRepetitive(&_msTimerFlash, FLASH_TIME_MS))
    {
        _flash = !_flash;
        
        if (_flash1Count) _flash1Count--;
        if (_flash2Count) _flash2Count--;
        if (_flash3Count) _flash3Count--;
        if (_flash4Count) _flash4Count--;
    }
    
    BIT1 = _flash1Count ? _flash : _on1;
    BIT2 = _flash2Count ? _flash : _on2;
    BIT3 = _flash3Count ? _flash : _on3;
    BIT4 = _flash4Count ? _flash : _on4;
}