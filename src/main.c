#include "nrf_gpio.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
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
void _close(void) {}
void _lseek(void) {}
void _read(void) {}
void _write(void) {}
void _kill(void) {}
void _fstat_r(void) {}
void _isatty_r(void) {}
void _getpid(void) {}
