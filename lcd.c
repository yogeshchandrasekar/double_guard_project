#include "lcd.h"
#include "I2C.H"
#include "EEPROM.H"
#include "KEYPAD.H"

#define MAX_ATTEMPTS 4
#define PASS_LEN     6

unsigned char value;
unsigned char digits = 0;
unsigned char attempts = 0;
unsigned long entered = 0;

void show_prompt(void)
{
    LCD_COMMAND(0x01);
    LCD_COMMAND(0x80);
    LCD_STRING("ENTER PASSWORD");
    LCD_COMMAND(0xC0);          
    entered = 0;
    digits = 0;
}

int main(void)
{
    LCD_INIT();
    I2C_INIT();

    LCD_COMMAND(0x01);
    LCD_COMMAND(0x80);
    LCD_STRING("TESTING");
    delay_ms(2000);

    save_password(123456UL);  
    delay_ms(10);

    show_prompt();

    while (1)
    {
        if (attempts >= MAX_ATTEMPTS)
        {
            LCD_COMMAND(0x01);
            LCD_COMMAND(0x80);
            LCD_STRING("SYSTEM LOCKED");
            while (1);     
        }

        value = keyscan();

        if (value == '=')                       
        {
            LCD_COMMAND(0x01);
            LCD_COMMAND(0x80);

            if (digits == PASS_LEN && read_password() == entered)
            {
                LCD_STRING("ACCESS OK");
                attempts = 0;
                delay_ms(2000);
                /* TODO: unlock door / relay here */
                show_prompt();
            }
            else
            {
                LCD_STRING("WRONG PASS");
                attempts++;
                delay_ms(1500);
                show_prompt();
            }
        }
        else if (value < 10)                    
        {
            if (digits < PASS_LEN)
            {
                LCD_DATA(value + '0');          
                entered = entered * 10 + value;
                digits++;
            }
        }
        else                                   
        {
            LCD_COMMAND(0x01);
            LCD_STRING("INVALID KEY");
            delay_ms(1000);
            show_prompt();
        }
    }
}
