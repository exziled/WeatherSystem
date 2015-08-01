/*
 * config_sync_sensors.c
 *
 * Created: 7/26/2015 12:47:26 AM
 *  Author: Ben
 */ 
#include "config_sync_sensors.h"
#include "adc.h"

#define ADC_TIMEOUT 1000

static struct adc_module adc_instance;

// Wind Direction: ADC
WEATHER_ERR_T config_wind_direction()
{
	struct adc_config wind_adc_config;
	
	adc_get_config_defaults(&wind_adc_config);
	wind_adc_config.gain_factor		= ADC_GAIN_FACTOR_DIV2;
	wind_adc_config.clock_prescaler = ADC_CLOCK_PRESCALER_DIV8;
	wind_adc_config.reference		= ADC_REFERENCE_AREFB;
	wind_adc_config.positive_input	= WIND_DIRECTION_ADC_INPUT;
	wind_adc_config.resolution		= ADC_RESOLUTION_12BIT;
	
	adc_init(&adc_instance, ADC, &wind_adc_config);
	adc_enable(&adc_instance);
	
	return W_ERR_NONE;
}


WEATHER_ERR_T sample_wind_direction(uint32_t * target)
{
	uint32_t status;
	int16_t timeout = ADC_TIMEOUT;
	
	adc_start_conversion(&adc_instance);
	
	do {
		status = adc_read(&adc_instance, (uint16_t *)target);
		timeout--;
	}
	while ((status == STATUS_BUSY) && (timeout > 0));
	
	if (timeout <= 0)
	{
		return W_ERR_TIMEOUT;
	}
	
	return W_ERR_NONE;
}
