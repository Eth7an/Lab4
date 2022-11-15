#include <msp430.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P6DIR |= BIT6;               // P1.0  output

    //PWM Generator
    TB0CCR0 = 16384;
    TB0CCTL1 = OUTMOD_7;
    TB0CCR1 = 3276;
    TB0CTL = TBSSEL_1 + MC_1 + TBCLR;

    TB0CCTL0 |= CCIE;
    TB0CCTL1 |= CCIE;
    TB0CCTL0 &=~CCIFG;
    TB0CCTL1 &=~CCIFG;

    _enable_interrupts();
}

#pragma vector = TIMER0_B0_VECTOR       //define the interrupt service vector
__interrupt void ISR_TB0_CCR0 (void)    // interrupt service routine
    {
    P6OUT |=BIT6;
    TB0CCTL0 &=~CCIFG;
    }

#pragma vector = TIMER0_B1_VECTOR
interrupt void ISR_TB0_CCR1  (void) {
    P6OUT &=~BIT6;
    TB0CCTL1 &=~CCIFG;
    }
