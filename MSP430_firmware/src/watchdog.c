#include "watchdog.h"

void watchdog_disable() {
  WDTCTL = WDTPW + WDTHOLD;
}

void watchdog_enable() {
  watchdog_pet();
}

void watchdog_pet() {
  WDTCTL = WDTPW + WDTCNTCL + WDTSSEL;
}
