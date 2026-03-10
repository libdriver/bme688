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
 * @file      driver_bme688_parallel.c
 * @brief     driver bme688 parallel source file
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

#include "driver_bme688_parallel.h"

static bme688_handle_t gs_handle;        /**< bme688 handle */

/**
 * @brief     parallel example init
 * @param[in] interface chip interface
 * @param[in] addr_pin chip address pin
 * @param[in] *config pointer to a parallel config structure
 * @param[in] *callback pointer to a callback address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t bme688_parallel_init(bme688_interface_t interface, bme688_address_t addr_pin,
                             bme688_parallel_config_t *config, 
                             void (*callback)(uint8_t status, bme688_parallel_data_t *data, uint8_t len))
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
    DRIVER_BME688_LINK_RECEIVE_CALLBACK(&gs_handle, callback);
    
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
    
    /* set sleep mode */
    res = bme688_set_mode(&gs_handle, BME688_MODE_SLEEP);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set mode failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default temperature oversampling */
    res = bme688_set_temperature_oversampling(&gs_handle, BME688_PARALLEL_DEFAULT_TEMPERATURE_OVERSAMPLING);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set temperature oversampling failed.\n");
        (void)bme688_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default pressure oversampling */
    res = bme688_set_pressure_oversampling(&gs_handle, BME688_PARALLEL_DEFAULT_PRESSURE_OVERSAMPLING);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set pressure oversampling failed.\n");
        (void)bme688_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default humidity oversampling */
    res = bme688_set_humidity_oversampling(&gs_handle, BME688_PARALLEL_DEFAULT_HUMIDITY_OVERSAMPLING);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set humidity oversampling failed.\n");
        (void)bme688_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default filter */
    res = bme688_set_filter(&gs_handle, BME688_PARALLEL_DEFAULT_FILTER);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set filter failed.\n");
        (void)bme688_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default spi wire */
    res = bme688_set_spi_wire(&gs_handle, BME688_PARALLEL_DEFAULT_SPI_WIRE);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set spi wire failed.\n");
        (void)bme688_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set parallel config */
    res = bme688_parallel_config(&gs_handle, config);
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
    
    return 0;
}

/**
 * @brief  parallel example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t bme688_parallel_deinit(void)
{
    /* set sleep mode */
    if (bme688_set_mode(&gs_handle, BME688_MODE_SLEEP)  != 0)
    {
        return 1;
    }
    
    /* heater off */
    if (bme688_set_heater_off(&gs_handle, BME688_BOOL_TRUE) != 0)
    {
        return 1;
    }
    
    /* close bme688 */
    if (bme688_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  parallel example server
 * @return status code
 *         - 0 success
 *         - 1 server failed
 * @note   none
 */
uint8_t bme688_parallel_server(void)
{
    if (bme688_parallel_progress(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  parallel example server reset
 * @return status code
 *         - 0 success
 *         - 1 reset failed
 * @note   none
 */
uint8_t bme688_parallel_server_reset(void)
{
    if (bme688_parallel_reset(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}
