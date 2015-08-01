/*
 * weather.h
 *
 * Created: 7/25/2015 8:07:08 PM
 *  Author: Ben
 */ 


#ifndef WEATHER_H_
#define WEATHER_H_

#include "contiki.h"

#define WEATHER_TYPE_RAIN	1
#define WEATHER_TYPE_WIND_S	2
#define WEATHER_TYPE_WIND_D 3

typedef struct event_data_ready_data
{
	uint16_t type;
	uint16_t data;
} WEATHER_EVT_DATA_T;


PROCESS_NAME(sensor_data_transfer);
PROCESS_NAME(async_weather_sensors);
PROCESS_NAME(sync_weather_sensors);

extern process_event_t evt_async_ready;
extern process_event_t evt_sync_ready;


#endif /* WEATHER_H_ */