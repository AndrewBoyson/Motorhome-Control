#include <stdint.h>

#include "../eeprom.h"

#include "eeprom-this.h"
#include "relay.h"
#include "led.h"
#include "pb.h"
#include "dplus.h"
#include "water.h"

static char    _pump            = 0;
static char    _fill            = 0;
static char    _drain           = 0;
static char    _inverter        = 0;
static int16_t _pumpMinlitres   = 0;
static int16_t _pumpDplusLitres = 0;
static int16_t _drainMaxLitres  = 0;

char    ControlGetPump           () { return _pump           ; }
char    ControlGetFill           () { return _fill           ; }
char    ControlGetDrain          () { return _drain          ; }
char    ControlGetInverter       () { return _inverter       ; }
int16_t ControlGetPumpMinLitres  () { return _pumpMinlitres  ; }
int16_t ControlGetPumpDplusLitres() { return _pumpDplusLitres; }
int16_t ControlGetDrainMaxLitres () { return _drainMaxLitres ; }

static void setPump    (char value) { _pump     = value; EepromSaveChar(EEPROM_PUMP_S8    , value); }
static void setFill    (char value) { _fill     = value; EepromSaveChar(EEPROM_FILL_S8    , value); }
static void setDrain   (char value) { _drain    = value; EepromSaveChar(EEPROM_DRAIN_S8   , value); }
static void setInverter(char value) { _inverter = value; EepromSaveChar(EEPROM_INVERTER_S8, value); }

void ControlSetPump  (char value)
{
    if (value && !_pump && _drain)
    {
        Led1Flash();
        return;
    }
    setPump(value);
}
void ControlSetFill  (char value)
{
    if (value && !_fill && _drain)
    {
        Led2Flash();
        return;
    }
    setFill(value);
}
void ControlSetDrain (char value)
{
    if (value && !_drain && (_fill || _pump))
    {
        Led3Flash();
        return;
    }
    setDrain(value);
}
void ControlSetInverter   (char value)
{
    setInverter(value);
}


void ControlSetPumpMinLitres  (int16_t value) { _pumpMinlitres   = value; EepromSaveS16 (EEPROM_PUMP_MIN_LITRES_S16,   value); }
void ControlSetPumpDplusLitres(int16_t value) { _pumpDplusLitres = value; EepromSaveS16 (EEPROM_PUMP_DPLUS_LITRES_S16, value); }
void ControlSetDrainMaxLitres (int16_t value) { _drainMaxLitres  = value; EepromSaveS16 (EEPROM_DRAIN_MAX_LITRES_S16,  value); }

void ControlInit()
{
    _pump            = EepromReadChar(EEPROM_PUMP_S8              );
    _fill            = EepromReadChar(EEPROM_FILL_S8              );
    _drain           = EepromReadChar(EEPROM_DRAIN_S8             );
    _inverter        = EepromReadChar(EEPROM_INVERTER_S8          );
    _pumpMinlitres   = EepromReadS16 (EEPROM_PUMP_MIN_LITRES_S16  );
    _pumpDplusLitres = EepromReadS16 (EEPROM_PUMP_DPLUS_LITRES_S16);
    _drainMaxLitres  = EepromReadS16 (EEPROM_DRAIN_MAX_LITRES_S16 );
}
void ControlMain()
{
    if (Pb1GetOneShot()) ControlSetPump    (!_pump    );
    if (Pb2GetOneShot()) ControlSetFill    (!_fill    );
    if (Pb3GetOneShot()) ControlSetDrain   (!_drain   );
    if (Pb4GetOneShot()) ControlSetInverter(!_inverter);
    
    if (_pump  &&          WaterGetLitresValid() && WaterGetLitres() < _pumpMinlitres  ) { setPump (0); Led1Flash(); }
    if (_pump  && Dplus && WaterGetLitresValid() && WaterGetLitres() < _pumpDplusLitres) { setPump (0); Led1Flash(); }
    if (_drain &&          WaterGetLitresValid() && WaterGetLitres() > _drainMaxLitres ) { setDrain(0); Led3Flash(); }
    
    Led1Set(_pump    );
    Led2Set(_fill    );
    Led3Set(_drain   );
    Led4Set(_inverter);
    
    Relay1Set(_pump    );
    Relay2Set(_fill    );
    Relay3Set(_drain   );
    Relay7Set(_inverter);
    Relay8Set(_inverter);
}
