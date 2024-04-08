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
#include "adc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "NRF24L01.h"
#include <stdio.h>
#include "GUI_Paint.h"
#include "fonts.h"
#include "LCD_Test.h"
#include "LCD_1in28.h"

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

static uint8_t adc_trans_task = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  MX_TIM16_Init();
  MX_TIM2_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */



  uint8_t TX_addr[] = {0xEE, 0xDD, 0xCC, 0xBB, 0xAA};
  uint8_t RX_addr[] = {0x99, 0x88, 0x77, 0x66, 0x55};

  uint32_t counter = 0;
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);


  nrf_init();

  nrf_tx_mode(TX_addr, 10);



//	DEV_Module_Init();
//
//	LCD_1IN28_SetBackLight(1000);
//	LCD_1IN28_Init(VERTICAL);
//	//LCD_1IN28_Clear(BLACK);
//
//	Paint_NewImage(LCD_1IN28_WIDTH,LCD_1IN28_HEIGHT, 0, BLACK);
//
//	Paint_SetClearFuntion(LCD_1IN28_Clear);
//	Paint_SetDisplayFuntion(LCD_1IN28_DrawPaint);
//	Paint_DrawString_EN(70, 100, "LOADING...", &Font16, BLACK, DARKORANGE);
//
//	Paint_Clear(WHITE);
//	DEV_Delay_ms(100);
//
//	Paint_DrawRectangle(115, 115, 136, 141, DARKRED, 2, 0);
//	Paint_DrawNum(120, 120, counter, &Font16, DARKBLUE, DARKGREEN);


  //Setup the interrupt last
  HAL_TIM_Base_Start_IT(&htim2);


  uint8_t RX_data[32] = {0};


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  // NRF Transmission Code
//	  HAL_Delay(500);
//	  int trans_stat = nrf_transmit(TX_data);
//	  if( trans_stat == 1){
//		  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
//
//	  }
//	  HAL_Delay(500);
//	  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
//	  TX_data[6]++;


//	Paint_ClearWindows(120, 100, 164, 116, BLACK);
//	Paint_DrawNum(120, 120, counter, &Font16, DARKBLUE, DARKGREEN);
//	counter++;
//	HAL_Delay(250);



	/*Code for sending the ADC value over NRF*/
	if (adc_trans_task == 1){
		//Read the ADC
		uint32_t adc_val = 0;
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
		adc_val = HAL_ADC_GetValue(&hadc1);

		//NRF Transmission Code
		int trans_stat = nrf_send_adc(adc_val);

		if(trans_stat == 1){
			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

		}
	adc_trans_task = 0;
	}

	if(HAL_GPIO_ReadPin(Button_In_GPIO_Port, Button_In_Pin) == 0){
		while(1){
			nrf_send_adc(3300);
		}

	}

	/*Code for receiving data over NRF*/
//	nrf_rx_mode(RX_addr, 10);
//	if(is_data_availible(1) == 1){
//	  nrf_receive(RX_data);
//	  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);


//	HAL_Delay(250);






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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
// Callback: timer has rolled over
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

  if (htim == &htim2 ){
	//Code to run for TIM2 IRQ
	adc_trans_task = 1;

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
