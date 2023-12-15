
#include <xc.h>
#include <stdint.h>

#define BIT1     RC3
#define BIT2     RC2
#define BIT3     RC1
#define BIT4     RC0
#define TRI1     TRISC3
#define TRI2     TRISC2
#define TRI3     TRISC1
#define TRI4     TRISC0

#define DEBOUNCE_MS  50

char Pb1 = 0;
char Pb2 = 0;
char Pb3 = 0;
char Pb4 = 0;

static char last1 = 0;
static char last2 = 0;
static char last3 = 0;
static char last4 = 0;

void PbInit()
{
    // Note that none of these pins are shared with an analogue input so need to set any ANSELx bits to 0
    TRI1 = 1;
    TRI2 = 1;
    TRI3 = 1;
    TRI4 = 1;
}

void PbTickHandler()
{
    static int8_t debounceMs1 = 0;
    static int8_t debounceMs2 = 0;
    static int8_t debounceMs3 = 0;
    static int8_t debounceMs4 = 0;
    
    if ( BIT1 && debounceMs1 <  DEBOUNCE_MS) debounceMs1++;
    if (!BIT1 && debounceMs1 >            0) debounceMs1--;
    if (         debounceMs1 == 0          ) Pb1 = 0;
    if (         debounceMs1 == DEBOUNCE_MS) Pb1 = 1;
    
    if ( BIT2 && debounceMs2 <  DEBOUNCE_MS) debounceMs2++;
    if (!BIT2 && debounceMs2 >            0) debounceMs2--;
    if (         debounceMs2 == 0          ) Pb2 = 0;
    if (         debounceMs2 == DEBOUNCE_MS) Pb2 = 1;
    
    if ( BIT3 && debounceMs3 <  DEBOUNCE_MS) debounceMs3++;
    if (!BIT3 && debounceMs3 >            0) debounceMs3--;
    if (         debounceMs3 == 0          ) Pb3 = 0;
    if (         debounceMs3 == DEBOUNCE_MS) Pb3 = 1;
    
    if ( BIT4 && debounceMs4 <  DEBOUNCE_MS) debounceMs4++;
    if (!BIT4 && debounceMs4 >            0) debounceMs4--;
    if (         debounceMs4 == 0          ) Pb4 = 0;
    if (         debounceMs4 == DEBOUNCE_MS) Pb4 = 1;
}

char Pb1GetOneShot() { char pb = Pb1; char os = pb && !last1; last1 = pb; return os; }
char Pb2GetOneShot() { char pb = Pb2; char os = pb && !last2; last2 = pb; return os; }
char Pb3GetOneShot() { char pb = Pb3; char os = pb && !last3; last3 = pb; return os; }
char Pb4GetOneShot() { char pb = Pb4; char os = pb && !last4; last4 = pb; return os; }