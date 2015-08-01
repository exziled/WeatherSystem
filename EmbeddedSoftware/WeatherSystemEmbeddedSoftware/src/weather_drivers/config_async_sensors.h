/*
 * wind.h
 *
 * Created: 7/22/2015 9:14:11 PM
 *  Author: Ben
 */ 


#ifndef __WIND_H_
#define __WIND_H_

#include "weather_error.h"
#include <stdint-gcc.h>

#define ASYNC_SENSOR_DEPTH 25

#define RAIN_INTERRUPT_PIN	0
#define RAIN_INTERRUPT_MUX	0
#define RAIN_INTERRUPT_LINE	0

#define WIND_SPEED_INTERRUPT_PIN	PIN_PA28A_EIC_EXTINT8
#define WIND_SPEED_INTERRUPT_MUX	MUX_PA28A_EIC_EXTINT8
#define WIND_SPEED_INTERRUPT_LINE	8

#define WIND_DIRECTION_PIN

// Rain Count - External Interrupt
typedef struct rain_data
{
	uint32_t clicks;
	uint32_t last_sample;	
	
} RAIN_DATA_T;

WEATHER_ERR_T config_rain_guage(void);
WEATHER_ERR_T sample_rain_guage(uint32_t * aggregate, uint32_t * start_time);
void rain_click_handle(void);

// Wind Speed - External Interrupt
typedef struct wind_speed
{
	uint32_t clicks;
	uint32_t last_sample;
} WIND_SPEED_T;

void config_wind_speed(void);
WEATHER_ERR_T sample_wind_speed(uint32_t * aggregate, uint32_t * start_time);
void wind_click_handle(void);

#endif /* __WIND_H_ */