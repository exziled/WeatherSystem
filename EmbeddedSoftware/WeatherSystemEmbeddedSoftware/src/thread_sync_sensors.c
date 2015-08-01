

#include "contiki.h"
#include "sys/etimer.h"
#include "weather_drivers/config_sync_sensors.h"
#include "weather.h"

#define SAMPLE_DELAY CLOCK_SECOND * 5

#include <stdio.h> /* For printf() */
#include <stdlib.h>
/*---------------------------------------------------------------------------*/
PROCESS(sync_weather_sensors, "Weather Sensor Configuration and Sampling");
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(sync_weather_sensors, ev, data)
{
	static struct etimer et;
	WEATHER_ERR_T err;
	uint32_t wind_dir_raw;
	static WEATHER_EVT_DATA_T wind_data;

	PROCESS_BEGIN();
	config_wind_direction();

	wind_data.type = WEATHER_TYPE_WIND_D;

	etimer_set(&et, SAMPLE_DELAY);

	while(1)
	{
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
		// Do something process related
		
		err = sample_wind_direction(&wind_dir_raw);
		wind_data.data = wind_dir_raw & 0xFFFF;
		
		process_post(&sensor_data_transfer, evt_sync_ready, &wind_data);
		
		etimer_set(&et, SAMPLE_DELAY);
	}

	PROCESS_END();
}
/*---------------------------------------------------------------------------*/
