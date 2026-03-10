[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BME688

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/bme688/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

BME688是首款配備人工智慧（AI）且集成高線性度、高精度壓力、濕度和溫度感測器的氣體感測器。該氣體感測器能夠檢測到十億分之一（ppb）範圍內的揮發性有機化合物（VOC）以及其他氣體，如一氧化碳和氫氣。

LibDriver BME688是LibDriver推出的BME688全功能驅動，該驅動提供大氣壓強，溫度，濕度和氣體讀取等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example gas](#example-gas)
    - [example parallel](#example-parallel) 
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver BME688的源文件。

/interface目錄包含了LibDriver BME688與平台無關的IIC、SPI總線模板。

/test目錄包含了LibDriver BME688驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver BME688編程範例。

/doc目錄包含了LibDriver BME688離線文檔。

/datasheet目錄包含了BME688數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC、SPI總線模板，完成指定平台的IIC、SPI總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

#### example basic

```C
#include "driver_bme688_basic.h"

uint8_t res;
uint32_t i;
float temperature_c;
float pressure_pa;
float humidity_percentage;

/* basic init */
res = bme688_basic_init(BME688_INTERFACE_IIC, BME688_ADDRESS_ADO_LOW);
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
{
    /* delay 1000ms */
    bme688_interface_delay_ms(1000);

    /* read data */
    res = bme688_basic_read((float *)&temperature_c, (float *)&pressure_pa, (float *)&humidity_percentage);
    if (res != 0)
    {
        (void)bme688_basic_deinit();

        return 1;
    }

    /* output */
    bme688_interface_debug_print("bme688: %d/%d.\n", i + 1, 3);
    bme688_interface_debug_print("bme688: temperature is %0.2fC.\n", temperature_c);
    bme688_interface_debug_print("bme688: pressure is %0.2fPa.\n", pressure_pa);
    bme688_interface_debug_print("bme688: humidity is %0.2f%%.\n", humidity_percentage);
    
    ...
}

...
    
/* deinit */
(void)bme688_basic_deinit();

return 0;
```

#### example gas

```C
#include "driver_bme688_gas.h"

uint8_t res;
uint32_t i;
float temperature_c;
float pressure_pa;
float humidity_percentage;
float ohms;
uint8_t index = 0;
float degree_celsius = 200.0f;
uint16_t gas_wait_ms = 150;

/* gas init */
res = bme688_gas_init(BME688_INTERFACE_IIC, BME688_ADDRESS_ADO_LOW);
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
{
    /* delay 1000ms */
    bme688_interface_delay_ms(1000);

    /* read data */
    res = bme688_gas_read(degree_celsius, gas_wait_ms, index,
                         (float *)&temperature_c, (float *)&pressure_pa, (float *)&humidity_percentage, (float *)&ohms);
    if (res != 0)
    {
        (void)bme688_gas_deinit();

        return 1;
    }

    /* output */
    bme688_interface_debug_print("bme688: %d/%d.\n", i + 1, 3);
    bme688_interface_debug_print("bme688: temperature is %0.2fC.\n", temperature_c);
    bme688_interface_debug_print("bme688: pressure is %0.2fPa.\n", pressure_pa);
    bme688_interface_debug_print("bme688: humidity is %0.2f%%.\n", humidity_percentage);
    bme688_interface_debug_print("bme688: gas index is %d.\n", index);
    bme688_interface_debug_print("bme688: degree celsius is %0.1fC.\n", degree_celsius);
    bme688_interface_debug_print("bme688: gas wait is %d ms.\n", gas_wait_ms);
    bme688_interface_debug_print("bme688: gas resistance is %0.2fohms.\n", ohms);
    
    ...
}

...
    
/* deinit */
(void)bme688_gas_deinit();

return 0;
```

#### example parallel

```C
#include "driver_bme688_parallel.h"

uint8_t res;
bme688_parallel_config_t config;
static uint8_t gs_flag = 0;
static const float gsc_heater_temp_prof[] = {320.0f, 100.0f, 330.0f, 350.0f, 
                                             400.0f, 150.0f, 200.0f, 250.0f, 
                                             300.0f, 350.0f};  
static const uint8_t gsc_heater_dur_prof[] = {5, 10, 5, 5, 5, 10, 5, 5, 5, 5}; 
static const float gsc_shared_heater_dur = 140.0f; 

static void a_receive_callback(uint8_t status, bme688_parallel_data_t *data, uint8_t len)
{
    switch (status)
    {
        case BME688_STATUS_CHANNEL_DATA :
        {
            /* output */
            bme688_interface_debug_print("bme688: irq channel data.\n");
            
            /* print all */
            bme688_interface_debug_print("bme688: [%d] temperature raw is 0x%08X.\n", data->channel, data->temperature_raw);
            bme688_interface_debug_print("bme688: [%d] temperature is %0.2fC.\n", data->channel, data->temperature_c);
            bme688_interface_debug_print("bme688: [%d] pressure raw is 0x%08X.\n", data->channel, data->pressure_raw);
            bme688_interface_debug_print("bme688: [%d] pressure is %0.2fpa.\n", data->channel, data->pressure_pa);
            bme688_interface_debug_print("bme688: [%d] humidity raw is 0x%08X.\n", data->channel, data->humidity_raw);
            bme688_interface_debug_print("bme688: [%d] humidity is %0.2f%%.\n",  data->channel, data->humidity_percentage);
            bme688_interface_debug_print("bme688: [%d] adc raw is 0x%04X.\n",  data->channel, data->adc_raw);
            bme688_interface_debug_print("bme688: [%d] adc range is 0x%02X.\n",  data->channel, data->adc_range);
            bme688_interface_debug_print("bme688: [%d] resistance ohms is %0.2fohms.\n", data->channel,data->ohms);
            
            break;
        }
        case BME688_STATUS_ALL_DATA :
        {
            uint8_t i;
            
            /* output */
            bme688_interface_debug_print("bme688: irq all data.\n");
            
            /* print all */
            for (i = 0; i < len; i++)
            {
                bme688_interface_debug_print("bme688: [%d] temperature raw is 0x%08X.\n", i, data[i].temperature_raw);
                bme688_interface_debug_print("bme688: [%d] temperature is %0.2fC.\n", i, data[i].temperature_c);
                bme688_interface_debug_print("bme688: [%d] pressure raw is 0x%08X.\n", i, data[i].pressure_raw);
                bme688_interface_debug_print("bme688: [%d] pressure is %0.2fpa.\n", i, data[i].pressure_pa);
                bme688_interface_debug_print("bme688: [%d] humidity raw is 0x%08X.\n", i, data[i].humidity_raw);
                bme688_interface_debug_print("bme688: [%d] humidity is %0.2f%%.\n",  i, data[i].humidity_percentage);
                bme688_interface_debug_print("bme688: [%d] adc raw is 0x%04X.\n",  i, data[i].adc_raw);
                bme688_interface_debug_print("bme688: [%d] adc range is 0x%02X.\n",  i, data[i].adc_range);
                bme688_interface_debug_print("bme688: [%d] resistance ohms is %0.2fohms.\n", i, data[i].ohms);
            }
            
            /* flag done */
            gs_flag = 1;
            
            break;
        }
        case BME688_STATUS_SEQUENCE_LOST :
        {
            /* output */
            bme688_interface_debug_print("bme688: irq sequence lost.\n");
            
            /* parallel reset */
            (void)bme688_parallel_server_reset();
            
            /* flag error */
            gs_flag = 2;
            
            break;
        }
        default :
        {
            bme688_interface_debug_print("bme688: unknown code.\n");
            
            break;
        }
    }
}

/* parallel config */
config.heater_temp_prof = gsc_heater_temp_prof;
config.heater_dur_prof = gsc_heater_dur_prof;
config.profile_len = 10;
config.shared_heater_dur = gsc_shared_heater_dur;
res = bme688_parallel_init(interface, addr, &config, a_receive_callback);
if (res != 0)
{
    return 1;
}

...
    
/* output */
bme688_interface_debug_print("bme688: parallel sample.\n");

/* init 0 */
gs_flag = 0;

/* loop all */
while (1)
{
    /* parallel server */
    (void)bme688_parallel_server();

    /* delay */
    bme688_interface_delay_ms((uint32_t)gsc_shared_heater_dur);

    /* check flag */
    if (gs_flag != 0)
    {
        if (gs_flag == 2)
        {
            bme688_interface_debug_print("bme688: find error.\n");
            (void)bme688_parallel_deinit(); 

            return 1;
        }

        /* init 0 */
        gs_flag = 0;

        /* check times */
        if (times != 0)
        {
            times--;

            /* check times */
            if (times == 0)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    
    ...
}

...
    
/* output */
bme688_interface_debug_print("bme688: parallel done.\n");

/* deinit */
(void)bme688_parallel_deinit();

return 0;
```

### 文檔

在線文檔: [https://www.libdriver.com/docs/bme688/index.html](https://www.libdriver.com/docs/bme688/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。
