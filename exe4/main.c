#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdbool.h>

const int BTN_R = 28;

const int LED_RED = 5;
const int LED_PURPLE = 8;
const int LED_BLUE = 11;
const int LED_GREEN = 15;

static void all_off(void) {
  gpio_put(LED_RED, 0);
  gpio_put(LED_PURPLE, 0);
  gpio_put(LED_BLUE, 0);
  gpio_put(LED_GREEN, 0);
}

static void one_on(int pin) {
  all_off();
  gpio_put(pin, 1);
}

int main(void) {
  // LEDs
  gpio_init(LED_RED);
  gpio_set_dir(LED_RED, GPIO_OUT);

  gpio_init(LED_PURPLE);
  gpio_set_dir(LED_PURPLE, GPIO_OUT);

  gpio_init(LED_BLUE);
  gpio_set_dir(LED_BLUE, GPIO_OUT);

  gpio_init(LED_GREEN);
  gpio_set_dir(LED_GREEN, GPIO_OUT);

  all_off();

  // Botão vermelho (pull-up -> apertado = 0)
  gpio_init(BTN_R);
  gpio_set_dir(BTN_R, GPIO_IN);
  gpio_pull_up(BTN_R);

  while (true) {
    if (!gpio_get(BTN_R)) {
      // sequência
      one_on(LED_RED);
      sleep_ms(300);

      one_on(LED_PURPLE);
      sleep_ms(300);

      one_on(LED_BLUE);
      sleep_ms(300);

      one_on(LED_GREEN);
      sleep_ms(300);

      all_off();

      // espera soltar (evita repetir várias vezes no mesmo aperto)
      while (!gpio_get(BTN_R)) {
        sleep_ms(10);
      }
    }

    sleep_ms(10);
  }

  return 0;
}