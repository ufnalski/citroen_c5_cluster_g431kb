/* USER CODE BEGIN Header */
/** https://autowp.github.io/
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
#include "dma.h"
#include "fdcan.h"
#include "i2c.h"
#include "rng.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "citroen_c5.h"
#include "ssd1306.h"

//#define USE_INTERNAL_TEMP_SENSOR

#ifdef USE_INTERNAL_TEMP_SENSOR
#include "internal_temp_sensor.h"
#endif
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// #define EXPERIMENT_WITH_MENU
#define MENU_UART_INSTANCE USART2
#define MENU_UART_HANDLE_PTR &huart2

#define MPH2KPH 1.609344

#define CAN_MSG_REPEAT_PERIOD 100
#define CAN_MSG_TIME_INTERVAL 1

#define ENGINE_SPEED_MAX 5600 // rpm
#define ENGINE_SPEED_INCREMENT 200
#define ENGINE_SPEED_DECREMENT 300
#define VEHICLE_SPEED_MAX 200 //650 //((uint16_t)(round(127*MPH2KPH))) // km/h
#define VEHICLE_SPEED_INCREMENT 3
#define ENGINE_SPEED_GEAR_SHIFT 4500 // rpm
#define COOLANT_TEMPERATURE 80 // degC
#define FUEL_LEVEL 75 // %
#define OIL_TEMP 150
#define ODOMETER 0 // please do not change it //(308*MPH2KPH) // km

#define DELAYED_START_INTERVAL 4000

// #define SEND_ALL_CONSECUTIVE_IDS
#define BEGINING_FROM_ID 0
#define PATTERN_TO_BE_SEND   0x55
#define FDCAN_DLC_BYTES_MIN 3
#define FDCAN_DLC_BYTES_MAX 8

#define PUSH_BUTTON_TIME_INTERVAL 100
#define NUMBER_OF_KEYS 1 // universal solution, but here we expect just a single key stroke
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
FDCAN_RxHeaderTypeDef RxHeader0;
uint8_t RxData0[8];

FDCAN_RxHeaderTypeDef RxHeader1;
uint8_t RxData1[8];
uint8_t RxDataUnits[8];
uint8_t RxDataOdometer[8];
uint8_t odometer_rx_flag = 0;

FDCAN_TxHeaderTypeDef TxHeader;
uint8_t TxData8[8];

uint32_t TxMailbox;

uint16_t vehicle_speed = 0;
uint16_t engine_speed = 0;
uint8_t gear_number;

uint8_t engine_speed_down;

uint32_t CanMsgSoftTimer50;
uint32_t CanMsgSoftTimer100;
uint32_t CanMsgSoftTimer200;
uint32_t CanMsgSoftTimer500;
uint32_t CanMsgSoftTimer;
uint32_t DelayedStartSoftTimer;

volatile uint8_t green_button_flag = 0;

uint16_t msg_id = BEGINING_FROM_ID;

char lcd_line[128];

uint8_t keyboard_keys[NUMBER_OF_KEYS];
volatile uint8_t keyboard_flag = 0;

#ifdef USE_INTERNAL_TEMP_SENSOR
typedef struct AdcValues
{
	uint16_t Raw[2]; /* Raw values from ADC */
	int32_t IntSensTmp; /* Temperature */
} adcval_t;

adcval_t Adc;

typedef struct Flags
{
	uint8_t ADCCMPLT;
} flag_t;

flag_t Flg =
{ 0, };
#endif

uint32_t mileage = ODOMETER;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void CalculateRpmSpeed(void);
void DisplayUnitsAndLanguage(void);

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
	MX_DMA_Init();
	MX_USART2_UART_Init();
	MX_FDCAN1_Init();
	MX_I2C3_Init();
	MX_RNG_Init();
	MX_ADC1_Init();
	MX_TIM3_Init();
	MX_USART1_UART_Init();
	/* USER CODE BEGIN 2 */

#ifdef USE_INTERNAL_TEMP_SENSOR
	HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) Adc.Raw, 2);
	HAL_TIM_Base_Start(&htim3); /* This timer starts ADC conversion */
#endif

	ssd1306_Init();
	ssd1306_Fill(Black);
	ssd1306_SetCursor(20, 0);
	ssd1306_WriteString("ufnalski.edu.pl", Font_6x8, White);
	ssd1306_SetCursor(10, 11);
	ssd1306_WriteString("Citroen C5 II 2011", Font_6x8, White);
	ssd1306_SetCursor(10, 22);
	ssd1306_WriteString("Instrument cluster", Font_6x8, White);
	ssd1306_SetCursor(12, 33);
	ssd1306_WriteString("CAN bus hacking", Font_6x8, White);
	ssd1306_UpdateScreen();

	HAL_FDCAN_ConfigGlobalFilter(&hfdcan1, FDCAN_REJECT, FDCAN_REJECT,
	FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE);

	if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK)
	{
		Error_Handler();
	}

	if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE,
			0) != HAL_OK)
	{
		/* Notification Error */
		Error_Handler();
	}

	if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO1_NEW_MESSAGE,
			0) != HAL_OK)
	{
		/* Notification Error */
		Error_Handler();
	}

	TxHeader.IdType = FDCAN_STANDARD_ID;
	TxHeader.TxFrameType = FDCAN_DATA_FRAME;
	TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	TxHeader.BitRateSwitch = FDCAN_BRS_ON;
	TxHeader.FDFormat = FDCAN_FD_CAN;
	TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	TxHeader.MessageMarker = 0;

	CanMsgSoftTimer50 = HAL_GetTick();
	CanMsgSoftTimer100 = HAL_GetTick();
	CanMsgSoftTimer200 = HAL_GetTick();
	CanMsgSoftTimer500 = HAL_GetTick();
	CanMsgSoftTimer = HAL_GetTick();
	DelayedStartSoftTimer = HAL_GetTick();

	memset(RxData0, 0x00, sizeof(RxData0));
	memset(RxData1, 0x00, sizeof(RxData1));

	HAL_UARTEx_ReceiveToIdle_DMA(MENU_UART_HANDLE_PTR, keyboard_keys, 1);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	while (1)
	{

		if (odometer_rx_flag == 1)
		{
			odometer_rx_flag = 0;
			mileage = (RxDataOdometer[0] << 16) | (RxDataOdometer[1] << 8)
					| (RxDataOdometer[3]);
			mileage /= 10;
		}

		if (green_button_flag == 1)
		{
			green_button_flag = 0;
			send_door_warning(CAN_MSG_TIME_INTERVAL);
		}

		// You can't enter the menu while driving :)
		if (keyboard_flag == 1)
		{
			keyboard_flag = 0;
			switch (keyboard_keys[0])
			{
			case 'm':
				send_steering_wheel_button_menu(CAN_MSG_TIME_INTERVAL);
				send_steering_wheel_button_left_scroll_0(CAN_MSG_TIME_INTERVAL);
				break;
			case 'b':
				send_steering_wheel_button_left_back(CAN_MSG_TIME_INTERVAL);
				send_steering_wheel_button_left_scroll_0(CAN_MSG_TIME_INTERVAL);
				break;
			case 'p':
				send_steering_wheel_button_left_scroll_pushed(
				CAN_MSG_TIME_INTERVAL);
				send_steering_wheel_button_left_scroll_0(
				PUSH_BUTTON_TIME_INTERVAL);
				break;
			case '0':
				send_steering_wheel_button_left_scroll_0(CAN_MSG_TIME_INTERVAL);
				break;
			case '1':
				send_steering_wheel_button_left_scroll_1(CAN_MSG_TIME_INTERVAL);
				break;
			case '2':
				send_steering_wheel_button_left_scroll_2(CAN_MSG_TIME_INTERVAL);
				break;
			case '3':
				send_steering_wheel_button_left_scroll_3(CAN_MSG_TIME_INTERVAL);
				break;
			case '4':
				send_steering_wheel_button_left_scroll_4(CAN_MSG_TIME_INTERVAL);
				break;
			case '5':
				send_steering_wheel_button_left_scroll_5(CAN_MSG_TIME_INTERVAL);
				break;
			case '6':
				send_steering_wheel_button_left_scroll_6(CAN_MSG_TIME_INTERVAL);
				break;
			case '7':
				send_steering_wheel_button_left_scroll_7(CAN_MSG_TIME_INTERVAL);
				break;
			case '8':
				send_steering_wheel_button_left_scroll_8(CAN_MSG_TIME_INTERVAL);
				break;
			default:
				;
			}
		}

		// every 50 ms
		if (HAL_GetTick() - CanMsgSoftTimer50 > 50)
		{
			CanMsgSoftTimer50 = HAL_GetTick();
			// You can't enter the menu while driving :)
#ifndef EXPERIMENT_WITH_MENU
			send_rpm_and_speed(engine_speed, vehicle_speed,
			CAN_MSG_TIME_INTERVAL);
#endif
		}
		// every 100 ms
		if (HAL_GetTick() - CanMsgSoftTimer100 > 100)
		{
			CanMsgSoftTimer100 = HAL_GetTick();
			send_ignition_on((RxData0[0]) >> 4, CAN_MSG_TIME_INTERVAL);
		}
		// every 200 ms
		if (HAL_GetTick() - CanMsgSoftTimer200 > 200)
		{
			CanMsgSoftTimer200 = HAL_GetTick();
			if (HAL_GetTick() - DelayedStartSoftTimer > DELAYED_START_INTERVAL)
			{
				CalculateRpmSpeed();
				send_christmas_lights_and_gear(gear_number,
				CAN_MSG_TIME_INTERVAL);
				send_christmas_lights_bis(CAN_MSG_TIME_INTERVAL);
				send_cruise_data(CAN_MSG_TIME_INTERVAL);
			}
		}
		// every 500 ms
		if (HAL_GetTick() - CanMsgSoftTimer500 > 500)
		{
			CanMsgSoftTimer500 = HAL_GetTick();
			send_fuel_level_and_oil_temp(FUEL_LEVEL, OIL_TEMP,
			CAN_MSG_TIME_INTERVAL);
			send_odometer_and_coolant_temp(COOLANT_TEMPERATURE, mileage,
			CAN_MSG_TIME_INTERVAL);
//			send_maintenance(CAN_MSG_TIME_INTERVAL);

#ifndef SEND_ALL_CONSECUTIVE_IDS
			ssd1306_SetCursor(2, 47);
			ssd1306_WriteString("Units & language:", Font_6x8, White);
			DisplayUnitsAndLanguage();
			ssd1306_SetCursor(16, 56);
			ssd1306_WriteString(lcd_line, Font_6x8, White);
			ssd1306_UpdateScreen();
#endif
			HAL_GPIO_TogglePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin);
		}

#ifdef SEND_ALL_CONSECUTIVE_IDS
		if ((HAL_GetTick() - CanMsgSoftTimer > CAN_MSG_REPEAT_PERIOD)
				&& (msg_id <= 0x7FF))
		{
			CanMsgSoftTimer = HAL_GetTick();

			for (uint32_t msg_length = FDCAN_DLC_BYTES_MAX;
					msg_length >= FDCAN_DLC_BYTES_MIN; msg_length--)
			{
				HAL_Delay(CAN_MSG_TIME_INTERVAL);
				TxHeader.DataLength = msg_length;
				TxHeader.Identifier = msg_id;
				memset(TxData8, PATTERN_TO_BE_SEND, sizeof(TxData8));

				if (msg_id != CAN_ID_ODOMETER_TO_IPC)
				{
					if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader,
							TxData8) != HAL_OK)
					{
						Error_Handler();
					}
				}
			}

			msg_id++;

#ifdef USE_INTERNAL_TEMP_SENSOR
					if (Flg.ADCCMPLT) /* Conversion completed, do calculations */
					{
						/* Temperature Sensor ADC-value, Reference Voltage ADC-value (if use) */
						Adc.IntSensTmp = TMPSENSOR_getTemperature(Adc.Raw[0],
								Adc.Raw[1]);

						Flg.ADCCMPLT = 0; /* Nullify flag */

					}
					sprintf(lcd_line, "uC temp.: %ld deg. C ", Adc.IntSensTmp);
					ssd1306_SetCursor(2, 45);
					ssd1306_WriteString(lcd_line, Font_6x8, White);
		#endif
			sprintf(lcd_line, "Brightness: %d  ", (RxData0[0]) >> 4);
			ssd1306_SetCursor(16, 45);
			ssd1306_WriteString(lcd_line, Font_6x8, White);

			sprintf(lcd_line, "Message ID: %u    ", msg_id - 1);
			ssd1306_SetCursor(16, 56);
			ssd1306_WriteString(lcd_line, Font_6x8, White);

			ssd1306_UpdateScreen(); // adds 100 ms at 100 kHz I2C!!!
			HAL_GPIO_TogglePin(BLUE_LED_GPIO_Port,
			BLUE_LED_Pin);
		}
#endif
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
	RCC_OscInitTypeDef RCC_OscInitStruct =
	{ 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct =
	{ 0 };

	/** Configure the main internal regulator output voltage
	 */
	HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI
			| RCC_OSCILLATORTYPE_HSI48;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
	RCC_OscInitStruct.PLL.PLLN = 10;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV4;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */
#ifdef USE_INTERNAL_TEMP_SENSOR
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	if (hadc->Instance == ADC1) /* Check if the interrupt comes from ACD1 */
	{
		/* Set flag to true */
		Flg.ADCCMPLT = 0xFF;
	}
}
#endif

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
	if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
	{
		/* Retreive Rx messages from RX FIFO0 */
		if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader0, RxData0)
				!= HAL_OK)
		{
			/* Reception Error */
			Error_Handler();
		}

		if (HAL_FDCAN_ActivateNotification(hfdcan,
		FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
		{
			/* Notification Error */
			Error_Handler();
		}
		else
		{
			HAL_GPIO_TogglePin(YELLOW_LED_GPIO_Port,
			YELLOW_LED_Pin);
		}
	}
}

void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
{
	if ((RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE) != RESET)
	{
		/* Retreive Rx messages from RX FIFO0 */
		if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, &RxHeader1, RxData1)
				!= HAL_OK)
		{
			/* Reception Error */
			Error_Handler();
		}
		else if (RxHeader1.Identifier == 0x2D7) // choice of units
		{
			memcpy(RxDataUnits, RxData1, 8);
		}
		else if ((RxHeader1.Identifier == CAN_ID_ODOMETER_FROM_IPC)
				&& (RxHeader1.DataLength == 6)) // odometer
		{
			odometer_rx_flag = 1;
			memcpy(RxDataOdometer, RxData1, 8);
		}
		else
		{
			;
		}

		if (HAL_FDCAN_ActivateNotification(hfdcan,
		FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK)
		{
			/* Notification Error */
			Error_Handler();
		}
		else
		{
			HAL_GPIO_TogglePin(YELLOW_LED_GPIO_Port,
			YELLOW_LED_Pin);
		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GREEN_BUTTON_Pin)
	{
		green_button_flag = 1;
	}
}

void CalculateRpmSpeed(void)
{
	if (!engine_speed_down)
	{
		if (engine_speed < ENGINE_SPEED_MAX - ENGINE_SPEED_INCREMENT)
		{
			engine_speed = engine_speed + ENGINE_SPEED_INCREMENT;

		}
		else if (gear_number < 5)
		{
			engine_speed_down = 1;
			gear_number++;
		}
		else
		{
			;
		}
	}
	else
	{
		if (engine_speed > ENGINE_SPEED_GEAR_SHIFT)
		{
			engine_speed = engine_speed - ENGINE_SPEED_DECREMENT;
		}
		else
		{
			engine_speed_down = 0;
		}
	}

	if (vehicle_speed < VEHICLE_SPEED_MAX - VEHICLE_SPEED_INCREMENT)
	{
		vehicle_speed = vehicle_speed + VEHICLE_SPEED_INCREMENT;
	}
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart->Instance == MENU_UART_INSTANCE)
	{
		keyboard_flag = 1;
		HAL_UARTEx_ReceiveToIdle_DMA(MENU_UART_HANDLE_PTR, keyboard_keys, 1);
	}
}

void DisplayUnitsAndLanguage(void)
{
	int str_length = 0;
	if (RxDataUnits[1] == 0x00)
	{
		str_length = sprintf(lcd_line, "l/100 km");
	}
	else if (RxDataUnits[1] == 0xE0)
	{
		str_length = sprintf(lcd_line, "mpg");
	}
	else if (RxDataUnits[1] == 0x40)
	{
		str_length = sprintf(lcd_line, "km/l");
	}
	else
	{
		str_length = sprintf(lcd_line, "Sth went wrong!");
	}

	if (RxDataUnits[0] == 0x01)
	{
		sprintf(lcd_line + str_length, " & EN          ");
	}
	else // reverse engineer more languages :)
	{
		sprintf(lcd_line + str_length, " & xx        ");
	}
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) // disabled to catch the odometer
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
//	__disable_irq();
//	while (1)
//	{
//	}
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
