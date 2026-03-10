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
 * @file      driver_bme688_parallel_test.c
 * @brief     driver bme688 parallel test source file
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

#include "driver_bme688_parallel_test.h"

static bme688_handle_t gs_handle;                                                    /**< bme688 handle */
static uint8_t gs_flag = 0;                                                          /**< local flag */
static const float gsc_heater_temp_prof[] = {320.0f, 100.0f, 330.0f, 350.0f, 
                                             400.0f, 150.0f, 200.0f, 250.0f, 
                                             300.0f, 350.0f};                        /**< store the heater temperature profile in degree celsius */
static const uint8_t gsc_heater_dur_prof[] = {5, 10, 5, 5, 5, 10, 5, 5, 5, 5};       /**< number of times tphg sequence needs to be repeated */
static const float gsc_shared_heater_dur = 140.0f;                                   /**< 140ms */

/**
 * @brief     interface receive callback
 * @param[in] status running status
 * @param[in] *data pointer to a parallel data address
 * @param[in] len data length
 * @note      none
 */
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
            (void)bme688_parallel_reset(&gs_handle);
            
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

/**
 * @brief     parallel test
 * @param[in] interface chip interface
 * @param[in] addr_pin chip address pin
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t bme688_parallel_test(bme688_interface_t interface, bme688_address_t addr_pin, uint32_t times)
{
    uint8_t res;
    bme688_parallel_config_t config;
    bme688_info_t info;
    
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
    DRIVER_BME688_LINK_RECEIVE_CALLBACK(&gs_handle, a_receive_callback);
    
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
    
    /* start parallel test */
    bme688_interface_debug_print("bme688: start parallel test.\n");
    
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
    
    /* parallel config */
    config.heater_temp_prof = gsc_heater_temp_prof;
    config.heater_dur_prof = gsc_heater_dur_prof;
    config.profile_len = 10;
    config.shared_heater_dur = gsc_shared_heater_dur;
    res = bme688_parallel_config(&gs_handle, &config);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: parallel config failed.\n");
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
    
    /* set parallel mode */
    res = bme688_set_mode(&gs_handle, BME688_MODE_PARALLEL);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set mode failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* init 0 */
    gs_flag = 0;
    
    /* loop all */
    while (1)
    {
        /* parallel progress */
        (void)bme688_parallel_progress(&gs_handle);
        
        /* delay */
        bme688_interface_delay_ms((uint32_t)gsc_shared_heater_dur);
        
        /* check flag */
        if (gs_flag != 0)
        {
            if (gs_flag == 2)
            {
                bme688_interface_debug_print("bme688: find error.\n");
                (void)bme688_deinit(&gs_handle); 
                
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
    }
    
    /* finish parallel test */
    bme688_interface_debug_print("bme688: finish parallel test.\n");
    (void)bme688_set_mode(&gs_handle, BME688_MODE_SLEEP);
    (void)bme688_set_heater_off(&gs_handle, BME688_BOOL_TRUE);
    (void)bme688_deinit(&gs_handle); 
    
    return 0;
}
