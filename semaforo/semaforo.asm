#include <xc.inc>   ; Inclui o arquivo de cabeçalho que contém definições específicas para o microcontrolador usado

CONFIG FOSC=XT      ; Configuração do oscilador, usando cristal externo (XT)
CONFIG WDTE=OFF     ; Watchdog Timer desativado
CONFIG PWRTE=ON     ; Power-up Timer ativado
CONFIG BOREN=ON     ; Brown-out Reset ativado
CONFIG LVP=OFF      ; Programação de baixa voltagem desativada
CONFIG CPD=OFF      ; Proteção de código do Data EEPROM desativada
CONFIG WRT=OFF      ; Proteção de escrita desativada
CONFIG CP=OFF       ; Proteção de código do programa desativada
    
#define _XTAL_FREQ 4000000   ; Define a frequência do cristal (4 MHz)
#define VERMELHO PORTB,7     ; Define o pino 7 do PORTB como VERMELHO (LED)
#define AMARELO	 PORTB,3     ; Define o pino 3 do PORTB como AMARELO (LED)
#define VERDE  	 PORTB,0     ; Define o pino 0 do PORTB como VERDE (LED)
#define CHAVE    PORTD,0     ; Define o pino 0 do PORTD como CHAVE (botão)
    
TEMPO1 EQU 0X20     ; Define o registrador TEMPO1 no endereço 0x20
TEMPO2 EQU 0X21     ; Define o registrador TEMPO2 no endereço 0x21
TEMPO3 EQU 0X22     ; Define o registrador TEMPO3 no endereço 0x22
 
PSECT code

INICIO:
    ;(Tri-state B) é utilizado para configurar a direção dos pinos do PORTB
    ; BANKSEL é uma instrução específica dos microcontroladores PIC que seleciona o 
    ; banco de memória adequado para acessar um registrador específico.
    BANKSEL TRISB        ; Seleciona o banco que contém TRISB
    MOVLW   00000000B    ; Carrega o valor 00000000 no WREG (todos os pinos como saída)
    MOVWF   TRISB        ; Configura os pinos do PORTB como saída
    BANKSEL TRISD        ; Seleciona o banco que contém TRISD
    MOVLW   11111111B    ; Carrega o valor 11111111 no WREG (todos os pinos como entrada)
    MOVWF   TRISD        ; Configura os pinos do PORTD como entrada
    BANKSEL PORTB        ; Seleciona o banco que contém PORTB
    CLRF PORTB           ; Limpa todos os bits do PORTB

MAIN:
    BTFSC CHAVE          ; Testa o bit CHAVE (PORTD,0), pula a próxima instrução se estiver limpo (CHAVE não pressionada)
    GOTO DESLIGADA       ; Vai para o rótulo DESLIGADA se CHAVE estiver pressionada

    BSF VERMELHO         ; Seta o bit VERMELHO (PORTB,7), ligando o LED
    MOVLW 60             ; A instrução MOVLW 12 carrega o valor literal 12 no registrador de trabalho (WREG).
    CALL ATRASO          ; Chama a sub-rotina ATRASO
    BCF VERMELHO         ; Reseta o bit VERMELHO (PORTB,7), desligando o LED
    MOVLW 10		 ; A instrução MOVLW 12 carrega o valor literal 12 no registrador de trabalho (WREG).
    CALL ATRASO          ; Chama a sub-rotina ATRASO novamente
    
    BTFSC CHAVE          ; Testa o bit CHAVE (PORTD,0), pula a próxima instrução se estiver limpo (CHAVE não pressionada)
    GOTO DESLIGADA       ; Vai para o rótulo DESLIGADA se CHAVE estiver pressionada
    
    BSF AMARELO          ; Seta o bit AMARELO (PORTB,3), ligando o LED
    MOVLW 20             ; A instrução MOVLW 12 carrega o valor literal 12 no registrador de trabalho (WREG).
    CALL ATRASO          ; Chama a sub-rotina ATRASO
    BCF AMARELO          ; Reseta o bit AMARELO (PORTB,3), desligando o LED
    MOVLW 10		 ; A instrução MOVLW 12 carrega o valor literal 12 no registrador de trabalho (WREG).
    CALL ATRASO          ; Chama a sub-rotina ATRASO novamente
    
    BTFSC CHAVE          ; Testa o bit CHAVE (PORTD,0), pula a próxima instrução se estiver limpo (CHAVE não pressionada)
    GOTO DESLIGADA       ; Vai para o rótulo DESLIGADA se CHAVE estiver pressionada
    
    BSF VERDE            ; Seta o bit VERDE (PORTB,0), ligando o LED
    MOVLW 40             ; A instrução MOVLW 12 carrega o valor literal 12 no registrador de trabalho (WREG).
    CALL ATRASO          ; Chama a sub-rotina ATRASO
    BCF VERDE            ; Reseta o bit VERDE (PORTB,0), desligando o LED
    MOVLW 10		 ; A instrução MOVLW 12 carrega o valor literal 12 no registrador de trabalho (WREG).
    CALL ATRASO          ; Chama a sub-rotina ATRASO novamente

    GOTO MAIN            ; Volta para o início do loop MAIN

DESLIGADA: ; Se chava estiver desligada então cai aqui...
    BANKSEL PORTB
    CLRF PORTB           ; Limpa todos os bits do PORTB (CLEAR)
    GOTO MAIN            ; Volta para o início do loop MAIN

ATRASO:
    MOVWF TEMPO3         ; Move o valor de WREG para o registrador TEMPO3
DL0:
    MOVLW 250            ; Carrega o valor 250 no WREG
    MOVWF TEMPO2         ; Move o valor de WREG para o registrador TEMPO2
DL1:    
    MOVLW 200            ; Carrega o valor 200 no WREG
    MOVWF TEMPO1         ; Move o valor de WREG para o registrador TEMPO1
DL2:
    NOP                  ; No Operation (sem operação, apenas atraso)
    NOP                  ; No Operation (sem operação, apenas atraso)
    DECFSZ TEMPO1,F      ; Decrementa TEMPO1, pula se zero
    GOTO   DL2           ; Vai para DL2 se TEMPO1 não for zero
    DECFSZ TEMPO2,F      ; Decrementa TEMPO2, pula se zero
    GOTO   DL1           ; Vai para DL1 se TEMPO2 não for zero        
    DECFSZ TEMPO3,F      ; Decrementa TEMPO3, pula se zero
    GOTO   DL0           ; Vai para DL0 se TEMPO3 não for zero
    RETURN               ; Retorna da sub-rotina
END                      ; Fim do código



