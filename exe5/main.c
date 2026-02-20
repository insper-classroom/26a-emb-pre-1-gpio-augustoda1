#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int BTN1_PIN = 26;
const int BTN2_PIN = 7;

static bool pressed_once(int pin) {
  // pull-up: apertado = 0
  if (!gpio_get(pin)) {
    sleep_ms(20);          // debounce
    if (!gpio_get(pin)) {  // confirmou que ainda está apertado
      while (!gpio_get(pin)) {
        sleep_ms(10);      // espera soltar (1 evento por aperto)
      }
      return true;
    }
  }
  return false;
}

int main(void) {
  stdio_init_all();

  gpio_init(BTN1_PIN);
  gpio_set_dir(BTN1_PIN, GPIO_IN);
  gpio_pull_up(BTN1_PIN);

  gpio_init(BTN2_PIN);
  gpio_set_dir(BTN2_PIN, GPIO_IN);
  gpio_pull_up(BTN2_PIN);

  int cnt1 = 0;
  int cnt2 = 0;

  while (true) {
    if (pressed_once(BTN1_PIN)) {
      printf("Botao 1: %d\n", cnt1);
      fflush(stdout);
      cnt1++;
    }

    if (pressed_once(BTN2_PIN)) {
      printf("Botao 2: %d\n", cnt2);
      fflush(stdout);
      cnt2++;
    }

    sleep_ms(5);
  }

  return 0;
}