/*
 * TPG_2.h
 *
 *  Created on: 17/10/2016
 *      Author: Crozzolo Marcos
 */

#ifndef POISSON_H_
#define POISSON_H_

#include "chip.h"

/**
 * @brief Error flags
 */

#define NO_ERROR		  0x000
#define INPUT_ADC_ERROR   0x001
#define OUTPUT_ADC_ERROR  0x002
#define VNIM_ERROR		  0x004
#define RW_EEPROM_ERROR   0x008
#define OOB_ADC_ERROR     0x010 // Analog read out of bounds
#define DISC_ERROR        0x020
#define CH1_ERROR		  0x040
#define CH2_ERROR		  0x080
#define CH3_ERROR		  0x100
#define CH4_ERROR		  0x200






/**
 * @brief Struct to contain calibration parameters
 */
typedef struct IA_Cal_Params_T {
	uint16_t slope[4];					/*!< Channel slope */
	uint16_t interc[4];					/*!< Channel intercept */
} IA_Cal_Params_T;


/**
 * @brief Set up the I/O ports configuration
 */
void portConfiguration(void);


// Bit number reference... For shifts. It's NOT a MASK
#define BIT0	0x00
#define BIT1	0x01
#define BIT2	0x02
#define BIT3	0x03
#define BIT4	0x04
#define BIT5	0x05
#define BIT6	0x06
#define BIT7	0x07
#define BIT8	0x08

// Bit Masks
#define BIT0_MSK	0x01
#define BIT1_MSK	0x02
#define BIT2_MSK	0x04
#define BIT3_MSK	0x08
#define BIT4_MSK	0x10
#define BIT5_MSK	0x20
#define BIT6_MSK	0x40
#define BIT7_MSK	0x80

#define BIT8_MSK	0x0100


/**
 * getNimVoltages() returns the state of the NIM Voltages
 * supervision lines. It is returned in the format
 * BIT7  BIT6  BIT5  BIT4  BIT3  BIT2  BIT1  BIT0
 *                               24VP  12VP  12VN
 *
 * If the bit is set, the voltage is present.
 * If the bit is cleared, the voltage is absent.
 *
 * @brief Returns The state of the NIM Voltages
 */
uint8_t getNimVoltages(void);

#define SUP_24VP_BIT		BIT2
#define SUP_12VP_BIT		BIT1
#define SUP_12VN_BIT		BIT0

/**
 * getModuleAddress() returns the Address of the Module
 * defined by the state of the ADDR lines in the INVAP Bus.
 * It's returned in the format
 * BIT7  BIT6  BIT5  BIT4  BIT3  BIT2  BIT1  BIT0
 *  0     0   ADDR5 ADDR4 ADDR3 ADDR2 ADDR1 ADDR0
 *
 * @brief Returns The address of the Module in the INVAP Bus
 */
uint8_t getModuleAddress(void);

#define ADD0_BIT		BIT0
#define ADD1_BIT		BIT1
#define ADD2_BIT		BIT2
#define ADD3_BIT		BIT3
#define ADD4_BIT		BIT4
#define ADD5_BIT		BIT5

/**
 * getRemoteLines() returns the state of the remote lines.
 * It's returned in the format
 * BIT15  BIT14  BIT13  BIT12  BIT11  BIT10   BIT9   BIT8          BIT7     BIT6    BIT5   BIT4   BIT3   BIT2   BIT1   BIT0
 *   0      0      0      0      0      0      0  ASHOTPC   ASCALE_FREQ  AGAINPC   ATEST     PC    PC3    PC2    PC1    PC0
 *
 * @brief Returns The state of the remote lines.
 */
uint16_t getRemoteLines(void);

#define ASHOTPC_BIT			BIT8
#define ASCALE_FREQ_BIT		BIT7
#define AGAINPC_BIT			BIT6
#define ATEST_BIT			BIT5
#define PC_BIT				BIT4
#define PC3_BIT				BIT3
#define PC2_BIT				BIT2
#define PC1_BIT				BIT1
#define PC0_BIT				BIT0


/**
 * getLocalConfiguration() returns the local configuration
 * Bits: the state of selection switches in local mode.
 * It's returned in the format
 *      BIT7               BIT6               BIT5         BIT4    BIT3   BIT2  BIT1  BIT0
 *  Sweep_SW     loc_Scale_Freq     loc_Pulse_Gain       rate_B  rate_A     Q2    Q1    Q0
 *
 * -- Q2 Q1 Q0 --
 *  000 =  10  Hz
 *  001 = 100  Hz
 *  010 =   1 kHz
 *  011 =  10 kHz
 *  100 = 100 kHz
 *
 * -- rate_B rate_A --
 *  00 =  1 [%/s]
 *  01 =  3 [%/s]
 *  10 =  5 [%/s]
 *  11 =  7 [%/s]
 *
 * -- loc_Pulse_Gain --
 *   0 = x1   Gain
 *   1 = x0.5 Gain
 *
 * -- loc_Scale_Freq --
 *   0 = x1   Scale
 *   1 = x0.5 Scale
 *
 * -- Sweep_SW --
 *   0 = Switch Released
 *   1 = Switch Pressed
 *
 * @brief Returns The state of the local configuration switches.
 */
uint8_t getLocalConfiguration(void);

#define SWEEP_SW_BIT			BIT7   // Not passed to
#define LOC_SCALE_FREQ_BIT		BIT6
#define lOC_PULSE_GAIN_BIT		BIT5
#define RATE_B_BIT				BIT4
#define RATE_A_BIT				BIT3
#define Q2_BIT					BIT2
#define Q1_BIT					BIT1
#define Q0_BIT					BIT0

/**
 * @brief Calibration parameters initialization
 */
void CalParamInit(void);

/**
 * @brief Saves the calibration parameters in external memory
 * @param params : pointer to IA_Cal_Params_T object
 * @param addr   : address where data will be stored
 * @return nothing
 */
void CalParamSave(IA_Cal_Params_T* params, uint16_t addr);


/**
 * @brief Prepares INVAP Bus communication packets
 * @return nothing
 */
void TPG_2_INVAPBusAttend(void);

uint8_t St_Check_Measures(void);

#define CHECK_OK		1
#define CHECK_ERROR		0


#define SWEEP_ON			1
#define SWEEP_OFF			0

#define MAX_FREQ_10_HZ		150
#define MIN_FREQ_10_HZ		 50

#define MAX_FREQ_100_HZ		1500
#define MIN_FREQ_100_HZ		 500

#define MAX_FREQ_1_kHZ		15000
#define MIN_FREQ_1_kHZ		 5000

#define MAX_FREQ_10_kHZ		150000
#define MIN_FREQ_10_kHZ		 50000

#define MAX_FREQ_100_kHZ	1500000
#define MIN_FREQ_100_kHZ	 500000


#define MAX_FREQ_OUT_OFF	MAX_FREQ_10_HZ
#define MIN_FREQ_OUT_OFF	0
#define MAX_RATE_OUT_OFF	100
#define MIN_RATE_OUT_OFF	-100


#define MAX_RATE_1_PPS		200
#define MIN_RATE_1_PPS		0

#define MAX_RATE_3_PPS		400
#define MIN_RATE_3_PPS		200

#define MAX_RATE_5_PPS		600
#define MIN_RATE_5_PPS		400

#define MAX_RATE_7_PPS		800
#define MIN_RATE_7_PPS		600

#define FREQ_MIN_FOR_RATE_CALCULUS		6000
#define MAX_RATE_FOR_STOP_SWEEP		   -5000 // -50 [%/s]

#define MAX_FREQ_DIFF		100   // 10Hz of máx difference


#define SETTLING_MEASUREMENT_CYCLES		10

// Bits de errores de hardware
#define RS485_FREQ_OUT_OF_BOUNDS		BIT0
#define DIFF_PLUS_FREQ_OUT_OF_BOUNDS	BIT1
#define DIFF_MINUS_FREQ_OUT_OF_BOUNDS	BIT2
#define DIFF_DISCREPANCE				BIT3
#define RS485_RATE_OUT_OF_BOUNDS		BIT4
#define DIFF_PLUS_RATE_OUT_OF_BOUNDS	BIT5
#define DIFF_MINUS_RATE_OUT_OF_BOUNDS	BIT6

#endif /* POISSON_H_ */
