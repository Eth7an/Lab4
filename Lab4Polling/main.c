#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT

    P1DIR |= BIT6;                     // P1.6 output
    P1SEL1 |= BIT6;                    // P1.6 options select
    PM5CTL0 &= ~LOCKLPM5;

    TB0CCR0 = 500-1;                         // PWM Period
    TB0CCTL1 = OUTMOD_7;                      // CCR1 reset/set
    TB0CCR1 = 50;                            // CCR1 PWM duty cycle
    TB0CTL = TBSSEL__SMCLK | MC__UP | TBCLR;  // SMCLK, up mode, clear TBR

    while(1) {
        P1OUT ^= BIT6;// For debugger
    }

}
