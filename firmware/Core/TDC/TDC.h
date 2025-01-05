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

#endif /* TDC_H_ */
