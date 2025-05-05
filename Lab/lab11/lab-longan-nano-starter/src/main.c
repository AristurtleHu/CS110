#include "assembly/example.h"
#include "lcd/lcd.h"
#include "utils.h"

void Inp_init(void) {
  rcu_periph_clock_enable(RCU_GPIOA);
  rcu_periph_clock_enable(RCU_GPIOC);

  gpio_init(GPIOA, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ,
            GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
  gpio_init(GPIOC, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ,
            GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
}

void IO_init(void) {
  Inp_init(); // inport init
  Lcd_Init(); // LCD init
}

void Board_self_test(void) {
  while (1) {
    LCD_ShowString(60, 25, (u8 *)"TEST (25s)", WHITE);
    if (Get_Button(JOY_LEFT)) {
      LCD_ShowString(5, 25, (u8 *)"L", BLUE);
      LCD_ShowString(60, 25, (u8 *)"TEST", RED);
    }
    if (Get_Button(JOY_DOWN)) {
      LCD_ShowString(25, 45, (u8 *)"D", BLUE);
      LCD_ShowString(60, 25, (u8 *)"TEST", GREEN);
    }
    if (Get_Button(JOY_UP)) {
      LCD_ShowString(25, 5, (u8 *)"U", BLUE);
    }
    if (Get_Button(JOY_RIGHT)) {
      LCD_ShowString(45, 25, (u8 *)"R", BLUE);
    }
    if (Get_Button(JOY_CTR)) {
      LCD_ShowString(25, 25, (u8 *)"C", BLUE);
    }
    if (Get_Button(BUTTON_1)) {
      LCD_ShowString(60, 5, (u8 *)"SW1", BLUE);
    }
    if (Get_Button(BUTTON_2)) {
      LCD_ShowString(60, 45, (u8 *)"SW2", BLUE);
    }
    draw();
    delay_1ms(10);
    LCD_Clear(BLACK);
  }
}

int main(void) {
  IO_init();
  Board_self_test();
}
