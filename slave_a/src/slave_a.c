/*
===============================================================================
 Name        : slave_a.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

#include "General.h"
#include "DIO.h"

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

#if defined (M0_SLAVE_PAUSE_AT_MAIN)
volatile unsigned int pause_at_main;
#endif

static uint32_t taps;
static uint32_t masked_taps;
static uint32_t xored_taps;

float r = 10.0; // [Hz]
float dt = 0.0000001; // [s]

// Normalize the probability to make (r*dt) Range > 1
// And range a power of 2
// The lowest probability is 10*0.0000001 = 1e-6
// 1e-6 * Range > 1 --> Range > 1e6 -- > Range = 1048576
uint32_t p;

void lfsr_init()
{
	taps = 0x00000000;
}

void M4_IRQHandler(void)
{
	Chip_CREG_ClearM4Event();
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, 1, 12);

}

int main(void) {

#if defined (M0_SLAVE_PAUSE_AT_MAIN)
    // Pause execution until debugger attaches and modifies variable
    while (pause_at_main == 0) {}
#endif

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
#if defined (__MULTICORE_MASTER) || defined (__MULTICORE_NONE)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
#endif
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif

    // TODO: insert code here
    //NVIC_EnableIRQ(M4_IRQn);

    Chip_SCU_PinMuxSet(1, 11, (SCU_MODE_FUNC0 | SCU_MODE_PULLUP | SCU_MODE_HIGHSPEEDSLEW_EN));
    Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 1, 11);

    Chip_SCU_PinMuxSet(1, 12, (SCU_MODE_FUNC0 | SCU_MODE_PULLUP | SCU_MODE_HIGHSPEEDSLEW_EN));
    Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 1, 12);
     //Force the counter to be placed into memory
    volatile static int i = 0 ;
    volatile static int j = 0 ;

    lfsr_init();
    p = (uint32_t) ((r*dt)*(1048576.0*1.0));

    // Enter an infinite loop, just incrementing a counter
    while(1) {

    	/*********************** LFSR *************************/

    	// Calculates the xored value
		xored_taps = 0; //0x80200003
		xored_taps = (taps&0x80000000)?xored_taps ^ 1 : xored_taps ^ 0;
		xored_taps = (taps&0x00200000)?xored_taps ^ 1 : xored_taps ^ 0;
		xored_taps = (taps&0x00000002)?xored_taps ^ 1 : xored_taps ^ 0;
		xored_taps = (taps&0x00000001)?xored_taps ^ 1 : xored_taps ^ 0;

		// Shift to the left and adds the  not xored value
		taps = (taps<<1) | (!xored_taps);

    	/******************************************************/
    	for(i=0; i < 1000; i++){
			for(j=0; j<10000; j++){

				}
			}
			Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, 1, 11);
    }
    return 0 ;
}
