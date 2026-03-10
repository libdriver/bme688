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
 * @file      driver_bme688_register_test.c
 * @brief     driver bme688 register test source file
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

#include "driver_bme688_register_test.h"
#include "stdlib.h"

static bme688_handle_t gs_handle;        /**< bme688 handle */

/**
 * @brief     register test
 * @param[in] interface chip interface
 * @param[in] addr_pin chip address pin
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t bme688_register_test(bme688_interface_t interface, bme688_address_t addr_pin)
{
    uint8_t res;
    uint8_t reg;
    uint8_t reg_check;
    uint8_t i;
    uint8_t index;
    uint16_t ms;
    float degree_celsius;
    float ma;
    float ma_check;
    bme688_info_t info;
    bme688_address_t addr_pin_check;
    bme688_interface_t interface_check;
    bme688_oversampling_t oversampling;
    bme688_mode_t mode;
    bme688_filter_t filter;
    bme688_spi_wire_t spi;
    bme688_bool_t enable;
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
    
    /* start register test */
    bme688_interface_debug_print("bme688: start register test.\n");
    
    /* bme688_set_interface/bme688_get_interface test */
    bme688_interface_debug_print("bme688: bme688_set_interface/bme688_get_interface test.\n");
    
    /* set interface */
    res = bme688_set_interface(&gs_handle, BME688_INTERFACE_SPI);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set interface failed.\n");
       
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set interface spi.\n");
    
    /* get interface */
    res = bme688_get_interface(&gs_handle, &interface_check);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get interface failed.\n");
       
        return 1;
    }
    bme688_interface_debug_print("bme688: check interface %s.\n", interface_check == BME688_INTERFACE_SPI ? "ok" : "error");
    
    /* set interface */
    res = bme688_set_interface(&gs_handle, BME688_INTERFACE_IIC);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set interface failed.\n");
       
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set interface iic.\n");
    
    /* get interface */
    res = bme688_get_interface(&gs_handle, &interface_check);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get interface failed.\n");
       
        return 1;
    }
    bme688_interface_debug_print("bme688: check interface %s.\n", interface_check == BME688_INTERFACE_IIC ? "ok" : "error");
    
    /* bme688_set_addr_pin/bme688_get_addr_pin test */
    bme688_interface_debug_print("bme688: bme688_set_addr_pin/bme688_get_addr_pin test.\n");
    
    /* set addr pin low */
    res = bme688_set_addr_pin(&gs_handle, BME688_ADDRESS_ADO_LOW);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set addr pin failed.\n");
       
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set addr pin low.\n");
    
    /* get addr pin */
    res = bme688_get_addr_pin(&gs_handle, &addr_pin_check);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get addr pin failed.\n");
       
        return 1;
    }
    bme688_interface_debug_print("bme688: check addr pin %s.\n", addr_pin_check == BME688_ADDRESS_ADO_LOW ? "ok" : "error");
    
    /* set addr pin high */
    res = bme688_set_addr_pin(&gs_handle, BME688_ADDRESS_ADO_HIGH);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set addr pin failed.\n");
       
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set addr pin high.\n");
    
    /* get addr pin */
    res = bme688_get_addr_pin(&gs_handle, &addr_pin_check);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get addr pin failed.\n");
       
        return 1;
    }
    bme688_interface_debug_print("bme688: check addr pin %s.\n", addr_pin_check == BME688_ADDRESS_ADO_HIGH ? "ok" : "error");
    
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
    
    /* bme688_set_temperature_oversampling/bme688_get_temperature_oversampling test */
    bme688_interface_debug_print("bme688: bme688_set_temperature_oversampling/bme688_get_temperature_oversampling test.\n");
    
    /* set temperature oversampling skip */
    res = bme688_set_temperature_oversampling(&gs_handle, BME688_OVERSAMPLING_SKIP);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set temperature oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set temperature oversampling skip.\n");
    
    /* get temperature oversampling */
    res = bme688_get_temperature_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get temperature oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check temperature oversampling %s.\n", oversampling == BME688_OVERSAMPLING_SKIP ? "ok" : "error");
    
    /* set temperature oversampling x1 */
    res = bme688_set_temperature_oversampling(&gs_handle, BME688_OVERSAMPLING_x1);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set temperature oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set temperature oversampling x1.\n");
    
    /* get temperature oversampling */
    res = bme688_get_temperature_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get temperature oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check temperature oversampling %s.\n", oversampling == BME688_OVERSAMPLING_x1 ? "ok" : "error");
    
    /* set temperature oversampling x2 */
    res = bme688_set_temperature_oversampling(&gs_handle, BME688_OVERSAMPLING_x2);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set temperature oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set temperature oversampling x2.\n");
    
    /* get temperature oversampling */
    res = bme688_get_temperature_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get temperature oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check temperature oversampling %s.\n", oversampling == BME688_OVERSAMPLING_x2 ? "ok" : "error");
    
    /* set temperature oversampling x4 */
    res = bme688_set_temperature_oversampling(&gs_handle, BME688_OVERSAMPLING_x4);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set temperature oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set temperature oversampling x4.\n");
    
    /* get temperature oversampling */
    res = bme688_get_temperature_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get temperature oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check temperature oversampling %s.\n", oversampling == BME688_OVERSAMPLING_x4 ? "ok" : "error");
    
    /* set temperature oversampling x8 */
    res = bme688_set_temperature_oversampling(&gs_handle, BME688_OVERSAMPLING_x8);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set temperature oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set temperature oversampling x8.\n");
    
    /* get temperature oversampling */
    res = bme688_get_temperature_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get temperature oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check temperature oversampling %s.\n", oversampling == BME688_OVERSAMPLING_x8 ? "ok" : "error");
    
    /* set temperature oversampling x16 */
    res = bme688_set_temperature_oversampling(&gs_handle, BME688_OVERSAMPLING_x16);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set temperature oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set temperature oversampling x16.\n");
    
    /* get temperature oversampling */
    res = bme688_get_temperature_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get temperature oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check temperature oversampling %s.\n", oversampling == BME688_OVERSAMPLING_x16 ? "ok" : "error");
    
    /* bme688_set_pressure_oversampling/bme688_get_pressure_oversampling test */
    bme688_interface_debug_print("bme688: bme688_set_pressure_oversampling/bme688_get_pressure_oversampling test.\n");
    
    /* set pressure oversampling skip */
    res = bme688_set_pressure_oversampling(&gs_handle, BME688_OVERSAMPLING_SKIP);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set pressure oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set pressure oversampling skip.\n");
    
    /* get pressure oversampling */
    res = bme688_get_pressure_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get pressure oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check pressure oversampling %s.\n", oversampling == BME688_OVERSAMPLING_SKIP ? "ok" : "error");
    
    /* set pressure oversampling x1 */
    res = bme688_set_pressure_oversampling(&gs_handle, BME688_OVERSAMPLING_x1);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set pressure oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set pressure oversampling x1.\n");
    
    /* get pressure oversampling */
    res = bme688_get_pressure_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get pressure oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check pressure oversampling %s.\n", oversampling == BME688_OVERSAMPLING_x1 ? "ok" : "error");
    
    /* set pressure oversampling x2 */
    res = bme688_set_pressure_oversampling(&gs_handle, BME688_OVERSAMPLING_x2);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set pressure oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set pressure oversampling x2.\n");
    
    /* get pressure oversampling */
    res = bme688_get_pressure_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get pressure oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check pressure oversampling %s.\n", oversampling == BME688_OVERSAMPLING_x2 ? "ok" : "error");
    
    /* set pressure oversampling x4 */
    res = bme688_set_pressure_oversampling(&gs_handle, BME688_OVERSAMPLING_x4);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set pressure oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set pressure oversampling x4.\n");
    
    /* get pressure oversampling */
    res = bme688_get_pressure_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get pressure oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check pressure oversampling %s.\n", oversampling == BME688_OVERSAMPLING_x4 ? "ok" : "error");
    
    /* set pressure oversampling x8 */
    res = bme688_set_pressure_oversampling(&gs_handle, BME688_OVERSAMPLING_x8);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set pressure oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set pressure oversampling x8.\n");
    
    /* get pressure oversampling */
    res = bme688_get_pressure_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get pressure oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check pressure oversampling %s.\n", oversampling == BME688_OVERSAMPLING_x8 ? "ok" : "error");
    
    /* set pressure oversampling x16 */
    res = bme688_set_pressure_oversampling(&gs_handle, BME688_OVERSAMPLING_x16);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set pressure oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set pressure oversampling x16.\n");
    
    /* get pressure oversampling */
    res = bme688_get_pressure_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get pressure oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check pressure oversampling %s.\n", oversampling == BME688_OVERSAMPLING_x16 ? "ok" : "error");
    
    /* bme688_set_humidity_oversampling/bme688_get_humidity_oversampling test */
    bme688_interface_debug_print("bme688: bme688_set_humidity_oversampling/bme688_get_humidity_oversampling test.\n");
    
    /* set humidity oversampling skip */
    res = bme688_set_humidity_oversampling(&gs_handle, BME688_OVERSAMPLING_SKIP);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set humidity oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set humidity oversampling skip.\n");
    
    /* get humidity oversampling */
    res = bme688_get_humidity_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get humidity oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check humidity oversampling %s.\n", oversampling == BME688_OVERSAMPLING_SKIP ? "ok" : "error");
    
    /* set humidity oversampling x1 */
    res = bme688_set_humidity_oversampling(&gs_handle, BME688_OVERSAMPLING_x1);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set humidity oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set humidity oversampling x1.\n");
    
    /* get humidity oversampling */
    res = bme688_get_humidity_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get humidity oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check humidity oversampling %s.\n", oversampling == BME688_OVERSAMPLING_x1 ? "ok" : "error");
    
    /* set humidity oversampling x2 */
    res = bme688_set_humidity_oversampling(&gs_handle, BME688_OVERSAMPLING_x2);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set humidity oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set humidity oversampling x2.\n");
    
    /* get humidity oversampling */
    res = bme688_get_humidity_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get humidity oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check humidity oversampling %s.\n", oversampling == BME688_OVERSAMPLING_x2 ? "ok" : "error");
    
    /* set humidity oversampling x4 */
    res = bme688_set_humidity_oversampling(&gs_handle, BME688_OVERSAMPLING_x4);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set humidity oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set humidity oversampling x4.\n");
    
    /* get humidity oversampling */
    res = bme688_get_humidity_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get humidity oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check humidity oversampling %s.\n", oversampling == BME688_OVERSAMPLING_x4 ? "ok" : "error");
    
    /* set humidity oversampling x8 */
    res = bme688_set_humidity_oversampling(&gs_handle, BME688_OVERSAMPLING_x8);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set humidity oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set humidity oversampling x8.\n");
    
    /* get humidity oversampling */
    res = bme688_get_humidity_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get humidity oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check humidity oversampling %s.\n", oversampling == BME688_OVERSAMPLING_x8 ? "ok" : "error");
    
    /* set humidity oversampling x16 */
    res = bme688_set_humidity_oversampling(&gs_handle, BME688_OVERSAMPLING_x16);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set humidity oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set humidity oversampling x16.\n");
    
    /* get humidity oversampling */
    res = bme688_get_humidity_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get humidity oversampling failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check humidity oversampling %s.\n", oversampling == BME688_OVERSAMPLING_x16 ? "ok" : "error");
    
    /* bme688_set_mode/bme688_get_mode test */
    bme688_interface_debug_print("bme688: bme688_set_mode/bme688_get_mode test.\n");
    
    /* set mode forced */
    res = bme688_set_mode(&gs_handle, BME688_MODE_FORCED);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set mode failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set mode forced.\n");
    
    res = bme688_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get mode failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check mode %s.\n", mode == BME688_MODE_FORCED ? "ok" : "error");
    
    /* set mode parallel */
    res = bme688_set_mode(&gs_handle, BME688_MODE_PARALLEL);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set mode failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set mode parallel.\n");
    
    res = bme688_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get mode failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check mode %s.\n", mode == BME688_MODE_PARALLEL ? "ok" : "error");
    
    /* delay 200ms */
    bme688_interface_delay_ms(200);
    
    /* set mode sleep */
    res = bme688_set_mode(&gs_handle, BME688_MODE_SLEEP);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set mode failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set mode sleep.\n");
    
    res = bme688_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get mode failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check mode %s.\n", mode == BME688_MODE_SLEEP ? "ok" : "error");
    
    /* bme688_set_filter/bme688_get_filter test */
    bme688_interface_debug_print("bme688: bme688_set_filter/bme688_get_filter test.\n");
    
    /* set filter off */
    res = bme688_set_filter(&gs_handle, BME688_FILTER_OFF);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set filter failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set filter off.\n");
    
    /* get filter */
    res = bme688_get_filter(&gs_handle, &filter);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get filter failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check filter %s.\n", filter == BME688_FILTER_OFF ? "ok" : "error");
    
    /* set filter coeff 1 */
    res = bme688_set_filter(&gs_handle, BME688_FILTER_COEFF_1);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set filter failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set filter coeff 1.\n");
    
    /* get filter */
    res = bme688_get_filter(&gs_handle, &filter);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get filter failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check filter %s.\n", filter == BME688_FILTER_COEFF_1 ? "ok" : "error");
    
    /* set filter coeff 3 */
    res = bme688_set_filter(&gs_handle, BME688_FILTER_COEFF_3);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set filter failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set filter coeff 3.\n");
    
    /* get filter */
    res = bme688_get_filter(&gs_handle, &filter);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get filter failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check filter %s.\n", filter == BME688_FILTER_COEFF_3 ? "ok" : "error");
    
    /* set filter coeff 7 */
    res = bme688_set_filter(&gs_handle, BME688_FILTER_COEFF_7);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set filter failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set filter coeff 7.\n");
    
    /* get filter */
    res = bme688_get_filter(&gs_handle, &filter);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get filter failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check filter %s.\n", filter == BME688_FILTER_COEFF_7 ? "ok" : "error");
    
    /* set filter coeff 15 */
    res = bme688_set_filter(&gs_handle, BME688_FILTER_COEFF_15);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set filter failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set filter coeff 15.\n");
    
    /* get filter */
    res = bme688_get_filter(&gs_handle, &filter);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get filter failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check filter %s.\n", filter == BME688_FILTER_COEFF_15 ? "ok" : "error");
    
    /* set filter coeff 31 */
    res = bme688_set_filter(&gs_handle, BME688_FILTER_COEFF_31);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set filter failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set filter coeff 31.\n");
    
    /* get filter */
    res = bme688_get_filter(&gs_handle, &filter);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get filter failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check filter %s.\n", filter == BME688_FILTER_COEFF_31 ? "ok" : "error");
    
    /* set filter coeff 63 */
    res = bme688_set_filter(&gs_handle, BME688_FILTER_COEFF_63);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set filter failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set filter coeff 63.\n");
    
    /* get filter */
    res = bme688_get_filter(&gs_handle, &filter);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get filter failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check filter %s.\n", filter == BME688_FILTER_COEFF_63 ? "ok" : "error");
    
    /* set filter coeff 127 */
    res = bme688_set_filter(&gs_handle, BME688_FILTER_COEFF_127);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set filter failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme688_interface_debug_print("bme688: set filter coeff 127.\n");
    
    /* get filter */
    res = bme688_get_filter(&gs_handle, &filter);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get filter failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check filter %s.\n", filter == BME688_FILTER_COEFF_127 ? "ok" : "error");
    
    /* if iic interface */
    if (interface == BME688_INTERFACE_IIC)
    {
        /* bme688_set_spi_wire/bme688_get_spi_wire test */
        bme688_interface_debug_print("bme688: bme688_set_spi_wire/bme688_get_spi_wire test.\n");
        
        /* set spi wire3 */
        res = bme688_set_spi_wire(&gs_handle, BME688_SPI_WIRE_3);
        if (res != 0)
        {
            bme688_interface_debug_print("bme688: set spi wire failed.\n");
            (void)bme688_deinit(&gs_handle); 
            
            return 1;
        }
        
        /* output */
        bme688_interface_debug_print("bme688: set spi wire 3.\n");
        
        /* get spi wire */
        res = bme688_get_spi_wire(&gs_handle, &spi);
        if (res != 0)
        {
            bme688_interface_debug_print("bme688: get spi wire failed.\n");
            (void)bme688_deinit(&gs_handle); 
            
            return 1;
        }
        bme688_interface_debug_print("bme688: check spi wire %s.\n", spi == BME688_SPI_WIRE_3 ? "ok" : "error");
        
        /* set spi wire4 */
        res = bme688_set_spi_wire(&gs_handle, BME688_SPI_WIRE_4);
        if (res != 0)
        {
            bme688_interface_debug_print("bme688: set spi wire failed.\n");
            (void)bme688_deinit(&gs_handle); 
            
            return 1;
        }
        
        /* output */
        bme688_interface_debug_print("bme688: set spi wire 4.\n");
        
        /* get spi wire */
        res = bme688_get_spi_wire(&gs_handle, &spi);
        if (res != 0)
        {
            bme688_interface_debug_print("bme688: get spi wire failed.\n");
            (void)bme688_deinit(&gs_handle); 
            
            return 1;
        }
        bme688_interface_debug_print("bme688: check spi wire %s.\n", spi == BME688_SPI_WIRE_4 ? "ok" : "error");
    }
    
    /* bme688_set_spi_wire_3_data_interrupt/bme688_get_spi_wire_3_data_interrupt test */
    bme688_interface_debug_print("bme688: bme688_set_spi_wire_3_data_interrupt/bme688_get_spi_wire_3_data_interrupt test.\n");
    
    /* enable spi wire 3 data interrupt */
    res = bme688_set_spi_wire_3_data_interrupt(&gs_handle, BME688_BOOL_TRUE);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set spi wire 3 data interrupt failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: enable spi wire 3 data interrupt.\n");
    res = bme688_get_spi_wire_3_data_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get spi wire 3 data interrupt failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check spi wire 3 data interrupt %s.\n", enable == BME688_BOOL_TRUE ? "ok" : "error");
    
    /* disable spi wire 3 data interrupt */
    res = bme688_set_spi_wire_3_data_interrupt(&gs_handle, BME688_BOOL_FALSE);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set spi wire 3 data interrupt failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: disable spi wire 3 data interrupt.\n");
    res = bme688_get_spi_wire_3_data_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get spi wire 3 data interrupt failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check spi wire 3 data interrupt %s.\n", enable == BME688_BOOL_FALSE ? "ok" : "error");
    
    for (i = 0; i < 3; i++)
    {
        bme688_section_t section;
        
        /* set section */
        if (i == 0)
        {
            section = BME688_SECTION_0;
        }
        else if (i == 1)
        {
            section = BME688_SECTION_1;
        }
        else
        {
            section = BME688_SECTION_2;
        }
        
        /* set section */
        bme688_interface_debug_print("bme688: set section %d.\n", i);
        
        /* bme688_get_new_data_status test */
        bme688_interface_debug_print("bme688: bme688_get_new_data_status test.\n");
        
        /* get new data status */
        res = bme688_get_new_data_status(&gs_handle, section, &enable);
        if (res != 0)
        {
            bme688_interface_debug_print("bme688: get new data status failed.\n");
            (void)bme688_deinit(&gs_handle); 
            
            return 1;
        }
        bme688_interface_debug_print("bme688: new data status is %s.\n", enable == BME688_BOOL_TRUE ? "true" : "false");
        
        /* bme688_get_gas_measuring_status test */
        bme688_interface_debug_print("bme688: bme688_get_gas_measuring_status test.\n");
        
        /* get gas measuring status */
        res = bme688_get_gas_measuring_status(&gs_handle, section, &enable);
        if (res != 0)
        {
            bme688_interface_debug_print("bme688: get gas measuring status failed.\n");
            (void)bme688_deinit(&gs_handle); 
            
            return 1;
        }
        bme688_interface_debug_print("bme688: gas measuring status is %s.\n", enable == BME688_BOOL_TRUE ? "true" : "false");
        
        /* bme688_get_measuring_status test */
        bme688_interface_debug_print("bme688: bme688_get_measuring_status test.\n");
        
        /* get measuring status */
        res = bme688_get_measuring_status(&gs_handle, section, &enable);
        if (res != 0)
        {
            bme688_interface_debug_print("bme688: get measuring status failed.\n");
            (void)bme688_deinit(&gs_handle); 
            
            return 1;
        }
        bme688_interface_debug_print("bme688: get measuring status is %s.\n", enable == BME688_BOOL_TRUE ? "true" : "false");
        
        /* bme688_get_gas_measuring_index test */
        bme688_interface_debug_print("bme688: bme688_get_gas_measuring_index test.\n");
        
        /* get gas measuring index */
        res = bme688_get_gas_measuring_index(&gs_handle, section, &index);
        if (res != 0)
        {
            bme688_interface_debug_print("bme688: get gas measuring index failed.\n");
            (void)bme688_deinit(&gs_handle); 
            
            return 1;
        }
        bme688_interface_debug_print("bme688: gas measuring index is 0x%02X.\n", index);
        
        /* bme688_get_gas_valid_status test */
        bme688_interface_debug_print("bme688: bme688_get_gas_valid_status test.\n");
        
        /* get gas valid status */
        res = bme688_get_gas_valid_status(&gs_handle, section, &enable);
        if (res != 0)
        {
            bme688_interface_debug_print("bme688: get gas valid status failed.\n");
            (void)bme688_deinit(&gs_handle); 
            
            return 1;
        }
        bme688_interface_debug_print("bme688: gas valid status is %s.\n", enable == BME688_BOOL_TRUE ? "true" : "false");
        
        /* bme688_get_heater_stability_status test */
        bme688_interface_debug_print("bme688: bme688_get_heater_stability_status test.\n");
        
        /* get heater stability status */
        res = bme688_get_heater_stability_status(&gs_handle, section, &enable);
        if (res != 0)
        {
            bme688_interface_debug_print("bme688: get heater stability status failed.\n");
            (void)bme688_deinit(&gs_handle); 
            
            return 1;
        }
        bme688_interface_debug_print("bme688: heater stability status is %s.\n", enable == BME688_BOOL_TRUE ? "true" : "false");
    }
    
    /* bme688_set_heater_off/bme688_get_heater_off test */
    bme688_interface_debug_print("bme688: bme688_set_heater_off/bme688_get_heater_off test.\n");
    
    /* disable heater off */
    res = bme688_set_heater_off(&gs_handle, BME688_BOOL_FALSE);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set heater off failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: disable heater off.\n");
    res = bme688_get_heater_off(&gs_handle, &enable);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get heater off failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check heater off %s.\n", enable == BME688_BOOL_FALSE ? "ok" : "error");
    
    /* enable heater off */
    res = bme688_set_heater_off(&gs_handle, BME688_BOOL_TRUE);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set heater off failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: enable heater off.\n");
    res = bme688_get_heater_off(&gs_handle, &enable);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get heater off failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check heater off %s.\n", enable == BME688_BOOL_TRUE ? "ok" : "error");
    
    /* bme688_set_run_gas/bme688_get_run_gas test */
    bme688_interface_debug_print("bme688: bme688_set_run_gas/bme688_get_run_gas test.\n");
    
    /* enable run gas */
    res = bme688_set_run_gas(&gs_handle, BME688_BOOL_TRUE);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set run gas failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: enable run gas.\n");
    res = bme688_get_run_gas(&gs_handle, &enable);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get run gas failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check run gas %s.\n", enable == BME688_BOOL_TRUE ? "ok" : "error");
    
    /* disable run gas */
    res = bme688_set_run_gas(&gs_handle, BME688_BOOL_FALSE);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set run gas failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: disable run gas.\n");
    res = bme688_get_run_gas(&gs_handle, &enable);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get run gas failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check run gas %s.\n", enable == BME688_BOOL_FALSE ? "ok" : "error");
    
    /* bme688_set_heater_profile/bme688_get_heater_profile test */
    bme688_interface_debug_print("bme688: bme688_set_heater_profile/bme688_get_heater_profile test.\n");
    
    /* set heater profile */
    res = bme688_set_heater_profile(&gs_handle, BME688_HEATER_PROFILE_FORCED_STEP_0_PARALLEL_NO_STEP);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: set heater profile forced mode step 0, parallel mode no step.\n");
    res = bme688_get_heater_profile(&gs_handle, &profile);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check heater profile %s.\n", profile == BME688_HEATER_PROFILE_FORCED_STEP_0_PARALLEL_NO_STEP ? "ok" : "error");
    
    /* set heater profile */
    res = bme688_set_heater_profile(&gs_handle, BME688_HEATER_PROFILE_FORCED_STEP_1_PARALLEL_STEP_0);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: set heater profile forced mode step 1, parallel mode step 0.\n");
    res = bme688_get_heater_profile(&gs_handle, &profile);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check heater profile %s.\n", profile == BME688_HEATER_PROFILE_FORCED_STEP_1_PARALLEL_STEP_0 ? "ok" : "error");
    
    /* set heater profile */
    res = bme688_set_heater_profile(&gs_handle, BME688_HEATER_PROFILE_FORCED_STEP_2_PARALLEL_STEP_0_1);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: set heater profile forced mode step 2, parallel mode step 0 - 1.\n");
    res = bme688_get_heater_profile(&gs_handle, &profile);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check heater profile %s.\n", profile == BME688_HEATER_PROFILE_FORCED_STEP_2_PARALLEL_STEP_0_1 ? "ok" : "error");
    
    /* set heater profile */
    res = bme688_set_heater_profile(&gs_handle, BME688_HEATER_PROFILE_FORCED_STEP_3_PARALLEL_STEP_0_2);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: set heater profile forced mode step 3, parallel mode step 0 - 2.\n");
    res = bme688_get_heater_profile(&gs_handle, &profile);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check heater profile %s.\n", profile == BME688_HEATER_PROFILE_FORCED_STEP_3_PARALLEL_STEP_0_2 ? "ok" : "error");
    
    /* set heater profile */
    res = bme688_set_heater_profile(&gs_handle, BME688_HEATER_PROFILE_FORCED_STEP_4_PARALLEL_STEP_0_3);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: set heater profile forced mode step 4, parallel mode step 0 - 3.\n");
    res = bme688_get_heater_profile(&gs_handle, &profile);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check heater profile %s.\n", profile == BME688_HEATER_PROFILE_FORCED_STEP_4_PARALLEL_STEP_0_3 ? "ok" : "error");
    
    /* set heater profile */
    res = bme688_set_heater_profile(&gs_handle, BME688_HEATER_PROFILE_FORCED_STEP_5_PARALLEL_STEP_0_4);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: set heater profile forced mode step 5, parallel mode step 0 - 4.\n");
    res = bme688_get_heater_profile(&gs_handle, &profile);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check heater profile %s.\n", profile == BME688_HEATER_PROFILE_FORCED_STEP_5_PARALLEL_STEP_0_4 ? "ok" : "error");
    
    /* set heater profile */
    res = bme688_set_heater_profile(&gs_handle, BME688_HEATER_PROFILE_FORCED_STEP_6_PARALLEL_STEP_0_5);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: set heater profile forced mode step 6, parallel mode step 0 - 5.\n");
    res = bme688_get_heater_profile(&gs_handle, &profile);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check heater profile %s.\n", profile == BME688_HEATER_PROFILE_FORCED_STEP_6_PARALLEL_STEP_0_5 ? "ok" : "error");
    
    /* set heater profile */
    res = bme688_set_heater_profile(&gs_handle, BME688_HEATER_PROFILE_FORCED_STEP_7_PARALLEL_STEP_0_6);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: set heater profile forced mode step 7, parallel mode step 0 - 6.\n");
    res = bme688_get_heater_profile(&gs_handle, &profile);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check heater profile %s.\n", profile == BME688_HEATER_PROFILE_FORCED_STEP_7_PARALLEL_STEP_0_6 ? "ok" : "error");
    
    /* set heater profile */
    res = bme688_set_heater_profile(&gs_handle, BME688_HEATER_PROFILE_FORCED_STEP_8_PARALLEL_STEP_0_7);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: set heater profile forced mode step 8, parallel mode step 0 - 7.\n");
    res = bme688_get_heater_profile(&gs_handle, &profile);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check heater profile %s.\n", profile == BME688_HEATER_PROFILE_FORCED_STEP_8_PARALLEL_STEP_0_7 ? "ok" : "error");
    
    /* set heater profile */
    res = bme688_set_heater_profile(&gs_handle, BME688_HEATER_PROFILE_FORCED_STEP_9_PARALLEL_STEP_0_8);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: set heater profile forced mode step 9, parallel mode step 0 - 8.\n");
    res = bme688_get_heater_profile(&gs_handle, &profile);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check heater profile %s.\n", profile == BME688_HEATER_PROFILE_FORCED_STEP_9_PARALLEL_STEP_0_8 ? "ok" : "error");
    
    /* set heater profile */
    res = bme688_set_heater_profile(&gs_handle, BME688_HEATER_PROFILE_FORCED_NO_STEP_PARALLEL_STEP_0_9);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: set heater profile forced mode no step, parallel mode step 0 - 9.\n");
    res = bme688_get_heater_profile(&gs_handle, &profile);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get heater profile failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check heater profile %s.\n", profile == BME688_HEATER_PROFILE_FORCED_NO_STEP_PARALLEL_STEP_0_9 ? "ok" : "error");
    
    /* bme688_set_gas_wait_shared/bme688_get_gas_wait_shared test */
    bme688_interface_debug_print("bme688: bme688_set_gas_wait_shared/bme688_get_gas_wait_shared test.\n");
    
    reg = rand() % 0xFF;
    res = bme688_set_gas_wait_shared(&gs_handle, reg);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: set gas wait shared failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: set gas wait shared 0x%02X.\n", reg);
    res = bme688_get_gas_wait_shared(&gs_handle, &reg_check);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: get gas wait shared failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check gas wait shared %s.\n", reg == reg_check ? "ok" : "error");
    
    /* bme688_set_idac_heater/bme688_get_idac_heater test */
    bme688_interface_debug_print("bme688: bme688_set_idac_heater/bme688_get_idac_heater test.\n");
    
    for (i = 0; i < 10; i++)
    {
        reg = rand() % 0xFFU;
        res = bme688_set_idac_heater(&gs_handle, i, reg);
        if (res != 0)
        {
            bme688_interface_debug_print("bme688: set idac heater failed.\n");
            (void)bme688_deinit(&gs_handle); 
            
            return 1;
        }
        bme688_interface_debug_print("bme688: set index %d idac heater 0x%02X.\n", i, reg);
        res = bme688_get_idac_heater(&gs_handle, i, &reg_check);
        if (res != 0)
        {
            bme688_interface_debug_print("bme688: get idac heater failed.\n");
            (void)bme688_deinit(&gs_handle); 
            
            return 1;
        }
        bme688_interface_debug_print("bme688: check idac heater %s.\n", reg == reg_check ? "ok" : "error");
    }
    
    /* bme688_set_resistance_heater/bme688_get_resistance_heater test */
    bme688_interface_debug_print("bme688: bme688_set_resistance_heater/bme688_get_resistance_heater test.\n");
    
    for (i = 0; i < 10; i++)
    {
        reg = rand() % 0xFFU;
        res = bme688_set_resistance_heater(&gs_handle, i, reg);
        if (res != 0)
        {
            bme688_interface_debug_print("bme688: set resistance heater failed.\n");
            (void)bme688_deinit(&gs_handle); 
            
            return 1;
        }
        bme688_interface_debug_print("bme688: set index %d resistance heater 0x%02X.\n", i, reg);
        res = bme688_get_resistance_heater(&gs_handle, i, &reg_check);
        if (res != 0)
        {
            bme688_interface_debug_print("bme688: get resistance heater failed.\n");
            (void)bme688_deinit(&gs_handle); 
            
            return 1;
        }
        bme688_interface_debug_print("bme688: check resistance heater %s.\n", reg == reg_check ? "ok" : "error");
    }
    
    /* bme688_set_gas_wait/bme688_get_gas_wait test */
    bme688_interface_debug_print("bme688: bme688_set_gas_wait/bme688_get_gas_wait test.\n");
    
    for (i = 0; i < 10; i++)
    {
        reg = rand() % 0xFFU;
        res = bme688_set_gas_wait(&gs_handle, i, reg);
        if (res != 0)
        {
            bme688_interface_debug_print("bme688: set gas wait failed.\n");
            (void)bme688_deinit(&gs_handle); 
            
            return 1;
        }
        bme688_interface_debug_print("bme688: set index %d gas wait 0x%02X.\n", i, reg);
        res = bme688_get_gas_wait(&gs_handle, i, &reg_check);
        if (res != 0)
        {
            bme688_interface_debug_print("bme688: get gas wait failed.\n");
            (void)bme688_deinit(&gs_handle); 
            
            return 1;
        }
        bme688_interface_debug_print("bme688: check gas wait %s.\n", reg == reg_check ? "ok" : "error");
    }
    
    /* bme688_resistance_heater_convert_to_register test */
    bme688_interface_debug_print("bme688: bme688_resistance_heater_convert_to_register test.\n");
    
    degree_celsius = (float)(rand() % 30000) / 100;
    res = bme688_resistance_heater_convert_to_register(&gs_handle, degree_celsius, &reg);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: resistance heater convert to register failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: %0.2fC convert to register 0x%02X.\n", degree_celsius, reg);
    
    /* bme688_gas_wait_convert_to_register test */
    bme688_interface_debug_print("bme688: bme688_gas_wait_convert_to_register test.\n");
    
    ms = rand() % 100 + 50;
    res = bme688_gas_wait_convert_to_register(&gs_handle, ms, &reg);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: gas wait convert to register failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: %dms convert to register 0x%02X.\n", ms, reg);
    
    /* bme688_idac_heater_convert_to_register/bme688_idac_heater_convert_to_data test */
    bme688_interface_debug_print("bme688: bme688_idac_heater_convert_to_register/bme688_idac_heater_convert_to_data test.\n");
    
    ma = (float)(rand() % 100) / 10.0f;
    bme688_interface_debug_print("bme688: idac heater ma before is %0.2fmA.\n", ma);
    res = bme688_idac_heater_convert_to_register(&gs_handle, ma, &reg);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: idac heater convert to register failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: idac heater reg is 0x%02X.\n", reg);
    res = bme688_idac_heater_convert_to_data(&gs_handle, reg, &ma_check);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: idac heater convert to data failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: idac heater ma after is %0.2fmA.\n", ma_check);
    
    /* bme688_gas_wait_shared_convert_to_register test */
    bme688_interface_debug_print("bme688: bme688_gas_wait_shared_convert_to_register test.\n");
    
    ms = rand() % 100 + 50;
    res = bme688_gas_wait_shared_convert_to_register(&gs_handle, ma, &reg);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: gas wait shared convert to register failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: %dms convert to register 0x%02X.\n", ms, reg);
    
    /* bme688_soft_reset test */
    bme688_interface_debug_print("bme688: bme688_soft_reset test.\n");
    
    /* soft reset */
    res = bme688_soft_reset(&gs_handle);
    if (res != 0)
    {
        bme688_interface_debug_print("bme688: soft reset failed.\n");
        (void)bme688_deinit(&gs_handle); 
        
        return 1;
    }
    bme688_interface_debug_print("bme688: check soft reset %s.\n", res == 0 ? "ok" : "error");
    
    /* finish register test */
    bme688_interface_debug_print("bme688: finish register test.\n");
    (void)bme688_deinit(&gs_handle); 

    return 0;
}
