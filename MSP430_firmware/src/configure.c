#include "configure.h"

// TODO: FIX THIS
void _verify_tag_length_value() {
  //unsigned int checksum = *((unsigned int *) 0x10C0);
  unsigned int address = 0x10C0;
  unsigned int xor_accumulator = 0;

  int test = 1;
  // CALBC1_1MHZ is the last entry in the TLV table
  while (test < 32) {
    xor_accumulator ^= *((unsigned int *) address + (2 * test));
    test++;
  }

  if (xor_accumulator == xor_accumulator) {
    P1DIR = BIT6;
    P1OUT = BIT6;
  } else {
    P1DIR = BIT0;
    P1OUT = BIT0;
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
