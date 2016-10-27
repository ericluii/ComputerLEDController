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

    // Notify that startup succeeded
    // Turn on LED P1.6
    P1DIR = BIT6;
    P1OUT = BIT6;

    // Prep LED P1.0 for output
    P1DIR |= BIT0;
    while (1) {
        watchdog_pet();
        /* Wait for 200000 cycles */
        __delay_cycles(200000);

        /* Toggle P1.0 output */
        P1OUT ^= BIT0;
    }

    return 0;
}
