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
 * @file      driver_bme688_parallel.h
 * @brief     driver bme688 parallel header file
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

#ifndef DRIVER_BME688_PARALLEL_H
#define DRIVER_BME688_PARALLEL_H

#include "driver_bme688_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup bme688_example_driver
 * @{
 */

/**
 * @brief bme688 parallel example default definition
 */
#define BME688_PARALLEL_DEFAULT_TEMPERATURE_OVERSAMPLING        BME688_OVERSAMPLING_x2            /**< temperature oversampling x2 */
#define BME688_PARALLEL_DEFAULT_PRESSURE_OVERSAMPLING           BME688_OVERSAMPLING_x16           /**< pressure oversampling x16 */
#define BME688_PARALLEL_DEFAULT_HUMIDITY_OVERSAMPLING           BME688_OVERSAMPLING_x1            /**< humidity oversampling x1 */
#define BME688_PARALLEL_DEFAULT_FILTER                          BME688_FILTER_COEFF_15            /**< filter coeff 15 */
#define BME688_PARALLEL_DEFAULT_SPI_WIRE                        BME688_SPI_WIRE_4                 /**< spi wire 4 */

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
                             void (*callback)(uint8_t status, bme688_parallel_data_t *data, uint8_t len));

/**
 * @brief  parallel example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t bme688_parallel_deinit(void);

/**
 * @brief  parallel example server
 * @return status code
 *         - 0 success
 *         - 1 server failed
 * @note   none
 */
uint8_t bme688_parallel_server(void);

/**
 * @brief  parallel example server reset
 * @return status code
 *         - 0 success
 *         - 1 reset failed
 * @note   none
 */
uint8_t bme688_parallel_server_reset(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
