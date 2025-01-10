/*
 * TDC.h
 *
 * Driver for TI TDC7200 -- Header file
 *
 * (C) T. Burkard | M. Schaer
 *
 */

#ifndef TDC_H_
#define TDC_H_

#include <stdint.h>
#include "stm32f0xx_hal.h"

#define TDC_CLOCK_PERIOD_FS 62500000 // 16 MHz in [fs]

/**
 * Convert 24bit buffer received from SPI to integer
 */
#define TDC_24BIT_BUF_TO_INT(buf) ((buf[0] << 16) + (buf[1] << 8) + buf[2])

/**
 * @brief Register addresses of the TDC
 *
 */
typedef enum {
    TDC_ADR_CONFIG1                = 0x00, // Configuration Register 1
    TDC_ADR_CONFIG2                = 0x01, // Configuration Register 2
    TDC_ADR_INT_STATUS             = 0x02, // Interrupt Status Register
    TDC_ADR_INT_MASK               = 0x03, // Interrupt Mask Register
    TDC_ADR_COARSE_CNTR_OVF_H      = 0x04, // Coarse Counter Overflow Value High
    TDC_ADR_COARSE_CNTR_OVF_L      = 0x05, // Coarse Counter Overflow Value Low
    TDC_ADR_CLOCK_CNTR_OVF_H       = 0x06, // CLOCK Counter Overflow Value High
    TDC_ADR_CLOCK_CNTR_OVF_L       = 0x07, // CLOCK Counter Overflow Value Low
    TDC_ADR_CLOCK_CNTR_STOP_MASK_H = 0x08, // CLOCK Counter STOP Mask High
    TDC_ADR_CLOCK_CNTR_STOP_MASK_L = 0x09, // CLOCK Counter STOP Mask Low
    TDC_ADR_TIME1                  = 0x10, // Measured Time 1
    TDC_ADR_CLOCK_COUNT1           = 0x11, // CLOCK Counter Value
    TDC_ADR_TIME2                  = 0x12, // Measured Time 2
    TDC_ADR_CLOCK_COUNT2           = 0x13, // CLOCK Counter Value
    TDC_ADR_TIME3                  = 0x14, // Measured Time 3
    TDC_ADR_CLOCK_COUNT3           = 0x15, // CLOCK Counter Value
    TDC_ADR_TIME4                  = 0x16, // Measured Time 4
    TDC_ADR_CLOCK_COUNT4           = 0x17, // CLOCK Counter Value
    TDC_ADR_TIME5                  = 0x18, // Measured Time 5
    TDC_ADR_CLOCK_COUNT5           = 0x19, // CLOCK Counter Value
    TDC_ADR_TIME6                  = 0x1A, // Measured Time 6
    TDC_ADR_CALIBRATION1           = 0x1B, // Calibration 1, 1 CLOCK Period
    TDC_ADR_CALIBRATION2           = 0x1C, // Calibration 2, 2/10/20/40 CLOCK Periods
    TDC_ADR_AMOUNT // Amount of registers
} TDC_adr_t;

/**
 * @brief Register sizes of the TDC
 *
 * Index = Register address (TDC_adr_t)
 * Value = Register size (in bytes)
 *
 */
extern const uint8_t TDC_REG_SIZE[TDC_ADR_AMOUNT];

/**
 * @brief Bit description of the TDC CONFIG1 register
 *
 */
typedef enum {
    TDC_CONFIG1_FORCE_CAL_OFF   = (0b0 << 7), // Calibration is not performed after interrupted measurement (for example, due to counter overflow or missing STOP signal)
    TDC_CONFIG1_FORCE_CAL_ON    = (0b1 << 7), // Calibration is always performed at the end (for example, after a counter overflow)
    TDC_CONFIG1_PARITY_EN_OFF   = (0b0 << 6), // Parity bit for Measurement Result Registers disabled (Parity Bit always 0)
    TDC_CONFIG1_PARITY_EN_ON    = (0b1 << 6), // Parity bit for Measurement Result Registers enabled (Even Parity)
    TDC_CONFIG1_TRIGG_EDGE_RISE = (0b0 << 5), // TRIGG is output as a Rising edge signal
    TDC_CONFIG1_TRIGG_EDGE_FALL = (0b1 << 5), // TRIGG is output as a Falling edge signal
    TDC_CONFIG1_STOP_EDGE_RISE  = (0b0 << 4), // Measurement is stopped on Rising edge of STOP signal
    TDC_CONFIG1_STOP_EDGE_FALL  = (0b1 << 4), // Measurement is stopped on Falling edge of STOP signal
    TDC_CONFIG1_START_EDGE_RISE = (0b0 << 3), // Measurement is started on Rising edge of START signal
    TDC_CONFIG1_START_EDGE_FALL = (0b1 << 3), // Measurement is started on Falling edge of START signal
    TDC_CONFIG1_MEAS_MODE_1     = (0b00 << 1), // Measurement Mode 1 (for expected time-of-flight < 500 ns).
    TDC_CONFIG1_MEAS_MODE_2     = (0b01 << 1), // Measurement Mode 2 (recommended)
    TDC_CONFIG1_START_MEAS      = (0b1 << 0),  // Start New Measurement. Writing a 1 will clear all bits in the Interrupt Status Register and Start the measurement (by generating an TRIGG signal) and will reset the content of all Measurement Results registers
} TDC_config1_t;

/**
 * @brief Bit description of the TDC CONFIG2 register
 *
 */
typedef enum {
    TDC_CONFIG2_CALIBRATION2_PERIODS_2  = (0b00 << 6),  // Measuring 2 CLOCK periods
    TDC_CONFIG2_CALIBRATION2_PERIODS_10 = (0b01 << 6),  // Measuring 10 CLOCK periods
    TDC_CONFIG2_CALIBRATION2_PERIODS_20 = (0b10 << 6),  // Measuring 20 CLOCK periods
    TDC_CONFIG2_CALIBRATION2_PERIODS_40 = (0b11 << 6),  // Measuring 40 CLOCK periods
    TDC_CONFIG2_AVG_CYCLES_1            = (0b000 << 3), // 1 Measurement Cycle only (no Multi-Cycle Averaging Mode)
    TDC_CONFIG2_AVG_CYCLES_2            = (0b001 << 3), // 2 Measurement Cycles
    TDC_CONFIG2_AVG_CYCLES_4            = (0b010 << 3), // 4 Measurement Cycles
    TDC_CONFIG2_AVG_CYCLES_8            = (0b011 << 3), // 8 Measurement Cycles
    TDC_CONFIG2_AVG_CYCLES_16           = (0b100 << 3), // 16 Measurement Cycles
    TDC_CONFIG2_AVG_CYCLES_32           = (0b101 << 3), // 32 Measurement Cycles
    TDC_CONFIG2_AVG_CYCLES_64           = (0b110 << 3), // 64 Measurement Cycles
    TDC_CONFIG2_AVG_CYCLES_128          = (0b111 << 3), // 128 Measurement Cycles
    TDC_CONFIG2_NUM_STOP_1              = (0b000 << 0), // Single Stop
    TDC_CONFIG2_NUM_STOP_2              = (0b001 << 0), // Two Stops
    TDC_CONFIG2_NUM_STOP_3              = (0b010 << 0), // Three Stops
    TDC_CONFIG2_NUM_STOP_4              = (0b011 << 0), // Four Stops
    TDC_CONFIG2_NUM_STOP_5              = (0b100 << 0), // Five Stops
} TDC_config2_t;

/**
 * @brief Bit description of the TDC INT_STATUS register
 *
 */
typedef enum {
    TDC_STATUS_MEAS_COMPLETE_FLAG  = (1 << 4), // Measurement has completed
    TDC_STATUS_MEAS_STARTED_FLAG   = (1 << 3), // Measurement has started (START signal received)
    TDC_STATUS_CLOCK_CNTR_OVF_INT  = (1 << 2), // Clock overflow detected, running measurement will be stopped immediately
    TDC_STATUS_COARSE_CNTR_OVF_INT = (1 << 1), // Coarse overflow detected, running measurement will be stopped immediately
    TDC_STATUS_NEW_MEAS_INT        = (1 << 0), // Interrupt detected - New Measurement has been completed
} TDC_status_t;

/**
 * @brief Bit description of the TDC INT_MASK register
 *
 */
typedef enum {
    TDC_MASK_CLOCK_CNTR_OVF_MASK_OFF  = (0 << 2), // CLOCK Counter Overflow Interrupt disabled
    TDC_MASK_CLOCK_CNTR_OVF_MASK_ON   = (1 << 2), // CLOCK Counter Overflow Interrupt enabled
    TDC_MASK_COARSE_CNTR_OVF_MASK_OFF = (0 << 1), // Coarse Counter Overflow Interrupt disabled
    TDC_MASK_COARSE_CNTR_OVF_MASK_ON  = (1 << 1), // Coarse Counter Overflow Interrupt enabled
    TDC_MASK_NEW_MEAS_MASK_OFF        = (0 << 0), // New Measurement Interrupt disabled
    TDC_MASK_NEW_MEAS_MASK_ON         = (1 << 0), // New Measurement Interrupt enabled
} TDC_mask_t;

/**
 * @brief Error codes of the TDC module
 *
 */
typedef enum {
    TDC_OK = 0,
    TDC_ERROR,
    TDC_WRONG_ADDRESS,
    TDC_WRONG_SIZE,
    TDC_COM_ERROR,
} TDC_error_t;

/**
 * @brief Handle for a TDC instance
 *
 */
typedef struct {
    SPI_HandleTypeDef* spi;
    GPIO_TypeDef*      cs_port;
    uint16_t           cs_pin;
    GPIO_TypeDef*      en_port;
    uint16_t           en_pin;
} TDC_t;

/**
 * @brief Initialize a TDC instance
 *
 * Note, SPI and GPIOs need to be initialized manually before calling this function.
 *
 * @param[out] tdc     -- Pointer to TDC handle
 * @param[in]  spi     -- Pointer to SPI handle
 * @param[in]  cs_port -- GPIO port of Chip Select
 * @param[in]  cs_pin  -- GPIO pin of Chip Select
 * @param[in]  en_port -- GPIO port of Enable
 * @param[in]  en_pin  -- GPIO pin of Enable
 *
 * @return TDC_error -- Error code
 */
TDC_error_t TDC_init(TDC_t* tdc, SPI_HandleTypeDef* spi, GPIO_TypeDef* cs_port, uint16_t cs_pin, GPIO_TypeDef* en_port, uint16_t en_pin);

/**
 * @brief Enable the TDC
 *
 * @param[in] tdc -- Pointer to TDC handle
 *
 * @return TDC_error_t -- Error code
 */
TDC_error_t TDC_enable(TDC_t* tdc);

/**
 * @brief Disable the TDC
 *
 * @param[in] tdc -- Pointer to TDC handle
 *
 * @return TDC_error_t -- Error code
 */
TDC_error_t TDC_disable(TDC_t* tdc);

/**
 * @brief Read register data from TDC
 *
 * @param[in]  tdc     -- Pointer to TDC handle
 * @param[in]  address -- Address of the register(s) to read
 * @param[out] rx_data -- Pointer to data
 *
 * @attention @p rx_data needs to provide space for at least TDC_REG_SIZE[ @p address ] bytes.
 *
 * @return TDC_error_t -- Error code
 */
TDC_error_t TDC_read(TDC_t* tdc, TDC_adr_t address, uint8_t* rx_data);

/**
 * @brief Write register data to TDC
 *
 * @param[in] tdc     -- Pointer to TDC handle
 * @param[in] address -- Address of the register(s) to write
 * @param[in] tx_data -- Pointer to data
 *
 * @attention @p tx_data needs to provide space for at least TDC_REG_SIZE[ @p address ] bytes.
 *
 * @return TDC_error_t -- Error code
 */
TDC_error_t TDC_write(TDC_t* tdc, TDC_adr_t address, uint8_t* tx_data);

/**
 * @brief Start measurement of TDC
 *
 * @param[in] tdc -- Pointer to TDC handle
 *
 * @return TDC_error_t -- Error code
 */
TDC_error_t TDC_start(TDC_t* tdc);

/**
 * @brief Read ToF measurement result from TDC
 *
 * @param[in] tdc  -- Pointer to TDC handle
 * @param[out] tof_fs -- ToF Measurement result [fs]
 *
 * @return TDC_error_t -- Error code
 */
TDC_error_t TDC_read_result(TDC_t* tdc, uint64_t* tof_fs);

#endif /* TDC_H_ */
