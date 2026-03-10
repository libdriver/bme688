[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BME688

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/bme688/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

BME688은 인공지능(AI)을 탑재한 최초의 가스 센서로, 높은 선형성과 정확도를 갖춘 압력, 습도, 온도 센서가 통합되어 있습니다. 이 가스 센서는 휘발성 유기 화합물(VOC)뿐만 아니라 일산화탄소, 수소와 같은 기타 가스를 ppb(십억분의 일) 수준까지 감지할 수 있습니다.

LibDriver BME688은 LibDriver에서 출시한 BME688의 모든 기능을 갖춘 드라이버입니다. 압력, 온도, 습도 및 가스 측정 기능을 제공합니다. LibDriver는 MISRA 표준을 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
    - [example gas](#example-gas)
    - [example parallel](#example-parallel)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver BME688의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver BME688용 플랫폼 독립적인 IIC, SPI버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver BME688드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver BME688프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver BME688오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 BME688데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인 IIC, SPI버스 템플릿을 참조하여 지정된 플랫폼에 대한 IIC, SPI버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

### 문서

온라인 문서: [https://www.libdriver.com/docs/bme688/index.html](https://www.libdriver.com/docs/bme688/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.