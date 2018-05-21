/*
===============================================================================
 Name        : TPG_2.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/


#include "chip.h"
#include <cr_section_macros.h>
#include "General.h"

// TODO: insert other include files here
#include "CAN.h"
#include "SPI.h"
#include "timer_vect.h"
#include "AD7699.h"
#include "DIO.h"
#include "INVAPBus.h"
#include "Poisson.h"

// Frequency measuring unit
#include "FMU.h"

// TODO: insert other definitions and declarations here
#define CALIB_EEPROM_DEV_ADDRESS 0X02      // Calibration EEPROM device address (address set in address pins of EEPROM ic)


#define DT_TIMER	1 // 500 us interval
uint8_t dtTimer;

Digital_In_T pulsesPin; // GPIO1
Digital_In_T upPin;   // PULS_0
Digital_In_T downPin; // PULS_1

//***************************************************************************************
// Mask for Taps for LFSR of 32 bits
// 2^31 + 2^21 + 2^1 + 1 = 2149580803 (10) = 0x80200003 (16)
#define LFSR_TAP_MSK	0x80200003
#define LFSR_TAPS       32

static uint32_t taps;
static uint32_t masked_taps;
static uint32_t xored_taps;

// Initial value to the LFSR counter
inline void lfsr_init()
{
	taps = 0x00000000;
}

// Estimated cicles to get a new random number:
// 1+1+32*(3) = 98 cicles (With out counting function calling times)
//
// In order to allow the M0 core to have new random numbers each 100 ns
// the SYS_CLK at 100 MHz is not enough (100MHz gives just 10 cicles per
// each 100 ns window):
//
// Two poisble solutions:
// - Increase the window to 1us --> at 100MHz it gives 100 cicles per window
// - Improve the function lfsr_count() in order to make it less time-consuming
inline void lfsr_count()
{
    int i;

	// get the masked taps to calculate the taps xored value
	masked_taps = LFSR_TAP_MSK & taps;

	// Calculates the xored value
	xored_taps = 0;
	for(i=0; i<LFSR_TAPS; i++)
	{
		xored_taps ^= (masked_taps & 0x00000001);
		masked_taps = masked_taps >> 1;
	}
	// Shift to the left and adds the  not xored value
	taps = (taps<<1) | ( (!xored_taps) & 0x00000001);

}

inline uint32_t lfsr_get_taps()
{
	return taps;
}


#define RATE_JUMP 10 // Hz
float r = RATE_JUMP; // [Hz]
float dt = 0.0005; // [s]
uint32_t p;

void calculate_p(void)
{
	// Normalize the probability to make (r*dt) Range > 1
	// And range a power of 2
	// The lowest probability is 10*0.0000001 = 1e-6
	// 1e-6 * Range > 1 --> Range > 1e6 -- > Range = 1048576
	p = (uint32_t) ((r*dt)*(1048576.0*1.0));
}
//*******************************************************************************


uint32_t amplitude, cAmplitude; // Range of average amplitude
uint32_t normal_dist = 0;
uint32_t n = 0;

int main(void) {


    SystemCoreClockUpdate();
    uint32_t mainFreq = SupervisorInit(); // Initialize Supervisor system

    // TODO: insert code here

	// Configure the I/O ports
	portConfiguration();

	// Timers
	dtTimer = TimeVect_GetTimerInitialize(DT_TIMER);

	// Init
	lfsr_init();

	// Analog output init
	// Clock setup
	Chip_Clock_SetBaseClock(CLK_BASE_APB3, CLKIN_IDIVC, true, false);
	Chip_Clock_Enable(CLK_APB3_DAC);
	// DAC init
	Chip_DAC_Init(LPC_DAC);
	Chip_DAC_SetBias(LPC_DAC, 0); // 1 MHz
	Chip_DAC_ConfigDAConverterControl(LPC_DAC, ~(DAC_DBLBUF_ENA | DAC_CNT_ENA) | DAC_DMA_ENA);
	Chip_DAC_UpdateValue(LPC_DAC, 0);
	// Pin configuration

	// Calculate p
	calculate_p();
	// Normalize the probability to make (r*dt) Range > 1
	// And range a power of 2
	// The lowest probability is 10*0.0000001 = 1e-6
	// 1e-6 * Range > 1 --> Range > 1e6 -- > Range = 1048576
	p = (uint32_t) ((r*dt)*(1048576.0*1.0));

	// Initial amplitude
	amplitude = 512;

    // Enter an infinite loop
    while(1) {

    	//************************************************************************************
		// Action performed each 1ms
    	if(TimeVect_IsTimer(dtTimer))
		{
			TimeVect_SetTimer(dtTimer, DT_TIMER);

			// Generate random number
			lfsr_count();
			normal_dist += taps%(1024);
			n++;
			if(p>(taps%(1048576)))
			{
				// Send pulse
				DIOSetPinHigh(pulsesPin.GPIOPort, pulsesPin.GPIOPin);
				DIOSetPinLow(pulsesPin.GPIOPort, pulsesPin.GPIOPin);


				// Normal distribution
				normal_dist = normal_dist /n;

				cAmplitude =  normal_dist;
				normal_dist = 0;
				n=0;
				// Update DAC output
				if(cAmplitude>=1024)
				{
					Chip_DAC_UpdateValue(LPC_DAC, 1024);
				}
				else
				{
					Chip_DAC_UpdateValue(LPC_DAC, cAmplitude);
				}
				Chip_DAC_UpdateValue(LPC_DAC, 0);

			}

		}
    	//************************************************************************************


    }
    return 0 ;
}



void portConfiguration(void)
{
	// ************** Bits de entrada   ***************************

	upPin.GPIOPort = 0;
	upPin.GPIOPin = 4;
	upPin.SMstate = 0;

	// COnfigures the pin as input, with the input buffer enabled
	DIOSinglePinSetup(upPin.GPIOPort, upPin.GPIOPin, DIO_INPUT, SCU_MODE_INACT | SCU_MODE_INBUFF_EN);
	// GPIO_IRQ configuration for the "input" Vector
	Chip_SCU_GPIOIntPinSel(6, upPin.GPIOPort, upPin.GPIOPin);
	// The interrupt as edge sensitive
	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH6);
	// And the edge a High to low transition
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH6);
	// Clears any pending interrupts
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH6);
	// Enable
	NVIC_EnableIRQ(PIN_INT6_IRQn);


	downPin.GPIOPort = 0;
	downPin.GPIOPin = 8;
	downPin.SMstate = 0;

	// COnfigures the pin as input, with the input buffer enabled
	DIOSinglePinSetup(downPin.GPIOPort, downPin.GPIOPin, DIO_INPUT, SCU_MODE_INACT | SCU_MODE_INBUFF_EN);
	// GPIO_IRQ configuration for the "input" Vector
	Chip_SCU_GPIOIntPinSel(7, downPin.GPIOPort, downPin.GPIOPin);
	// The interrupt as edge sensitive
	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH7);
	// And the edge a High to low transition
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH7);
	// Clears any pending interrupts
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH7);
	// Enable
	NVIC_EnableIRQ(PIN_INT7_IRQn);




	// ************** Bits de salida   ***************************
	pulsesPin.GPIOPort = 3;
	pulsesPin.GPIOPin = 3;
	pulsesPin.SMstate = 0;

	DIOSinglePinSetup(pulsesPin.GPIOPort, pulsesPin.GPIOPin, DIO_OUTPUT,  SCU_MODE_PULLUP | SCU_MODE_HIGHSPEEDSLEW_EN);
	// Init port
	DIOSetPinLow(pulsesPin.GPIOPort, pulsesPin.GPIOPin);
}


// UP BUTTON
void GPIO6_IRQHandler(void)
{
	__disable_irq();
	// Clears the interrupt pending for this interupt
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH6);

	// Up Button
	r += RATE_JUMP;
	calculate_p();

	__enable_irq();

}

// DOWN BUTTON
void GPIO7_IRQHandler(void)
{
	__disable_irq();
	// Clears the interrupt pending for this interupt
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH7);

	// Down Button
	// Up Button
	r -= RATE_JUMP;
	calculate_p();

	__enable_irq();

}
