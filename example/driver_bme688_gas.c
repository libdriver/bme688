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
 * @file      driver_bme688_gas.c
 * @brief     driver bme688 gas source file
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

#include "driver_bme688_gas.h"

static bme688_handle_t gs_handle;        /**< bme688 handle */

/**
 * @brief     gas example init
 * @param[in] interface chip interface
 * @param[in] addr_pin chip address pin
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t bme688_gas_init(bme688_interface_t interface, bme688_address_t addr_pin)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_BME688_LINK_INIT(&gs_handle, bme688_handle_t); 
    DRIVER_BME688_LINK_IIC_INIT(&gs_handle, bme688_interface_iic_init);
    DRIVER_BME688_LINK_IIC_DEINIT(&gs_handle, bme688_interface_iic_deinit);
    DRIVER_BME688_LINK_IIC_READ(&gs_handle, bme688_interface_iic_read);
    DRIVER_BME688_LINK_IIC_WRITE(&gs_handle, bme688_interface_iic_write);
    DRIVER_BME688_LINK_SPI_INIT(&gs_handle, bme688_interface_spi_init);
    DRIVER_BME688_LINK_SPI_DEINIT(&gs_handle, bme688_interface_spi_deinit);
    DRIVER_BME688_LINK_SPI_READ(&gs_handle, bme688_interface_spi_read);
    DRIVER_BME688_LINK_SPI_WRITE(&gs_handle, bme688_interface_spi_write);
    DRIVER_BME688_LINK_DELAY_MS(&gs_handle, bme688_interface_delay_ms);
    DRIVER_BME688_LINK_DEBUG_PRINT(&gs_handle, bme688_interface_debug_print);
    DRIVER_BME688_LINK_RECEIVE_CALLBACK(&gs_handle, bme688_interface_receive_callback);
    
    /* set interface */
    res = bme688_set_interface(&gs_handle, interface);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set interface failed.\n");
       
        return 1;
    }
    
    /* set addr pin */
    res = bme688_set_addr_pin(&gs_handle, addr_pin);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set addr pin failed.\n");
       
        return 1;
    }
    
    /* bme688 init */
    res = bme688_init(&gs_handle);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: init failed.\n");
        
        return 1;
    }
    
    /* set default temperature oversampling */
    res = bme688_set_temperature_oversampling(&gs_handle, BME688_GAS_DEFAULT_TEMPERATURE_OVERSAMPLING);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set temperature oversampling failed.\n");
        (void)bme688_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default pressure oversampling */
    res = bme688_set_pressure_oversampling(&gs_handle, BME688_GAS_DEFAULT_PRESSURE_OVERSAMPLING);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set pressure oversampling failed.\n");
        (void)bme688_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default humidity oversampling */
    res = bme688_set_humidity_oversampling(&gs_handle, BME688_GAS_DEFAULT_HUMIDITY_OVERSAMPLING);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set humidity oversampling failed.\n");
        (void)bme688_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default filter */
    res = bme688_set_filter(&gs_handle, BME688_GAS_DEFAULT_FILTER);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set filter failed.\n");
        (void)bme688_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default spi wire */
    res = bme688_set_spi_wire(&gs_handle, BME688_GAS_DEFAULT_SPI_WIRE);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set spi wire failed.\n");
        (void)bme688_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable heater off */
    res = bme688_set_heater_off(&gs_handle, BME688_BOOL_FALSE);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set heat off failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable run gas */
    res = bme688_set_run_gas(&gs_handle, BME688_BOOL_TRUE);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set run gas failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set sleep mode */
    res = bme688_set_mode(&gs_handle, BME688_MODE_SLEEP);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set mode failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      gas example read
 * @param[in]  degree_celsius input degree celsius
 * @param[in]  gas_wait_ms gas wait ms
 * @param[in]  index convert index
 * @param[out] *temperature pointer to a converted temperature buffer
 * @param[out] *pressure pointer to a converted pressure buffer
 * @param[out] *humidity_percentage pointer to a converted humidity percentage buffer
 * @param[out] *ohms pointer to an ohms buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t bme688_gas_read(float degree_celsius, uint16_t gas_wait_ms, uint8_t index,
                        float *temperature, float *pressure, float *humidity_percentage, float *ohms)
{
    uint8_t res;
    uint8_t reg;
    uint32_t temperature_yaw;
    uint32_t pressure_yaw;
    uint32_t humidity_raw;
    uint16_t adc_raw;
    uint8_t adc_range;
    uint8_t index_check;
    bme688_heater_profile_t profile;
    
    /* set convert index */
    if (index == 0)
    {
        profile = BME688_HEATER_PROFILE_FORCED_STEP_0_PARALLEL_NO_STEP;
        
    }
    else if (index == 1)
    {
        profile = BME688_HEATER_PROFILE_FORCED_STEP_1_PARALLEL_STEP_0;
        
    }
    else if (index == 2)
    {
        profile = BME688_HEATER_PROFILE_FORCED_STEP_2_PARALLEL_STEP_0_1;
        
    }
    else if (index == 3)
    {
        profile = BME688_HEATER_PROFILE_FORCED_STEP_3_PARALLEL_STEP_0_2;
        
    }
    else if (index == 4)
    {
        profile = BME688_HEATER_PROFILE_FORCED_STEP_4_PARALLEL_STEP_0_3;
        
    }
    else if (index == 5)
    {
        profile = BME688_HEATER_PROFILE_FORCED_STEP_5_PARALLEL_STEP_0_4;
        
    }
    else if (index == 6)
    {
        profile = BME688_HEATER_PROFILE_FORCED_STEP_6_PARALLEL_STEP_0_5;
        
    }
    else if (index == 7)
    {
        profile = BME688_HEATER_PROFILE_FORCED_STEP_7_PARALLEL_STEP_0_6;
        
    }
    else if (index == 8)
    {
        profile = BME688_HEATER_PROFILE_FORCED_STEP_8_PARALLEL_STEP_0_7;
        
    }
    else if (index == 9)
    {
        profile = BME688_HEATER_PROFILE_FORCED_STEP_9_PARALLEL_STEP_0_8;
        
    }
    else
    {
        return 1;
    }
    
    /* set degree celsius */
    res = bme688_resistance_heater_convert_to_register(&gs_handle, degree_celsius, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set resistance heater */
    res = bme688_set_resistance_heater(&gs_handle, index, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set gas wait */
    res = bme688_gas_wait_convert_to_register(&gs_handle, gas_wait_ms, &reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set gas wait */
    res = bme688_set_gas_wait(&gs_handle, index, reg);
    if (res != 0)
    {
        return 1;
    }
    
    /* set heater profile */
    res = bme688_set_heater_profile(&gs_handle, profile);
    if (res != 0)
    {
        return 1;
    }
    
    /* read */
    if (bme688_read(&gs_handle, BME688_SECTION_0, (uint32_t *)&temperature_yaw, 
                    temperature, (uint32_t *)&pressure_yaw, pressure,
                   (uint32_t *)&humidity_raw, humidity_percentage,
                    &adc_raw, &adc_range, ohms, &index_check) != 0)
    {
        return 1;
    }
    
    /* check index */
    if (index_check != index)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  gas example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t bme688_gas_deinit(void)
{
    /* close bme688 */
    if (bme688_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}
