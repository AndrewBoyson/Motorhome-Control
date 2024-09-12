#include <xc.h>
#include "../msticker.h"
#include "../mstimer.h"
#include "../can.h"

#include "eeprom-this.h"
#include "can-this.h"
#include "relay.h"
#include "led.h"
#include "pb.h"
#include "dplus.h"
#include "ehu.h"
#include "control.h"

#define _XTAL_FREQ 8000000

void __interrupt() isr(void)
{
    if (MsTickerHadInterrupt())
    {
        MsTimerTickHandler();
        PbTickHandler();
        DplusTickHandler();
        EhuTickHandler();
        MsTickerHandleInterrupt();
    }
}
void main()
{
    __delay_ms(3000); //This prevents multiple resets when programming.
    MsTickerInit(EEPROM_MS_TICK_COUNT_U16);
    CanInit();
    CanThisInit();
    RelayInit();
    LedInit();
    PbInit();
    DplusInit();
    EhuInit();
    ControlInit();
    ei();
    PEIE = 1; //Enable peripheral interrupts - specifically Timer 1 and ADC
    while(1)
    {
        MsTimerMain();
        CanMain();
        CanThisMain();
        LedMain();
        ControlMain();
    }
}
