
#include <xc.h>

#define BIT1     LATBbits.LB5 //Use LAT not PORT to avoid the read modify write problem
#define BIT2     LATBbits.LB4
#define BIT3     LATBbits.LB1
#define BIT4     LATBbits.LB0
#define BIT5     LATCbits.LC7
#define BIT6     LATCbits.LC6
#define BIT7     LATCbits.LC5
#define BIT8     LATCbits.LC4
#define TRI1     TRISB5
#define TRI2     TRISB4
#define TRI3     TRISB1
#define TRI4     TRISB0
#define TRI5     TRISC7
#define TRI6     TRISC6
#define TRI7     TRISC5
#define TRI8     TRISC4

void RelayInit()
{
    TRI1 = 1;
    TRI2 = 1;
    TRI3 = 1;
    TRI4 = 1;
    TRI5 = 1;
    TRI6 = 1;
    TRI7 = 1;
    TRI8 = 1;
    BIT1 = 0;
    BIT2 = 0;
    BIT3 = 0;
    BIT4 = 0;
    BIT5 = 0;
    BIT6 = 0;
    BIT7 = 0;
    BIT8 = 0;
}
void Relay1Set(char state) { TRI1 = !state; }
void Relay2Set(char state) { TRI2 = !state; }
void Relay3Set(char state) { TRI3 = !state; }
void Relay4Set(char state) { TRI4 = !state; }
void Relay5Set(char state) { TRI5 = !state; }
void Relay6Set(char state) { TRI6 = !state; }
void Relay7Set(char state) { TRI7 = !state; }
void Relay8Set(char state) { TRI8 = !state; }
