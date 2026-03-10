/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_bme688.h
 * @brief     driver bme688 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2026-03-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2026/03/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_BME688_H
#define DRIVER_BME688_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup bme688_driver bme688 driver function
 * @brief    bme688 driver modules
 * @{
 */

/**
 * @addtogroup bme688_base_driver
 * @{
 */

/**
 * @brief bme688 bool enumeration definition
 */
typedef enum
{
    BME688_BOOL_FALSE = 0x00,        /**< false */
    BME688_BOOL_TRUE  = 0x01,        /**< true */
} bme688_bool_t;

/**
 * @brief bme688 interface enumeration definition
 */
typedef enum
{
    BME688_INTERFACE_IIC = 0x00,        /**< iic interface */
    BME688_INTERFACE_SPI = 0x01,        /**< spi interface */
} bme688_interface_t;

/**
 * @brief bme688 address enumeration definition
 */
typedef enum
{
    BME688_ADDRESS_ADO_LOW  = (0x76 << 1),        /**< ADO is low */
    BME688_ADDRESS_ADO_HIGH = (0x77 << 1),        /**< ADO is HIGH */
} bme688_address_t;

/**
 * @brief bme688 oversampling enumeration definition
 */
typedef enum
{
    BME688_OVERSAMPLING_SKIP = 0x00,        /**< oversampling x1 */
    BME688_OVERSAMPLING_x1   = 0x01,        /**< oversampling x1 */
    BME688_OVERSAMPLING_x2   = 0x02,        /**< oversampling x2 */
    BME688_OVERSAMPLING_x4   = 0x03,        /**< oversampling x4 */
    BME688_OVERSAMPLING_x8   = 0x04,        /**< oversampling x8 */
    BME688_OVERSAMPLING_x16  = 0x05,        /**< oversampling x16 */
} bme688_oversampling_t;

/**
 * @brief bme688 mode enumeration definition
 */
typedef enum
{
    BME688_MODE_SLEEP    = 0x00,        /**< sleep mode */
    BME688_MODE_FORCED   = 0x01,        /**< forced mode */
    BME688_MODE_PARALLEL = 0x02,        /**< parallel mode */
} bme688_mode_t;

/**
 * @brief bme688 filter enumeration definition
 */
typedef enum
{
    BME688_FILTER_OFF       = 0x00,        /**< off */
    BME688_FILTER_COEFF_1   = 0x01,        /**< coeff 1 */
    BME688_FILTER_COEFF_3   = 0x02,        /**< coeff 3 */
    BME688_FILTER_COEFF_7   = 0x03,        /**< coeff 7 */
    BME688_FILTER_COEFF_15  = 0x04,        /**< coeff 15 */
    BME688_FILTER_COEFF_31  = 0x05,        /**< coeff 31 */
    BME688_FILTER_COEFF_63  = 0x06,        /**< coeff 63 */
    BME688_FILTER_COEFF_127 = 0x07,        /**< coeff 127 */
} bme688_filter_t;

/**
 * @brief bme688 spi wire enumeration definition
 */
typedef enum
{
    BME688_SPI_WIRE_4 = 0x00,        /**< 4 wire */
    BME688_SPI_WIRE_3 = 0x01,        /**< 3 wire */
} bme688_spi_wire_t;

/**
 * @brief bme688 heater profile enumeration definition
 */
typedef enum
{
    BME688_HEATER_PROFILE_FORCED_STEP_0_PARALLEL_NO_STEP   = 0x00,        /**< forced mode step 0, parallel mode no step */
    BME688_HEATER_PROFILE_FORCED_STEP_1_PARALLEL_STEP_0    = 0x01,        /**< forced mode step 1, parallel mode step 0 */
    BME688_HEATER_PROFILE_FORCED_STEP_2_PARALLEL_STEP_0_1  = 0x02,        /**< forced mode step 2, parallel mode step 0 - 1 */
    BME688_HEATER_PROFILE_FORCED_STEP_3_PARALLEL_STEP_0_2  = 0x03,        /**< forced mode step 3, parallel mode step 0 - 2 */
    BME688_HEATER_PROFILE_FORCED_STEP_4_PARALLEL_STEP_0_3  = 0x04,        /**< forced mode step 4, parallel mode step 0 - 3 */
    BME688_HEATER_PROFILE_FORCED_STEP_5_PARALLEL_STEP_0_4  = 0x05,        /**< forced mode step 5, parallel mode step 0 - 4 */
    BME688_HEATER_PROFILE_FORCED_STEP_6_PARALLEL_STEP_0_5  = 0x06,        /**< forced mode step 6, parallel mode step 0 - 5 */
    BME688_HEATER_PROFILE_FORCED_STEP_7_PARALLEL_STEP_0_6  = 0x07,        /**< forced mode step 7, parallel mode step 0 - 6 */
    BME688_HEATER_PROFILE_FORCED_STEP_8_PARALLEL_STEP_0_7  = 0x08,        /**< forced mode step 8, parallel mode step 0 - 7 */
    BME688_HEATER_PROFILE_FORCED_STEP_9_PARALLEL_STEP_0_8  = 0x09,        /**< forced mode step 9, parallel mode step 0 - 8 */
    BME688_HEATER_PROFILE_FORCED_NO_STEP_PARALLEL_STEP_0_9 = 0x0A,        /**< forced mode no step, parallel mode step 0 - 9 */
} bme688_heater_profile_t;

/**
 * @brief bme688 section enumeration definition
 */
typedef enum
{
    BME688_SECTION_0 = 0x00,        /**< section 0 */
    BME688_SECTION_1 = 0x01,        /**< section 1 */
    BME688_SECTION_2 = 0x02,        /**< section 2 */
} bme688_section_t;

/**
 * @brief bme688 status enumeration definition
 */
typedef enum
{
    BME688_STATUS_CHANNEL_DATA  = 0x00,        /**< channel data */
    BME688_STATUS_ALL_DATA      = 0x01,        /**< all data */
    BME688_STATUS_SEQUENCE_LOST = 0x02,        /**< sequence lost */
} bme688_status_t;

/**
 * @brief bme688 parallel data structure definition
 */
typedef struct bme688_parallel_data_s
{
    uint8_t channel;                  /**< channel */
    uint32_t temperature_raw;         /**< temperature raw data */
    float temperature_c;              /**< temperature in C */
    uint32_t pressure_raw;            /**< pressure raw data */
    float pressure_pa;                /**< pressure in pa */
    uint32_t humidity_raw;            /**< humidity raw data */
    float humidity_percentage;        /**< humidity in percentage */
    uint16_t adc_raw;                 /**< adc raw */
    uint8_t adc_range;                /**< adc range */
    float ohms;                       /**< resistance ohms */
} bme688_parallel_data_t;

/**
 * @brief bme688 parallel config structure definition
 */
typedef struct bme688_parallel_config_s
{
    const float *heater_temp_prof;         /**< store the heater temperature profile in degree celsius */
    const uint8_t *heater_dur_prof;        /**< number of times tphg sequence needs to be repeated */
    uint8_t profile_len;                  /**< length of the heating profile */
    float shared_heater_dur;               /**< heating duration for parallel mode in milliseconds */
} bme688_parallel_config_t;

/**
 * @brief bme688 handle structure definition
 */
typedef struct bme688_handle_s
{
    uint8_t iic_addr;                                                                   /**< iic device address */
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    uint8_t (*spi_init)(void);                                                          /**< point to a spi_init function address */
    uint8_t (*spi_deinit)(void);                                                        /**< point to a spi_deinit function address */
    uint8_t (*spi_read)(uint8_t reg, uint8_t *buf, uint16_t len);                       /**< point to a spi_read function address */
    uint8_t (*spi_write)(uint8_t reg, uint8_t *buf, uint16_t len);                      /**< point to a spi_write function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    void (*receive_callback)(uint8_t status, bme688_parallel_data_t *data, 
                             uint8_t len);                                              /**< point to a receive_callback function address */
    uint8_t inited;                                                                     /**< inited flag */
    uint8_t iic_spi;                                                                    /**< iic spi interface */
    uint8_t page;                                                                       /**< spi page */
    uint16_t par_h1;                                                                    /**< calibration coefficient for the humidity sensor */
    uint16_t par_h2;                                                                    /**< calibration coefficient for the humidity sensor */
    int8_t par_h3;                                                                      /**< calibration coefficient for the humidity sensor */
    int8_t par_h4;                                                                      /**< calibration coefficient for the humidity sensor */
    int8_t par_h5;                                                                      /**< calibration coefficient for the humidity sensor */
    uint8_t par_h6;                                                                     /**< calibration coefficient for the humidity sensor */
    int8_t par_h7;                                                                      /**< calibration coefficient for the humidity sensor */
    int8_t par_gh1;                                                                     /**< calibration coefficient for the gas sensor */
    int16_t par_gh2;                                                                    /**< calibration coefficient for the gas sensor */
    int8_t par_gh3;                                                                     /**< calibration coefficient for the gas sensor */
    uint16_t par_t1;                                                                    /**< calibration coefficient for the temperature sensor */
    int16_t par_t2;                                                                     /**< calibration coefficient for the temperature sensor */
    int8_t par_t3;                                                                      /**< calibration coefficient for the temperature sensor */
    uint16_t par_p1;                                                                    /**< calibration coefficient for the pressure sensor */
    int16_t par_p2;                                                                     /**< calibration coefficient for the pressure sensor */
    int8_t par_p3;                                                                      /**< calibration coefficient for the pressure sensor */
    int16_t par_p4;                                                                     /**< calibration coefficient for the pressure sensor */
    int16_t par_p5;                                                                     /**< calibration coefficient for the pressure sensor */
    int8_t par_p6;                                                                      /**< calibration coefficient for the pressure sensor */
    int8_t par_p7;                                                                      /**< calibration coefficient for the pressure sensor */
    int16_t par_p8;                                                                     /**< calibration coefficient for the pressure sensor */
    int16_t par_p9;                                                                     /**< calibration coefficient for the pressure sensor */
    uint8_t par_p10;                                                                    /**< calibration coefficient for the pressure sensor */
    uint8_t res_heat_range;                                                             /**< heater resistance range coefficient */
    int8_t res_heat_val;                                                                /**< heater resistance value coefficient */
    int8_t range_sw_err;                                                                /**< gas resistance range switching error coefficient */
    int8_t amb_temp;                                                                    /**< ambient temperature in degree c */
    float t_fine;                                                                       /**< variable to store the intermediate temperature coefficient */
    bme688_parallel_data_t parallel_data[10];                                           /**< parallel data */
    uint8_t parallel_sequence_number[3];                                                /**< parallel sequence number */
    uint8_t parallel_sequence_trigger[3];                                               /**< parallel sequence trigger */
    uint8_t parallel_data_len;                                                          /**< parallel data length */
    uint16_t parallel_data_flag;                                                        /**< parallel data flag */
} bme688_handle_t;

/**
 * @brief bme688 information structure definition
 */
typedef struct bme688_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} bme688_info_t;

/**
 * @}
 */

/**
 * @defgroup bme688_link_driver bme688 link driver function
 * @brief    bme688 link driver modules
 * @ingroup  bme688_driver
 * @{
 */

/**
 * @brief     initialize bme688_handle_t structure
 * @param[in] HANDLE pointer to a bme688 handle structure
 * @param[in] STRUCTURE bme688_handle_t
 * @note      none
 */
#define DRIVER_BME688_LINK_INIT(HANDLE, STRUCTURE)          memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE pointer to a bme688 handle structure
 * @param[in] FUC pointer to an iic_init function address
 * @note      none
 */
#define DRIVER_BME688_LINK_IIC_INIT(HANDLE, FUC)           (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE pointer to a bme688 handle structure
 * @param[in] FUC pointer to an iic_deinit function address
 * @note      none
 */
#define DRIVER_BME688_LINK_IIC_DEINIT(HANDLE, FUC)         (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE pointer to a bme688 handle structure
 * @param[in] FUC pointer to an iic_read function address
 * @note      none
 */
#define DRIVER_BME688_LINK_IIC_READ(HANDLE, FUC)           (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE pointer to a bme688 handle structure
 * @param[in] FUC pointer to an iic_write function address
 * @note      none
 */
#define DRIVER_BME688_LINK_IIC_WRITE(HANDLE, FUC)          (HANDLE)->iic_write = FUC

/**
 * @brief     link spi_init function
 * @param[in] HANDLE pointer to a bme688 handle structure
 * @param[in] FUC pointer to a spi_init function address
 * @note      none
 */
#define DRIVER_BME688_LINK_SPI_INIT(HANDLE, FUC)           (HANDLE)->spi_init = FUC

/**
 * @brief     link spi_deinit function
 * @param[in] HANDLE pointer to a bme688 handle structure
 * @param[in] FUC pointer to a spi_deinit function address
 * @note      none
 */
#define DRIVER_BME688_LINK_SPI_DEINIT(HANDLE, FUC)         (HANDLE)->spi_deinit = FUC

/**
 * @brief     link spi_read function
 * @param[in] HANDLE pointer to a bme688 handle structure
 * @param[in] FUC pointer to a spi_read function address
 * @note      none
 */
#define DRIVER_BME688_LINK_SPI_READ(HANDLE, FUC)           (HANDLE)->spi_read = FUC

/**
 * @brief     link spi_write function
 * @param[in] HANDLE pointer to a bme688 handle structure
 * @param[in] FUC pointer to a spi_write function address
 * @note      none
 */
#define DRIVER_BME688_LINK_SPI_WRITE(HANDLE, FUC)          (HANDLE)->spi_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to a bme688 handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_BME688_LINK_DELAY_MS(HANDLE, FUC)           (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to a bme688 handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_BME688_LINK_DEBUG_PRINT(HANDLE, FUC)        (HANDLE)->debug_print = FUC

/**
 * @brief     link receive_callback function
 * @param[in] HANDLE pointer to a bme688 handle structure
 * @param[in] FUC pointer to a receive_callback function address
 * @note      none
 */
#define DRIVER_BME688_LINK_RECEIVE_CALLBACK(HANDLE, FUC)   (HANDLE)->receive_callback = FUC

/**
 * @}
 */

/**
 * @defgroup bme688_base_driver bme688 base driver function
 * @brief    bme688 base driver modules
 * @ingroup  bme688_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a bme688 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t bme688_info(bme688_info_t *info);

/**
 * @brief     set the interface
 * @param[in] *handle pointer to a bme688 handle structure
 * @param[in] interface chip interface
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t bme688_set_interface(bme688_handle_t *handle, bme688_interface_t interface);

/**
 * @brief      get the interface
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[out] *interface pointer to a chip interface buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t bme688_get_interface(bme688_handle_t *handle, bme688_interface_t *interface);

/**
 * @brief     set the iic address pin
 * @param[in] *handle pointer to a bme688 handle structure
 * @param[in] addr_pin iic address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t bme688_set_addr_pin(bme688_handle_t *handle, bme688_address_t addr_pin);

/**
 * @brief      get the iic address pin
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[out] *addr_pin pointer to an iic address pin buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t bme688_get_addr_pin(bme688_handle_t *handle, bme688_address_t *addr_pin);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a bme688 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic or spi initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 id is error
 *            - 5 get nvm calibration failed
 *            - 6 read calibration failed
 * @note      none
 */
uint8_t bme688_init(bme688_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a bme688 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t bme688_deinit(bme688_handle_t *handle);

/**
 * @brief      read the temperature pressure humidity and gas resistance
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  section set section
 * @param[out] *temperature_raw pointer to a raw temperature buffer
 * @param[out] *temperature_c pointer to a converted temperature buffer
 * @param[out] *pressure_raw pointer to a raw pressure buffer
 * @param[out] *pressure_pa pointer to a converted pressure buffer
 * @param[out] *humidity_raw pointer to a raw humidity buffer
 * @param[out] *humidity_percentage pointer to a converted humidity percentage buffer
 * @param[out] *adc_raw pointer to an adc raw buffer
 * @param[out] *adc_range pointer to an adc range buffer
 * @param[out] *ohms pointer to an ohms buffer
 * @param[out] *index pointer to a heater index buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 compensate failed
 *             - 5 read timeout
 *             - 6 gas is invalid
 *             - 7 heater is not stable
 * @note       none
 */
uint8_t bme688_read(bme688_handle_t *handle, bme688_section_t section,
                    uint32_t *temperature_raw, float *temperature_c,
                    uint32_t *pressure_raw, float *pressure_pa,
                    uint32_t *humidity_raw, float *humidity_percentage,
                    uint16_t *adc_raw, uint8_t *adc_range, float *ohms, uint8_t *index);

/**
 * @brief      read the temperature pressure and humidity data
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  section set section
 * @param[out] *temperature_raw pointer to a raw temperature buffer
 * @param[out] *temperature_c pointer to a converted temperature buffer
 * @param[out] *pressure_raw pointer to a raw pressure buffer
 * @param[out] *pressure_pa pointer to a converted pressure buffer
 * @param[out] *humidity_raw pointer to a raw humidity buffer
 * @param[out] *humidity_percentage pointer to a converted humidity percentage buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 compensate failed
 *             - 5 read timeout
 * @note       none
 */
uint8_t bme688_read_temperature_pressure_humidity(bme688_handle_t *handle, bme688_section_t section,
                                                  uint32_t *temperature_raw, float *temperature_c,
                                                  uint32_t *pressure_raw, float *pressure_pa,
                                                  uint32_t *humidity_raw, float *humidity_percentage);

/**
 * @brief      read the pressure data
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  section set section
 * @param[out] *pressure_raw pointer to a raw pressure buffer
 * @param[out] *pressure_pa pointer to a converted pressure buffer
 * @return     status code
 *             - 0 success
 *             - 1 pressure read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 compensate pressure failed
 *             - 5 read timeout
 * @note       none
 */
uint8_t bme688_read_pressure(bme688_handle_t *handle, bme688_section_t section, uint32_t *pressure_raw, float *pressure_pa);

/**
 * @brief      read the temperature data
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  section set section
 * @param[out] *temperature_raw pointer to a raw temperature buffer
 * @param[out] *temperature_c pointer to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 temperature read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 compensate temperature failed
 *             - 5 read timeout
 * @note       none
 */
uint8_t bme688_read_temperature(bme688_handle_t *handle, bme688_section_t section, uint32_t *temperature_raw, float *temperature_c);

/**
 * @brief      read the humidity data
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  section set section
 * @param[out] *humidity_raw pointer to a raw humidity buffer
 * @param[out] *humidity_percentage pointer to a converted humidity percentage buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 compensate humidity failed
 *             - 5 read timeout
 * @note       none
 */
uint8_t bme688_read_humidity(bme688_handle_t *handle, bme688_section_t section, uint32_t *humidity_raw, float *humidity_percentage);

/**
 * @brief      read the gas resistance
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  section set section
 * @param[out] *adc_raw pointer to an adc raw buffer
 * @param[out] *adc_range pointer to an adc range buffer
 * @param[out] *ohms pointer to an ohms buffer
 * @param[out] *index pointer to a heater index buffer
 * @return     status code
 *             - 0 success
 *             - 1 gas resistance read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 compensate gas resistance failed
 *             - 5 read timeout
 *             - 6 gas is invalid
 *             - 7 heater is not stable
 * @note       none
 */
uint8_t bme688_read_gas_resistance(bme688_handle_t *handle, bme688_section_t section, uint16_t *adc_raw, uint8_t *adc_range, float *ohms, uint8_t *index);

/**
 * @brief     parallel progress
 * @param[in] *handle pointer to a bme688 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 parallel progress failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 not parallel mode
 *            - 5 not ready
 *            - 6 index is invalid
 *            - 7 compensate failed
 *            - 8 gas is invalid
 *            - 9 heater is not stable
 *            - 10 sequence is lost
 * @note      none
 */
uint8_t bme688_parallel_progress(bme688_handle_t *handle);

/**
 * @brief     parallel reset
 * @param[in] *handle pointer to a bme688 handle structure
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme688_parallel_reset(bme688_handle_t *handle);

/**
 * @brief     parallel config
 * @param[in] *handle pointer to a bme688 handle structure
 * @param[in] *config pointer to a bme688 parallel config structure
 * @return    status code
 *            - 0 success
 *            - 1 parallel config failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 config is invalid
 *            - 5 profile_len > 10
 *            - 6 ms >= 0x0783
 * @note      none
 */
uint8_t bme688_parallel_config(bme688_handle_t *handle, bme688_parallel_config_t *config);

/**
 * @brief      get new data status
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  section set section
 * @param[out] *enable pointer to a bool buffer
 * @return     status code
 *             - 0 success
 *             - 1 get new data status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_new_data_status(bme688_handle_t *handle, bme688_section_t section, bme688_bool_t *enable);

/**
 * @brief      get gas measuring status
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  section set section
 * @param[out] *enable pointer to a bool buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gas measuring status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_gas_measuring_status(bme688_handle_t *handle, bme688_section_t section, bme688_bool_t *enable);

/**
 * @brief      get measuring status
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  section set section
 * @param[out] *enable pointer to a bool buffer
 * @return     status code
 *             - 0 success
 *             - 1 get measuring status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_measuring_status(bme688_handle_t *handle, bme688_section_t section, bme688_bool_t *enable);

/**
 * @brief      get gas measuring index
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  section set section
 * @param[out] *index pointer to an index buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gas measuring index failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_gas_measuring_index(bme688_handle_t *handle, bme688_section_t section, uint8_t *index);

/**
 * @brief      get gas valid status
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  section set section
 * @param[out] *enable pointer to a bool buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gas valid status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_gas_valid_status(bme688_handle_t *handle, bme688_section_t section, bme688_bool_t *enable);

/**
 * @brief      get heater stability status
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  section set section
 * @param[out] *enable pointer to a bool buffer
 * @return     status code
 *             - 0 success
 *             - 1 get heater stability status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_heater_stability_status(bme688_handle_t *handle, bme688_section_t section, bme688_bool_t *enable);

/**
 * @brief      get sub measurement index
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  section set section
 * @param[out] *ind pointer to an index buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sub measurement index failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_sub_measurement_index(bme688_handle_t *handle, bme688_section_t section, uint8_t *ind);

/**
 * @brief     set idac heater
 * @param[in] *handle pointer to a bme688 handle structure
 * @param[in] index input index
 * @param[in] reg input register
 * @return    status code
 *            - 0 success
 *            - 1 set idac heater failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 index > 9
 * @note      none
 */
uint8_t bme688_set_idac_heater(bme688_handle_t *handle, uint8_t index, uint8_t reg);

/**
 * @brief      get idac heater
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  index input index
 * @param[out] *reg pointer to an input register buffer
 * @return     status code
 *             - 0 success
 *             - 1 get idac heater failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 index > 9
 * @note       none
 */
uint8_t bme688_get_idac_heater(bme688_handle_t *handle, uint8_t index, uint8_t *reg);

/**
 * @brief     set resistance heater
 * @param[in] *handle pointer to a bme688 handle structure
 * @param[in] index input index
 * @param[in] reg input register
 * @return    status code
 *            - 0 success
 *            - 1 set resistance heater failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 index > 9
 * @note      none
 */
uint8_t bme688_set_resistance_heater(bme688_handle_t *handle, uint8_t index, uint8_t reg);

/**
 * @brief      get resistance heater
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  index input index
 * @param[out] *reg pointer to an input register buffer
 * @return     status code
 *             - 0 success
 *             - 1 get resistance heater failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 index > 9
 * @note       none
 */
uint8_t bme688_get_resistance_heater(bme688_handle_t *handle, uint8_t index, uint8_t *reg);

/**
 * @brief     set gas wait
 * @param[in] *handle pointer to a bme688 handle structure
 * @param[in] index input index
 * @param[in] reg input register
 * @return    status code
 *            - 0 success
 *            - 1 set gas wait failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 index > 9
 * @note      none
 */
uint8_t bme688_set_gas_wait(bme688_handle_t *handle, uint8_t index, uint8_t reg);

/**
 * @brief      get gas wait
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  index input index
 * @param[out] *reg pointer to an input register buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gas wait failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 index > 9
 * @note       none
 */
uint8_t bme688_get_gas_wait(bme688_handle_t *handle, uint8_t index, uint8_t *reg);

/**
 * @brief     set gas wait shared
 * @param[in] *handle pointer to a bme688 handle structure
 * @param[in] reg input register
 * @return    status code
 *            - 0 success
 *            - 1 set gas wait shared failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme688_set_gas_wait_shared(bme688_handle_t *handle, uint8_t reg);

/**
 * @brief      get gas wait shared
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[out] *reg pointer to an input register buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gas wait shared failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_gas_wait_shared(bme688_handle_t *handle, uint8_t *reg);

/**
 * @brief     soft reset
 * @param[in] *handle pointer to a bme688 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 soft reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme688_soft_reset(bme688_handle_t *handle);

/**
 * @brief     enable or disable spi wire3 data interrupt
 * @param[in] *handle pointer to a bme688 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set spi wire 3 data interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme688_set_spi_wire_3_data_interrupt(bme688_handle_t *handle, bme688_bool_t enable);

/**
 * @brief      get spi wire3 data interrupt status
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get spi wire 3 data interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_spi_wire_3_data_interrupt(bme688_handle_t *handle, bme688_bool_t *enable);

/**
 * @brief     set humidity oversampling
 * @param[in] *handle pointer to a bme688 handle structure
 * @param[in] oversampling humidity oversampling
 * @return    status code
 *            - 0 success
 *            - 1 set humidity oversampling failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme688_set_humidity_oversampling(bme688_handle_t *handle, bme688_oversampling_t oversampling);

/**
 * @brief      get humidity oversampling
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[out] *oversampling pointer to a humidity oversampling buffer
 * @return     status code
 *             - 0 success
 *             - 1 get humidity oversampling failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_humidity_oversampling(bme688_handle_t *handle, bme688_oversampling_t *oversampling);

/**
 * @brief     set temperature oversampling
 * @param[in] *handle pointer to a bme688 handle structure
 * @param[in] oversampling temperature oversampling
 * @return    status code
 *            - 0 success
 *            - 1 set temperature oversampling failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme688_set_temperature_oversampling(bme688_handle_t *handle, bme688_oversampling_t oversampling);

/**
 * @brief      get temperature oversampling
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[out] *oversampling pointer to a oversampling buffer
 * @return     status code
 *             - 0 success
 *             - 1 get temperature oversampling failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_temperature_oversampling(bme688_handle_t *handle, bme688_oversampling_t *oversampling);

/**
 * @brief     set pressure oversampling
 * @param[in] *handle pointer to a bme688 handle structure
 * @param[in] oversampling pressure oversampling
 * @return    status code
 *            - 0 success
 *            - 1 set pressure oversampling failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme688_set_pressure_oversampling(bme688_handle_t *handle, bme688_oversampling_t oversampling);

/**
 * @brief      get pressure oversampling
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[out] *oversampling pointer to a oversampling buffer
 * @return     status code
 *             - 0 success
 *             - 1 get pressure oversampling failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_pressure_oversampling(bme688_handle_t *handle, bme688_oversampling_t *oversampling);

/**
 * @brief     set mode
 * @param[in] *handle pointer to a bme688 handle structure
 * @param[in] mode chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme688_set_mode(bme688_handle_t *handle, bme688_mode_t mode);

/**
 * @brief      get mode
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[out] *mode pointer to a mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_mode(bme688_handle_t *handle, bme688_mode_t *mode);

/**
 * @brief     set filter
 * @param[in] *handle pointer to a bme688 handle structure
 * @param[in] filter input filter
 * @return    status code
 *            - 0 success
 *            - 1 set filter failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme688_set_filter(bme688_handle_t *handle, bme688_filter_t filter);

/**
 * @brief      get filter
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[out] *filter pointer to a filter buffer
 * @return     status code
 *             - 0 success
 *             - 1 get filter failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_filter(bme688_handle_t *handle, bme688_filter_t *filter);

/**
 * @brief     set spi wire
 * @param[in] *handle pointer to a bme688 handle structure
 * @param[in] spi spi wire
 * @return    status code
 *            - 0 success
 *            - 1 set spi wire failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme688_set_spi_wire(bme688_handle_t *handle, bme688_spi_wire_t spi);

/**
 * @brief      get spi wire
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[out] *spi pointer to a spi wire buffer
 * @return     status code
 *             - 0 success
 *             - 1 get spi wire failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_spi_wire(bme688_handle_t *handle, bme688_spi_wire_t *spi);

/**
 * @brief     enable or disable heater off
 * @param[in] *handle pointer to a bme688 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set heater off failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme688_set_heater_off(bme688_handle_t *handle, bme688_bool_t enable);

/**
 * @brief      get heater off status
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get heater off failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_heater_off(bme688_handle_t *handle, bme688_bool_t *enable);

/**
 * @brief     enable or disable run gas
 * @param[in] *handle pointer to a bme688 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set run gas failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme688_set_run_gas(bme688_handle_t *handle, bme688_bool_t enable);

/**
 * @brief      get run gas status
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get run gas failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_run_gas(bme688_handle_t *handle, bme688_bool_t *enable);

/**
 * @brief     set heater profile
 * @param[in] *handle pointer to a bme688 handle structure
 * @param[in] profile heater profile
 * @return    status code
 *            - 0 success
 *            - 1 set heater profile failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme688_set_heater_profile(bme688_handle_t *handle, bme688_heater_profile_t profile);

/**
 * @brief      get heater profile
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[out] *profile pointer to a profile buffer
 * @return     status code
 *             - 0 success
 *             - 1 get heater profile failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_heater_profile(bme688_handle_t *handle, bme688_heater_profile_t *profile);

/**
 * @brief      convert the resistance heater to the register raw data
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  degree_celsius input degree celsius
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_resistance_heater_convert_to_register(bme688_handle_t *handle, float degree_celsius, uint8_t *reg);

/**
 * @brief      convert the idac heater to the register raw data
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  ma input ma
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_idac_heater_convert_to_register(bme688_handle_t *handle, float ma, uint8_t *reg);

/**
 * @brief      convert the register raw data to idac heater
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  reg register raw data
 * @param[out] *ma pointer to a ma buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_idac_heater_convert_to_data(bme688_handle_t *handle, uint8_t reg, float *ma);

/**
 * @brief      convert the gas wait to the register raw data
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  ms input ms
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 1 ms >= 0x0FC0
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_gas_wait_convert_to_register(bme688_handle_t *handle, uint16_t ms, uint8_t *reg);

/**
 * @brief      convert the gas wait shared to the register raw data
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  m input ms
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 1 ms >= 0x0783
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_gas_wait_shared_convert_to_register(bme688_handle_t *handle, float m, uint8_t *reg);

/**
 * @}
 */

/**
 * @defgroup bme688_extern_driver bme688 extern driver function
 * @brief    bme688 extern driver modules
 * @ingroup  bme688_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle pointer to a bme688 handle structure
 * @param[in] reg register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t bme688_set_reg(bme688_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle pointer to a bme688 handle structure
 * @param[in]  reg register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t bme688_get_reg(bme688_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
