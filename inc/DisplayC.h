#ifndef DISPLAYC_H
#define DISPLAYC_H

//USA O DISPLAY PARA DIGITAR
//USA O DISPLAY PARA DIGITAR
//USA O DISPLAY PARA DIGITAR
//USA O DISPLAY PARA DIGITAR
//USA O DISPLAY PARA DIGITAR

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define OLED_ADDRESS 0x3C

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define MAX_MSG_LEN 30  // Tamanho máximo da mensagem exibida

ssd1306_t ssd;
char mensagem[MAX_MSG_LEN + 1] = "";
int indice = 0;

void atualizar_display() {
    ssd1306_fill(&ssd, false);
    ssd1306_draw_string(&ssd, mensagem, 10, 20);
    ssd1306_send_data(&ssd);
}

void processar_entrada_uart() {
    while (uart_is_readable(UART_ID)) {
        char c = uart_getc(UART_ID);
        
        if (c == '\b' || c == 127) {  // BACKSPACE
            if (indice > 0) {
                mensagem[--indice] = '\0';
                printf("\b \b");
            }
        } else if (c == '\n' || c == '\r') {  // ENTER
            mensagem[indice] = '\0';
            printf("\nMensagem recebida: %s\n", mensagem);
            indice = 0;
            atualizar_display();
            printf("\nDigite outra mensagem: ");
        } else if (indice < MAX_MSG_LEN) {
            mensagem[indice++] = c;
            mensagem[indice] = '\0';
            printf("%c", c);
            atualizar_display();
        }
    }
}

void setup_uart() {
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    uart_set_hw_flow(UART_ID, false, false);
    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
    uart_set_fifo_enabled(UART_ID, false);
}

void setup_display() {
    i2c_init(I2C_PORT, 400000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    ssd1306_init(&ssd, WIDTH, HEIGHT, false, OLED_ADDRESS, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_send_data(&ssd);
    atualizar_display();
}

int Display() {
    stdio_init_all();
    setup_uart();
    setup_display();

    printf("Digite uma mensagem para exibir no OLED: ");

    while (1) {
        processar_entrada_uart();
        sleep_ms(50);  // Reduz latência e melhora a resposta
    }
}
#endif