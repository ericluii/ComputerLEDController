#include <msp430.h>
#include <configure.h>
#include <watchdog.h>

int main(void)
{
    // Disable watchdog before doing anything
    watchdog_disable();
    // Configure clock speeds and other clock sensitive things
    configure_clocks();

    // Ready to do stuff
    watchdog_enable();

    /* Set P1.0 direction to output */
    P1DIR |= 0x01;

    /* Set P1.0 output high */
    P1OUT |= 0x01;

    __delay_cycles(1000000);

    while (1) {
        watchdog_pet();
        /* Wait for 200000 cycles */
        __delay_cycles(200000);

        /* Toggle P1.0 output */
        P1OUT ^= 0x01;
    }

    return 0;
}
