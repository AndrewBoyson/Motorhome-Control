extern void ControlInit(void);
extern void ControlMain(void);

extern char    ControlGetPump           (void);
extern char    ControlGetFill           (void);
extern char    ControlGetDrain          (void);
extern char    ControlGetInverter       (void);
extern char    ControlGetLpgHeater      (void);
extern int16_t ControlGetPumpMinLitres  (void);
extern int16_t ControlGetPumpDplusLitres(void);
extern int16_t ControlGetDrainMaxLitres (void);

extern void ControlSetPump           (char    value);
extern void ControlSetFill           (char    value);
extern void ControlSetDrain          (char    value);
extern void ControlSetInverter       (char    value);
extern void ControlSetLpgHeater      (char    value);
extern void ControlSetPumpMinLitres  (int16_t value);
extern void ControlSetPumpDplusLitres(int16_t value);
extern void ControlSetDrainMaxLitres (int16_t value);