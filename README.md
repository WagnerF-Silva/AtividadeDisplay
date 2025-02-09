# README - Controle de LEDs RGB e Display OLED via UART

## Descrição
Este projeto utiliza a UART para receber comandos via USB e controlá-los em um Raspberry Pi RP2040. Os comandos permitem alternar LEDs RGB e exibir caracteres em um display OLED SSD1306. Além disso, também suporta exibição de números em uma matriz de LEDs WS2812.

## Hardware Utilizado
- **Microcontrolador:** Raspberry Pi RP2040 (exemplo: Raspberry Pi Pico)
- **Display:** OLED SSD1306 via protocolo I2C
- **LEDs RGB:** 3 LEDs individuais conectados a pinos GPIO
- **Matriz WS2812:** LEDs endereçáveis via PIO
- **Botões:** Conectados aos pinos GPIO 5 e 6

## Bibliotecas Utilizadas
- `pico/stdlib.h` - Biblioteca padrão para controle de GPIO e UART
- `hardware/i2c.h` - Controle do barramento I2C
- `hardware/uart.h` - Comunicação via UART
- `ssd1306.h` - Controle do display OLED
- `ws2812.h` - Controle dos LEDs WS2812
- `hardware/pio.h`, `hardware/gpio.h`, `hardware/timer.h` - Controle de hardware

## Instalação
1. Configure o ambiente de desenvolvimento do Raspberry Pi Pico (SDK do RP2040).
2. Compile o código e faça o upload para a placa.
3. Conecte a placa ao computador via USB e abra um terminal serial para enviar comandos.

## Comandos Disponíveis
Os seguintes comandos podem ser digitados no terminal serial para controlar LEDs e o display:

| Comando | Ação |
|---------|--------|
| `r` | Alterna o LED vermelho |
| `g` | Alterna o LED verde |
| `b` | Alterna o LED azul |
| `0-9` | Exibe números na matriz WS2812 |
| `-` | Ativa a matriz numérica |
| Qualquer caractere | Exibe o caractere no display OLED |

## Funcionamento
1. O microcontrolador aguarda a conexão USB.
2. Ao receber um caractere via UART, ele pode:
   - Exibir o caractere no display OLED.
   - Alternar o estado dos LEDs RGB.
   - Atualizar a matriz WS2812 para exibir números.
3. O loop principal garante que os comandos sejam processados continuamente.

## Possíveis Melhorias
- Adicionar suporte a mais caracteres no display OLED.
- Melhorar a interface com a matriz WS2812 para exibir padrões mais complexos.
- Implementar um buffer de entrada para armazenar strings mais longas no display.

## Autores
Desenvolvido para o Raspberry Pi RP2040 com foco em controle via UART.

