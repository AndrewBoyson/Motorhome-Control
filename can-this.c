#include "../canids.h"
#include "../mstimer.h"
#include "../msticker.h"
#include "../can.h"
#include "control.h"
#include "dplus.h"
#include "ehu.h"
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
        case CAN_ID_CONTROL + CAN_ID_LPG_HEATER:        ControlSetLpgHeater      (*(    char*)pData); break;
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
    {  char    value = ControlGetPump           (); static struct CanTransmitState state; CanTransmitOnChange(&state, CAN_ID_CONTROL, CAN_ID_PUMP             , sizeof(value), &value); }
    {  char    value = ControlGetFill           (); static struct CanTransmitState state; CanTransmitOnChange(&state, CAN_ID_CONTROL, CAN_ID_FILL             , sizeof(value), &value); }
    {  char    value = ControlGetDrain          (); static struct CanTransmitState state; CanTransmitOnChange(&state, CAN_ID_CONTROL, CAN_ID_DRAIN            , sizeof(value), &value); }
    {  char    value = ControlGetInverter       (); static struct CanTransmitState state; CanTransmitOnChange(&state, CAN_ID_CONTROL, CAN_ID_INVERTER         , sizeof(value), &value); }
    {  char    value = ControlGetLpgHeater      (); static struct CanTransmitState state; CanTransmitOnChange(&state, CAN_ID_CONTROL, CAN_ID_LPG_HEATER       , sizeof(value), &value); }
    {  char    value = Dplus                      ; static struct CanTransmitState state; CanTransmitOnChange(&state, CAN_ID_CONTROL, CAN_ID_D_PLUS           , sizeof(value), &value); }
    {  char    value = Ehu                        ; static struct CanTransmitState state; CanTransmitOnChange(&state, CAN_ID_CONTROL, CAN_ID_EHU              , sizeof(value), &value); }
    {  int16_t value = ControlGetPumpMinLitres  (); static struct CanTransmitState state; CanTransmitOnChange(&state, CAN_ID_CONTROL, CAN_ID_PUMP_MIN_LITRES  , sizeof(value), &value); }
    {  int16_t value = ControlGetPumpDplusLitres(); static struct CanTransmitState state; CanTransmitOnChange(&state, CAN_ID_CONTROL, CAN_ID_PUMP_DPLUS_LITRES, sizeof(value), &value); }
    {  int16_t value = ControlGetDrainMaxLitres (); static struct CanTransmitState state; CanTransmitOnChange(&state, CAN_ID_CONTROL, CAN_ID_DRAIN_MAX_LITRES , sizeof(value), &value); }
}
