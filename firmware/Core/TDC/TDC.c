/*
 * TDC.c
 *
 * Driver for TI TDC7200 -- Source file
 *
 * (C) T. Burkard | M. Schaer
 *
 */

#include "TDC/TDC.h"
#include <stdbool.h>

#define TDC_AUTO_INC_OFF (0 << 7)
#define TDC_AUTO_INC_ON  (1 << 7)

#define TDC_RW_READ  (0 << 6)
#define TDC_RW_WRITE (1 << 6)

#define TDC_CMD_READ  (TDC_AUTO_INC_ON | TDC_RW_READ)
#define TDC_CMD_WRITE (TDC_AUTO_INC_ON | TDC_RW_WRITE)

const uint8_t TDC_REG_SIZE[TDC_ADR_AMOUNT] = {
    // Register Address              Register Size [bytes]
    [TDC_ADR_CONFIG1]                = 1,
    [TDC_ADR_CONFIG2]                = 1,
    [TDC_ADR_INT_STATUS]             = 1,
    [TDC_ADR_INT_MASK]               = 1,
    [TDC_ADR_COARSE_CNTR_OVF_H]      = 1,
    [TDC_ADR_COARSE_CNTR_OVF_L]      = 1,
    [TDC_ADR_CLOCK_CNTR_OVF_H]       = 1,
    [TDC_ADR_CLOCK_CNTR_OVF_L]       = 1,
    [TDC_ADR_CLOCK_CNTR_STOP_MASK_H] = 1,
    [TDC_ADR_CLOCK_CNTR_STOP_MASK_L] = 1,
    [TDC_ADR_TIME1]                  = 3,
    [TDC_ADR_CLOCK_COUNT1]           = 3,
    [TDC_ADR_TIME2]                  = 3,
    [TDC_ADR_CLOCK_COUNT2]           = 3,
    [TDC_ADR_TIME3]                  = 3,
    [TDC_ADR_CLOCK_COUNT3]           = 3,
    [TDC_ADR_TIME4]                  = 3,
    [TDC_ADR_CLOCK_COUNT4]           = 3,
    [TDC_ADR_TIME5]                  = 3,
    [TDC_ADR_CLOCK_COUNT5]           = 3,
    [TDC_ADR_TIME6]                  = 3,
    [TDC_ADR_CALIBRATION1]           = 3,
    [TDC_ADR_CALIBRATION2]           = 3,
};

static TDC_error_t send(TDC_t* tdc, TDC_adr_t address, uint8_t* data, bool write);

TDC_error_t TDC_init(TDC_t* tdc, SPI_HandleTypeDef* spi, GPIO_TypeDef* cs_port, uint16_t cs_pin, GPIO_TypeDef* en_port, uint16_t en_pin)
{
    if ((tdc == NULL) || (spi == NULL) || (cs_port == NULL) || (en_port == NULL)) {
        return TDC_ERROR;
    }

    tdc->spi     = spi;
    tdc->cs_port = cs_port;
    tdc->cs_pin  = cs_pin;
    tdc->en_port = en_port;
    tdc->en_pin  = en_pin;

    return TDC_OK;
}

TDC_error_t TDC_enable(TDC_t* tdc)
{
    if (tdc == NULL) {
        return TDC_ERROR;
    }

    HAL_GPIO_WritePin(tdc->en_port, tdc->en_pin, GPIO_PIN_SET);

    return TDC_OK;
}

TDC_error_t TDC_disable(TDC_t* tdc)
{
    if (tdc == NULL) {
        return TDC_ERROR;
    }

    HAL_GPIO_WritePin(tdc->en_port, tdc->en_pin, GPIO_PIN_RESET);

    return TDC_OK;
}

TDC_error_t TDC_write(TDC_t* tdc, TDC_adr_t address, uint8_t* tx_data)
{
    return send(tdc, address, tx_data, true);
}

TDC_error_t TDC_read(TDC_t* tdc, TDC_adr_t address, uint8_t* rx_data)
{
    return send(tdc, address, rx_data, false);
}

TDC_error_t TDC_start(TDC_t* tdc)
{
    uint8_t     data[TDC_REG_SIZE[TDC_ADR_CONFIG1]];
    TDC_error_t error_code = TDC_OK;

    if ((error_code = TDC_read(tdc, TDC_ADR_CONFIG1, data)) != TDC_OK) {
        return error_code;
    }

    data[0] |= TDC_CONFIG1_START_MEAS;

    return TDC_write(tdc, TDC_ADR_CONFIG1, data);
}

TDC_error_t TDC_read_result(TDC_t* tdc, uint64_t* tof_fs)
{
    uint8_t time1_buf[TDC_REG_SIZE[TDC_ADR_TIME1]];
    uint8_t time2_buf[TDC_REG_SIZE[TDC_ADR_TIME2]];
    uint8_t clock_count1_buf[TDC_REG_SIZE[TDC_ADR_CLOCK_COUNT1]];
    uint8_t calibration1_buf[TDC_REG_SIZE[TDC_ADR_CALIBRATION1]];
    uint8_t calibration2_buf[TDC_REG_SIZE[TDC_ADR_CALIBRATION2]];
    uint8_t config2_buf[TDC_REG_SIZE[TDC_ADR_CONFIG2]];

    uint32_t time1;
    uint32_t time2;
    uint32_t clock_count1;
    uint32_t calibration1;
    uint32_t calibration2;
    uint32_t calibration2_periods;

    TDC_error_t error_code = TDC_OK;

    // Read registers

    if ((error_code = TDC_read(tdc, TDC_ADR_TIME1, time1_buf)) != TDC_OK) {
        return error_code;
    }

    time1 = TDC_24BIT_BUF_TO_INT(time1_buf);

    if ((error_code = TDC_read(tdc, TDC_ADR_TIME2, time2_buf)) != TDC_OK) {
        return error_code;
    }

    time2 = TDC_24BIT_BUF_TO_INT(time2_buf);

    if ((error_code = TDC_read(tdc, TDC_ADR_CLOCK_COUNT1, clock_count1_buf)) != TDC_OK) {
        return error_code;
    }

    clock_count1 = TDC_24BIT_BUF_TO_INT(clock_count1_buf);

    if ((error_code = TDC_read(tdc, TDC_ADR_CALIBRATION1, calibration1_buf)) != TDC_OK) {
        return error_code;
    }

    calibration1 = TDC_24BIT_BUF_TO_INT(calibration1_buf);

    if ((error_code = TDC_read(tdc, TDC_ADR_CALIBRATION2, calibration2_buf)) != TDC_OK) {
        return error_code;
    }

    calibration2 = TDC_24BIT_BUF_TO_INT(calibration2_buf);

    if ((error_code = TDC_read(tdc, TDC_ADR_CONFIG2, config2_buf)) != TDC_OK) {
        return error_code;
    }

    if (config2_buf[0] & TDC_CONFIG2_CALIBRATION2_PERIODS_10) {
        calibration2_periods = 10;
    } else if (config2_buf[0] & TDC_CONFIG2_CALIBRATION2_PERIODS_20) {
        calibration2_periods = 20;
    } else if (config2_buf[0] & TDC_CONFIG2_CALIBRATION2_PERIODS_40) {
        calibration2_periods = 40;
    } else { // TDC_CONFIG2_CALIBRATION2_PERIODS_2
    	calibration2_periods = 2;
    }

    // Calculations

    double cal_count = (double)(calibration2 - calibration1) / (calibration2_periods - 1);
    uint64_t norm_lsb_fs = (uint64_t)(TDC_CLOCK_PERIOD_FS / cal_count);

    *tof_fs = (int64_t)norm_lsb_fs * ((int64_t)time1 - (int64_t)time2) + ((int64_t)clock_count1 * TDC_CLOCK_PERIOD_FS);

    return TDC_OK;
}

/**
 * @brief Read/write register data from/to TDC
 *
 * Function for both reading and writing register data, depending on @p write parameter.
 *
 * @param[in]     tdc     -- Pointer to TDC handle
 * @param[in]     address -- Address of the register(s) to read/write
 * @param[in,out] data    -- Pointer to data
 * @param[in]     write -- True = write, false = read
 *
 * @attention @p data needs to provide space for at least TDC_REG_SIZE[ @p address ] bytes.
 *
 * @return TDC_error_t -- Error code
 */
static TDC_error_t send(TDC_t* tdc, TDC_adr_t address, uint8_t* data, bool write)
{
    uint8_t size; // number of data bytes
    uint8_t cmd = address | (write ? TDC_CMD_WRITE : TDC_CMD_READ);

    if ((tdc == NULL) || (data == NULL)) {
        return TDC_ERROR;
    }

    if (address >= TDC_ADR_AMOUNT) {
        return TDC_WRONG_ADDRESS;
    }

    size = TDC_REG_SIZE[address];

    HAL_GPIO_WritePin(tdc->cs_port, tdc->cs_pin, GPIO_PIN_RESET);
    HAL_Delay(1); // 1 ms

    if (HAL_SPI_Transmit(tdc->spi, &cmd, 1, HAL_MAX_DELAY) != HAL_OK) {
        return TDC_COM_ERROR;
    }

    if (write) {
        if (HAL_SPI_Transmit(tdc->spi, data, size, HAL_MAX_DELAY) != HAL_OK) {
            return TDC_COM_ERROR;
        }
    } else {
        if (HAL_SPI_Receive(tdc->spi, data, size, HAL_MAX_DELAY) != HAL_OK) {
            return TDC_COM_ERROR;
        }
    }

    HAL_GPIO_WritePin(tdc->cs_port, tdc->cs_pin, GPIO_PIN_SET);
    HAL_Delay(1); // 1 ms

    return TDC_OK;
}
