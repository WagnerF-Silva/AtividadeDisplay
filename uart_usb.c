/*
 * Utiliza a UART para controlar LEDs RGB e exibir entrada no display OLED.
 */

 #include <stdlib.h>
 #include <string.h>
 #include "hardware/i2c.h"
 #include "hardware/uart.h"
 #include "inc/ssd1306.h"
 #include "inc/font.h"
 #include <stdio.h>
 #include "pico/stdlib.h"
 #include "DisplayC.h"
 //adicionado ws2812
 #include <stdio.h>
#include "hardware/pio.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "ws2812.pio.h"
#include "ws2812.h"
 

#define BTN_A 5
#define BTN_B 6

 #define led_pin_g 11
 #define led_pin_b 12
 #define led_pin_r 13
 
 int main()
 {      
     stdio_init_all();
    //

     // Aguarda conexão USB antes de prosseguir
     while (!stdio_usb_connected()) {
         sleep_ms(100);
     }
 
     sleep_ms(2000); // Tempo extra para estabilizar a conexão
 
     setup_display();  // Inicializa o display OLED
 
     // Configura os pinos dos LEDs como saída
     gpio_init(led_pin_r);
     gpio_set_dir(led_pin_r, GPIO_OUT);
     gpio_put(led_pin_r, 0); // Inicialmente desligado
 
     gpio_init(led_pin_g);
     gpio_set_dir(led_pin_g, GPIO_OUT);
     gpio_put(led_pin_g, 0); // Inicialmente desligado
 
     gpio_init(led_pin_b);
     gpio_set_dir(led_pin_b, GPIO_OUT);
     gpio_put(led_pin_b, 0); // Inicialmente desligado
 
     printf("RP2040 inicializado. Digite para atualizar o display e acionar LEDs.\n");
     fflush(stdout);
     
     while (true)
     {
         if (stdio_usb_connected()) // Certifica-se de que o USB está conectado
         {
             char c = getchar(); // Substitui scanf por getchar
             printf("Recebido: '%c'\n", c);
             fflush(stdout);

             // Atualiza a string do display
             if (indice < MAX_MSG_LEN)
             {
                 mensagem[indice++] = c;
                 mensagem[indice] = '\0';
                 atualizar_display();
             }
             switch (c)
             {
            case '-':
                printf("Matriz Numerica Ativada");
                //ADICIONAR ATUALIZAR MATRIZ
                Matriz();
                fflush(stdout);
                break;
             case '0':
                 printf("Numero 0 na Matriz\n");
                 //ADICIONAR ATUALIZAR MATRIZ
                 fflush(stdout);
                 break;
             case '1':
                 printf("Numero 1 na Matriz\n");
                 fflush(stdout);
                 break;
            case '2':
                 printf("Numero 2 na Matriz\n");
                 fflush(stdout);
                 break;
            case '3':
                 printf("Numero 3 na Matriz\n");
                 fflush(stdout);
                 break;    
            case '4':
                 printf("Numero 4 na Matriz\n");
                 fflush(stdout);
                 break;    
            case '5':
                 printf("Numero 5 na Matriz\n");
                 fflush(stdout);
                 break;   
            case '6':
                 printf("Numero 6 na Matriz\n");
                 fflush(stdout);
                 break;    
            case '7':
                 printf("Numero 7 na Matriz\n");
                 fflush(stdout);
                 break;       
            case '8':
                 printf("Numero 8 na Matriz\n");
                 fflush(stdout);
                 break;    
            case '9':
                 printf("Numero 9 na Matriz\n");
                 fflush(stdout);
                 break;
                 case 'r':
                 gpio_put(led_pin_r, !gpio_get(led_pin_r));
                 printf("LED vermelho alternado!\n");
                 fflush(stdout);
                 break;
                 
                 //controla led por comando de texto
             case 'g':
                 gpio_put(led_pin_g, !gpio_get(led_pin_g));
                 printf("LED verde alternado!\n");
                 fflush(stdout);
                 break;
             case 'b':
                 gpio_put(led_pin_b, !gpio_get(led_pin_b));
                 printf("LED azul alternado!\n");
                 fflush(stdout);
                 break; 
             default:
                 printf("Caractere exibido no display: '%c'\n", c);
                 fflush(stdout);
             }
             
             // Alterna o LED correspondente
             /*switch (c)
             {
             case 'r':
                 gpio_put(led_pin_r, !gpio_get(led_pin_r));
                 printf("LED vermelho alternado!\n");
                 fflush(stdout);
                 break;
             case 'g':
                 gpio_put(led_pin_g, !gpio_get(led_pin_g));
                 printf("LED verde alternado!\n");
                 fflush(stdout);
                 break;
             case 'b':
                 gpio_put(led_pin_b, !gpio_get(led_pin_b));
                 printf("LED azul alternado!\n");
                 fflush(stdout);
                 break;
             default:
                 printf("Caractere exibido no display: '%c'\n", c);
                 fflush(stdout);
             }*/
         }
         sleep_ms(40);
     }
 
     return 0;
 }
 