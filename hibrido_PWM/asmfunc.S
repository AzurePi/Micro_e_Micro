; Inclui o arquivo de cabeçalho com definições para registradores AVR
#include <avr/io.h>

.global _setup_pwm
.global _vel1         
.global _vel2
.global _vel3
.global _stop

; Configuração do PWM do pino 6 no Timer 0 
_setup_pwm:
    ; Configura o pino 6 (PD6/OC0A) como saída
    lds r16, DDRD        ; Carrega o valor atual do registrador DDRD
    ori r16, (1 << 6)    ; Define o bit 6 (PD6) como saída
    sts DDRD, r16        ; Salva a configuração no registrador DDRD

    ; Configura TCCR0A: Fast PWM, não invertido no OC0A
    ldi r16, (1 << COM0A1) | (1 << WGM01) | (1 << WGM00) ; Configura COM0A1, WGM01, WGM00
    sts TCCR0A, r16      ; Salva o valor no TCCR0A

    ; Configura TCCR0B: Prescaler de 64
    ldi r16, (1 << CS01) | (1 << CS00) ; Configura prescaler de 64
    sts TCCR0B, r16      ; Salva o valor no TCCR0B

    ret

; Carrega o valor de r24 no OCR0A para gerar o duty cycle
_set_duty:
    mov r16, r24         ; Carrega o valor no registrador r16
    sts OCR0A, r16       ; Armazena o valor no registrador OCR0A

    ret


_vel1:
    ldi   r24, 255    ; Carrega 255 no registrador r24 para gerar 100% de duty cycle
    rcall _set_duty
    ret

_vel2:
    ldi   r24, 168    ; Carrega 168 no registrador r24 para gerar 66% de duty cycle
    rcall _set_duty
    ret

_vel3:
    ldi   r24, 84     ; Carrega 84 no registrador r24 para gerar 33% de duty cycle
    rcall _set_duty
    ret


_stop:
    ldi   r24, 0     ; Carrega 0 no registrador r24 para desligar o motor
    rcall _set_duty
    ret
