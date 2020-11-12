#define PBDDR (*(volatile undigned char *)0xEE00A)
#define P4DDR (*(volatile undigned char *)0xEE003)
#define PBDR (*(volatile undigned char *)0xFFFDA)
#define P4DR (*(volatile undigned char *)0xFFFD3)

typedef unsigned int u_int;
typedef unsigned short u_short;
typedef unsigned long u_long;

u_long R0H, R0L, R2L, ER1 = 0;

void wait_ms(u_int ms);
void LCD_OUT8();

int main(void)
{
  char letter[] = {
      0x49, 0x20, 0x4C, 0x20, 0x49, 0x20, 0x4B, 0x20, 0x45, 0x20,
      0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0xCE, 0xDF, 0xB9, 0x20,
      0xD3, 0x20, 0xDD, 0x20, 0x21, 0x21, 0x00, 0x20, 0x20, 0x20,
      0x20};
  char myletter[] = {
      0x00, 0x01, 0x02};
  P4DDR = 0xFF;
  PBDDR = 0xFF;

  // reset_software
  wait_ms(50);
  for (int i = 0; i < 3; i++) // 3_times
  {
    R0L = 0x30;
    R0H &= 0xFA;
    LCD_OUT8();
    wait_ms(5);
  }

  // init_config_LCD
  R0L = 0x38;
  R0H &= 0xFA;
  LCD_OUT8();
  wait_ms(5);

  R0L = 0x0E;
  R0H &= 0xFA;
  LCD_OUT8();
  wait_ms(5);

  R0L = 0x01;
  R0H &= 0xFA;
  LCD_OUT8();
  wait_ms(5);

  R0L = 0x06;
  R0H &= 0xFA;
  LCD_OUT8();
  wait_ms(5); // wait_5ms

  //move_my_char
  R2L = 0x08;
  R0L = 0x40;
  R0H = 0xFA;
  LCD_OUT8();
  while (1)
  {
    R0L = ER1;
    R0H |= 0x01;
    LCD_OUT8();
    R0H &= 0xFA;
    R2L--;
    if (R2L == 0)
      break;
  }
  // lcd_disp
  for (int i = 0; i < 32; i++)
  {
    R0L = 0x01;
    R0H &= 0xFA;
    LCD_OUT8();
    wait_ms(5);

    R2L = 16; //16_character
    ER1 = letter;
    while (1)
    {
      R0L = ER1;
      R0H |= 0x01;
      LCD_OUT8();
      R0H &= 0xFA;
      ER1++;
      R2L--;
      if (R2L == 0)
        break;
    }
    R0L = 0xC0;
    R0H &= 0xFA;
    LCD_OUT8();
    R2L = 16;
    ER1 = letter + 16;

    while (1)
    {
      R0L = ER1;
      R0H |= 0x01;
      LCD_OUT8(R0H);
      R0H &= 0xFA;
      ER1++;
      R2L--;
      if (R2L == 0)
        break;
    }
  }

  while (1)
    ;
}

void wait_ms(u_long tm)
{
  while (tm--)
  {
    for (u_short t = 0; t < 4165; t++)
      ;
  }
}

void LCD_OUT8()
{
  P4DR = R0H;
  R0H |= 0x02;
  P4DR = R0H;
  PBDR = R0L;
  wait_ms(50);
  R0H &= 0xAD;
  P4DR = R0H;
  wait_ms(50);
}
