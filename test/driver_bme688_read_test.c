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
 * @file      driver_bme688_read_test.c
 * @brief     driver bme688 read test source file
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

#include "driver_bme688_read_test.h"

static bme688_handle_t gs_handle;        /**< bme688 handle */

/**
 * @brief     read test
 * @param[in] interface chip interface
 * @param[in] addr_pin chip address pin
 * @param[in] index input index
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t bme688_read_test(bme688_interface_t interface, bme688_address_t addr_pin, uint8_t index, uint32_t times)
{
    uint8_t res;
    uint8_t reg;
    uint32_t i;
    uint32_t temperature_raw;
    uint32_t pressure_raw;
    uint32_t humidity_raw;
    float temperature_c;
    float pressure_pa;
    float humidity_percentage;
    uint16_t adc_raw;
    uint8_t adc_range;
    float ohms;
    uint8_t index_output;
    bme688_info_t info;
    bme688_heater_profile_t profile;
    
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
    
    /* get bme688 info */
    res = bme688_info(&info);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print bme688 */
        bme688_interface_debug_print("bme688: chip is %s.\n", info.chip_name);
        bme688_interface_debug_print("bme688: manufacturer is %s.\n", info.manufacturer_name);
        bme688_interface_debug_print("bme688: interface is %s.\n", info.interface);
        bme688_interface_debug_print("bme688: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        bme688_interface_debug_print("bme688: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        bme688_interface_debug_print("bme688: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        bme688_interface_debug_print("bme688: max current is %0.2fmA.\n", info.max_current_ma);
        bme688_interface_debug_print("bme688: max temperature is %0.1fC.\n", info.temperature_max);
        bme688_interface_debug_print("bme688: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start read test */
    bme688_interface_debug_print("bme688: start read test.\n");
    
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
    
    /* init */
    res = bme688_init(&gs_handle);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: init failed.\n");
       
        return 1;
    }
    
    /* set spi wire4 */
    res = bme688_set_spi_wire(&gs_handle, BME688_SPI_WIRE_4);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set spi wire failed.\n");
        (void)bme688_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set humidity oversampling x1 */
    res = bme688_set_humidity_oversampling(&gs_handle, BME688_OVERSAMPLING_x1);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set humidity oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set temperature oversampling x2 */
    res = bme688_set_temperature_oversampling(&gs_handle, BME688_OVERSAMPLING_x2);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set temperature oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set pressure oversampling x16 */
    res = bme688_set_pressure_oversampling(&gs_handle, BME688_OVERSAMPLING_x16);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set pressure oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set filter 15 */
    res = bme688_set_filter(&gs_handle, BME688_FILTER_COEFF_15);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set filter failed.\n");
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
    
    /* 5.0mA */
    res = bme688_idac_heater_convert_to_register(&gs_handle, 5.0f, &reg);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: idac heat convert to register failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set idac heater */
    res = bme688_set_idac_heater(&gs_handle, index, reg);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set idac heat failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* 200C */
    res = bme688_resistance_heater_convert_to_register(&gs_handle, 200.0f, &reg);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: resistance heat convert to register failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set resistance heater */
    res = bme688_set_resistance_heater(&gs_handle, index, reg);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set resistance heat failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* 150ms */
    res = bme688_gas_wait_convert_to_register(&gs_handle, 150, &reg);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: gas wait convert to register failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    res = bme688_set_gas_wait(&gs_handle, index, reg);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set gas wait failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
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
        profile = BME688_HEATER_PROFILE_FORCED_STEP_9_PARALLEL_STEP_0_8;
    }
    
    /* set heater profile */
    res = bme688_set_heater_profile(&gs_handle, profile);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set heater profile failed.\n");
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
    
    /* delay 1000ms */
    bme688_interface_delay_ms(1000);
    
    /* loop */
    for (i = 0; i < times; i++)
    {
        /* read */
        res = bme688_read(&gs_handle, BME688_SECTION_0, 
                          &temperature_raw, &temperature_c, 
                          &pressure_raw, &pressure_pa,
                          &humidity_raw, &humidity_percentage,
                          &adc_raw, &adc_range, &ohms, &index_output);
        if (res != 0)
        {
            bme688_interface_debug_print("bme688: read failed.\n");
            (void)bme688_deinit(&gs_handle); 
            
            return 1;
        }
        
        /* delay 1000ms */
        bme688_interface_delay_ms(1000);
        
        /* output */
        bme688_interface_debug_print("bme688: temperature is %0.2fC.\n", temperature_c);
        bme688_interface_debug_print("bme688: pressure is %0.2fpa.\n", pressure_pa);
        bme688_interface_debug_print("bme688: humidity is %0.2f%%.\n", humidity_percentage);
        bme688_interface_debug_print("bme688: gas index is %d.\n", index_output);
        bme688_interface_debug_print("bme688: gas resistance is %0.2fohms.\n", ohms);
    }
    
    /* finish read test */
    bme688_interface_debug_print("bme688: finish read test.\n");
    (void)bme688_set_heater_off(&gs_handle, BME688_BOOL_TRUE);
    (void)bme688_deinit(&gs_handle); 
    
    return 0;
}
