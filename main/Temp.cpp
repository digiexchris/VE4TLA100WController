#include "Temp.hpp"

void TempMonitor::startTempMonitor(void *param)
{
	// Make sure that the internal pull-up resistor is enabled on the GPIO pin
    // so that one can connect up a sensor without needing an external pull-up.
    // (Note: The internal (~47k) pull-ups of the ESP do appear to work, at
    // least for simple setups (one or two sensors connected with short leads),
    // but do not technically meet the pull-up requirements from the ds18x20
    // datasheet and may not always be reliable. For a real application, a proper
    // 4.7k external pull-up resistor is recommended instead!)
    gpio_set_pull_mode(TEMP_SENSOR_PIN, GPIO_PULLUP_ONLY);
	
	size_t sensorCount = NULL;
	
	ds18x20_addr_t addrs[5];
	
	esp_err_t res;
	
	//Scan for temp sensor
	res = ds18x20_scan_devices(TEMP_SENSOR_PIN, addrs, 2, &sensorCount);
	if (res != ESP_OK)
	{
		printf("Couldn't get temp sensor address\n");
		State::setTemp(-999);
		vTaskDelete(NULL);
	}

	float temperature;
	
	//block the startup so everything can settle
	xTaskNotifyWait( 0x00,      /* Don't clear any notification bits on entry. */
		ULONG_MAX, /* Reset the notification value to 0 on exit. */
		NULL, /* Notified value pass out in
								ulNotifiedValue. */
		pdMS_TO_TICKS(100)); /* Block for 100 MS and just continue otherwise incase a notification got missed*/
	
	while (1)
	{
		while (1)
		{
			res = ds18x20_measure_and_read(TEMP_SENSOR_PIN, addrs[0], &temperature);
			if (res != ESP_OK) {
				State::setTemp(-9.00);
			}
			else {
				State::setTemp(temperature);
			}

			vTaskDelay(pdMS_TO_TICKS(1000));
		}
	}
}