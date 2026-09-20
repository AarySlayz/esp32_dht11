#include <dht.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define DHT11_GPIO GPIO_NUM_18

static const char *TAG = "dht11";

void app_main(void)
{
	while (true)
	{
		float humidity;
		float temperature;

		esp_err_t result = dht_read_float_data(
			DHT_TYPE_DHT11, DHT11_GPIO, &humidity, &temperature);

		if (result == ESP_OK)
		{
			float temperature_fahrenheit = temperature * 9.0f / 5.0f + 32.0f;

			ESP_LOGI(TAG, "Temperature: %.1f F, Humidity: %.1f %%",
					 temperature_fahrenheit, humidity);
		}
		else
		{
			ESP_LOGE(TAG, "Could not read DHT11: %s", esp_err_to_name(result));
		}

		vTaskDelay(pdMS_TO_TICKS(2000));
	}
}
