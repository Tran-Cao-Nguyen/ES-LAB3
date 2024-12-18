/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "global.h"
#include "fsm_auto.h"
#include "fsm_man.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void system_init();
void test_LedDebug();
void test_LedY0();
void test_LedY1();
void test_7seg();
void keyInput();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  MX_FSMC_Init();
  /* USER CODE BEGIN 2 */
  system_init();
  led7_SetColon(1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  fsm_automatic_run();
  while (1)
  {
//	  while(!flag_timer1);
//	  flag_timer1 = 0;
//	  fsm_automatic_run();


	  while(!flag_timer3);
	  flag_timer3 = 0;
	  counter++;
	  button_Scan();
	  keyInput();
	  fsm_manual_run();
	  fsm_automatic_run();

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void system_init (){
	HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y0_Pin, RESET);
	HAL_GPIO_WritePin(OUTPUT_Y1_GPIO_Port, OUTPUT_Y1_Pin, RESET);
	HAL_GPIO_WritePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin, RESET);
	timer_init();
	led7_init();
	setTimer2(1000);
	setTimer1(1000);
	setTimer3(250);
	button_init();
	lcd_init();
}


uint8_t count_led_debug = 0;
uint8_t count_led_Y0 = 0;
uint8_t count_led_Y1 = 0;

void test_LedDebug(){
	count_led_debug = (count_led_debug + 1)%20;
	if(count_led_debug == 0){
		HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
	}
}

void test_LedY0(){
	count_led_Y0 = (count_led_Y0+ 1)%100;
	if(count_led_Y0 > 40){
		HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y0_Pin, 1);
	} else {
		HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y0_Pin, 0);
	}
}

void test_LedY1(){
	count_led_Y1 = (count_led_Y1+ 1)%40;
	if(count_led_Y1 > 10){
		HAL_GPIO_WritePin(OUTPUT_Y1_GPIO_Port, OUTPUT_Y1_Pin, 0);
	} else {
		HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y1_Pin, 1);
	}
}

void test_7seg(){
	//write number1 at led index 0 (not show dot)
	led7_SetDigit(1, 0, 0);
	led7_SetDigit(5, 1, 0);
	led7_SetDigit(4, 2, 0);
	led7_SetDigit(7, 3, 0);
}

void keyInput()
{
	switch(status){
		case RED_GREEN:
			if(button_count[0] == 1)
			{
				status = MAN_RED;
				tempRed = redDuration;
				tempGreen = greenDuration;
				tempAmber = amberDuration;
				oldRed = redDuration;
				oldAmber = amberDuration;
				oldGreen = greenDuration;
			}
			break;
		case RED_AMBER:
			if(button_count[0] == 1)
			{
				status = MAN_RED;
				tempRed = redDuration;
				tempGreen = greenDuration;
				tempAmber = amberDuration;
				oldRed = redDuration;
				oldAmber = amberDuration;
				oldGreen = greenDuration;
			}
			break;
		case GREEN_RED:
			if(button_count[0] == 1)
			{
				status = MAN_RED;
				tempRed = redDuration;
				tempGreen = greenDuration;
				tempAmber = amberDuration;
				oldRed = redDuration;
				oldAmber = amberDuration;
				oldGreen = greenDuration;
			}
			break;
		case INIT:
			if(button_count[0] == 1)
			{
				status = MAN_RED;
				tempRed = redDuration;
				tempGreen = greenDuration;
				tempAmber = amberDuration;
				oldRed = redDuration;
				oldAmber = amberDuration;
				oldGreen = greenDuration;
			}
			break;
		case MAN_RED:

			if(button_count[0] == 1)
			{
//				if(button_count[2] != 1)
//				{
//					redDuration = tempRed;
//				}
				status = MAN_AMBER;
				mode = 3;
			}
			if(button_count[1] == 1 && mode == 2)
			{
				tempRed += 1000;
				if (tempRed > 99000)
				{
					tempRed = 1000;
				}
			}
			if(button_count[2] == 1)
			{
				redDuration = tempRed;
			}
			break;
		case MAN_AMBER:

			if (button_count[0] == 1)
			{
//				if(button_count[2] != 1)
//				{
//					amberDuration = tempAmber;
//				}
				status = MAN_GREEN;
				mode = 4;
			}
			if (button_count[1] == 1  && mode == 3)
			{
				tempAmber += 1000;
				if (tempAmber > 99000)
				{
					tempAmber = 1000;
				}
			}
			if(button_count[2] == 1)
			{
				amberDuration = tempAmber;
			}
			break;
		case MAN_GREEN:

			if (button_count[0] == 1)
			{
//				if(button_count[2] != 1)
//				{
//					greenDuration = tempGreen;
//				}
				if (redDuration == (greenDuration + amberDuration))
				{
					status = RED_GREEN;
					redCounter = redDuration / 1000;
					greenCounter = greenDuration / 1000;
					amberCounter = amberDuration / 1000;
					mode = 1;
					HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
				}
				else
				{
					status = ERROR;
				}
			}
			if (button_count[1] == 1 && mode == 4)
			{
				tempGreen += 1000;
				if (tempGreen > 99000)
				{
					tempGreen = 1000;
				}
			}
			if(button_count[2] == 1)
			{
				greenDuration = tempGreen;
			}

			break;
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
