[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BME688

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/bme688/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The BME688 is the first gas sensor with Artificial Intelligence (AI) and integrated high-linearity and high-accuracy pressure, humidity and temperature sensors. The gas sensor can detect Volatile Organic Compounds (VOCs) and other gases such as carbon monoxide and hydrogen in the part per billion (ppb) range.

LibDriver BME688 is a full-featured driver for BME688, launched by LibDriver.It provides pressure reading, temperature reading, humidity reading, gas reading and additional features. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example gas](#example-gas)
    - [example parallel](#example-parallel)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver BME688 source files.

/interface includes LibDriver BME688 IIC, SPI platform independent template.

/test includes LibDriver BME688 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver BME688 sample code.

/doc includes LibDriver BME688 offline document.

/datasheet includes BME688 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC, SPI platform independent template and finish your platform IIC, SPI driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

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

### Document

Online documents: [https://www.libdriver.com/docs/bme688/index.html](https://www.libdriver.com/docs/bme688/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.