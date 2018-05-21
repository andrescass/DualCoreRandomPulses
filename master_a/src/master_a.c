/*
===============================================================================
 Name        : master_a.c
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

#if defined (__MULTICORE_MASTER_SLAVE_M0APP) | defined (__MULTICORE_MASTER_SLAVE_M0SUB)
#include "cr_start_m0.h"
#endif

#include "General.h"
#include "DIO.h"
#include "app_multicore_cfg.h"
#include "ipc_msg.h"


// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable

	uint32_t mainPLLfreq = Chip_Clock_SetupMainPLLHz(CLKIN_IRC, BASE_FREQ-10000000, BASE_FREQ, BASE_FREQ+10000000);
	while(!Chip_Clock_MainPLLLocked()){}
	Chip_Clock_SetBaseClock(CLK_BASE_MX, CLKIN_MAINPLL, 1, 0);
	mainPLLfreq = Chip_Clock_SetupMainPLLHz(CLKIN_IRC, 190000000-10000000, BASE_FREQ, 190000000+10000000);
	while(!Chip_Clock_MainPLLLocked()){}
	Chip_Clock_SetBaseClock(CLK_BASE_MX, CLKIN_MAINPLL, 1, 0);
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

    // Start M0APP slave processor
#if defined (__MULTICORE_MASTER_SLAVE_M0APP)
    cr_start_m0(SLAVE_M0APP,&__core_m0app_START__);
#endif

    // Start M0SUB slave processor
#if defined (__MULTICORE_MASTER_SLAVE_M0SUB)
    cr_start_m0(SLAVE_M0SUB,&__core_m0sub_START__);
#endif

    // TODO: insert code here
    Digital_In_T led_O;
	led_O.GPIOPort = 0;
	led_O.GPIOPin = 14;
	led_O.SMstate = 0;

	Digital_In_T led_error;
	led_error.GPIOPort = 1;
	led_error.GPIOPin = 12;
	led_error.SMstate = 0;

	Digital_In_T tec_1;
	tec_1.GPIOPort = 0;
	tec_1.GPIOPin = 4;
	tec_1.SMstate = 0;
	int tec_1_down = 0;

	Digital_In_T tec_2;
	tec_2.GPIOPort = 0;
	tec_2.GPIOPin = 8;
	tec_2.SMstate = 0;
	int tec_2_down = 0;

	DIOSinglePinSetup(led_O.GPIOPort, led_O.GPIOPin, DIO_OUTPUT,  SCU_MODE_PULLUP | SCU_MODE_HIGHSPEEDSLEW_EN);
	DIOSinglePinSetup(led_error.GPIOPort, led_error.GPIOPin, DIO_OUTPUT,  SCU_MODE_PULLUP | SCU_MODE_HIGHSPEEDSLEW_EN);
	DIOSinglePinSetup(tec_1.GPIOPort, tec_1.GPIOPin, DIO_INPUT,   SCU_MODE_INACT | SCU_MODE_INBUFF_EN);
	DIOSinglePinSetup(tec_2.GPIOPort, tec_2.GPIOPin, DIO_INPUT,   SCU_MODE_INACT | SCU_MODE_INBUFF_EN);

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    volatile static int j = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        for(i=0; i < 1000; i++){
        	for(j=0; j<10000; j++){

        	}

        	if(!DIOGetPinState(tec_1.GPIOPort, tec_1.GPIOPin) && !tec_1_down){
				//DIOSetPinHigh(led_error.GPIOPort, led_error.GPIOPin);
        		//__DSB();
        		//__SEV();
        		LPC_CREG->M4TXEVENT = 0x1;

				tec_1_down = 1;


				//
				IPC_pushMsgTout(CPUID_M0APP, &tec_1_down, 0);

			} else {
				tec_1_down = 0;
			}

        	if(!DIOGetPinState(tec_2.GPIOPort, tec_2.GPIOPin) && !tec_2_down){
				//DIOSetPinLow(led_error.GPIOPort, led_error.GPIOPin);

				tec_2_down = 1;

			} else {
				tec_2_down = 0;
			}
        }
        DIOSetPinToggle(led_O.GPIOPort, led_O.GPIOPin);
        LPC_CREG->M4TXEVENT = 0x1;
        //Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, 0, 14);


    }
    return 0 ;
}
