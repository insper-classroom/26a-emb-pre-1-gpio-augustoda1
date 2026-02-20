#include <stdio.h>

#include "hardware/gpio.h"
#include "pico/stdlib.h"

static const int FIRST_GPIO = 2;     // segmentos A..G em GP2..GP8
static const int BTN_PIN_G = 28;     // botão em GP28 (pull-up)

static const uint8_t DIGIT_BITS[10] = {
    0x3f, // 0
    0x06, // 1
    0x5b, // 2
    0x4f, // 3
    0x66, // 4
    0x6d, // 5
    0x7d, // 6
    0x07, // 7
    0x7f, // 8
    0x67  // 9
};

static void seven_seg_init(int first_gpio) {
  for (int gpio = first_gpio; gpio < first_gpio + 7; gpio++) {
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_OUT);
    gpio_put(gpio, 0);
  }
}

static void seven_seg_display(int first_gpio, int digit) {
  int d = digit;
  if (d < 0) {
    d = 0;
  } else if (d > 9) {
    d = 9;
  }

  uint8_t value = DIGIT_BITS[d];
  for (int i = 0; i < 7; i++) {
    int gpio = first_gpio + i;
    int bit = (value >> i) & 1;
    gpio_put(gpio, bit);
  }
}

int main(void) {
  stdio_init_all();

  // botão (pull-up -> não pressionado = 1)
  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  seven_seg_init(FIRST_GPIO);

  int cnt = 0;
  int last_btn = 1;

  seven_seg_display(FIRST_GPIO, cnt);

  while (true) {
    int btn = gpio_get(BTN_PIN_G);

    // borda de descida: 1 -> 0 (pressionou)
    if ((last_btn != 0) && (btn == 0)) {
      cnt++;
      if (cnt > 9) {
        cnt = 0;
      }
      seven_seg_display(FIRST_GPIO, cnt);
      printf("cnt: %d\n", cnt);
    }

    last_btn = btn;
    sleep_ms(10);
  }

  return 0;
}