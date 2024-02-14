#include "../canids.h"
#include "../mstimer.h"
#include "../msticker.h"
#include "../can.h"
#include "control.h"
#include "dplus.h"
#include "water.h"

static void receive(uint16_t id, uint8_t length, void* pData)
{
    switch(id)
    {
        case CAN_ID_SERVER  + CAN_ID_TIME:              MsTickerRegulate         (*(uint32_t*)pData); break;
        
        case CAN_ID_TANK    + CAN_ID_FRESH_LITRES:      WaterSetLitres           (*( int16_t*)pData); break;
        
        case CAN_ID_CONTROL + CAN_ID_PUMP:              ControlSetPump           (*(    char*)pData); break;
        case CAN_ID_CONTROL + CAN_ID_FILL:              ControlSetFill           (*(    char*)pData); break;
        case CAN_ID_CONTROL + CAN_ID_DRAIN:             ControlSetDrain          (*(    char*)pData); break;
        case CAN_ID_CONTROL + CAN_ID_INVERTER:          ControlSetInverter       (*(    char*)pData); break;
        case CAN_ID_CONTROL + CAN_ID_PUMP_MIN_LITRES:   ControlSetPumpMinLitres  (*( int16_t*)pData); break;
        case CAN_ID_CONTROL + CAN_ID_PUMP_DPLUS_LITRES: ControlSetPumpDplusLitres(*( int16_t*)pData); break;
        case CAN_ID_CONTROL + CAN_ID_DRAIN_MAX_LITRES:  ControlSetDrainMaxLitres (*( int16_t*)pData); break;
    }
}

void CanThisInit(void)
{
    CanReceive = &receive;
}
void CanThisMain(void)
{
    /*
    static uint32_t msTimerWaterPump       = 0;
    static uint32_t msTimerWaterFill       = 0;
    static uint32_t msTimerWaterDrain      = 0;
    static uint32_t msTimerInverter        = 0;
    static uint32_t msTimerDPlus           = 0;
    static uint32_t msTimerPumpMinLitres   = 0;
    static uint32_t msTimerPumpDplusLitres = 0;
    static uint32_t msTimerDrainMaxLitres  = 0;
    
    static char sendWaterPump       = 0;
    static char sendWaterFill       = 0;
    static char sendWaterDrain      = 0;
    static char sendInverter        = 0;
    static char sendDPlus           = 0;
    static char sendPumpMinLitres   = 0;
    static char sendPumpDplusLitres = 0;
    static char sendDrainMaxLitres  = 0;
    
    if (MsTimerRepetitive(&msTimerWaterPump      , BASE_MS + CAN_ID_PUMP             )) sendWaterPump       = 1;
    if (MsTimerRepetitive(&msTimerWaterFill      , BASE_MS + CAN_ID_FILL             )) sendWaterFill       = 1;
    if (MsTimerRepetitive(&msTimerWaterDrain     , BASE_MS + CAN_ID_DRAIN            )) sendWaterDrain      = 1;
    if (MsTimerRepetitive(&msTimerInverter       , BASE_MS + CAN_ID_INVERTER         )) sendInverter        = 1;
    if (MsTimerRepetitive(&msTimerDPlus          , BASE_MS + CAN_ID_D_PLUS           )) sendDPlus           = 1;
    if (MsTimerRepetitive(&msTimerPumpMinLitres  , BASE_MS + CAN_ID_PUMP_MIN_LITRES  )) sendPumpMinLitres   = 1;
    if (MsTimerRepetitive(&msTimerPumpDplusLitres, BASE_MS + CAN_ID_PUMP_DPLUS_LITRES)) sendPumpDplusLitres = 1;
    if (MsTimerRepetitive(&msTimerDrainMaxLitres , BASE_MS + CAN_ID_DRAIN_MAX_LITRES )) sendDrainMaxLitres  = 1;
    
    if (sendWaterPump      ) { char    value = ControlGetPump           (); sendWaterPump       = CanTransmit(CAN_ID_CONTROL + CAN_ID_PUMP             , sizeof(value), &value); }
    if (sendWaterFill      ) { char    value = ControlGetFill           (); sendWaterFill       = CanTransmit(CAN_ID_CONTROL + CAN_ID_FILL             , sizeof(value), &value); }
    if (sendWaterDrain     ) { char    value = ControlGetDrain          (); sendWaterDrain      = CanTransmit(CAN_ID_CONTROL + CAN_ID_DRAIN            , sizeof(value), &value); }
    if (sendInverter       ) { char    value = ControlGetInverter       (); sendInverter        = CanTransmit(CAN_ID_CONTROL + CAN_ID_INVERTER         , sizeof(value), &value); }
    if (sendDPlus          ) { char    value = Dplus                      ; sendDPlus           = CanTransmit(CAN_ID_CONTROL + CAN_ID_D_PLUS           , sizeof(value), &value); }
    if (sendPumpMinLitres  ) { int16_t value = ControlGetPumpMinLitres  (); sendPumpMinLitres   = CanTransmit(CAN_ID_CONTROL + CAN_ID_PUMP_MIN_LITRES  , sizeof(value), &value); }
    if (sendPumpDplusLitres) { int16_t value = ControlGetPumpDplusLitres(); sendPumpDplusLitres = CanTransmit(CAN_ID_CONTROL + CAN_ID_PUMP_DPLUS_LITRES, sizeof(value), &value); }
    if (sendDrainMaxLitres ) { int16_t value = ControlGetDrainMaxLitres (); sendDrainMaxLitres  = CanTransmit(CAN_ID_CONTROL + CAN_ID_DRAIN_MAX_LITRES , sizeof(value), &value); }
    */
    
    {  char    value = ControlGetPump           (); static struct CanTransmitState state; CanTransmitOnChange(&state, CAN_ID_CONTROL, CAN_ID_PUMP             , sizeof(value), &value); }
    {  char    value = ControlGetFill           (); static struct CanTransmitState state; CanTransmitOnChange(&state, CAN_ID_CONTROL, CAN_ID_FILL             , sizeof(value), &value); }
    {  char    value = ControlGetDrain          (); static struct CanTransmitState state; CanTransmitOnChange(&state, CAN_ID_CONTROL, CAN_ID_DRAIN            , sizeof(value), &value); }
    {  char    value = ControlGetInverter       (); static struct CanTransmitState state; CanTransmitOnChange(&state, CAN_ID_CONTROL, CAN_ID_INVERTER         , sizeof(value), &value); }
    {  char    value = Dplus                      ; static struct CanTransmitState state; CanTransmitOnChange(&state, CAN_ID_CONTROL, CAN_ID_D_PLUS           , sizeof(value), &value); }
    {  int16_t value = ControlGetPumpMinLitres  (); static struct CanTransmitState state; CanTransmitOnChange(&state, CAN_ID_CONTROL, CAN_ID_PUMP_MIN_LITRES  , sizeof(value), &value); }
    {  int16_t value = ControlGetPumpDplusLitres(); static struct CanTransmitState state; CanTransmitOnChange(&state, CAN_ID_CONTROL, CAN_ID_PUMP_DPLUS_LITRES, sizeof(value), &value); }
    {  int16_t value = ControlGetDrainMaxLitres (); static struct CanTransmitState state; CanTransmitOnChange(&state, CAN_ID_CONTROL, CAN_ID_DRAIN_MAX_LITRES , sizeof(value), &value); }
}
