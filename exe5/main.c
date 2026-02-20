#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int BTN1_PIN = 26;
const int BTN2_PIN = 7;

static bool read_stable_low(int pin) {
  // pull-up: apertado = 0
  if (!gpio_get(pin)) {
    sleep_ms(20);          // debounce do aperto
    if (!gpio_get(pin)) {  // ainda está baixo -> aperto válido
      return true;
    }
  }
  return false;
}

static void wait_release_stable_high(int pin) {
  // espera soltar: precisa ficar em 1 de forma estável
  while (true) {
    if (gpio_get(pin)) {
      sleep_ms(20);        // debounce da soltura
      if (gpio_get(pin)) { // confirmou alto estável
        return;
      }
    }
    sleep_ms(5);
  }
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
    if (read_stable_low(BTN1_PIN)) {
      printf("Botao 1: %d\n", cnt1);
      fflush(stdout);
      cnt1++;
      wait_release_stable_high(BTN1_PIN);
    }

    if (read_stable_low(BTN2_PIN)) {
      printf("Botao 2: %d\n", cnt2);
      fflush(stdout);
      cnt2++;
      wait_release_stable_high(BTN2_PIN);
    }

    sleep_ms(5);
  }

  return 0;
}