#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"			//IDF����ǻ���FreeRTOS
#include "esp_system.h"				//esp32 ϵͳ������
#include "esp_spi_flash.h"			//�����д��
#include <esp_log.h>				//��־��

const static char *TAG = "Hello World";

void app_main()						//�������
{
	uint8_t MAC[6];
	ESP_LOGI(TAG, "Hello ESP32");

	// ��ӡоƬ��Ϣ
	esp_chip_info_t chip_info;
	esp_chip_info(&chip_info);


	ESP_LOGI(TAG, "ESP32 Chip Cores Count:  %d", chip_info.cores);		//��������

	ESP_LOGI(TAG, "ESP32 Chip Revision is:  %d", chip_info.revision);	//�汾��

	switch(chip_info.model)												//оƬ����
	{
		case 1:	ESP_LOGI(TAG, "ESP32 Chip Model is:  ESP32");break;
		case 2:	ESP_LOGI(TAG, "ESP32 Chip Model is:  ESP32S2");break;
		default:ESP_LOGI(TAG, "ESP32 Chip Model is:  Unknown Model");break;
	}

	ESP_LOGI(TAG, "ESP32 Chip Features is:  %d", chip_info.features);	//оƬ����


	ESP_LOGI(TAG, "WiFi%s%s, ",
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",		//�Ƿ��о�������
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : ""		//�Ƿ��е͹�������
	);

	ESP_LOGI(TAG, "SPI Flash Chip Size: %dMByte %s flash",
			spi_flash_get_chip_size() / (1024 * 1024),									//Flash��С
			(chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "Embedded" : "External"		//�ڲ��ⲿFlash
	);


	ESP_LOGI(TAG, "Free Heap Size is:  %d Byte", esp_get_free_heap_size());						//������С
	ESP_LOGI(TAG, "Free Internal Heap Size is:  %d Byte", esp_get_free_internal_heap_size());	//���еĶ��ڴ��С
	ESP_LOGI(TAG, "Free minimum Heap Size is:  %d Byte", esp_get_minimum_free_heap_size());

	esp_base_mac_addr_get(MAC);		//��ȡMAC��ַ
	ESP_LOGI(TAG, "Base MAC Addr :  %02X.%02X.%02X.%02X.%02X.%02X", MAC[0], MAC[1], MAC[2], MAC[3], MAC[4], MAC[5]);


	while(1)
	{
	    for (int i = 10; i >= 0; i--)
	    {
	        printf("Restarting in %d seconds...\n", i);
	        vTaskDelay(1000 / portTICK_PERIOD_MS);
	    }
	}

}
