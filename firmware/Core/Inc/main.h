/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/**
  Wrapper function for the MX_TIM1_Init function
*/
void WRP_MX_TIM1_Init(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOF
#define TDC_OPT_ENABLE_Pin GPIO_PIN_1
#define TDC_OPT_ENABLE_GPIO_Port GPIOA
#define VCP_TX_Pin GPIO_PIN_2
#define VCP_TX_GPIO_Port GPIOA
#define TDC_ELE_ENABLE_Pin GPIO_PIN_3
#define TDC_ELE_ENABLE_GPIO_Port GPIOA
#define LD_ENABLE_Pin GPIO_PIN_4
#define LD_ENABLE_GPIO_Port GPIOA
#define START_OPT_Pin GPIO_PIN_0
#define START_OPT_GPIO_Port GPIOB
#define LD_PULSE_Pin GPIO_PIN_1
#define LD_PULSE_GPIO_Port GPIOB
#define START_ELE_Pin GPIO_PIN_8
#define START_ELE_GPIO_Port GPIOA
#define INT_ELE_Pin GPIO_PIN_9
#define INT_ELE_GPIO_Port GPIOA
#define INT_OPT_Pin GPIO_PIN_10
#define INT_OPT_GPIO_Port GPIOA
#define STOP_ELE_Pin GPIO_PIN_11
#define STOP_ELE_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define VCP_RX_Pin GPIO_PIN_15
#define VCP_RX_GPIO_Port GPIOA
#define SPI_CLK_Pin GPIO_PIN_3
#define SPI_CLK_GPIO_Port GPIOB
#define SPI_MISO_Pin GPIO_PIN_4
#define SPI_MISO_GPIO_Port GPIOB
#define SPI_MOSI_Pin GPIO_PIN_5
#define SPI_MOSI_GPIO_Port GPIOB
#define SPI_CS_ELE_Pin GPIO_PIN_6
#define SPI_CS_ELE_GPIO_Port GPIOB
#define SPI_CS_OPT_Pin GPIO_PIN_7
#define SPI_CS_OPT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
