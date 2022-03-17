ESP-IDF  HelloWorld 例程 AND 日志库 esp_log 
====================

### 头文件

```c
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"			//IDF框架是基于FreeRTOS
#include "esp_system.h"				//esp32 系统操作库
#include "esp_spi_flash.h"			//闪存读写库
#include <esp_log.h>				//日志库
```



```c
void app_main()						//程序入口
/*作为程序入口，类似于main()
可以初始化一些应用，创建其他 task
app_main 函数不能返回，否则会删除 main task 导致 crash
*/
```

### 日志库

考虑到线程安全，在FREERTOS中尽量使用ESP_LOGX来输出调试信息和打印消息

日志记录库提供了两种设置日志详细程度的方法：

- **在编译时**：在`menuconfig`中，使用选项设置详细程度`CONFIG_LOG_DEFAULT_LEVEL`。详细程度高于的所有日志记录语句`CONFIG_LOG_DEFAULT_LEVEL` 将被预处理器删除。

```c
#ifndef LOG_LOCAL_LEVEL
#ifndef BOOTLOADER_BUILD
#define LOG_LOCAL_LEVEL  CONFIG_LOG_DEFAULT_LEVEL
#else
#define LOG_LOCAL_LEVEL  CONFIG_LOG_BOOTLOADER_LEVEL
#endif
#endif
#define ESP_LOG_LEVEL_LOCAL(level, tag, format, ...) do {               \
        if ( LOG_LOCAL_LEVEL >= level ) ESP_LOG_LEVEL(level, tag, format, ##__VA_ARGS__); \
 } while(0)
```

- **在运行时**：详细级别低于的所有日志CONFIG_LOG_DEFAULT_LEVEL默认情况下启用。该功能esp_log_level_set()可用于按模块设置日志记录级别。模块由其标签标识，这些标签是可读的ASCII零终止字符串。

```c
//该功能esp_log_level_set()无法将日志记录级别设置为高于CONFIG_LOG_DEFAULT_LEVEL。要在编译时增加特定文件的日志级别，使用宏LOG_LOCAL_LEVEL
```

有以下详细级别：

`ESP_LOGE` -错误（最低）
`ESP_LOGW` - 警告
`ESP_LOGI` -信息
`ESP_LOGD` -调试
`ESP_LOGV` -详细（最高）

在每个使用日志记录功能的C文件中，定义TAG变量：

```c
static const char* TAG = "Hello ESP32";
```

然后使用日志记录宏之一生成输出，例如：

```c
uint16_t ap_count = 0;
ESP_LOGI(TAG, "Total APs scanned = %u", ap_count);
```

` esp_chip_info_t` 结构体

```c
	esp_chip_info_t a ={
		.cores = 核心数量
		.features = 芯片特性
		.model = 芯片类型,ESP32/ESP32S2
		.revision = 版本号
	};
```

