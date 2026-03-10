[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BME688

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/bme688/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der BME688 ist der erste Gassensor mit künstlicher Intelligenz (KI) und integrierten, hochlinearen und hochpräzisen Sensoren für Druck, Feuchtigkeit und Temperatur. Der Gassensor kann flüchtige organische Verbindungen (VOCs) und andere Gase wie Kohlenmonoxid und Wasserstoff im ppb-Bereich (Teile pro Milliarde) nachweisen.

LibDriver BME688 ist ein vollfunktionaler Treiber für BME688, der von LibDriver eingeführt wurde. Er bietet Funktionen zur Messung von Druck, Temperatur, Luftfeuchtigkeit und Gasen. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
    - [example gas](#example-gas)
    - [example parallel](#example-parallel)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver BME688-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver BME688 IIC, SPI.

/test enthält den Testcode des LibDriver BME688-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver BME688-Beispielcode.

/doc enthält das LibDriver BME688-Offlinedokument.

/Datenblatt enthält BME688-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC, SPI-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC, SPI-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/bme688/index.html](https://www.libdriver.com/docs/bme688/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.