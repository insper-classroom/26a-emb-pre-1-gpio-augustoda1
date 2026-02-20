#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN1_PIN = 26;
const int BTN2_PIN = 7;

int main(void) {
  stdio_init_all();

  // Botão 1
  gpio_init(BTN1_PIN);
  gpio_set_dir(BTN1_PIN, GPIO_IN);
  gpio_pull_up(BTN1_PIN);

  // Botão 2
  gpio_init(BTN2_PIN);
  gpio_set_dir(BTN2_PIN, GPIO_IN);
  gpio_pull_up(BTN2_PIN);

  while (true) {

    if (!gpio_get(BTN1_PIN)) {
      printf("Botao 1\n");
      while (!gpio_get(BTN1_PIN)) {
        sleep_ms(10);
      }
    }

    if (!gpio_get(BTN2_PIN)) {
      printf("Botao 2\n");
      while (!gpio_get(BTN2_PIN)) {
        sleep_ms(10);
      }
    }

    sleep_ms(10);
  }

  return 0;
}