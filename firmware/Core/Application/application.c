/*
 * Application.c
 *
 *  Created on: Jan 17, 2025
 *      Author: T. Burkard, M. Schaer
 */
/* *********************** INCLUDES ********************************** */
#include "application.h"
#include "main.h"
#include "TDC.h"

#include <stdio.h>
#include <string.h>

/* *********************** EXTERNAL VARIABLES *********************** */
extern SPI_HandleTypeDef hspi1;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;

/* ************************* STATIC VARIABLES  ********************** */
static TDC_t tdc_ele;
static TDC_t tdc_opt;

/* ********************** FORWARD DECLARATIONS ********************** */
static void TerminalWrite(uint64_t tof_fs);

/* ****************************************************************** */
/*                         MEASUREMENT ELECTRICAL                     */
/* ****************************************************************** */
void SetupMsmtEle(void)
{
	  if (TDC_init(&tdc_ele, &hspi1, SPI_CS_ELE_GPIO_Port, SPI_CS_ELE_Pin, TDC_ELE_ENABLE_GPIO_Port, TDC_ELE_ENABLE_Pin) != TDC_OK) {
	    for (;;) {} // TODO: Error handling...
	  }

	  if (TDC_enable(&tdc_ele) != TDC_OK) {
	    for (;;) {} // TODO: Error handling...
	  }

	  uint8_t data[TDC_REG_SIZE[TDC_ADR_CONFIG1]];

	  if (TDC_read(&tdc_ele, TDC_ADR_CONFIG1, data) != TDC_OK) {
	    for (;;) {} // TODO: Error handling...
	  }

	  data[0] |= TDC_CONFIG1_MEAS_MODE_1;

	  if (TDC_write(&tdc_ele, TDC_ADR_CONFIG1, data) != TDC_OK) {
		for (;;) {} // TODO: Error handling...
	  }
}

void DoMsmtEle(void)
{
	uint64_t tof_fs = 0;
	HAL_StatusTypeDef status = HAL_OK;
	(void) status;

	if (TDC_start(&tdc_ele) != TDC_OK) {
	  for (;;) {} // TODO: Error handling...
	}

	// *((volatile uint32_t*)(GPIOA_BASE + 0x14)) |= (1 << 8);
	// *((volatile uint32_t*)(GPIOA_BASE + 0x14)) |= (1 << 11);

	// Start the timer to toggle pins from low to high
	WRP_MX_TIM1_Init();
	status = HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_1);
	status = HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_4);

	HAL_Delay(2); // 2 ms

	if (TDC_read_result(&tdc_ele, &tof_fs) != TDC_OK) {
	  for (;;) {} // TODO: Error handling...
	}

	TerminalWrite(tof_fs);

	// Start timer one more time to toggle pins from high to low
	WRP_MX_TIM1_Init();
	status = HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_1);
	status = HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_4);

	HAL_Delay(2); // 2 ms
}


/* ****************************************************************** */
/*                         MEASUREMENT OPTICAL                        */
/* ****************************************************************** */
void SetupMsmtOpt(void)
{
	  if (TDC_init(&tdc_opt, &hspi1, SPI_CS_OPT_GPIO_Port, SPI_CS_OPT_Pin, TDC_OPT_ENABLE_GPIO_Port, TDC_OPT_ENABLE_Pin) != TDC_OK) {
	    for (;;) {} // TODO: Error handling...
	  }

	  if (TDC_enable(&tdc_opt) != TDC_OK) {
	    for (;;) {} // TODO: Error handling...
	  }

	  uint8_t data[TDC_REG_SIZE[TDC_ADR_CONFIG1]];

	  if (TDC_read(&tdc_opt, TDC_ADR_CONFIG1, data) != TDC_OK) {
	    for (;;) {} // TODO: Error handling...
	  }

	  data[0] |= TDC_CONFIG1_MEAS_MODE_1 | TDC_CONFIG1_STOP_EDGE_FALL;

	  if (TDC_write(&tdc_opt, TDC_ADR_CONFIG1, data) != TDC_OK) {
		for (;;) {} // TODO: Error handling...
	  }
}

void DoMsmtOpt(void)
{
	uint64_t tof_fs = 0;
	HAL_StatusTypeDef status = HAL_OK;
	(void) status;

	if (TDC_start(&tdc_opt) != TDC_OK) {
	  for (;;) {} // TODO: Error handling...
	}

	// Start the timer to toggle pins from low to high
	WRP_MX_TIM3_Init();
	status = HAL_TIM_OC_Start(&htim3, TIM_CHANNEL_3);
	status = HAL_TIM_OC_Start(&htim3, TIM_CHANNEL_4);

	HAL_Delay(2); // 2 ms

	if (TDC_read_result(&tdc_opt, &tof_fs) != TDC_OK) {
	  for (;;) {} // TODO: Error handling...
	}

	TerminalWrite(tof_fs);

	// Start timer one more time to toggle pins from high to low
	WRP_MX_TIM3_Init();
	status = HAL_TIM_OC_Start(&htim3, TIM_CHANNEL_3);
	status = HAL_TIM_OC_Start(&htim3, TIM_CHANNEL_4);

	HAL_Delay(2); // 2 ms
}

/* ****************************************************************** */
/*                           GENERAL FUNCTIONS                        */
/* ****************************************************************** */
static void TerminalWrite(uint64_t tof_fs)
{
	char string[50] = "";
	sprintf(string, "ToF = %lu [ps]\n", (uint32_t)(tof_fs / 1000));
	HAL_UART_Transmit(&huart2, (uint8_t*)string, strlen(string), 10000);
}
