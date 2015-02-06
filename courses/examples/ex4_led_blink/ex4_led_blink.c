/*
 * ex4_led_blink.c
 *  Author: thibaut.viard
 */

#include "sam.h"

/*
 * LED1 definitions
 */
#define LED1_PIO  PIOC
#define LED1_PIN  PIO_PC10

/*
 * LED2 definitions
 */
#define LED2_PIO  PIOC
#define LED2_PIN  PIO_PC17

// Global state variable for LED toggle
static uint32_t ul_toggle=0 ;
// Global state variable for tick count
static uint32_t ul_tickcount=0 ;

/**
 * \brief Initialization of board components.
 *
 */
static void hardware_init( void )
{
  // Assign the LED1 pin as OUTPUT
  LED1_PIO->PIO_OER = LED1_PIN ;
  // Clear the LED1 pin level, ie put to 0V -> the pin is connected to the LED cathode, anode is connected to +3.3V.
  LED1_PIO->PIO_CODR = LED1_PIN ;

  // Assign the LED2 pin as OUTPUT
  LED2_PIO->PIO_OER = LED2_PIN ;
  // Set the LED2 pin level, ie put to 0V -> the pin is connected to the LED cathode, anode is connected to +3.3V.
  LED2_PIO->PIO_SODR = LED2_PIN ;

  // Configure Systick to trig every millisecond
  SysTick_Config( SystemCoreClock/1000UL ) ;
  NVIC_EnableIRQ( SysTick_IRQn ) ;
}

/**
 * \brief Toggle the LED.
 *
 */
static void toggle_LED( void )
{
  if ( ul_toggle == 0 )
  {
    // Set the LED1 pin level, ie put to 3.3V -> this light off the LED
    LED1_PIO->PIO_SODR=LED1_PIN ;

    // Clear the LED2 pin level, ie put to 0V -> this light on the LED
    LED2_PIO->PIO_CODR=LED2_PIN ;

    ul_toggle=1 ;
  }
  else
  {
    // Clear the LED1 pin level, ie put to 0V -> this light on the LED
    LED1_PIO->PIO_CODR=LED1_PIN ;

    // Set the LED2 pin level, ie put to 3.3V -> this light off the LED
    LED2_PIO->PIO_SODR=LED2_PIN ;

    ul_toggle=0 ;
  }
}

/**
 *  \brief SysTick Interrupt handler.
 */
void SysTick_Handler( void )
{
  ul_tickcount++ ;

  // Toggle LEDs every second (ie 1000ms)
  if ( ul_tickcount % 1000 == 0 )
  {
    toggle_LED() ;
  }
}

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main( void )
{
  // Initialize hardware
  hardware_init() ;

  while ( 1 )
  {
  }
}


