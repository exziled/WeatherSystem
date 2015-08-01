

#include "contiki.h"
#include "sys/etimer.h"
#include "weather_drivers/config_async_sensors.h"
#include "weather.h"

#define SAMPLE_DELAY CLOCK_SECOND

#include <stdio.h> /* For printf() */
#include <stdlib.h>
/*---------------------------------------------------------------------------*/
PROCESS(async_weather_sensors, "Weather Sensor Configuration and Sampling");
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(async_weather_sensors, ev, data)
{
	static struct etimer et;
	WEATHER_ERR_T err;
	uint32_t wind_clicks, rain_clicks;
	static WEATHER_EVT_DATA_T wind_data, rain_data;

	PROCESS_BEGIN();
	config_rain_guage();
	config_wind_speed();

	wind_data.type = WEATHER_TYPE_WIND_S;
	rain_data.type = WEATHER_TYPE_RAIN;

	etimer_set(&et, SAMPLE_DELAY);

	while(1)
	{
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
		// Do something process related
		
		err = sample_wind_speed(&wind_clicks, NULL);
		err = sample_rain_guage(&rain_clicks, NULL);;
		
		wind_data.data = wind_clicks & 0xFFFF;
		rain_data.data = rain_clicks & 0xFFFF;
		
		// Get Actual Wind Speed and Rain Amount
		
		process_post(&sensor_data_transfer, evt_async_ready, &wind_data);
		process_post(&sensor_data_transfer, evt_async_ready, &rain_data);			
		
		etimer_set(&et, SAMPLE_DELAY);
	}

	PROCESS_END();
}
/*---------------------------------------------------------------------------*/
