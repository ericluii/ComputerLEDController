#include <msp430.h>

int main(void)
{
    /* Hold the watchdog */
    WDTCTL = WDTPW + WDTHOLD;

    /* Set P1.0 direction to output */
    P1DIR |= 0x01;

    /* Set P1.0 output high */
    P1OUT |= 0x01;

    while (1) {
        /* Wait for 200000 cycles */
        __delay_cycles(200000);

        /* Toggle P1.0 output */
        P1OUT ^= 0x01;
    }
}
