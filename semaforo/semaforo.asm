#include <xc.inc>   ; Inclui o arquivo de cabe�alho que cont�m defini��es espec�ficas para o microcontrolador usado

CONFIG FOSC=XT      ; Configura��o do oscilador, usando cristal externo (XT)
CONFIG WDTE=OFF     ; Watchdog Timer desativado
CONFIG PWRTE=ON     ; Power-up Timer ativado
CONFIG BOREN=ON     ; Brown-out Reset ativado
CONFIG LVP=OFF      ; Programa��o de baixa voltagem desativada
CONFIG CPD=OFF      ; Prote��o de c�digo do Data EEPROM desativada
CONFIG WRT=OFF      ; Prote��o de escrita desativada
CONFIG CP=OFF       ; Prote��o de c�digo do programa desativada
    
#define _XTAL_FREQ 4000000   ; Define a frequ�ncia do cristal (4 MHz)
#define VERMELHO PORTB,7     ; Define o pino 7 do PORTB como VERMELHO (LED)
#define AMARELO	 PORTB,3     ; Define o pino 3 do PORTB como AMARELO (LED)
#define VERDE  	 PORTB,0     ; Define o pino 0 do PORTB como VERDE (LED)
#define CHAVE    PORTD,0     ; Define o pino 0 do PORTD como CHAVE (bot�o)
    
TEMPO1 EQU 0X20     ; Define o registrador TEMPO1 no endere�o 0x20
TEMPO2 EQU 0X21     ; Define o registrador TEMPO2 no endere�o 0x21
TEMPO3 EQU 0X22     ; Define o registrador TEMPO3 no endere�o 0x22
 
PSECT code

INICIO:
    ;(Tri-state B) � utilizado para configurar a dire��o dos pinos do PORTB
    ; BANKSEL � uma instru��o espec�fica dos microcontroladores PIC que seleciona o 
    ; banco de mem�ria adequado para acessar um registrador espec�fico.
    BANKSEL TRISB        ; Seleciona o banco que cont�m TRISB
    MOVLW   00000000B    ; Carrega o valor 00000000 no WREG (todos os pinos como sa�da)
    MOVWF   TRISB        ; Configura os pinos do PORTB como sa�da
    BANKSEL TRISD        ; Seleciona o banco que cont�m TRISD
    MOVLW   11111111B    ; Carrega o valor 11111111 no WREG (todos os pinos como entrada)
    MOVWF   TRISD        ; Configura os pinos do PORTD como entrada
    BANKSEL PORTB        ; Seleciona o banco que cont�m PORTB
    CLRF PORTB           ; Limpa todos os bits do PORTB

MAIN:
    BTFSC CHAVE          ; Testa o bit CHAVE (PORTD,0), pula a pr�xima instru��o se estiver limpo (CHAVE n�o pressionada)
    GOTO DESLIGADA       ; Vai para o r�tulo DESLIGADA se CHAVE estiver pressionada

    BSF VERMELHO         ; Seta o bit VERMELHO (PORTB,7), ligando o LED
    MOVLW 60             ; A instru��o MOVLW 12 carrega o valor literal 12 no registrador de trabalho (WREG).
    CALL ATRASO          ; Chama a sub-rotina ATRASO
    BCF VERMELHO         ; Reseta o bit VERMELHO (PORTB,7), desligando o LED
    MOVLW 10		 ; A instru��o MOVLW 12 carrega o valor literal 12 no registrador de trabalho (WREG).
    CALL ATRASO          ; Chama a sub-rotina ATRASO novamente
    
    BTFSC CHAVE          ; Testa o bit CHAVE (PORTD,0), pula a pr�xima instru��o se estiver limpo (CHAVE n�o pressionada)
    GOTO DESLIGADA       ; Vai para o r�tulo DESLIGADA se CHAVE estiver pressionada
    
    BSF AMARELO          ; Seta o bit AMARELO (PORTB,3), ligando o LED
    MOVLW 20             ; A instru��o MOVLW 12 carrega o valor literal 12 no registrador de trabalho (WREG).
    CALL ATRASO          ; Chama a sub-rotina ATRASO
    BCF AMARELO          ; Reseta o bit AMARELO (PORTB,3), desligando o LED
    MOVLW 10		 ; A instru��o MOVLW 12 carrega o valor literal 12 no registrador de trabalho (WREG).
    CALL ATRASO          ; Chama a sub-rotina ATRASO novamente
    
    BTFSC CHAVE          ; Testa o bit CHAVE (PORTD,0), pula a pr�xima instru��o se estiver limpo (CHAVE n�o pressionada)
    GOTO DESLIGADA       ; Vai para o r�tulo DESLIGADA se CHAVE estiver pressionada
    
    BSF VERDE            ; Seta o bit VERDE (PORTB,0), ligando o LED
    MOVLW 40             ; A instru��o MOVLW 12 carrega o valor literal 12 no registrador de trabalho (WREG).
    CALL ATRASO          ; Chama a sub-rotina ATRASO
    BCF VERDE            ; Reseta o bit VERDE (PORTB,0), desligando o LED
    MOVLW 10		 ; A instru��o MOVLW 12 carrega o valor literal 12 no registrador de trabalho (WREG).
    CALL ATRASO          ; Chama a sub-rotina ATRASO novamente

    GOTO MAIN            ; Volta para o in�cio do loop MAIN

DESLIGADA: ; Se chava estiver desligada ent�o cai aqui...
    BANKSEL PORTB
    CLRF PORTB           ; Limpa todos os bits do PORTB (CLEAR)
    GOTO MAIN            ; Volta para o in�cio do loop MAIN

ATRASO:
    MOVWF TEMPO3         ; Move o valor de WREG para o registrador TEMPO3
DL0:
    MOVLW 250            ; Carrega o valor 250 no WREG
    MOVWF TEMPO2         ; Move o valor de WREG para o registrador TEMPO2
DL1:    
    MOVLW 200            ; Carrega o valor 200 no WREG
    MOVWF TEMPO1         ; Move o valor de WREG para o registrador TEMPO1
DL2:
    NOP                  ; No Operation (sem opera��o, apenas atraso)
    NOP                  ; No Operation (sem opera��o, apenas atraso)
    DECFSZ TEMPO1,F      ; Decrementa TEMPO1, pula se zero
    GOTO   DL2           ; Vai para DL2 se TEMPO1 n�o for zero
    DECFSZ TEMPO2,F      ; Decrementa TEMPO2, pula se zero
    GOTO   DL1           ; Vai para DL1 se TEMPO2 n�o for zero        
    DECFSZ TEMPO3,F      ; Decrementa TEMPO3, pula se zero
    GOTO   DL0           ; Vai para DL0 se TEMPO3 n�o for zero
    RETURN               ; Retorna da sub-rotina
END                      ; Fim do c�digo



