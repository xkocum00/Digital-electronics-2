# Lab 1: FILIP KOCUM

[https://github.com/xkocum00/Digital-electronics-2] (https://github.com/xkocum00/Digital-electronics-2)
### Blink example

1. What is the meaning of the following binary operators in C?
   * `|`   OR
   * `&`   AND
   * `^`   XOR
   * `~`   NOT
   * `<<`  posun bitu vlevo
   * `>>`  posun bitu vpravo

2. Complete truth table with operators: `|`, `&`, `^`, `~`

| **b** | **a** |**b or a** | **b and a** | **b xor a** | **not b** |
| :-: | :-: | :-: | :-: | :-: | :-: |
| 0 | 0 | 0 | 0 | 0 | 1 |
| 0 | 1 | 1 | 0 | 1 | 1 |
| 1 | 0 | 1 | 0 | 1 | 0 |
| 1 | 1 | 1 | 1 | 0 | 0 |


### Morse code

1. Listing of C code with syntax highlighting which repeats one "dot" and one "line" on a LED:

```c
#define LED_GREEN   PB5     // AVR pin where green LED is connected
#define DOT_DELAY   200     // delay when make dot
#define BREAK_DELAY 600     // delay between character
#define LONG_DELAY  1400    // pause between words 7 dots long

#ifndef F_CPU           // Preprocessor directive allows for conditional
                        // compilation. The #ifndef means "if not defined".
# define F_CPU 16000000 // CPU frequency in Hz required for delay
#endif                  // The #ifndef directive must be closed by #endif

/* Includes ----------------------------------------------------------*/
/* Include another C language file into the current file at the location
 * of the #include statement prior to compiling the source code.
 */
#include <util/delay.h> // Functions for busy-wait delay loops
#include <avr/io.h>     // AVR device-specific IO definitions

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle one LED and use delay library.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Set pin as output in Data Direction Register
    // DDRB = DDRB or 0010 0000
    DDRB = DDRB | (1<<LED_GREEN);
    
    // Set pin LOW in Data Register (LED off)
    // PORTB = PORTB and 1101 1111
    PORTB = PORTB & ~(1<<LED_GREEN);
    int x;
    // Infinite loop
    while (1)
    {
        
        // Pause several milliseconds
        _delay_ms(LONG_DELAY);
        // WORD = "SOS" 
        // WORD IN MORSE = "... --- ..." + break between words


        // S ...
        for (x = 1; x<=3; x++)
        {
            PORTB = PORTB ^ (1<<LED_GREEN);     //LED ON
            _delay_ms(DOT_DELAY);
            PORTB = PORTB & ~(1<<LED_GREEN);    //LED OFF
            _delay_ms(DOT_DELAY);
        }
        _delay_ms(BREAK_DELAY);
        // O ---
        for (x = 1; x<=3; x++)
        {
            PORTB = PORTB ^ (1<<LED_GREEN);     //LED ON
            _delay_ms(BREAK_DELAY);
            PORTB = PORTB & ~(1<<LED_GREEN);    //LED OFF
            _delay_ms(DOT_DELAY);
        }
        _delay_ms(BREAK_DELAY);
        // S ...
        for (x = 1; x<=3; x++)
        {
            PORTB = PORTB ^ (1<<LED_GREEN);     //LED ON
            _delay_ms(DOT_DELAY);
            PORTB = PORTB & ~(1<<LED_GREEN);    //LED OFF
            _delay_ms(DOT_DELAY);
        }
        
    }

    // Will never reach this
    return 0;
}
```


2. Scheme of Morse code application, i.e. connection of AVR device, LED, resistor, and supply voltage. The image can be drawn on a computer or by hand. Always name all components and their values!

   ![your figure](img1)
