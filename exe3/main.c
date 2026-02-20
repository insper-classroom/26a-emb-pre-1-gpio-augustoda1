#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdbool.h>
#include <stdio.h>

const int BTN_G = 26;
const int BTN_R = 28;

const int LED_G = 6;
const int LED_R = 4;

int main(void) {
  stdio_init_all();

  // LEDs como saída
  gpio_init(LED_G);
  gpio_set_dir(LED_G, GPIO_OUT);
  gpio_put(LED_G, 0);

  gpio_init(LED_R);
  gpio_set_dir(LED_R, GPIO_OUT);
  gpio_put(LED_R, 0);

  // Botões como entrada com pull-up
  gpio_init(BTN_G);
  gpio_set_dir(BTN_G, GPIO_IN);
  gpio_pull_up(BTN_G);

  gpio_init(BTN_R);
  gpio_set_dir(BTN_R, GPIO_IN);
  gpio_pull_up(BTN_R);

  bool led_g_state = false;
  bool led_r_state = false;

  while (true) {

    // Botão verde: toggle LED verde ao apertar
    if (!gpio_get(BTN_G)) {
      led_g_state = !led_g_state;
      gpio_put(LED_G, led_g_state);

      while (!gpio_get(BTN_G)) {
        sleep_ms(10);
      }
    }

    // Botão vermelho: toggle LED vermelho ao apertar
    if (!gpio_get(BTN_R)) {
      led_r_state = !led_r_state;
      gpio_put(LED_R, led_r_state);

      while (!gpio_get(BTN_R)) {
        sleep_ms(10);
      }
    }

    sleep_ms(10);
  }

  return 0;
}