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
//#include "GUI_Paint.h"
//#include "fonts.h"
//#include "image.h"
//#include "LCD_Test.h"

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

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void LCD_WriteReg(uint8_t _dat)
{
    HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi2, (uint8_t *)&_dat, 1, 500);
    HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_SET);
}

void LCD_WriteData_Byte(uint8_t _dat){
    HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,GPIO_PIN_SET);
    HAL_SPI_Transmit(&hspi2, (uint8_t *)&_dat, 1, 500);
    HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_SET);
}

void LCD_WriteData_Word(uint16_t _dat)
{
  uint8_t i = (_dat >> 8);// & 0xff;
  HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,GPIO_PIN_SET);
  HAL_SPI_Transmit(&hspi2, (uint8_t *)&i, 1, 500);
  HAL_SPI_Transmit(&hspi2, (uint8_t *)&_dat, 1, 500);
  HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_SET);
}

void LCD1in28works(void){//LCD_Reset
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);
    HAL_Delay(100);

    /************* Start Initial Sequence **********/
      LCD_WriteReg(0xEF);
      LCD_WriteReg(0xEB);
      LCD_WriteData_Byte(0x14);

      LCD_WriteReg(0xFE);
      LCD_WriteReg(0xEF);

      LCD_WriteReg(0xEB);
      LCD_WriteData_Byte(0x14);

      LCD_WriteReg(0x84);
      LCD_WriteData_Byte(0x40);

      LCD_WriteReg(0x85);
      LCD_WriteData_Byte(0xFF);

      LCD_WriteReg(0x86);
      LCD_WriteData_Byte(0xFF);

      LCD_WriteReg(0x87);
      LCD_WriteData_Byte(0xFF);

      LCD_WriteReg(0x88);
      LCD_WriteData_Byte(0x0A);

      LCD_WriteReg(0x89);
      LCD_WriteData_Byte(0x21);

      LCD_WriteReg(0x8A);
      LCD_WriteData_Byte(0x00);

      LCD_WriteReg(0x8B);
      LCD_WriteData_Byte(0x80);

      LCD_WriteReg(0x8C);
      LCD_WriteData_Byte(0x01);

      LCD_WriteReg(0x8D);
      LCD_WriteData_Byte(0x01);

      LCD_WriteReg(0x8E);
      LCD_WriteData_Byte(0xFF);

      LCD_WriteReg(0x8F);
      LCD_WriteData_Byte(0xFF);


      LCD_WriteReg(0xB6);
      LCD_WriteData_Byte(0x00);
      LCD_WriteData_Byte(0x20);

      LCD_WriteReg(0x36);
      LCD_WriteData_Byte(0x08);//�?剧疆涓虹�?��?��

      LCD_WriteReg(0x3A);
      LCD_WriteData_Byte(0x05);


      LCD_WriteReg(0x90);
      LCD_WriteData_Byte(0x08);
      LCD_WriteData_Byte(0x08);
      LCD_WriteData_Byte(0x08);
      LCD_WriteData_Byte(0x08);

      LCD_WriteReg(0xBD);
      LCD_WriteData_Byte(0x06);

      LCD_WriteReg(0xBC);
      LCD_WriteData_Byte(0x00);

      LCD_WriteReg(0xFF);
      LCD_WriteData_Byte(0x60);
      LCD_WriteData_Byte(0x01);
      LCD_WriteData_Byte(0x04);

      LCD_WriteReg(0xC3);
      LCD_WriteData_Byte(0x13);
      LCD_WriteReg(0xC4);
      LCD_WriteData_Byte(0x13);

      LCD_WriteReg(0xC9);
      LCD_WriteData_Byte(0x22);

      LCD_WriteReg(0xBE);
      LCD_WriteData_Byte(0x11);

      LCD_WriteReg(0xE1);
      LCD_WriteData_Byte(0x10);
      LCD_WriteData_Byte(0x0E);

      LCD_WriteReg(0xDF);
      LCD_WriteData_Byte(0x21);
      LCD_WriteData_Byte(0x0c);
      LCD_WriteData_Byte(0x02);

      LCD_WriteReg(0xF0);
      LCD_WriteData_Byte(0x45);
      LCD_WriteData_Byte(0x09);
      LCD_WriteData_Byte(0x08);
      LCD_WriteData_Byte(0x08);
      LCD_WriteData_Byte(0x26);
      LCD_WriteData_Byte(0x2A);

      LCD_WriteReg(0xF1);
      LCD_WriteData_Byte(0x43);
      LCD_WriteData_Byte(0x70);
      LCD_WriteData_Byte(0x72);
      LCD_WriteData_Byte(0x36);
      LCD_WriteData_Byte(0x37);
      LCD_WriteData_Byte(0x6F);


      LCD_WriteReg(0xF2);
      LCD_WriteData_Byte(0x45);
      LCD_WriteData_Byte(0x09);
      LCD_WriteData_Byte(0x08);
      LCD_WriteData_Byte(0x08);
      LCD_WriteData_Byte(0x26);
      LCD_WriteData_Byte(0x2A);

      LCD_WriteReg(0xF3);
      LCD_WriteData_Byte(0x43);
      LCD_WriteData_Byte(0x70);
      LCD_WriteData_Byte(0x72);
      LCD_WriteData_Byte(0x36);
      LCD_WriteData_Byte(0x37);
      LCD_WriteData_Byte(0x6F);

      LCD_WriteReg(0xED);
      LCD_WriteData_Byte(0x1B);
      LCD_WriteData_Byte(0x0B);

      LCD_WriteReg(0xAE);
      LCD_WriteData_Byte(0x77);

      LCD_WriteReg(0xCD);
      LCD_WriteData_Byte(0x63);


      LCD_WriteReg(0x70);
      LCD_WriteData_Byte(0x07);
      LCD_WriteData_Byte(0x07);
      LCD_WriteData_Byte(0x04);
      LCD_WriteData_Byte(0x0E);
      LCD_WriteData_Byte(0x0F);
      LCD_WriteData_Byte(0x09);
      LCD_WriteData_Byte(0x07);
      LCD_WriteData_Byte(0x08);
      LCD_WriteData_Byte(0x03);

      LCD_WriteReg(0xE8);
      LCD_WriteData_Byte(0x34);

      LCD_WriteReg(0x62);
      LCD_WriteData_Byte(0x18);
      LCD_WriteData_Byte(0x0D);
      LCD_WriteData_Byte(0x71);
      LCD_WriteData_Byte(0xED);
      LCD_WriteData_Byte(0x70);
      LCD_WriteData_Byte(0x70);
      LCD_WriteData_Byte(0x18);
      LCD_WriteData_Byte(0x0F);
      LCD_WriteData_Byte(0x71);
      LCD_WriteData_Byte(0xEF);
      LCD_WriteData_Byte(0x70);
      LCD_WriteData_Byte(0x70);

      LCD_WriteReg(0x63);
      LCD_WriteData_Byte(0x18);
      LCD_WriteData_Byte(0x11);
      LCD_WriteData_Byte(0x71);
      LCD_WriteData_Byte(0xF1);
      LCD_WriteData_Byte(0x70);
      LCD_WriteData_Byte(0x70);
      LCD_WriteData_Byte(0x18);
      LCD_WriteData_Byte(0x13);
      LCD_WriteData_Byte(0x71);
      LCD_WriteData_Byte(0xF3);
      LCD_WriteData_Byte(0x70);
      LCD_WriteData_Byte(0x70);

      LCD_WriteReg(0x64);
      LCD_WriteData_Byte(0x28);
      LCD_WriteData_Byte(0x29);
      LCD_WriteData_Byte(0xF1);
      LCD_WriteData_Byte(0x01);
      LCD_WriteData_Byte(0xF1);
      LCD_WriteData_Byte(0x00);
      LCD_WriteData_Byte(0x07);

      LCD_WriteReg(0x66);
      LCD_WriteData_Byte(0x3C);
      LCD_WriteData_Byte(0x00);
      LCD_WriteData_Byte(0xCD);
      LCD_WriteData_Byte(0x67);
      LCD_WriteData_Byte(0x45);
      LCD_WriteData_Byte(0x45);
      LCD_WriteData_Byte(0x10);
      LCD_WriteData_Byte(0x00);
      LCD_WriteData_Byte(0x00);
      LCD_WriteData_Byte(0x00);

      LCD_WriteReg(0x67);
      LCD_WriteData_Byte(0x00);
      LCD_WriteData_Byte(0x3C);
      LCD_WriteData_Byte(0x00);
      LCD_WriteData_Byte(0x00);
      LCD_WriteData_Byte(0x00);
      LCD_WriteData_Byte(0x01);
      LCD_WriteData_Byte(0x54);
      LCD_WriteData_Byte(0x10);
      LCD_WriteData_Byte(0x32);
      LCD_WriteData_Byte(0x98);

      LCD_WriteReg(0x74);
      LCD_WriteData_Byte(0x10);
      LCD_WriteData_Byte(0x85);
      LCD_WriteData_Byte(0x80);
      LCD_WriteData_Byte(0x00);
      LCD_WriteData_Byte(0x00);
      LCD_WriteData_Byte(0x4E);
      LCD_WriteData_Byte(0x00);

        LCD_WriteReg(0x98);
      LCD_WriteData_Byte(0x3e);
      LCD_WriteData_Byte(0x07);

      LCD_WriteReg(0x35);
      LCD_WriteReg(0x21);

      LCD_WriteReg(0x11);
      HAL_Delay(120);
      LCD_WriteReg(0x29);
      HAL_Delay(20);

      //Start Backlight
      HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
      TIM16->CCR1 = 1000;

      //Set Cursor
      LCD_WriteReg(0x2a);
        LCD_WriteData_Byte(0x00);
        LCD_WriteData_Byte(0x00);
        LCD_WriteData_Byte(0x00);
        LCD_WriteData_Byte(0xEF);/*********Xend-1********/

        LCD_WriteReg(0x2b);
        LCD_WriteData_Byte(0x00);
        LCD_WriteData_Byte(0x00);
        LCD_WriteData_Byte(0x00);
        LCD_WriteData_Byte(0xEF);

        LCD_WriteReg(0x2c);

        //Write Color to display
        for(uint8_t i = 0; i <= 239; i++){
            for(uint8_t j = 0; j <= 239; j++){
                LCD_WriteData_Word(0x00FF);
            }
        }
}

/* Functions for the NRF module
static uint8_t *read_register(uint8_t reg)
{
    uint8_t command = NRF24L01P_CMD_R_REGISTER | reg;
    uint8_t status;
    uint8_t read_val[5] ={0};

    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&hspi1, &command, &status, 1, 2000);
    for(int i = 0; i<5; i++)
    	HAL_SPI_Receive(&hspi1, &read_val[i], 1, 2000);
    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_SET);

    return read_val;
}

static uint8_t write_register(uint8_t reg, uint8_t value)
{
    uint8_t command = NRF24L01P_CMD_W_REGISTER | reg;
    uint8_t status;
    uint8_t write_val = value;

    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&hspi1, &command, &status, 1, 2000);
    HAL_SPI_Transmit(&hspi1, &write_val, 1, 2000);
    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_SET);

    return write_val;
}
End of functions for the NRF module*/


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
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_USART1_UART_Init();
  MX_TIM16_Init();
  /* USER CODE BEGIN 2 */
  LCD1in28works();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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