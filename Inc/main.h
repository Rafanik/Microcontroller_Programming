/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains all variables and macros for
  *                      the main program body
  * Authors			   : Rafał Szczepanik, Kacper Kaczmarek
  * Project            : University of Warsaw Project for subject
  * 					 "Programming Microcontrollers in C"
  * Github             : https://github.com/Rafanik/PMIK_microcontroller_programming
  ******************************************************************************
  *
  * No rights reserved
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
enum STATE { YES = 1, NO = 0};
enum STATE DISPLAY; // if PIN should be displayed
enum STATE PREV_ALARM; // it is previous alarm state in while loop
enum STATE CHECK_PIN; // if uC in while loop should check for correct PIN
enum STATE CORRECT_PIN; // if PIN is correct
enum STATE DATE;// if date should be displayed
enum STATE CHECK_SMS; // if system in while lopp should check sms for new one-time PIN
extern enum STATE ALARM; // enum from alarm.c. if system should run alarm
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define D4_Pin GPIO_PIN_0
#define D4_GPIO_Port GPIOC
#define D5_Pin GPIO_PIN_1
#define D5_GPIO_Port GPIOC
#define D6_Pin GPIO_PIN_2
#define D6_GPIO_Port GPIOC
#define D7_Pin GPIO_PIN_3
#define D7_GPIO_Port GPIOC
#define CZUJNIK_Pin GPIO_PIN_0
#define CZUJNIK_GPIO_Port GPIOA
#define CZUJNIK_EXTI_IRQn EXTI0_IRQn
#define BUZZER_Pin GPIO_PIN_1
#define BUZZER_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define ROW2_Pin GPIO_PIN_10
#define ROW2_GPIO_Port GPIOB
#define ROW2_EXTI_IRQn EXTI15_10_IRQn
#define ROW3_Pin GPIO_PIN_12
#define ROW3_GPIO_Port GPIOB
#define ROW3_EXTI_IRQn EXTI15_10_IRQn
#define ROW4_Pin GPIO_PIN_13
#define ROW4_GPIO_Port GPIOB
#define ROW4_EXTI_IRQn EXTI15_10_IRQn
#define ROW1_Pin GPIO_PIN_14
#define ROW1_GPIO_Port GPIOB
#define ROW1_EXTI_IRQn EXTI15_10_IRQn
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define EN_Pin GPIO_PIN_10
#define EN_GPIO_Port GPIOC
#define RW_Pin GPIO_PIN_11
#define RW_GPIO_Port GPIOC
#define RS_Pin GPIO_PIN_12
#define RS_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define COL2_Pin GPIO_PIN_7
#define COL2_GPIO_Port GPIOB
#define COL1_Pin GPIO_PIN_8
#define COL1_GPIO_Port GPIOB
#define COL3_Pin GPIO_PIN_9
#define COL3_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
