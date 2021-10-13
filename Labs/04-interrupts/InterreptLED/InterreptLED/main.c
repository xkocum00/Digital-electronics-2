/***********************************************************************
 * 
 * Control LEDs using functions from GPIO and Timer libraries. Do not 
 * use delay library any more.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-Present Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_D1  PB5
#define LED_D2  PB4
#define LED_D3  PB3
#define LED_D4  PB2
#define BTN		PD0

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "gpio.h"           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle one LED on the Multi-function shield using 
             the internal 8- or 16-bit Timer/Counter.
 * Returns:  none
 **********************************************************************/

// Global Variables for leds
uint8_t leds[4] = {LED_D1, LED_D2, LED_D3, LED_D4};
int led_count = 0;
int back = 0;

int main(void)
{
    // Configuration of LED(s) at port B
    GPIO_config_output(&DDRB, LED_D1);
    GPIO_write_low(&PORTB, LED_D1);
    
    GPIO_config_output(&DDRB, LED_D2);
    GPIO_write_low(&PORTB, LED_D2);
    
    GPIO_config_output(&DDRB, LED_D3);
    GPIO_write_low(&PORTB, LED_D3);
    
    GPIO_config_output(&DDRB, LED_D4);
    GPIO_write_low(&PORTB, LED_D4);
        
    // Configuration of 16-bit Timer/Counter1 for LED blinking
    // Set the overflow prescaler to 262 ms and enable interrupt
    TIM1_overflow_262ms();
    TIM1_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();
    
    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Toggle D1 LED on Multi-function shield.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{

    // WRITE YOUR CODE HERE

    if(led_count == 1) {
        back = 1;
    }
    if(led_count == 0) {
        back = 0;
    }
    
    //Adjusting the led_count value
    if(back == 0){
        led_count = led_count + 1;
    }
    else if(back == 1){
        led_count = led_count - 1;
    }
    
    //Toggling on the new led
    GPIO_toggle(&PORTB, leds[led_count]);
}