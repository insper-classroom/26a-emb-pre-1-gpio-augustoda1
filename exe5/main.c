#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int BTN1_PIN = 26;
const int BTN2_PIN = 7;

static bool button_pressed_debounced(int pin) {
  // pull-up: apertado = 0
  if (!gpio_get(pin)) {
    sleep_ms(20);                 // filtra bouncing
    if (!gpio_get(pin)) {         // confirmou que ainda está apertado
      while (!gpio_get(pin)) {    // espera soltar (evita múltiplas contagens)
        sleep_ms(10);
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

  int cnt_1 = 0;
  int cnt_2 = 0;

  while (true) {
    if (button_pressed_debounced(BTN1_PIN)) {
      cnt_1++;
      printf("Botao 1: %d\n", cnt_1);
    }

    if (button_pressed_debounced(BTN2_PIN)) {
      cnt_2++;
      printf("Botao 2: %d\n", cnt_2);
    }

    sleep_ms(5);
  }

  return 0;
}