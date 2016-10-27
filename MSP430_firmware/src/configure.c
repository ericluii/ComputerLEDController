#include <stdint.h>
#include "configure.h"

void _verify_tag_length_value() {
  uint16_t * address = (uint16_t *) 0x10C2;
  uint16_t xor_accumulator = 0;

  // CALBC1_1MHZ is the last entry in the TLV table
  while (address < (uint16_t *) 0x1100) {
    xor_accumulator ^= *(address++);
  }

  if (xor_accumulator + TLV_CHECKSUM == 0) {
    // Toggle on P1.6 if checksum passes
    P1DIR = BIT6;

    int i;
    for (i = 0; i < 10; i++) {
      P1OUT ^= BIT6;
      __delay_cycles(200000);
    }
  } else {
    // Turn on P1.0 and do nothing if checksum fails
    P1DIR = BIT0;
    P1OUT = BIT0;

    // Lock in error state if bad TLV
    while (1) { /* no-op */}
  }
}

// Overview:
//  1,000,000 cycles per second on DCOCTL/MCLCK/CPU
//  12,000 cycles per second for ACLK
//  Watchdog timer needs to be pet every 32768 cycles
//    - 32768/12000 = 2.73 seconds
//    - Which is once every 2,730,000 cycles on the main CPU

void _configure_cpu() {
  // Verify that Tag-Length-Value table is not corrupted before using
  _verify_tag_length_value();

  // Set DCO Clock Speed to 1 MHZ
  // Used by CPU and Timer1_A3
  DCOCTL = CALDCO_1MHZ;
  BCSCTL1 = CALBC1_1MHZ;
}

void _configure_watchdog() {
  // Configure ACLCK to use VL0 for 12KHz Clock Speed
  BCSCTL3 |= LFXT1S1;

  // Use ACLCK for watchdog
  // This is set when we pet the watchdog
  // WDTCTL |= WDTSSEL;
}

void configure_clocks() {
    _configure_cpu();
    _configure_watchdog();
}
