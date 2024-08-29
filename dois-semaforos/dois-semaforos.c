#include <xc.h>

// Configurações de Bits de Configuração do PIC16F877A
// CONFIG
#pragma config FOSC = XT        // Bits de Seleção do Oscilador (Oscilador XT)
#pragma config WDTE = OFF       // Watchdog Timer (WDT desativado)
#pragma config PWRTE = ON       // Habilitação do Timer de Inicialização (Timer de Inicialização habilitado)
#pragma config CP = OFF         // Proteção de Código (Proteção de Código desativada)

// Definimos a frequência do oscilador como 4MHz
#define _XTAL_FREQ  4000000

// Definições para as saídas
// Renomeamos os pinos para facilitar o acesso
#define LEDA_Verde     PORTBbits.RB5 // LED verde do semáforo 1
#define LEDA_Amarelo   PORTBbits.RB6 // LED amarelo do semáforo 1
#define LEDA_Vermelho  PORTBbits.RB7 // LED vermelho do semáforo 1
#define LEDB_Verde     PORTBbits.RB2 // LED verde do semáforo 2
#define LEDB_Amarelo   PORTBbits.RB1 // LED amarelo do semáforo 2
#define LEDB_Vermelho  PORTBbits.RB0 // LED vermelho do semáforo 2
#define BOTAO          PORTDbits.RD0 // Input do botão

// Definições globais para tornar o código mais compreensível
#define LIGAR    1
#define DESLIGAR 0
#define TodosSaida   0x00
#define TodosLimpar  0x00

// Variáveis gerais
unsigned char count;

// Declaração de protótipos
void MCU_Delayms(unsigned int t);

// Função principal
void main(void) {
    // Inicializamos o PIC
    TRISB = TodosSaida; // Configura o PORTB como saída
    PORTB = TodosLimpar; // Limpa o PORTB
    while(1) { // Inicia a sequência do semáforo
        if (BOTAO == LIGAR) break;
        
        LEDA_Verde = LIGAR; // Liga o LED verde do semáforo 1
        LEDB_Vermelho = LIGAR; // Liga o LED vermelho do semáforo 2
        MCU_Delayms(9000); // Delay de 9 segundos
        LEDA_Verde = DESLIGAR; // Desliga o LED verde do semáforo 1
        // Faz o LED amarelo do semáforo 1 piscar
        for(count = 0; count < 10; count++) { // Faz o LED amarelo do primeiro semáforo piscar
            LEDA_Amarelo ^= 1; // Alterna o estado do LED amarelo
            MCU_Delayms(300); // Delay de 0,3 segundos
        }
        LEDB_Vermelho = DESLIGAR; // Desliga o LED vermelho do semáforo 2
        
        if (BOTAO == LIGAR) break;
        
        LEDB_Verde = LIGAR; // Liga o LED verde do semáforo 2
        LEDA_Vermelho = LIGAR; // Liga o LED vermelho do semáforo 1
        MCU_Delayms(9000); // Delay de 9 segundos
        LEDB_Verde = DESLIGAR; // Desliga o LED verde do semáforo 2
        // Faz o LED amarelo do semáforo 2 piscar
        for(count = 0; count < 10; count++) { // Faz o LED amarelo do segundo semáforo piscar
            LEDB_Amarelo ^= 1; // Alterna o estado do LED amarelo
            MCU_Delayms(300); // Delay de 0,3 segundos
        }
        LEDA_Vermelho = DESLIGAR; // Desliga o LED vermelho do semáforo 1    
    } // Fim da sequência do semáforo.
    // A sequência se repete indefinidamente
}

// Função para gerar delays em milissegundos
void MCU_Delayms(unsigned int t) {
    unsigned int acc;
    // Repetir enquanto acc for menor que t
    for(acc = 0; acc < t; acc++) {
        __delay_ms(1); // Delay de 1 milissegundo
    }
}
