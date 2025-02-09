/**
 * Copyright (c) 2014 - 2020, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be
 * reverse engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_error.h"
#include "nrf_esb.h"
#include "nrf_esb_error_codes.h"
#include "nrf_gpio.h"
#include "sdk_common.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
// #include "boards.h"
#include "app_util.h"
#include "nrf_delay.h"
#include "nrf_drv_clock.h"
#include "nrfx_gpiote.h"

#include "debug_swo.h"
#include "timebase.h"
#include <common/protocol/esb_protocol.h>

static volatile uint32_t test_flag = 1;

/* this is the ESB listener address for this device, static fir tests, can be
 * set via command later */
static const uint8_t esb_listener_address[5] = {123, 45, 67, 89,
                                                1}; /* temporary, for tests. */

static void button_handler(nrfx_gpiote_pin_t pin,
                           nrf_gpiote_polarity_t action) {

  debug_swo_printf("BUTTON PRESSED\n");

  test_flag = 1;
}

void clocks_start(void) {
  NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
  NRF_CLOCK->TASKS_HFCLKSTART = 1;

  while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0)
    ;
}

/* This is an example GPIO configuration for the Particle Xenon board */
void gpio_init(void) {
  nrfx_gpiote_pin_t button_pin = NRF_GPIO_PIN_MAP(0, 11);
  nrfx_gpiote_in_config_t button_cfg =
      NRFX_GPIOTE_CONFIG_IN_SENSE_HITOLO(false);
  button_cfg.pull = NRF_GPIO_PIN_PULLUP;
  nrfx_gpiote_init();
  nrfx_gpiote_in_init(button_pin, &button_cfg, button_handler);
  nrfx_gpiote_in_event_enable(button_pin, true);

  /* turn user LED on*/
  nrf_gpio_cfg_output(NRF_GPIO_PIN_MAP(1, 12));
  nrf_gpio_pin_set(NRF_GPIO_PIN_MAP(1, 12));
}

static void rf_antenna_init(void) {
  nrf_gpio_cfg_output(NRF_GPIO_PIN_MAP(0, 24));
  nrf_gpio_cfg_output(NRF_GPIO_PIN_MAP(0, 25));

  /* Enable PCB antenna */
  nrf_gpio_pin_set(NRF_GPIO_PIN_MAP(0, 24));
  nrf_gpio_pin_clear(NRF_GPIO_PIN_MAP(0, 25));
}

static void power_manage(void) {
  // WFE - SEV - WFE sequence to wait until a radio event require further
  // actions.
  __SEV();
  __WFE();
  __WFE();
}
int main(void) {
  ret_code_t err_code;
  UNUSED_VARIABLE(err_code);

  debug_swo_init();

  gpio_init();

  debug_swo_printf("startup\n");
  clocks_start();

  timebase_init();

  rf_antenna_init();

  esb_protocol_init(esb_listener_address);
  while (true) {
    if (1 == test_flag) {
      test_flag = 0;
      // do something
    }
    esb_protocol_process();
    power_manage();
  }
}


/* dummy functions to shut up linker 
 * TODO: find better method to provide these stubs*/
void _close(void)
{
}
void _lseek(void)
{
}
void _read(void)
{
}
void _write(void)
{
}
void _kill(void)
{
}
void _fstat_r(void)
{
}
void _isatty_r(void)
{
}
void _getpid(void)
{
}


