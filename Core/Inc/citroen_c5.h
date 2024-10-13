/*
 * mustang.h
 *
 *  Created on: Jan 9, 2024
 *      Author: user
 */

// Sources:
// https://autowp.github.io/

#ifndef INC_CITROEN_C5_H_
#define INC_CITROEN_C5_H_

#include "main.h"
#include <string.h>
#include <math.h>

#define CAN_ID_ODOMETER_TO_IPC 0xF6 // mileage cannot be decreased - do not send random patterns!
#define CAN_ID_ODOMETER_FROM_IPC 0x257 // sent couple of times at the power-up

void send_steering_wheel_button_menu(uint32_t delay_before_send);
void send_steering_wheel_button_left_back(uint32_t delay_before_send);
void send_steering_wheel_button_left_scroll_pushed(uint32_t delay_before_send);
void send_steering_wheel_button_left_scroll_0(uint32_t delay_before_send);
void send_steering_wheel_button_left_scroll_1(uint32_t delay_before_send);
void send_steering_wheel_button_left_scroll_2(uint32_t delay_before_send);
void send_steering_wheel_button_left_scroll_3(uint32_t delay_before_send);
void send_steering_wheel_button_left_scroll_4(uint32_t delay_before_send);
void send_steering_wheel_button_left_scroll_5(uint32_t delay_before_send);
void send_steering_wheel_button_left_scroll_6(uint32_t delay_before_send);
void send_steering_wheel_button_left_scroll_7(uint32_t delay_before_send);
void send_steering_wheel_button_left_scroll_8(uint32_t delay_before_send);

void send_door_warning(uint32_t delay_before_send);
void send_cruise_data(uint32_t delay_before_send);
void send_christmas_lights_and_gear(uint8_t gear_number, uint32_t delay_before_send);
void send_christmas_lights_bis(uint32_t delay_before_send);
void send_odometer_and_coolant_temp(uint8_t coolant_temp, uint32_t odometer, uint32_t delay_before_send);
void send_fuel_level_and_oil_temp(uint8_t fuel, uint8_t oil_temp, uint32_t delay_before_send);
void send_ignition_on(uint8_t lcd_brightness, uint32_t delay_before_send);
void send_rpm_and_speed(uint16_t rpm, uint16_t speed, uint32_t delay_before_send);

void send_maintenance(uint32_t delay_before_send);

#endif /* INC_CITROEN_C5_H_ */
