/*
 * thread_data_transfer.c
 *
 * Created: 7/25/2015 7:27:42 PM
 *  Author: Ben
 */ 
#include <stdio.h>

#include "weather.h"

process_event_t evt_async_ready;
process_event_t evt_sync_ready;

static volatile WEATHER_EVT_DATA_T * recv_data;

PROCESS(sensor_data_transfer, "Data Collection and Transfer Thread");
PROCESS_THREAD(sensor_data_transfer, ev, data)
{
	PROCESS_BEGIN();
	
	evt_async_ready = process_alloc_event();
	evt_sync_ready = process_alloc_event();
	
	while(1)
	{
		PROCESS_WAIT_EVENT_UNTIL(ev == evt_async_ready || ev == evt_sync_ready);
	
		recv_data = (WEATHER_EVT_DATA_T *)data;
	
		if (recv_data->type == WEATHER_TYPE_RAIN)
		{
			printf("Rain Data: ");
		} else if (recv_data->type == WEATHER_TYPE_WIND_S) {
			printf("Wind Speed: ");
		} else if (recv_data->type == WEATHER_TYPE_WIND_D) {
			printf("Wind Direction: ");
		}else {
			printf("Type Unknown %d: ", recv_data->type);
		}
		
		printf("%d\r\n", recv_data->data);
	}
	
	PROCESS_END()
}