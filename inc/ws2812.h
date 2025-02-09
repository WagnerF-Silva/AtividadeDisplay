#ifndef WS2812_H
#define WS2812_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "ws2812.pio.h"

#define WS2812_PIN 7
#define NUM_PIXELS 25
#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_RX_PIN 1
#define BTN_A 5
#define BTN_B 6
#define LED_GREEN 11
#define LED_BLUE 12

volatile bool led_green_state = false;
volatile bool led_blue_state = false;
volatile int num = 0;

const bool num_patterns[10][25] = {
    { 0,1,1,1,0, 0,1,0,1,0, 0,1,0,1,0, 0,1,0,1,0, 0,1,1,1,0 },
    { 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0 },
    { 0,1,1,1,0, 0,1,0,0,0, 0,1,1,1,0, 0,0,0,1,0, 0,1,1,1,0 },
    { 0,1,1,1,0, 0,0,0,1,0, 0,1,1,1,0, 0,0,0,1,0, 0,1,1,1,0 },
    { 0,1,0,0,0, 0,0,0,1,0, 0,1,1,1,0, 0,1,0,1,0, 0,1,0,1,0 },
    { 0,1,1,1,0, 0,0,0,1,0, 0,1,1,1,0, 0,1,0,0,0, 0,1,1,1,0 },
    { 0,1,1,1,0, 0,1,0,1,0, 0,1,1,1,0, 0,1,0,0,0, 0,1,1,1,0 },
    { 0,1,0,0,0, 0,0,0,1,0, 0,1,0,0,0, 0,0,0,1,0, 0,1,1,1,0 },
    { 0,1,1,1,0, 0,1,0,1,0, 0,1,1,1,0, 0,1,0,1,0, 0,1,1,1,0 },
    { 0,1,1,1,0, 0,0,0,1,0, 0,1,1,1,0, 0,1,0,1,0, 0,1,1,1,0 }
};

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

void update_led_matrix() {
    for (int i = 0; i < NUM_PIXELS; i++) {
        put_pixel(num_patterns[num][i] ? urgb_u32(0, 100, 0) : urgb_u32(0, 0, 0));
    }
}

void debounce() {
    static uint32_t last_press = 0;
    uint32_t now = to_ms_since_boot(get_absolute_time());
    if (now - last_press < 200) return;
    last_press = now;
}

void button_callback(uint gpio, uint32_t events) {
    debounce();
    if (gpio == BTN_A) {
        led_green_state = !led_green_state;
        gpio_put(LED_GREEN, led_green_state);
    } else if (gpio == BTN_B) {
        led_blue_state = !led_blue_state;
        gpio_put(LED_BLUE, led_blue_state);
    }
    update_led_matrix();
}

void setup_gpio() {
    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);
    gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, &button_callback);
    
    gpio_init(BTN_B);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_B);
    gpio_set_irq_enabled_with_callback(BTN_B, GPIO_IRQ_EDGE_FALL, true, &button_callback);
    
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_put(LED_GREEN, false);
    
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_put(LED_BLUE, false);
}

void on_uart_rx() {
    while (uart_is_readable(UART_ID)) {
        char received_char = uart_getc(UART_ID);
        printf("Caractere recebido: %c\n", received_char);
        if (received_char >= '0' && received_char <= '9') {
            num = received_char - '0';
            update_led_matrix();
        }
        
    }
}

void setup_uart2() {
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    uart_set_irq_enables(UART_ID, true, false);
    irq_set_exclusive_handler(UART0_IRQ, on_uart_rx);
    irq_set_enabled(UART0_IRQ, true);
}

int Matriz() {
    stdio_init_all();
    setup_uart2();
    setup_gpio();
    
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, false);
    update_led_matrix();
    
    while (1) {}
}

#endif
