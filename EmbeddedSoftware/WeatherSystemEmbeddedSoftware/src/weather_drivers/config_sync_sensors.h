/*
 * config_sync_sensors.h
 *
 * Created: 7/26/2015 12:47:38 AM
 *  Author: Ben
 */ 


#ifndef CONFIG_SYNC_SENSORS_H_
#define CONFIG_SYNC_SENSORS_H_

#include <stdint.h>
#include "weather_error.h"

#define WIND_DIRECTION_ADC_INPUT ADC_POSITIVE_INPUT_PIN11

WEATHER_ERR_T config_wind_direction(void);
WEATHER_ERR_T sample_wind_direction(uint32_t * target);

#endif /* CONFIG_SYNC_SENSORS_H_ */