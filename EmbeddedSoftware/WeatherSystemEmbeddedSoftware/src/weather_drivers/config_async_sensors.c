/*
 * wind.c
 *
 * Created: 7/22/2015 9:12:24 PM
 *  Author: Ben
 */ 

#include "config_async_sensors.h"
#include "sys/contiki-clock.h"
#include "extint.h"

static volatile RAIN_DATA_T g_rain_callback;
static volatile WIND_SPEED_T g_wind_speed_callback;

WEATHER_ERR_T config_rain_guage()
{	
	struct extint_chan_conf rain_extint_chan;
	
	extint_chan_get_config_defaults(&rain_extint_chan);
	
	rain_extint_chan.gpio_pin		= RAIN_INTERRUPT_PIN;
	rain_extint_chan.gpio_pin_mux	= RAIN_INTERRUPT_MUX;
	rain_extint_chan.gpio_pin_pull	= EXTINT_PULL_UP;
	rain_extint_chan.detection_criteria = EXTINT_DETECT_RISING;
	
	extint_chan_set_config(RAIN_INTERRUPT_LINE, &rain_extint_chan);
	extint_register_callback(rain_click_handle, RAIN_INTERRUPT_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(RAIN_INTERRUPT_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	
	return W_ERR_NONE;
}

WEATHER_ERR_T sample_rain_guage(uint32_t * aggregate, uint32_t * start_time)
{
	if (aggregate != NULL)
		*aggregate = g_rain_callback.clicks;
	if (start_time != NULL)
		*start_time = g_rain_callback.last_sample;
	
	g_rain_callback.clicks = 0;
	g_rain_callback.last_sample = clock_seconds();
	
	return W_ERR_NONE;
}

void rain_click_handle(void)
{
	g_rain_callback.clicks++;
}

void config_wind_speed()
{
	struct extint_chan_conf wind_speed_chan;
	
	extint_chan_get_config_defaults(&wind_speed_chan);
	
	wind_speed_chan.gpio_pin		= WIND_SPEED_INTERRUPT_PIN;
	wind_speed_chan.gpio_pin_mux	= WIND_SPEED_INTERRUPT_MUX;
	wind_speed_chan.gpio_pin_pull	= EXTINT_PULL_UP;
	wind_speed_chan.detection_criteria = EXTINT_DETECT_RISING;
	
	extint_chan_set_config(WIND_SPEED_INTERRUPT_LINE, &wind_speed_chan);
	extint_register_callback(wind_click_handle, WIND_SPEED_INTERRUPT_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(WIND_SPEED_INTERRUPT_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	
	return;
}

// Return aggregate and clear out buffer
WEATHER_ERR_T sample_wind_speed(uint32_t * aggregate, uint32_t * start_time)
{
		
		if (aggregate != NULL)
			*aggregate = g_wind_speed_callback.clicks;
		if (start_time != NULL)
			*start_time = g_wind_speed_callback.last_sample;
		
		g_wind_speed_callback.clicks = 0;
		g_wind_speed_callback.last_sample = clock_seconds();
		
		return W_ERR_NONE;
}

void wind_click_handle(void)
{
	g_wind_speed_callback.clicks++;
}