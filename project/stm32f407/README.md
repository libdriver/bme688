### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

SPI Pin: SCK/MISO/MOSI/CS  PA5/PA6/PA7/PA4.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. BME688

#### 3.1 Command Instruction

1. Show bme688 chip and driver information.

   ```shell
   bme688 (-i | --information)
   ```

2. Show bme688 help.

   ```shell
   bme688 (-h | --help)
   ```

3. Show bme688 pin connections of the current board.

   ```shell
   bme688 (-p | --port)
   ```

4. Run bme688 register test.

   ```shell
   bme688 (-t reg | --test=reg) [--addr=<0 | 1>] [--interface=<iic | spi>]
   ```

5. Run bme688 read test, num means the test times, index is the gas index. 

   ```shell
   bme688 (-t read | --test=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--index=<index>] [--times=<num>]
   ```

6. Run bme688 parallel test, num means the test times. 

   ```shell
   bme688 (-t parallel | --test=parallel) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
   ```
   
7. Run bme688 read function, num means the read times. 

   ```shell
   bme688 (-e read | --example=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
   ```

8. Run bme688 gas function, num means the read times, index is the gas index, degree is the set degree, wait is the wait time in ms.

   ```shell
   bme688 (-e gas | --example=gas) [--addr=<0 | 1>] [--interface=<iic | spi>] [--index=<index>] [--degree=<degree>] [--wait=<ms>] [--times=<num>]
   ```
   
9. Run bme688 parallel function, num means the read times.

   ```shell
   bme688 (-e parallel | --example=parallel) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
   ```
   
#### 3.2 Command Example

```shell
bme688 -i

bme688: chip is Bosch BME688.
bme688: manufacturer is Bosch.
bme688: interface is IIC SPI.
bme688: driver version is 1.0.
bme688: min supply voltage is 1.7V.
bme688: max supply voltage is 3.6V.
bme688: max current is 0.85mA.
bme688: max temperature is 85.0C.
bme688: min temperature is -40.0C.
```

```shell
bme688 -p

bme688: SPI interface SCK connected to GPIOA PIN5.
bme688: SPI interface MISO connected to GPIOA PIN6.
bme688: SPI interface MOSI connected to GPIOA PIN7.
bme688: SPI interface CS connected to GPIOA PIN4.
bme688: SCL connected to GPIOB PIN8.
bme688: SDA connected to GPIOB PIN9.
```

```shell
bme688 -t reg --addr=0 --interface=iic

bme688: chip is Bosch BME688.
bme688: manufacturer is Bosch.
bme688: interface is IIC SPI.
bme688: driver version is 1.0.
bme688: min supply voltage is 1.7V.
bme688: max supply voltage is 3.6V.
bme688: max current is 0.85mA.
bme688: max temperature is 85.0C.
bme688: min temperature is -40.0C.
bme688: start register test.
bme688: bme688_set_interface/bme688_get_interface test.
bme688: set interface spi.
bme688: check interface ok.
bme688: set interface iic.
bme688: check interface ok.
bme688: bme688_set_addr_pin/bme688_get_addr_pin test.
bme688: set addr pin low.
bme688: check addr pin ok.
bme688: set addr pin high.
bme688: check addr pin ok.
bme688: bme688_set_temperature_oversampling/bme688_get_temperature_oversampling test.
bme688: set temperature oversampling skip.
bme688: check temperature oversampling ok.
bme688: set temperature oversampling x1.
bme688: check temperature oversampling ok.
bme688: set temperature oversampling x2.
bme688: check temperature oversampling ok.
bme688: set temperature oversampling x4.
bme688: check temperature oversampling ok.
bme688: set temperature oversampling x8.
bme688: check temperature oversampling ok.
bme688: set temperature oversampling x16.
bme688: check temperature oversampling ok.
bme688: bme688_set_pressure_oversampling/bme688_get_pressure_oversampling test.
bme688: set pressure oversampling skip.
bme688: check pressure oversampling ok.
bme688: set pressure oversampling x1.
bme688: check pressure oversampling ok.
bme688: set pressure oversampling x2.
bme688: check pressure oversampling ok.
bme688: set pressure oversampling x4.
bme688: check pressure oversampling ok.
bme688: set pressure oversampling x8.
bme688: check pressure oversampling ok.
bme688: set pressure oversampling x16.
bme688: check pressure oversampling ok.
bme688: bme688_set_humidity_oversampling/bme688_get_humidity_oversampling test.
bme688: set humidity oversampling skip.
bme688: check humidity oversampling ok.
bme688: set humidity oversampling x1.
bme688: check humidity oversampling ok.
bme688: set humidity oversampling x2.
bme688: check humidity oversampling ok.
bme688: set humidity oversampling x4.
bme688: check humidity oversampling ok.
bme688: set humidity oversampling x8.
bme688: check humidity oversampling ok.
bme688: set humidity oversampling x16.
bme688: check humidity oversampling ok.
bme688: bme688_set_mode/bme688_get_mode test.
bme688: set mode forced.
bme688: check mode ok.
bme688: set mode parallel.
bme688: check mode ok.
bme688: set mode sleep.
bme688: check mode ok.
bme688: bme688_set_filter/bme688_get_filter test.
bme688: set filter off.
bme688: check filter ok.
bme688: set filter coeff 1.
bme688: check filter ok.
bme688: set filter coeff 3.
bme688: check filter ok.
bme688: set filter coeff 7.
bme688: check filter ok.
bme688: set filter coeff 15.
bme688: check filter ok.
bme688: set filter coeff 31.
bme688: check filter ok.
bme688: set filter coeff 63.
bme688: check filter ok.
bme688: set filter coeff 127.
bme688: check filter ok.
bme688: bme688_set_spi_wire/bme688_get_spi_wire test.
bme688: set spi wire 3.
bme688: check spi wire ok.
bme688: set spi wire 4.
bme688: check spi wire ok.
bme688: bme688_set_spi_wire_3_data_interrupt/bme688_get_spi_wire_3_data_interrupt test.
bme688: enable spi wire 3 data interrupt.
bme688: check spi wire 3 data interrupt ok.
bme688: disable spi wire 3 data interrupt.
bme688: check spi wire 3 data interrupt ok.
bme688: set section 0.
bme688: bme688_get_new_data_status test.
bme688: new data status is true.
bme688: bme688_get_gas_measuring_status test.
bme688: gas measuring status is false.
bme688: bme688_get_measuring_status test.
bme688: get measuring status is false.
bme688: bme688_get_gas_measuring_index test.
bme688: gas measuring index is 0x0F.
bme688: bme688_get_gas_valid_status test.
bme688: gas valid status is false.
bme688: bme688_get_heater_stability_status test.
bme688: heater stability status is false.
bme688: set section 1.
bme688: bme688_get_new_data_status test.
bme688: new data status is false.
bme688: bme688_get_gas_measuring_status test.
bme688: gas measuring status is false.
bme688: bme688_get_measuring_status test.
bme688: get measuring status is false.
bme688: bme688_get_gas_measuring_index test.
bme688: gas measuring index is 0x00.
bme688: bme688_get_gas_valid_status test.
bme688: gas valid status is false.
bme688: bme688_get_heater_stability_status test.
bme688: heater stability status is false.
bme688: set section 2.
bme688: bme688_get_new_data_status test.
bme688: new data status is false.
bme688: bme688_get_gas_measuring_status test.
bme688: gas measuring status is false.
bme688: bme688_get_measuring_status test.
bme688: get measuring status is false.
bme688: bme688_get_gas_measuring_index test.
bme688: gas measuring index is 0x00.
bme688: bme688_get_gas_valid_status test.
bme688: gas valid status is false.
bme688: bme688_get_heater_stability_status test.
bme688: heater stability status is false.
bme688: bme688_set_heater_off/bme688_get_heater_off test.
bme688: disable heater off.
bme688: check heater off ok.
bme688: enable heater off.
bme688: check heater off ok.
bme688: bme688_set_run_gas/bme688_get_run_gas test.
bme688: enable run gas.
bme688: check run gas ok.
bme688: disable run gas.
bme688: check run gas ok.
bme688: bme688_set_heater_profile/bme688_get_heater_profile test.
bme688: set heater profile forced mode step 0, parallel mode no step.
bme688: check heater profile ok.
bme688: set heater profile forced mode step 1, parallel mode step 0.
bme688: check heater profile ok.
bme688: set heater profile forced mode step 2, parallel mode step 0 - 1.
bme688: check heater profile ok.
bme688: set heater profile forced mode step 3, parallel mode step 0 - 2.
bme688: check heater profile ok.
bme688: set heater profile forced mode step 4, parallel mode step 0 - 3.
bme688: check heater profile ok.
bme688: set heater profile forced mode step 5, parallel mode step 0 - 4.
bme688: check heater profile ok.
bme688: set heater profile forced mode step 6, parallel mode step 0 - 5.
bme688: check heater profile ok.
bme688: set heater profile forced mode step 7, parallel mode step 0 - 6.
bme688: check heater profile ok.
bme688: set heater profile forced mode step 8, parallel mode step 0 - 7.
bme688: check heater profile ok.
bme688: set heater profile forced mode step 9, parallel mode step 0 - 8.
bme688: check heater profile ok.
bme688: set heater profile forced mode no step, parallel mode step 0 - 9.
bme688: check heater profile ok.
bme688: bme688_set_gas_wait_shared/bme688_get_gas_wait_shared test.
bme688: set gas wait shared 0xEE.
bme688: check gas wait shared ok.
bme688: bme688_set_idac_heater/bme688_get_idac_heater test.
bme688: set index 0 idac heater 0xDE.
bme688: check idac heater ok.
bme688: set index 1 idac heater 0xB8.
bme688: check idac heater ok.
bme688: set index 2 idac heater 0x5F.
bme688: check idac heater ok.
bme688: set index 3 idac heater 0xF3.
bme688: check idac heater ok.
bme688: set index 4 idac heater 0x65.
bme688: check idac heater ok.
bme688: set index 5 idac heater 0x3C.
bme688: check idac heater ok.
bme688: set index 6 idac heater 0x0C.
bme688: check idac heater ok.
bme688: set index 7 idac heater 0x84.
bme688: check idac heater ok.
bme688: set index 8 idac heater 0xB8.
bme688: check idac heater ok.
bme688: set index 9 idac heater 0xD5.
bme688: check idac heater ok.
bme688: bme688_set_resistance_heater/bme688_get_resistance_heater test.
bme688: set index 0 resistance heater 0x16.
bme688: check resistance heater ok.
bme688: set index 1 resistance heater 0x09.
bme688: check resistance heater ok.
bme688: set index 2 resistance heater 0x03.
bme688: check resistance heater ok.
bme688: set index 3 resistance heater 0xED.
bme688: check resistance heater ok.
bme688: set index 4 resistance heater 0xDF.
bme688: check resistance heater ok.
bme688: set index 5 resistance heater 0xBF.
bme688: check resistance heater ok.
bme688: set index 6 resistance heater 0xFB.
bme688: check resistance heater ok.
bme688: set index 7 resistance heater 0x90.
bme688: check resistance heater ok.
bme688: set index 8 resistance heater 0xB2.
bme688: check resistance heater ok.
bme688: set index 9 resistance heater 0x1E.
bme688: check resistance heater ok.
bme688: bme688_set_gas_wait/bme688_get_gas_wait test.
bme688: set index 0 gas wait 0xBB.
bme688: check gas wait ok.
bme688: set index 1 gas wait 0xFA.
bme688: check gas wait ok.
bme688: set index 2 gas wait 0xC8.
bme688: check gas wait ok.
bme688: set index 3 gas wait 0x2C.
bme688: check gas wait ok.
bme688: set index 4 gas wait 0xF9.
bme688: check gas wait ok.
bme688: set index 5 gas wait 0xA7.
bme688: check gas wait ok.
bme688: set index 6 gas wait 0xCF.
bme688: check gas wait ok.
bme688: set index 7 gas wait 0x2B.
bme688: check gas wait ok.
bme688: set index 8 gas wait 0xCA.
bme688: check gas wait ok.
bme688: set index 9 gas wait 0xFA.
bme688: check gas wait ok.
bme688: bme688_resistance_heater_convert_to_register test.
bme688: 67.68C convert to register 0x2F.
bme688: bme688_gas_wait_convert_to_register test.
bme688: 91ms convert to register 0x56.
bme688: bme688_idac_heater_convert_to_register/bme688_idac_heater_convert_to_data test.
bme688: idac heater ma before is 7.60mA.
bme688: idac heater reg is 0x76.
bme688: idac heater ma after is 7.00mA.
bme688: bme688_gas_wait_shared_convert_to_register test.
bme688: 108ms convert to register 0x0E.
bme688: bme688_soft_reset test.
bme688: check soft reset ok.
bme688: finish register test.
```

```shell
bme688 -t read --addr=0 --interface=iic --times=3

bme688: chip is Bosch BME688.
bme688: manufacturer is Bosch.
bme688: interface is IIC SPI.
bme688: driver version is 1.0.
bme688: min supply voltage is 1.7V.
bme688: max supply voltage is 3.6V.
bme688: max current is 0.85mA.
bme688: max temperature is 85.0C.
bme688: min temperature is -40.0C.
bme688: start read test.
bme688: temperature is 25.53C.
bme688: pressure is 102389.73pa.
bme688: humidity is 23.11%.
bme688: gas index is 0.
bme688: gas resistance is 144591.92ohms.
bme688: temperature is 25.54C.
bme688: pressure is 102389.65pa.
bme688: humidity is 23.09%.
bme688: gas index is 0.
bme688: gas resistance is 45133.99ohms.
bme688: temperature is 25.55C.
bme688: pressure is 102389.66pa.
bme688: humidity is 23.00%.
bme688: gas index is 0.
bme688: gas resistance is 27450.14ohms.
bme688: finish read test.
```

```shell
bme688 -t parallel --addr=0 --interface=iic --times=3

bme688: chip is Bosch BME688.
bme688: manufacturer is Bosch.
bme688: interface is IIC SPI.
bme688: driver version is 1.0.
bme688: min supply voltage is 1.7V.
bme688: max supply voltage is 3.6V.
bme688: max current is 0.85mA.
bme688: max temperature is 85.0C.
bme688: min temperature is -40.0C.
bme688: start parallel test.
bme688: irq channel data.
bme688: [0] temperature raw is 0x0007B462.
bme688: [0] temperature is 27.38C.
bme688: [0] pressure raw is 0x0004A9B4.
bme688: [0] pressure is 102158.75pa.
bme688: [0] humidity raw is 0x00003BC4.
bme688: [0] humidity is 22.99%.
bme688: [0] adc raw is 0x0275.
bme688: [0] adc range is 0x0C.
bme688: [0] resistance ohms is 14391.72ohms.
bme688: irq channel data.
bme688: [1] temperature raw is 0x0007C234.
bme688: [1] temperature is 28.51C.
bme688: [1] pressure raw is 0x0004ADDF.
bme688: [1] pressure is 102165.54pa.
bme688: [1] humidity raw is 0x00003B52.
bme688: [1] humidity is 22.46%.
bme688: [1] adc raw is 0x013F.
bme688: [1] adc range is 0x08.
bme688: [1] resistance ohms is 291157.25ohms.
bme688: irq channel data.
bme688: [2] temperature raw is 0x0007C8A3.
bme688: [2] temperature is 29.04C.
bme688: [2] pressure raw is 0x0004AFD8.
bme688: [2] pressure is 102167.08pa.
bme688: [2] humidity raw is 0x00003B1E.
bme688: [2] humidity is 22.22%.
bme688: [2] adc raw is 0x035E.
bme688: [2] adc range is 0x0B.
bme688: [2] resistance ohms is 24873.69ohms.
bme688: irq channel data.
bme688: [3] temperature raw is 0x0007D065.
bme688: [3] temperature is 29.68C.
bme688: [3] pressure raw is 0x0004B233.
bme688: [3] pressure is 102169.81pa.
bme688: [3] humidity raw is 0x00003AD9.
bme688: [3] humidity is 21.89%.
bme688: [3] adc raw is 0x00ED.
bme688: [3] adc range is 0x0B.
bme688: [3] resistance ohms is 39131.77ohms.
bme688: irq channel data.
bme688: [4] temperature raw is 0x0007D63E.
bme688: [4] temperature is 30.16C.
bme688: [4] pressure raw is 0x0004B3FA.
bme688: [4] pressure is 102171.66pa.
bme688: [4] humidity raw is 0x00003A8F.
bme688: [4] humidity is 21.53%.
bme688: [4] adc raw is 0x02E8.
bme688: [4] adc range is 0x0A.
bme688: [4] resistance ohms is 53422.37ohms.
bme688: irq channel data.
bme688: [5] temperature raw is 0x0007DAF7.
bme688: [5] temperature is 30.55C.
bme688: [5] pressure raw is 0x0004B562.
bme688: [5] pressure is 102174.36pa.
bme688: [5] humidity raw is 0x00003A13.
bme688: [5] humidity is 20.90%.
bme688: [5] adc raw is 0x0069.
bme688: [5] adc range is 0x07.
bme688: [5] resistance ohms is 712347.81ohms.
bme688: irq channel data.
bme688: [6] temperature raw is 0x0007DC16.
bme688: [6] temperature is 30.64C.
bme688: [6] pressure raw is 0x0004B5BB.
bme688: [6] pressure is 102174.40pa.
bme688: [6] humidity raw is 0x000039E7.
bme688: [6] humidity is 20.67%.
bme688: [6] adc raw is 0x003F.
bme688: [6] adc range is 0x09.
bme688: [6] resistance ohms is 186249.55ohms.
bme688: irq channel data.
bme688: [7] temperature raw is 0x0007DDAF.
bme688: [7] temperature is 30.77C.
bme688: [7] pressure raw is 0x0004B637.
bme688: [7] pressure is 102174.91pa.
bme688: [7] humidity raw is 0x000039C1.
bme688: [7] humidity is 20.48%.
bme688: [7] adc raw is 0x0107.
bme688: [7] adc range is 0x0A.
bme688: [7] resistance ohms is 76440.73ohms.
bme688: irq channel data.
bme688: [8] temperature raw is 0x0007DFA5.
bme688: [8] temperature is 30.93C.
bme688: [8] pressure raw is 0x0004B6D3.
bme688: [8] pressure is 102174.88pa.
bme688: [8] humidity raw is 0x0000399E.
bme688: [8] humidity is 20.30%.
bme688: [8] adc raw is 0x032C.
bme688: [8] adc range is 0x0A.
bme688: [8] resistance ohms is 51240.99ohms.
bme688: irq channel data.
bme688: [9] temperature raw is 0x0007E1CA.
bme688: [9] temperature is 31.10C.
bme688: [9] pressure raw is 0x0004B77B.
bme688: [9] pressure is 102175.29pa.
bme688: [9] humidity raw is 0x0000397D.
bme688: [9] humidity is 20.14%.
bme688: [9] adc raw is 0x02CF.
bme688: [9] adc range is 0x0A.
bme688: [9] resistance ohms is 54271.78ohms.
bme688: irq all data.
bme688: [0] temperature raw is 0x0007B462.
bme688: [0] temperature is 27.38C.
bme688: [0] pressure raw is 0x0004A9B4.
bme688: [0] pressure is 102158.75pa.
bme688: [0] humidity raw is 0x00003BC4.
bme688: [0] humidity is 22.99%.
bme688: [0] adc raw is 0x0275.
bme688: [0] adc range is 0x0C.
bme688: [0] resistance ohms is 14391.72ohms.
bme688: [1] temperature raw is 0x0007C234.
bme688: [1] temperature is 28.51C.
bme688: [1] pressure raw is 0x0004ADDF.
bme688: [1] pressure is 102165.54pa.
bme688: [1] humidity raw is 0x00003B52.
bme688: [1] humidity is 22.46%.
bme688: [1] adc raw is 0x013F.
bme688: [1] adc range is 0x08.
bme688: [1] resistance ohms is 291157.25ohms.
bme688: [2] temperature raw is 0x0007C8A3.
bme688: [2] temperature is 29.04C.
bme688: [2] pressure raw is 0x0004AFD8.
bme688: [2] pressure is 102167.08pa.
bme688: [2] humidity raw is 0x00003B1E.
bme688: [2] humidity is 22.22%.
bme688: [2] adc raw is 0x035E.
bme688: [2] adc range is 0x0B.
bme688: [2] resistance ohms is 24873.69ohms.
bme688: [3] temperature raw is 0x0007D065.
bme688: [3] temperature is 29.68C.
bme688: [3] pressure raw is 0x0004B233.
bme688: [3] pressure is 102169.81pa.
bme688: [3] humidity raw is 0x00003AD9.
bme688: [3] humidity is 21.89%.
bme688: [3] adc raw is 0x00ED.
bme688: [3] adc range is 0x0B.
bme688: [3] resistance ohms is 39131.77ohms.
bme688: [4] temperature raw is 0x0007D63E.
bme688: [4] temperature is 30.16C.
bme688: [4] pressure raw is 0x0004B3FA.
bme688: [4] pressure is 102171.66pa.
bme688: [4] humidity raw is 0x00003A8F.
bme688: [4] humidity is 21.53%.
bme688: [4] adc raw is 0x02E8.
bme688: [4] adc range is 0x0A.
bme688: [4] resistance ohms is 53422.37ohms.
bme688: [5] temperature raw is 0x0007DAF7.
bme688: [5] temperature is 30.55C.
bme688: [5] pressure raw is 0x0004B562.
bme688: [5] pressure is 102174.36pa.
bme688: [5] humidity raw is 0x00003A13.
bme688: [5] humidity is 20.90%.
bme688: [5] adc raw is 0x0069.
bme688: [5] adc range is 0x07.
bme688: [5] resistance ohms is 712347.81ohms.
bme688: [6] temperature raw is 0x0007DC16.
bme688: [6] temperature is 30.64C.
bme688: [6] pressure raw is 0x0004B5BB.
bme688: [6] pressure is 102174.40pa.
bme688: [6] humidity raw is 0x000039E7.
bme688: [6] humidity is 20.67%.
bme688: [6] adc raw is 0x003F.
bme688: [6] adc range is 0x09.
bme688: [6] resistance ohms is 186249.55ohms.
bme688: [7] temperature raw is 0x0007DDAF.
bme688: [7] temperature is 30.77C.
bme688: [7] pressure raw is 0x0004B637.
bme688: [7] pressure is 102174.91pa.
bme688: [7] humidity raw is 0x000039C1.
bme688: [7] humidity is 20.48%.
bme688: [7] adc raw is 0x0107.
bme688: [7] adc range is 0x0A.
bme688: [7] resistance ohms is 76440.73ohms.
bme688: [8] temperature raw is 0x0007DFA5.
bme688: [8] temperature is 30.93C.
bme688: [8] pressure raw is 0x0004B6D3.
bme688: [8] pressure is 102174.88pa.
bme688: [8] humidity raw is 0x0000399E.
bme688: [8] humidity is 20.30%.
bme688: [8] adc raw is 0x032C.
bme688: [8] adc range is 0x0A.
bme688: [8] resistance ohms is 51240.99ohms.
bme688: [9] temperature raw is 0x0007E1CA.
bme688: [9] temperature is 31.10C.
bme688: [9] pressure raw is 0x0004B77B.
bme688: [9] pressure is 102175.29pa.
bme688: [9] humidity raw is 0x0000397D.
bme688: [9] humidity is 20.14%.
bme688: [9] adc raw is 0x02CF.
bme688: [9] adc range is 0x0A.
bme688: [9] resistance ohms is 54271.78ohms.
bme688: irq channel data.
bme688: [0] temperature raw is 0x0007E4AA.
bme688: [0] temperature is 31.34C.
bme688: [0] pressure raw is 0x0004B85D.
bme688: [0] pressure is 102175.65pa.
bme688: [0] humidity raw is 0x00003956.
bme688: [0] humidity is 19.95%.
bme688: [0] adc raw is 0x0261.
bme688: [0] adc range is 0x0A.
bme688: [0] resistance ohms is 58354.23ohms.
bme688: irq channel data.
bme688: [1] temperature raw is 0x0007E246.
bme688: [1] temperature is 31.14C.
bme688: [1] pressure raw is 0x0004B79A.
bme688: [1] pressure is 102176.55pa.
bme688: [1] humidity raw is 0x00003913.
bme688: [1] humidity is 19.59%.
bme688: [1] adc raw is 0x0202.
bme688: [1] adc range is 0x05.
bme688: [1] resistance ohms is 1997074.62ohms.
bme688: irq channel data.
bme688: [2] temperature raw is 0x0007E337.
bme688: [2] temperature is 31.22C.
bme688: [2] pressure raw is 0x0004B7E9.
bme688: [2] pressure is 102175.81pa.
bme688: [2] humidity raw is 0x0000390F.
bme688: [2] humidity is 19.57%.
bme688: [2] adc raw is 0x02D4.
bme688: [2] adc range is 0x0A.
bme688: [2] resistance ohms is 54099.75ohms.
bme688: irq channel data.
bme688: [3] temperature raw is 0x0007E5E2.
bme688: [3] temperature is 31.44C.
bme688: [3] pressure raw is 0x0004B8BB.
bme688: [3] pressure is 102176.12pa.
bme688: [3] humidity raw is 0x000038FF.
bme688: [3] humidity is 19.50%.
bme688: [3] adc raw is 0x0280.
bme688: [3] adc range is 0x0A.
bme688: [3] resistance ohms is 57142.86ohms.
bme688: irq channel data.
bme688: [4] temperature raw is 0x0007E8B0.
bme688: [4] temperature is 31.67C.
bme688: [4] pressure raw is 0x0004B998.
bme688: [4] pressure is 102176.37pa.
bme688: [4] humidity raw is 0x000038E5.
bme688: [4] humidity is 19.38%.
bme688: [4] adc raw is 0x0213.
bme688: [4] adc range is 0x0A.
bme688: [4] resistance ohms is 61642.19ohms.
bme688: irq channel data.
bme688: [5] temperature raw is 0x0007E820.
bme688: [5] temperature is 31.62C.
bme688: [5] pressure raw is 0x0004B965.
bme688: [5] pressure is 102177.47pa.
bme688: [5] humidity raw is 0x000038B4.
bme688: [5] humidity is 19.12%.
bme688: [5] adc raw is 0x02EC.
bme688: [5] adc range is 0x06.
bme688: [5] resistance ohms is 852622.81ohms.
bme688: irq channel data.
bme688: [6] temperature raw is 0x0007E7CB.
bme688: [6] temperature is 31.60C.
bme688: [6] pressure raw is 0x0004B94C.
bme688: [6] pressure is 102177.23pa.
bme688: [6] humidity raw is 0x000038AB.
bme688: [6] humidity is 19.07%.
bme688: [6] adc raw is 0x02A9.
bme688: [6] adc range is 0x08.
bme688: [6] resistance ohms is 222463.61ohms.
bme688: irq channel data.
bme688: [7] temperature raw is 0x0007E87B.
bme688: [7] temperature is 31.65C.
bme688: [7] pressure raw is 0x0004B983.
bme688: [7] pressure is 102177.16pa.
bme688: [7] humidity raw is 0x000038A1.
bme688: [7] humidity is 19.02%.
bme688: [7] adc raw is 0x0084.
bme688: [7] adc range is 0x0A.
bme688: [7] resistance ohms is 86603.52ohms.
bme688: irq channel data.
bme688: [8] temperature raw is 0x0007E9E1.
bme688: [8] temperature is 31.77C.
bme688: [8] pressure raw is 0x0004B9F1.
bme688: [8] pressure is 102177.30pa.
bme688: [8] humidity raw is 0x00003897.
bme688: [8] humidity is 18.97%.
bme688: [8] adc raw is 0x0296.
bme688: [8] adc range is 0x0A.
bme688: [8] resistance ohms is 56313.24ohms.
bme688: irq channel data.
bme688: [9] temperature raw is 0x0007EBB4.
bme688: [9] temperature is 31.92C.
bme688: [9] pressure raw is 0x0004BA80.
bme688: [9] pressure is 102177.57pa.
bme688: [9] humidity raw is 0x00003887.
bme688: [9] humidity is 18.90%.
bme688: [9] adc raw is 0x0282.
bme688: [9] adc range is 0x0A.
bme688: [9] resistance ohms is 57066.43ohms.
bme688: irq all data.
bme688: [0] temperature raw is 0x0007E4AA.
bme688: [0] temperature is 31.34C.
bme688: [0] pressure raw is 0x0004B85D.
bme688: [0] pressure is 102175.65pa.
bme688: [0] humidity raw is 0x00003956.
bme688: [0] humidity is 19.95%.
bme688: [0] adc raw is 0x0261.
bme688: [0] adc range is 0x0A.
bme688: [0] resistance ohms is 58354.23ohms.
bme688: [1] temperature raw is 0x0007E246.
bme688: [1] temperature is 31.14C.
bme688: [1] pressure raw is 0x0004B79A.
bme688: [1] pressure is 102176.55pa.
bme688: [1] humidity raw is 0x00003913.
bme688: [1] humidity is 19.59%.
bme688: [1] adc raw is 0x0202.
bme688: [1] adc range is 0x05.
bme688: [1] resistance ohms is 1997074.62ohms.
bme688: [2] temperature raw is 0x0007E337.
bme688: [2] temperature is 31.22C.
bme688: [2] pressure raw is 0x0004B7E9.
bme688: [2] pressure is 102175.81pa.
bme688: [2] humidity raw is 0x0000390F.
bme688: [2] humidity is 19.57%.
bme688: [2] adc raw is 0x02D4.
bme688: [2] adc range is 0x0A.
bme688: [2] resistance ohms is 54099.75ohms.
bme688: [3] temperature raw is 0x0007E5E2.
bme688: [3] temperature is 31.44C.
bme688: [3] pressure raw is 0x0004B8BB.
bme688: [3] pressure is 102176.12pa.
bme688: [3] humidity raw is 0x000038FF.
bme688: [3] humidity is 19.50%.
bme688: [3] adc raw is 0x0280.
bme688: [3] adc range is 0x0A.
bme688: [3] resistance ohms is 57142.86ohms.
bme688: [4] temperature raw is 0x0007E8B0.
bme688: [4] temperature is 31.67C.
bme688: [4] pressure raw is 0x0004B998.
bme688: [4] pressure is 102176.37pa.
bme688: [4] humidity raw is 0x000038E5.
bme688: [4] humidity is 19.38%.
bme688: [4] adc raw is 0x0213.
bme688: [4] adc range is 0x0A.
bme688: [4] resistance ohms is 61642.19ohms.
bme688: [5] temperature raw is 0x0007E820.
bme688: [5] temperature is 31.62C.
bme688: [5] pressure raw is 0x0004B965.
bme688: [5] pressure is 102177.47pa.
bme688: [5] humidity raw is 0x000038B4.
bme688: [5] humidity is 19.12%.
bme688: [5] adc raw is 0x02EC.
bme688: [5] adc range is 0x06.
bme688: [5] resistance ohms is 852622.81ohms.
bme688: [6] temperature raw is 0x0007E7CB.
bme688: [6] temperature is 31.60C.
bme688: [6] pressure raw is 0x0004B94C.
bme688: [6] pressure is 102177.23pa.
bme688: [6] humidity raw is 0x000038AB.
bme688: [6] humidity is 19.07%.
bme688: [6] adc raw is 0x02A9.
bme688: [6] adc range is 0x08.
bme688: [6] resistance ohms is 222463.61ohms.
bme688: [7] temperature raw is 0x0007E87B.
bme688: [7] temperature is 31.65C.
bme688: [7] pressure raw is 0x0004B983.
bme688: [7] pressure is 102177.16pa.
bme688: [7] humidity raw is 0x000038A1.
bme688: [7] humidity is 19.02%.
bme688: [7] adc raw is 0x0084.
bme688: [7] adc range is 0x0A.
bme688: [7] resistance ohms is 86603.52ohms.
bme688: [8] temperature raw is 0x0007E9E1.
bme688: [8] temperature is 31.77C.
bme688: [8] pressure raw is 0x0004B9F1.
bme688: [8] pressure is 102177.30pa.
bme688: [8] humidity raw is 0x00003897.
bme688: [8] humidity is 18.97%.
bme688: [8] adc raw is 0x0296.
bme688: [8] adc range is 0x0A.
bme688: [8] resistance ohms is 56313.24ohms.
bme688: [9] temperature raw is 0x0007EBB4.
bme688: [9] temperature is 31.92C.
bme688: [9] pressure raw is 0x0004BA80.
bme688: [9] pressure is 102177.57pa.
bme688: [9] humidity raw is 0x00003887.
bme688: [9] humidity is 18.90%.
bme688: [9] adc raw is 0x0282.
bme688: [9] adc range is 0x0A.
bme688: [9] resistance ohms is 57066.43ohms.
bme688: irq channel data.
bme688: [0] temperature raw is 0x0007ED62.
bme688: [0] temperature is 32.06C.
bme688: [0] pressure raw is 0x0004BB00.
bme688: [0] pressure is 102178.44pa.
bme688: [0] humidity raw is 0x00003877.
bme688: [0] humidity is 18.82%.
bme688: [0] adc raw is 0x024E.
bme688: [0] adc range is 0x0A.
bme688: [0] resistance ohms is 59122.40ohms.
bme688: irq channel data.
bme688: [1] temperature raw is 0x0007E8E4.
bme688: [1] temperature is 31.69C.
bme688: [1] pressure raw is 0x0004B99D.
bme688: [1] pressure is 102178.27pa.
bme688: [1] humidity raw is 0x0000385A.
bme688: [1] humidity is 18.65%.
bme688: [1] adc raw is 0x020B.
bme688: [1] adc range is 0x05.
bme688: [1] resistance ohms is 1984015.50ohms.
bme688: irq channel data.
bme688: [2] temperature raw is 0x0007E919.
bme688: [2] temperature is 31.70C.
bme688: [2] pressure raw is 0x0004B9B1.
bme688: [2] pressure is 102177.66pa.
bme688: [2] humidity raw is 0x0000386A.
bme688: [2] humidity is 18.73%.
bme688: [2] adc raw is 0x02A4.
bme688: [2] adc range is 0x0A.
bme688: [2] resistance ohms is 55797.73ohms.
bme688: irq channel data.
bme688: [3] temperature raw is 0x0007EB31.
bme688: [3] temperature is 31.88C.
bme688: [3] pressure raw is 0x0004BA54.
bme688: [3] pressure is 102178.16pa.
bme688: [3] humidity raw is 0x00003863.
bme688: [3] humidity is 18.71%.
bme688: [3] adc raw is 0x0272.
bme688: [3] adc range is 0x0A.
bme688: [3] resistance ohms is 57683.64ohms.
bme688: irq channel data.
bme688: [4] temperature raw is 0x0007ED86.
bme688: [4] temperature is 32.07C.
bme688: [4] pressure raw is 0x0004BB09.
bme688: [4] pressure is 102178.80pa.
bme688: [4] humidity raw is 0x0000385B.
bme688: [4] humidity is 18.68%.
bme688: [4] adc raw is 0x01E6.
bme688: [4] adc range is 0x0A.
bme688: [4] resistance ohms is 63713.29ohms.
bme688: irq channel data.
bme688: [5] temperature raw is 0x0007EC44.
bme688: [5] temperature is 31.96C.
bme688: [5] pressure raw is 0x0004BAA5.
bme688: [5] pressure is 102178.87pa.
bme688: [5] humidity raw is 0x00003842.
bme688: [5] humidity is 18.54%.
bme688: [5] adc raw is 0x02C3.
bme688: [5] adc range is 0x06.
bme688: [5] resistance ohms is 875026.69ohms.
bme688: irq channel data.
bme688: [6] temperature raw is 0x0007EBB0.
bme688: [6] temperature is 31.92C.
bme688: [6] pressure raw is 0x0004BA7B.
bme688: [6] pressure is 102178.21pa.
bme688: [6] humidity raw is 0x00003843.
bme688: [6] humidity is 18.54%.
bme688: [6] adc raw is 0x029B.
bme688: [6] adc range is 0x08.
bme688: [6] resistance ohms is 224512.17ohms.
bme688: irq channel data.
bme688: [7] temperature raw is 0x0007EC27.
bme688: [7] temperature is 31.95C.
bme688: [7] pressure raw is 0x0004BAA1.
bme688: [7] pressure is 102178.02pa.
bme688: [7] humidity raw is 0x00003842.
bme688: [7] humidity is 18.54%.
bme688: [7] adc raw is 0x0073.
bme688: [7] adc range is 0x0A.
bme688: [7] resistance ohms is 88123.92ohms.
bme688: irq channel data.
bme688: [8] temperature raw is 0x0007ED63.
bme688: [8] temperature is 32.06C.
bme688: [8] pressure raw is 0x0004BB00.
bme688: [8] pressure is 102178.49pa.
bme688: [8] humidity raw is 0x00003842.
bme688: [8] humidity is 18.55%.
bme688: [8] adc raw is 0x0285.
bme688: [8] adc range is 0x0A.
bme688: [8] resistance ohms is 56952.17ohms.
bme688: irq channel data.
bme688: [9] temperature raw is 0x0007EF0C.
bme688: [9] temperature is 32.19C.
bme688: [9] pressure raw is 0x0004BB80.
bme688: [9] pressure is 102179.09pa.
bme688: [9] humidity raw is 0x0000383D.
bme688: [9] humidity is 18.53%.
bme688: [9] adc raw is 0x0284.
bme688: [9] adc range is 0x0A.
bme688: [9] resistance ohms is 56990.20ohms.
bme688: irq all data.
bme688: [0] temperature raw is 0x0007ED62.
bme688: [0] temperature is 32.06C.
bme688: [0] pressure raw is 0x0004BB00.
bme688: [0] pressure is 102178.44pa.
bme688: [0] humidity raw is 0x00003877.
bme688: [0] humidity is 18.82%.
bme688: [0] adc raw is 0x024E.
bme688: [0] adc range is 0x0A.
bme688: [0] resistance ohms is 59122.40ohms.
bme688: [1] temperature raw is 0x0007E8E4.
bme688: [1] temperature is 31.69C.
bme688: [1] pressure raw is 0x0004B99D.
bme688: [1] pressure is 102178.27pa.
bme688: [1] humidity raw is 0x0000385A.
bme688: [1] humidity is 18.65%.
bme688: [1] adc raw is 0x020B.
bme688: [1] adc range is 0x05.
bme688: [1] resistance ohms is 1984015.50ohms.
bme688: [2] temperature raw is 0x0007E919.
bme688: [2] temperature is 31.70C.
bme688: [2] pressure raw is 0x0004B9B1.
bme688: [2] pressure is 102177.66pa.
bme688: [2] humidity raw is 0x0000386A.
bme688: [2] humidity is 18.73%.
bme688: [2] adc raw is 0x02A4.
bme688: [2] adc range is 0x0A.
bme688: [2] resistance ohms is 55797.73ohms.
bme688: [3] temperature raw is 0x0007EB31.
bme688: [3] temperature is 31.88C.
bme688: [3] pressure raw is 0x0004BA54.
bme688: [3] pressure is 102178.16pa.
bme688: [3] humidity raw is 0x00003863.
bme688: [3] humidity is 18.71%.
bme688: [3] adc raw is 0x0272.
bme688: [3] adc range is 0x0A.
bme688: [3] resistance ohms is 57683.64ohms.
bme688: [4] temperature raw is 0x0007ED86.
bme688: [4] temperature is 32.07C.
bme688: [4] pressure raw is 0x0004BB09.
bme688: [4] pressure is 102178.80pa.
bme688: [4] humidity raw is 0x0000385B.
bme688: [4] humidity is 18.68%.
bme688: [4] adc raw is 0x01E6.
bme688: [4] adc range is 0x0A.
bme688: [4] resistance ohms is 63713.29ohms.
bme688: [5] temperature raw is 0x0007EC44.
bme688: [5] temperature is 31.96C.
bme688: [5] pressure raw is 0x0004BAA5.
bme688: [5] pressure is 102178.87pa.
bme688: [5] humidity raw is 0x00003842.
bme688: [5] humidity is 18.54%.
bme688: [5] adc raw is 0x02C3.
bme688: [5] adc range is 0x06.
bme688: [5] resistance ohms is 875026.69ohms.
bme688: [6] temperature raw is 0x0007EBB0.
bme688: [6] temperature is 31.92C.
bme688: [6] pressure raw is 0x0004BA7B.
bme688: [6] pressure is 102178.21pa.
bme688: [6] humidity raw is 0x00003843.
bme688: [6] humidity is 18.54%.
bme688: [6] adc raw is 0x029B.
bme688: [6] adc range is 0x08.
bme688: [6] resistance ohms is 224512.17ohms.
bme688: [7] temperature raw is 0x0007EC27.
bme688: [7] temperature is 31.95C.
bme688: [7] pressure raw is 0x0004BAA1.
bme688: [7] pressure is 102178.02pa.
bme688: [7] humidity raw is 0x00003842.
bme688: [7] humidity is 18.54%.
bme688: [7] adc raw is 0x0073.
bme688: [7] adc range is 0x0A.
bme688: [7] resistance ohms is 88123.92ohms.
bme688: [8] temperature raw is 0x0007ED63.
bme688: [8] temperature is 32.06C.
bme688: [8] pressure raw is 0x0004BB00.
bme688: [8] pressure is 102178.49pa.
bme688: [8] humidity raw is 0x00003842.
bme688: [8] humidity is 18.55%.
bme688: [8] adc raw is 0x0285.
bme688: [8] adc range is 0x0A.
bme688: [8] resistance ohms is 56952.17ohms.
bme688: [9] temperature raw is 0x0007EF0C.
bme688: [9] temperature is 32.19C.
bme688: [9] pressure raw is 0x0004BB80.
bme688: [9] pressure is 102179.09pa.
bme688: [9] humidity raw is 0x0000383D.
bme688: [9] humidity is 18.53%.
bme688: [9] adc raw is 0x0284.
bme688: [9] adc range is 0x0A.
bme688: [9] resistance ohms is 56990.20ohms.
bme688: finish parallel test.
```

```shell
bme688 -e read --addr=0 --interface=iic --index=0 --times=3

bme688: 1/3.
bme688: temperature is 26.20C.
bme688: pressure is 102401.77Pa.
bme688: humidity is 20.71%.
bme688: 2/3.
bme688: temperature is 26.20C.
bme688: pressure is 102401.55Pa.
bme688: humidity is 20.85%.
bme688: 3/3.
bme688: temperature is 26.20C.
bme688: pressure is 102401.52Pa.
bme688: humidity is 20.97%.
```

```shell
bme688 -e gas --addr=0 --interface=iic --index=0 --degree=200.0 --wait=150 --times=3

bme688: 1/3.
bme688: temperature is 25.93C.
bme688: pressure is 102406.48Pa.
bme688: humidity is 22.01%.
bme688: gas index is 0.
bme688: degree celsius is 200.0C.
bme688: gas wait is 150 ms.
bme688: gas resistance is 154263.33ohms.
bme688: 2/3.
bme688: temperature is 25.94C.
bme688: pressure is 102406.54Pa.
bme688: humidity is 22.04%.
bme688: gas index is 0.
bme688: degree celsius is 200.0C.
bme688: gas wait is 150 ms.
bme688: gas resistance is 96622.01ohms.
bme688: 3/3.
bme688: temperature is 25.95C.
bme688: pressure is 102406.45Pa.
bme688: humidity is 22.02%.
bme688: gas index is 0.
bme688: degree celsius is 200.0C.
bme688: gas wait is 150 ms.
bme688: gas resistance is 79950.03ohms.
```

```shell
bme688 -e parallel --addr=0 --interface=iic --times=3

bme688: parallel sample.
bme688: irq channel data.
bme688: [0] temperature raw is 0x0007B646.
bme688: [0] temperature is 27.54C.
bme688: [0] pressure raw is 0x0004AA3F.
bme688: [0] pressure is 102160.91pa.
bme688: [0] humidity raw is 0x00003C4B.
bme688: [0] humidity is 23.72%.
bme688: [0] adc raw is 0x01C4.
bme688: [0] adc range is 0x0C.
bme688: [0] resistance ohms is 16343.21ohms.
bme688: irq channel data.
bme688: [1] temperature raw is 0x0007C412.
bme688: [1] temperature is 28.67C.
bme688: [1] pressure raw is 0x0004AE68.
bme688: [1] pressure is 102167.62pa.
bme688: [1] humidity raw is 0x00003C20.
bme688: [1] humidity is 23.57%.
bme688: [1] adc raw is 0x0093.
bme688: [1] adc range is 0x08.
bme688: [1] resistance ohms is 341219.59ohms.
bme688: irq channel data.
bme688: [2] temperature raw is 0x0007CA80.
bme688: [2] temperature is 29.19C.
bme688: [2] pressure raw is 0x0004B05D.
bme688: [2] pressure is 102169.77pa.
bme688: [2] humidity raw is 0x00003BFC.
bme688: [2] humidity is 23.42%.
bme688: [2] adc raw is 0x02C0.
bme688: [2] adc range is 0x0B.
bme688: [2] resistance ohms is 27397.26ohms.
bme688: irq channel data.
bme688: [3] temperature raw is 0x0007D23E.
bme688: [3] temperature is 29.83C.
bme688: [3] pressure raw is 0x0004B2B9.
bme688: [3] pressure is 102172.08pa.
bme688: [3] humidity raw is 0x00003BBA.
bme688: [3] humidity is 23.11%.
bme688: [3] adc raw is 0x009A.
bme688: [3] adc range is 0x0B.
bme688: [3] resistance ohms is 42356.05ohms.
bme688: irq channel data.
bme688: [4] temperature raw is 0x0007D813.
bme688: [4] temperature is 30.31C.
bme688: [4] pressure raw is 0x0004B47E.
bme688: [4] pressure is 102174.03pa.
bme688: [4] humidity raw is 0x00003B71.
bme688: [4] humidity is 22.75%.
bme688: [4] adc raw is 0x02AD.
bme688: [4] adc range is 0x0A.
bme688: [4] resistance ohms is 55471.29ohms.
bme688: irq channel data.
bme688: [5] temperature raw is 0x0007DCC5.
bme688: [5] temperature is 30.69C.
bme688: [5] pressure raw is 0x0004B5E8.
bme688: [5] pressure is 102175.98pa.
bme688: [5] humidity raw is 0x00003ADB.
bme688: [5] humidity is 21.97%.
bme688: [5] adc raw is 0x0044.
bme688: [5] adc range is 0x07.
bme688: [5] resistance ohms is 740955.12ohms.
bme688: irq channel data.
bme688: [6] temperature raw is 0x0007DDE4.
bme688: [6] temperature is 30.79C.
bme688: [6] pressure raw is 0x0004B63F.
bme688: [6] pressure is 102176.35pa.
bme688: [6] humidity raw is 0x00003AA7.
bme688: [6] humidity is 21.70%.
bme688: [6] adc raw is 0x036B.
bme688: [6] adc range is 0x08.
bme688: [6] resistance ohms is 197492.77ohms.
bme688: irq channel data.
bme688: [7] temperature raw is 0x0007DF7B.
bme688: [7] temperature is 30.92C.
bme688: [7] pressure raw is 0x0004B6BD.
bme688: [7] pressure is 102176.41pa.
bme688: [7] humidity raw is 0x00003A7B.
bme688: [7] humidity is 21.47%.
bme688: [7] adc raw is 0x00EE.
bme688: [7] adc range is 0x0A.
bme688: [7] resistance ohms is 78191.81ohms.
bme688: irq channel data.
bme688: [8] temperature raw is 0x0007E174.
bme688: [8] temperature is 31.08C.
bme688: [8] pressure raw is 0x0004B758.
bme688: [8] pressure is 102176.71pa.
bme688: [8] humidity raw is 0x00003A50.
bme688: [8] humidity is 21.26%.
bme688: [8] adc raw is 0x030E.
bme688: [8] adc range is 0x0A.
bme688: [8] resistance ohms is 52181.00ohms.
bme688: irq channel data.
bme688: [9] temperature raw is 0x0007E399.
bme688: [9] temperature is 31.25C.
bme688: [9] pressure raw is 0x0004B7FF.
bme688: [9] pressure is 102177.27pa.
bme688: [9] humidity raw is 0x00003A26.
bme688: [9] humidity is 21.04%.
bme688: [9] adc raw is 0x02CE.
bme688: [9] adc range is 0x0A.
bme688: [9] resistance ohms is 54306.32ohms.
bme688: irq all data.
bme688: [0] temperature raw is 0x0007B646.
bme688: [0] temperature is 27.54C.
bme688: [0] pressure raw is 0x0004AA3F.
bme688: [0] pressure is 102160.91pa.
bme688: [0] humidity raw is 0x00003C4B.
bme688: [0] humidity is 23.72%.
bme688: [0] adc raw is 0x01C4.
bme688: [0] adc range is 0x0C.
bme688: [0] resistance ohms is 16343.21ohms.
bme688: [1] temperature raw is 0x0007C412.
bme688: [1] temperature is 28.67C.
bme688: [1] pressure raw is 0x0004AE68.
bme688: [1] pressure is 102167.62pa.
bme688: [1] humidity raw is 0x00003C20.
bme688: [1] humidity is 23.57%.
bme688: [1] adc raw is 0x0093.
bme688: [1] adc range is 0x08.
bme688: [1] resistance ohms is 341219.59ohms.
bme688: [2] temperature raw is 0x0007CA80.
bme688: [2] temperature is 29.19C.
bme688: [2] pressure raw is 0x0004B05D.
bme688: [2] pressure is 102169.77pa.
bme688: [2] humidity raw is 0x00003BFC.
bme688: [2] humidity is 23.42%.
bme688: [2] adc raw is 0x02C0.
bme688: [2] adc range is 0x0B.
bme688: [2] resistance ohms is 27397.26ohms.
bme688: [3] temperature raw is 0x0007D23E.
bme688: [3] temperature is 29.83C.
bme688: [3] pressure raw is 0x0004B2B9.
bme688: [3] pressure is 102172.08pa.
bme688: [3] humidity raw is 0x00003BBA.
bme688: [3] humidity is 23.11%.
bme688: [3] adc raw is 0x009A.
bme688: [3] adc range is 0x0B.
bme688: [3] resistance ohms is 42356.05ohms.
bme688: [4] temperature raw is 0x0007D813.
bme688: [4] temperature is 30.31C.
bme688: [4] pressure raw is 0x0004B47E.
bme688: [4] pressure is 102174.03pa.
bme688: [4] humidity raw is 0x00003B71.
bme688: [4] humidity is 22.75%.
bme688: [4] adc raw is 0x02AD.
bme688: [4] adc range is 0x0A.
bme688: [4] resistance ohms is 55471.29ohms.
bme688: [5] temperature raw is 0x0007DCC5.
bme688: [5] temperature is 30.69C.
bme688: [5] pressure raw is 0x0004B5E8.
bme688: [5] pressure is 102175.98pa.
bme688: [5] humidity raw is 0x00003ADB.
bme688: [5] humidity is 21.97%.
bme688: [5] adc raw is 0x0044.
bme688: [5] adc range is 0x07.
bme688: [5] resistance ohms is 740955.12ohms.
bme688: [6] temperature raw is 0x0007DDE4.
bme688: [6] temperature is 30.79C.
bme688: [6] pressure raw is 0x0004B63F.
bme688: [6] pressure is 102176.35pa.
bme688: [6] humidity raw is 0x00003AA7.
bme688: [6] humidity is 21.70%.
bme688: [6] adc raw is 0x036B.
bme688: [6] adc range is 0x08.
bme688: [6] resistance ohms is 197492.77ohms.
bme688: [7] temperature raw is 0x0007DF7B.
bme688: [7] temperature is 30.92C.
bme688: [7] pressure raw is 0x0004B6BD.
bme688: [7] pressure is 102176.41pa.
bme688: [7] humidity raw is 0x00003A7B.
bme688: [7] humidity is 21.47%.
bme688: [7] adc raw is 0x00EE.
bme688: [7] adc range is 0x0A.
bme688: [7] resistance ohms is 78191.81ohms.
bme688: [8] temperature raw is 0x0007E174.
bme688: [8] temperature is 31.08C.
bme688: [8] pressure raw is 0x0004B758.
bme688: [8] pressure is 102176.71pa.
bme688: [8] humidity raw is 0x00003A50.
bme688: [8] humidity is 21.26%.
bme688: [8] adc raw is 0x030E.
bme688: [8] adc range is 0x0A.
bme688: [8] resistance ohms is 52181.00ohms.
bme688: [9] temperature raw is 0x0007E399.
bme688: [9] temperature is 31.25C.
bme688: [9] pressure raw is 0x0004B7FF.
bme688: [9] pressure is 102177.27pa.
bme688: [9] humidity raw is 0x00003A26.
bme688: [9] humidity is 21.04%.
bme688: [9] adc raw is 0x02CE.
bme688: [9] adc range is 0x0A.
bme688: [9] resistance ohms is 54306.32ohms.
bme688: irq channel data.
bme688: [0] temperature raw is 0x0007E674.
bme688: [0] temperature is 31.49C.
bme688: [0] pressure raw is 0x0004B8E1.
bme688: [0] pressure is 102177.35pa.
bme688: [0] humidity raw is 0x000039FA.
bme688: [0] humidity is 20.83%.
bme688: [0] adc raw is 0x0264.
bme688: [0] adc range is 0x0A.
bme688: [0] resistance ohms is 58234.76ohms.
bme688: irq channel data.
bme688: [1] temperature raw is 0x0007E408.
bme688: [1] temperature is 31.29C.
bme688: [1] pressure raw is 0x0004B818.
bme688: [1] pressure is 102178.88pa.
bme688: [1] humidity raw is 0x000039A6.
bme688: [1] humidity is 20.37%.
bme688: [1] adc raw is 0x01F4.
bme688: [1] adc range is 0x05.
bme688: [1] resistance ohms is 2017734.00ohms.
bme688: irq channel data.
bme688: [2] temperature raw is 0x0007E4FC.
bme688: [2] temperature is 31.37C.
bme688: [2] pressure raw is 0x0004B867.
bme688: [2] pressure is 102178.30pa.
bme688: [2] humidity raw is 0x00003998.
bme688: [2] humidity is 20.30%.
bme688: [2] adc raw is 0x02CD.
bme688: [2] adc range is 0x0A.
bme688: [2] resistance ohms is 54340.90ohms.
bme688: irq channel data.
bme688: [3] temperature raw is 0x0007E7A5.
bme688: [3] temperature is 31.59C.
bme688: [3] pressure raw is 0x0004B93A.
bme688: [3] pressure is 102178.30pa.
bme688: [3] humidity raw is 0x00003974.
bme688: [3] humidity is 20.12%.
bme688: [3] adc raw is 0x027E.
bme688: [3] adc range is 0x0A.
bme688: [3] resistance ohms is 57219.49ohms.
bme688: irq channel data.
bme688: [4] temperature raw is 0x0007EA75.
bme688: [4] temperature is 31.82C.
bme688: [4] pressure raw is 0x0004BA14.
bme688: [4] pressure is 102179.15pa.
bme688: [4] humidity raw is 0x00003952.
bme688: [4] humidity is 19.96%.
bme688: [4] adc raw is 0x0208.
bme688: [4] adc range is 0x0A.
bme688: [4] resistance ohms is 62135.92ohms.
bme688: irq channel data.
bme688: [5] temperature raw is 0x0007E9E7.
bme688: [5] temperature is 31.77C.
bme688: [5] pressure raw is 0x0004B9E3.
bme688: [5] pressure is 102180.03pa.
bme688: [5] humidity raw is 0x00003911.
bme688: [5] humidity is 19.61%.
bme688: [5] adc raw is 0x02C8.
bme688: [5] adc range is 0x06.
bme688: [5] resistance ohms is 872231.69ohms.
bme688: irq channel data.
bme688: [6] temperature raw is 0x0007E996.
bme688: [6] temperature is 31.74C.
bme688: [6] pressure raw is 0x0004B9CD.
bme688: [6] pressure is 102179.48pa.
bme688: [6] humidity raw is 0x000038FE.
bme688: [6] humidity is 19.51%.
bme688: [6] adc raw is 0x029F.
bme688: [6] adc range is 0x08.
bme688: [6] resistance ohms is 223923.03ohms.
bme688: irq channel data.
bme688: [7] temperature raw is 0x0007EA43.
bme688: [7] temperature is 31.80C.
bme688: [7] pressure raw is 0x0004BA05.
bme688: [7] pressure is 102179.06pa.
bme688: [7] humidity raw is 0x000038EC.
bme688: [7] humidity is 19.42%.
bme688: [7] adc raw is 0x0081.
bme688: [7] adc range is 0x0A.
bme688: [7] resistance ohms is 86868.00ohms.
bme688: irq channel data.
bme688: [8] temperature raw is 0x0007EBA9.
bme688: [8] temperature is 31.91C.
bme688: [8] pressure raw is 0x0004BA75.
bme688: [8] pressure is 102178.88pa.
bme688: [8] humidity raw is 0x000038DC.
bme688: [8] humidity is 19.34%.
bme688: [8] adc raw is 0x029E.
bme688: [8] adc range is 0x0A.
bme688: [8] resistance ohms is 56017.50ohms.
bme688: irq channel data.
bme688: [9] temperature raw is 0x0007ED77.
bme688: [9] temperature is 32.06C.
bme688: [9] pressure raw is 0x0004BB00.
bme688: [9] pressure is 102179.54pa.
bme688: [9] humidity raw is 0x000038C8.
bme688: [9] humidity is 19.25%.
bme688: [9] adc raw is 0x029F.
bme688: [9] adc range is 0x0A.
bme688: [9] resistance ohms is 55980.76ohms.
bme688: irq all data.
bme688: [0] temperature raw is 0x0007E674.
bme688: [0] temperature is 31.49C.
bme688: [0] pressure raw is 0x0004B8E1.
bme688: [0] pressure is 102177.35pa.
bme688: [0] humidity raw is 0x000039FA.
bme688: [0] humidity is 20.83%.
bme688: [0] adc raw is 0x0264.
bme688: [0] adc range is 0x0A.
bme688: [0] resistance ohms is 58234.76ohms.
bme688: [1] temperature raw is 0x0007E408.
bme688: [1] temperature is 31.29C.
bme688: [1] pressure raw is 0x0004B818.
bme688: [1] pressure is 102178.88pa.
bme688: [1] humidity raw is 0x000039A6.
bme688: [1] humidity is 20.37%.
bme688: [1] adc raw is 0x01F4.
bme688: [1] adc range is 0x05.
bme688: [1] resistance ohms is 2017734.00ohms.
bme688: [2] temperature raw is 0x0007E4FC.
bme688: [2] temperature is 31.37C.
bme688: [2] pressure raw is 0x0004B867.
bme688: [2] pressure is 102178.30pa.
bme688: [2] humidity raw is 0x00003998.
bme688: [2] humidity is 20.30%.
bme688: [2] adc raw is 0x02CD.
bme688: [2] adc range is 0x0A.
bme688: [2] resistance ohms is 54340.90ohms.
bme688: [3] temperature raw is 0x0007E7A5.
bme688: [3] temperature is 31.59C.
bme688: [3] pressure raw is 0x0004B93A.
bme688: [3] pressure is 102178.30pa.
bme688: [3] humidity raw is 0x00003974.
bme688: [3] humidity is 20.12%.
bme688: [3] adc raw is 0x027E.
bme688: [3] adc range is 0x0A.
bme688: [3] resistance ohms is 57219.49ohms.
bme688: [4] temperature raw is 0x0007EA75.
bme688: [4] temperature is 31.82C.
bme688: [4] pressure raw is 0x0004BA14.
bme688: [4] pressure is 102179.15pa.
bme688: [4] humidity raw is 0x00003952.
bme688: [4] humidity is 19.96%.
bme688: [4] adc raw is 0x0208.
bme688: [4] adc range is 0x0A.
bme688: [4] resistance ohms is 62135.92ohms.
bme688: [5] temperature raw is 0x0007E9E7.
bme688: [5] temperature is 31.77C.
bme688: [5] pressure raw is 0x0004B9E3.
bme688: [5] pressure is 102180.03pa.
bme688: [5] humidity raw is 0x00003911.
bme688: [5] humidity is 19.61%.
bme688: [5] adc raw is 0x02C8.
bme688: [5] adc range is 0x06.
bme688: [5] resistance ohms is 872231.69ohms.
bme688: [6] temperature raw is 0x0007E996.
bme688: [6] temperature is 31.74C.
bme688: [6] pressure raw is 0x0004B9CD.
bme688: [6] pressure is 102179.48pa.
bme688: [6] humidity raw is 0x000038FE.
bme688: [6] humidity is 19.51%.
bme688: [6] adc raw is 0x029F.
bme688: [6] adc range is 0x08.
bme688: [6] resistance ohms is 223923.03ohms.
bme688: [7] temperature raw is 0x0007EA43.
bme688: [7] temperature is 31.80C.
bme688: [7] pressure raw is 0x0004BA05.
bme688: [7] pressure is 102179.06pa.
bme688: [7] humidity raw is 0x000038EC.
bme688: [7] humidity is 19.42%.
bme688: [7] adc raw is 0x0081.
bme688: [7] adc range is 0x0A.
bme688: [7] resistance ohms is 86868.00ohms.
bme688: [8] temperature raw is 0x0007EBA9.
bme688: [8] temperature is 31.91C.
bme688: [8] pressure raw is 0x0004BA75.
bme688: [8] pressure is 102178.88pa.
bme688: [8] humidity raw is 0x000038DC.
bme688: [8] humidity is 19.34%.
bme688: [8] adc raw is 0x029E.
bme688: [8] adc range is 0x0A.
bme688: [8] resistance ohms is 56017.50ohms.
bme688: [9] temperature raw is 0x0007ED77.
bme688: [9] temperature is 32.06C.
bme688: [9] pressure raw is 0x0004BB00.
bme688: [9] pressure is 102179.54pa.
bme688: [9] humidity raw is 0x000038C8.
bme688: [9] humidity is 19.25%.
bme688: [9] adc raw is 0x029F.
bme688: [9] adc range is 0x0A.
bme688: [9] resistance ohms is 55980.76ohms.
bme688: irq channel data.
bme688: [0] temperature raw is 0x0007EF23.
bme688: [0] temperature is 32.20C.
bme688: [0] pressure raw is 0x0004BB81.
bme688: [0] pressure is 102180.14pa.
bme688: [0] humidity raw is 0x000038B2.
bme688: [0] humidity is 19.14%.
bme688: [0] adc raw is 0x0258.
bme688: [0] adc range is 0x0A.
bme688: [0] resistance ohms is 58715.60ohms.
bme688: irq channel data.
bme688: [1] temperature raw is 0x0007EAA9.
bme688: [1] temperature is 31.83C.
bme688: [1] pressure raw is 0x0004BA1B.
bme688: [1] pressure is 102180.70pa.
bme688: [1] humidity raw is 0x00003891.
bme688: [1] humidity is 18.95%.
bme688: [1] adc raw is 0x0218.
bme688: [1] adc range is 0x05.
bme688: [1] resistance ohms is 1965451.00ohms.
bme688: irq channel data.
bme688: [2] temperature raw is 0x0007EADB.
bme688: [2] temperature is 31.85C.
bme688: [2] pressure raw is 0x0004BA30.
bme688: [2] pressure is 102179.77pa.
bme688: [2] humidity raw is 0x0000389B.
bme688: [2] humidity is 19.00%.
bme688: [2] adc raw is 0x02E4.
bme688: [2] adc range is 0x0A.
bme688: [2] resistance ohms is 53556.48ohms.
bme688: irq channel data.
bme688: [3] temperature raw is 0x0007ECED.
bme688: [3] temperature is 32.02C.
bme688: [3] pressure raw is 0x0004BAD2.
bme688: [3] pressure is 102180.11pa.
bme688: [3] humidity raw is 0x0000389A.
bme688: [3] humidity is 19.00%.
bme688: [3] adc raw is 0x02A3.
bme688: [3] adc range is 0x0A.
bme688: [3] resistance ohms is 55834.24ohms.
bme688: irq channel data.
bme688: [4] temperature raw is 0x0007EF45.
bme688: [4] temperature is 32.21C.
bme688: [4] pressure raw is 0x0004BB88.
bme688: [4] pressure is 102180.74pa.
bme688: [4] humidity raw is 0x00003896.
bme688: [4] humidity is 18.99%.
bme688: [4] adc raw is 0x0216.
bme688: [4] adc range is 0x0A.
bme688: [4] resistance ohms is 61508.89ohms.
bme688: irq channel data.
bme688: [5] temperature raw is 0x0007EE06.
bme688: [5] temperature is 32.11C.
bme688: [5] pressure raw is 0x0004BB25.
bme688: [5] pressure is 102180.79pa.
bme688: [5] humidity raw is 0x00003897.
bme688: [5] humidity is 18.99%.
bme688: [5] adc raw is 0x032C.
bme688: [5] adc range is 0x06.
bme688: [5] resistance ohms is 819855.88ohms.
bme688: irq channel data.
bme688: [6] temperature raw is 0x0007ED73.
bme688: [6] temperature is 32.06C.
bme688: [6] pressure raw is 0x0004BAFA.
bme688: [6] pressure is 102180.38pa.
bme688: [6] humidity raw is 0x000038A0.
bme688: [6] humidity is 19.04%.
bme688: [6] adc raw is 0x02D8.
bme688: [6] adc range is 0x08.
bme688: [6] resistance ohms is 215851.61ohms.
bme688: irq channel data.
bme688: [7] temperature raw is 0x0007EDEA.
bme688: [7] temperature is 32.10C.
bme688: [7] pressure raw is 0x0004BB20.
bme688: [7] pressure is 102180.17pa.
bme688: [7] humidity raw is 0x000038A3.
bme688: [7] humidity is 19.06%.
bme688: [7] adc raw is 0x0096.
bme688: [7] adc range is 0x0A.
bme688: [7] resistance ohms is 85049.84ohms.
bme688: irq channel data.
bme688: [8] temperature raw is 0x0007EF26.
bme688: [8] temperature is 32.20C.
bme688: [8] pressure raw is 0x0004BB7E.
bme688: [8] pressure is 102180.80pa.
bme688: [8] humidity raw is 0x0000389E.
bme688: [8] humidity is 19.04%.
bme688: [8] adc raw is 0x02B2.
bme688: [8] adc range is 0x0A.
bme688: [8] resistance ohms is 55291.58ohms.
bme688: irq channel data.
bme688: [9] temperature raw is 0x0007F0CE.
bme688: [9] temperature is 32.34C.
bme688: [9] pressure raw is 0x0004BBFE.
bme688: [9] pressure is 102181.34pa.
bme688: [9] humidity raw is 0x00003890.
bme688: [9] humidity is 18.97%.
bme688: [9] adc raw is 0x029E.
bme688: [9] adc range is 0x0A.
bme688: [9] resistance ohms is 56017.50ohms.
bme688: irq all data.
bme688: [0] temperature raw is 0x0007EF23.
bme688: [0] temperature is 32.20C.
bme688: [0] pressure raw is 0x0004BB81.
bme688: [0] pressure is 102180.14pa.
bme688: [0] humidity raw is 0x000038B2.
bme688: [0] humidity is 19.14%.
bme688: [0] adc raw is 0x0258.
bme688: [0] adc range is 0x0A.
bme688: [0] resistance ohms is 58715.60ohms.
bme688: [1] temperature raw is 0x0007EAA9.
bme688: [1] temperature is 31.83C.
bme688: [1] pressure raw is 0x0004BA1B.
bme688: [1] pressure is 102180.70pa.
bme688: [1] humidity raw is 0x00003891.
bme688: [1] humidity is 18.95%.
bme688: [1] adc raw is 0x0218.
bme688: [1] adc range is 0x05.
bme688: [1] resistance ohms is 1965451.00ohms.
bme688: [2] temperature raw is 0x0007EADB.
bme688: [2] temperature is 31.85C.
bme688: [2] pressure raw is 0x0004BA30.
bme688: [2] pressure is 102179.77pa.
bme688: [2] humidity raw is 0x0000389B.
bme688: [2] humidity is 19.00%.
bme688: [2] adc raw is 0x02E4.
bme688: [2] adc range is 0x0A.
bme688: [2] resistance ohms is 53556.48ohms.
bme688: [3] temperature raw is 0x0007ECED.
bme688: [3] temperature is 32.02C.
bme688: [3] pressure raw is 0x0004BAD2.
bme688: [3] pressure is 102180.11pa.
bme688: [3] humidity raw is 0x0000389A.
bme688: [3] humidity is 19.00%.
bme688: [3] adc raw is 0x02A3.
bme688: [3] adc range is 0x0A.
bme688: [3] resistance ohms is 55834.24ohms.
bme688: [4] temperature raw is 0x0007EF45.
bme688: [4] temperature is 32.21C.
bme688: [4] pressure raw is 0x0004BB88.
bme688: [4] pressure is 102180.74pa.
bme688: [4] humidity raw is 0x00003896.
bme688: [4] humidity is 18.99%.
bme688: [4] adc raw is 0x0216.
bme688: [4] adc range is 0x0A.
bme688: [4] resistance ohms is 61508.89ohms.
bme688: [5] temperature raw is 0x0007EE06.
bme688: [5] temperature is 32.11C.
bme688: [5] pressure raw is 0x0004BB25.
bme688: [5] pressure is 102180.79pa.
bme688: [5] humidity raw is 0x00003897.
bme688: [5] humidity is 18.99%.
bme688: [5] adc raw is 0x032C.
bme688: [5] adc range is 0x06.
bme688: [5] resistance ohms is 819855.88ohms.
bme688: [6] temperature raw is 0x0007ED73.
bme688: [6] temperature is 32.06C.
bme688: [6] pressure raw is 0x0004BAFA.
bme688: [6] pressure is 102180.38pa.
bme688: [6] humidity raw is 0x000038A0.
bme688: [6] humidity is 19.04%.
bme688: [6] adc raw is 0x02D8.
bme688: [6] adc range is 0x08.
bme688: [6] resistance ohms is 215851.61ohms.
bme688: [7] temperature raw is 0x0007EDEA.
bme688: [7] temperature is 32.10C.
bme688: [7] pressure raw is 0x0004BB20.
bme688: [7] pressure is 102180.17pa.
bme688: [7] humidity raw is 0x000038A3.
bme688: [7] humidity is 19.06%.
bme688: [7] adc raw is 0x0096.
bme688: [7] adc range is 0x0A.
bme688: [7] resistance ohms is 85049.84ohms.
bme688: [8] temperature raw is 0x0007EF26.
bme688: [8] temperature is 32.20C.
bme688: [8] pressure raw is 0x0004BB7E.
bme688: [8] pressure is 102180.80pa.
bme688: [8] humidity raw is 0x0000389E.
bme688: [8] humidity is 19.04%.
bme688: [8] adc raw is 0x02B2.
bme688: [8] adc range is 0x0A.
bme688: [8] resistance ohms is 55291.58ohms.
bme688: [9] temperature raw is 0x0007F0CE.
bme688: [9] temperature is 32.34C.
bme688: [9] pressure raw is 0x0004BBFE.
bme688: [9] pressure is 102181.34pa.
bme688: [9] humidity raw is 0x00003890.
bme688: [9] humidity is 18.97%.
bme688: [9] adc raw is 0x029E.
bme688: [9] adc range is 0x0A.
bme688: [9] resistance ohms is 56017.50ohms.
bme688: parallel done.
```

```shell
bme688 -h

Usage:
  bme688 (-i | --information)
  bme688 (-h | --help)
  bme688 (-p | --port)
  bme688 (-t reg | --test=reg) [--addr=<0 | 1>] [--interface=<iic | spi>]
  bme688 (-t read | --test=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--index=<index>] [--times=<num>]
  bme688 (-t parallel | --test=parallel) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
  bme688 (-e read | --example=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
  bme688 (-e gas | --example=gas) [--addr=<0 | 1>] [--interface=<iic | spi>] [--index=<index>]
         [--degree=<degree>] [--wait=<ms>] [--times=<num>]
  bme688 (-e parallel | --example=parallel) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]

Options:
      --addr=<0 | 1>                 Set the chip iic address.([default: 0])
      --degree=<degree>              Set the heater expected temperature in degree celsius.([default: 200.0])
  -e <read | gas | parallel>, --example=<read | gas | parallel>
                                     Run the driver example.
  -h, --help                         Show the help.
  -i, --information                  Show the chip information.
      --index=<index>                Set the heater index and it range is 0 - 9.([default: 0])
      --interface=<iic | spi>        Set the chip interface.([default: iic])
  -p, --port                         Display the pin connections of the current board.
  -t <reg | read | parallel>, --test=<reg | read | parallel>
                                     Run the driver test.
      --times=<num>                  Set the running times.([default: 3])
      --wait=<ms>                    Set the heater wait time in ms.([default: 150])
```

