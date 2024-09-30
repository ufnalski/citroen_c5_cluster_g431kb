/*
 * focus.c
 *
 *  Created on: Jan 9, 2024
 *      Author: user
 *
 *  Sources:
 *  https://autowp.github.io/
 *
 */

#include "citroen_c5.h"
#include "fdcan.h"

extern FDCAN_TxHeaderTypeDef TxHeader;
extern uint8_t TxData8[8];

// ------------------------------------------------ 0xA2 (steering wheel buttons) -------------
// https://www.youtube.com/watch?v=nzGVbwNSqzk
// https://frenchcarforum.co.uk/forum/viewtopic.php?t=80934
void send_steering_wheel_button_menu(uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_5;
	TxHeader.Identifier = 0xA2;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0x00;
	TxData8[1] = 0x08;
	TxData8[2] = 0x00;
	TxData8[3] = 0x00;
	TxData8[4] = 0x00;

	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

void send_steering_wheel_button_left_back(uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_5;
	TxHeader.Identifier = 0xA2;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0x00;
	TxData8[1] = 0x00;
	TxData8[2] = 0x00;
	TxData8[3] = 0x00;
	TxData8[4] = 0x10;

	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

void send_steering_wheel_button_left_scroll_pushed(uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_5;
	TxHeader.Identifier = 0xA2;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0x00;
	TxData8[1] = 0x00;
	TxData8[2] = 0x00;
	TxData8[3] = 0x00;
	TxData8[4] = 0x20;

	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

void send_steering_wheel_button_left_scroll_0(uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_5;
	TxHeader.Identifier = 0xA2;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0x00;
	TxData8[1] = 0x00;
	TxData8[2] = 0x00;
	TxData8[3] = 0x00;
	TxData8[4] = 0x00;

	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

void send_steering_wheel_button_left_scroll_1(uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_5;
	TxHeader.Identifier = 0xA2;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0x00;
	TxData8[1] = 0x00;
	TxData8[2] = 0x00;
	TxData8[3] = 0x01;
	TxData8[4] = 0x00;

	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

void send_steering_wheel_button_left_scroll_2(uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_5;
	TxHeader.Identifier = 0xA2;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0x00;
	TxData8[1] = 0x00;
	TxData8[2] = 0x00;
	TxData8[3] = 0x02;
	TxData8[4] = 0x00;

	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

void send_steering_wheel_button_left_scroll_3(uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_5;
	TxHeader.Identifier = 0xA2;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0x00;
	TxData8[1] = 0x00;
	TxData8[2] = 0x00;
	TxData8[3] = 0x04;
	TxData8[4] = 0x00;

	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

void send_steering_wheel_button_left_scroll_4(uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_5;
	TxHeader.Identifier = 0xA2;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0x00;
	TxData8[1] = 0x00;
	TxData8[2] = 0x00;
	TxData8[3] = 0x08;
	TxData8[4] = 0x00;

	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

void send_steering_wheel_button_left_scroll_5(uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_5;
	TxHeader.Identifier = 0xA2;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0x00;
	TxData8[1] = 0x00;
	TxData8[2] = 0x00;
	TxData8[3] = 0x10;
	TxData8[4] = 0x00;

	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

void send_steering_wheel_button_left_scroll_6(uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_5;
	TxHeader.Identifier = 0xA2;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0x00;
	TxData8[1] = 0x00;
	TxData8[2] = 0x00;
	TxData8[3] = 0x20;
	TxData8[4] = 0x00;

	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

void send_steering_wheel_button_left_scroll_7(uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_5;
	TxHeader.Identifier = 0xA2;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0x00;
	TxData8[1] = 0x00;
	TxData8[2] = 0x00;
	TxData8[3] = 0x40;
	TxData8[4] = 0x00;

	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

void send_steering_wheel_button_left_scroll_8(uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_5;
	TxHeader.Identifier = 0xA2;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0x00;
	TxData8[1] = 0x00;
	TxData8[2] = 0x00;
	TxData8[3] = 0x80;
	TxData8[4] = 0x00;

	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

// ----------------------------------------------- 0E8 (text warnings) --------
// https://www.youtube.com/watch?v=a4WXy9XJC9c
void send_door_warning(uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_7;
	TxHeader.Identifier = 0x0E8;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0x10;
	TxData8[1] = 0;
	TxData8[2] = 0;
	TxData8[3] = 0;
	TxData8[4] = 0;
	TxData8[5] = 0;
	TxData8[6] = 0;

	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

//----------------------------------- 0x128 (many indicators) ---------------------------
void send_christmas_lights_and_gear(uint8_t gear_number,
		uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x128;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0xFF;
	TxData8[1] = 0xFF;
	TxData8[2] = 0xFF;
	TxData8[3] = 0xFF;
	TxData8[4] = 0xFF;
	TxData8[5] = 0xFF;

	TxData8[6] = 0x00;
	switch (gear_number)
	{
	case 0:
		TxData8[6] = (TxData8[6] & 0b00001111) | 0b10010000; // 1st gear
		break;
	case 1:
		TxData8[6] = (TxData8[6] & 0b00001111) | 0b10000000; // 2nd gear
		break;
	case 2:
		TxData8[6] = (TxData8[6] & 0b00001111) | 0b01110000; // 3rd gear
		break;
	case 3:
		TxData8[6] = (TxData8[6] & 0b00001111) | 0b01100000; // 4th gear
		break;
	case 4:
		TxData8[6] = (TxData8[6] & 0b00001111) | 0b01010000; // 5th gear
		break;
	case 5:
		TxData8[6] = (TxData8[6] & 0b00001111) | 0b01000000; // 6th gear
		break;
	case 'P':
		TxData8[6] = (TxData8[6] & 0b00001111) | 0b00000000; // P
		break;
	case 'R':
		TxData8[6] = (TxData8[6] & 0b00001111) | 0b00010000; // R
		break;
	case 'N':
		TxData8[6] = (TxData8[6] & 0b00001111) | 0b00100000; // N
		break;
	case 'D':
		TxData8[6] = (TxData8[6] & 0b00001111) | 0b00110000; // D
		break;
	default:
		TxData8[6] = (TxData8[6] & 0b11110000);
	}

	TxData8[7] = 0xFF;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

// ------------------------------------------- 0x168 (many indicators) --------------
void send_christmas_lights_bis(uint32_t delay_before_send)
{

	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x168;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0xff;
	TxData8[1] = 0xff;
	TxData8[2] = 0xff;
	TxData8[3] = 0xff;
	TxData8[4] = 0xff;
	TxData8[5] = 0xff;
	TxData8[6] = 0xff;
	TxData8[7] = 0xff;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}

}

// ------------------------------------------------------- 0x36 (ignition) -----------------
void send_ignition_on(uint8_t lcd_brightness, uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x36;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0b00001110;  // ignition on -> activates arrows!!!
	TxData8[1] = 0;
	TxData8[2] = 0;
	TxData8[3] = 0b00100000 | lcd_brightness;
	TxData8[4] = 0b00000001; // ignition
	TxData8[5] = 0;
	TxData8[6] = 0;
	TxData8[7] = 0b10100000;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

// ---------------------------------------------- 0x1A8 (cruise data) -----------
void send_cruise_data(uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x1A8;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0x55;
	TxData8[1] = 0x55;
	TxData8[2] = 0x55;
	TxData8[3] = 0x55;
	TxData8[4] = 0x55;
	TxData8[5] = 0x04; // trip distance
	TxData8[6] = 0x55;
	TxData8[7] = 0x55;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

// ------------------------------------------- 0xB6 (rpm and ground speed) ------------------
void send_rpm_and_speed(uint16_t rpm, uint16_t speed,
		uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0xB6;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = (uint8_t) (rpm >> 5);
	TxData8[1] = (uint8_t) (rpm << 3);
	TxData8[2] = (uint8_t) ((speed * 100) >> 8);
	TxData8[3] = (uint8_t) (speed * 100);
	TxData8[4] = 0x00;
	TxData8[5] = 0x00;
	TxData8[6] = 0x00;
	TxData8[7] = 0x00; //0xD0;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

// ------------------------------------------------ 0x161 (fuel level and oil temp) -----------
void send_fuel_level_and_oil_temp(uint8_t fuel, uint8_t oil_temp,
		uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_7;
	TxHeader.Identifier = 0x161;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0;
	TxData8[1] = 0;
	TxData8[2] = oil_temp + 39; // wild guess
	TxData8[3] = fuel;
	TxData8[4] = 0;
	TxData8[5] = 0;
	TxData8[6] = 0;
	TxData8[7] = 0;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

// --------------------------------------- 0xF6 (coolant temp and odometer) ---------
void send_odometer_and_coolant_temp(uint8_t coolant_temp, float odometer,
		uint32_t delay_before_send)
{
	coolant_temp += 39;  // incorrect formula?
	odometer *= 10;
	uint32_t mileage = round(odometer);
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0xF6;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0x8E; // 0x8e;  //0x88;
	TxData8[1] = coolant_temp;

	// It looks like you cannot decrease the displayed value (contrary to e.g. Peugeot 308 T9).
	TxData8[2] = (uint8_t) (mileage >> 16);
	TxData8[3] = (uint8_t) (mileage >> 8);
	TxData8[4] = (uint8_t) mileage;
	TxData8[5] = 0x8E; //0xAA; //0x6f;
	TxData8[6] = 0xAA; //(uint8_t) round(25.0 / 2.0 - 39.5);
	TxData8[7] = 0x00; //0xAA; //0x23;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

// ------------------------------------------ 0x3E7 (maintenance(?)) ---------
void send_maintenance(uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_5;
	TxHeader.Identifier = 0x3E7;
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0x40;
	TxData8[1] = 0x00;
	TxData8[2] = 0xFE;
	TxData8[3] = 0x00;
	TxData8[4] = 0xAA;

	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}
