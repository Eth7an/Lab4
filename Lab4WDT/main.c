#include <msp430.h>

int main(void) {
    WDTCTL = WDT_ADLY_250;                      // WDT 1000ms, SMCLK, interval timer
    P1OUT &= ~BIT0;
    P1DIR |= BIT0;
    PM5CTL0 &= ~LOCKLPM5;
    SFRIE1 |= WDTIE;
    _enable_interrupts();
    while (1);
}

#pragma vector=WDT_VECTOR

__interrupt void wdtled(void) {
    P1OUT^=BIT0;
}
