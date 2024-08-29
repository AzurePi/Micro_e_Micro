#include <xc.h>

// Configura��es de Bits de Configura��o do PIC16F877A
// CONFIG
#pragma config FOSC = XT        // Bits de Sele��o do Oscilador (Oscilador XT)
#pragma config WDTE = OFF       // Watchdog Timer (WDT desativado)
#pragma config PWRTE = ON       // Habilita��o do Timer de Inicializa��o (Timer de Inicializa��o habilitado)
#pragma config CP = OFF         // Prote��o de C�digo (Prote��o de C�digo desativada)

// Definimos a frequ�ncia do oscilador como 4MHz
#define _XTAL_FREQ  4000000

// Defini��es para as sa�das
// Renomeamos os pinos para facilitar o acesso
#define LEDA_Verde     PORTBbits.RB5 // LED verde do sem�foro 1
#define LEDA_Amarelo   PORTBbits.RB6 // LED amarelo do sem�foro 1
#define LEDA_Vermelho  PORTBbits.RB7 // LED vermelho do sem�foro 1
#define LEDB_Verde     PORTBbits.RB2 // LED verde do sem�foro 2
#define LEDB_Amarelo   PORTBbits.RB1 // LED amarelo do sem�foro 2
#define LEDB_Vermelho  PORTBbits.RB0 // LED vermelho do sem�foro 2
#define BOTAO          PORTDbits.RD0 // Input do bot�o

// Defini��es globais para tornar o c�digo mais compreens�vel
#define LIGAR    1
#define DESLIGAR 0
#define TodosSaida   0x00
#define TodosLimpar  0x00

// Vari�veis gerais
unsigned char count;

// Declara��o de prot�tipos
void MCU_Delayms(unsigned int t);

// Fun��o principal
void main(void) {
    // Inicializamos o PIC
    TRISB = TodosSaida; // Configura o PORTB como sa�da
    PORTB = TodosLimpar; // Limpa o PORTB
    while(1) { // Inicia a sequ�ncia do sem�foro
        if (BOTAO == LIGAR) break;
        
        LEDA_Verde = LIGAR; // Liga o LED verde do sem�foro 1
        LEDB_Vermelho = LIGAR; // Liga o LED vermelho do sem�foro 2
        MCU_Delayms(9000); // Delay de 9 segundos
        LEDA_Verde = DESLIGAR; // Desliga o LED verde do sem�foro 1
        // Faz o LED amarelo do sem�foro 1 piscar
        for(count = 0; count < 10; count++) { // Faz o LED amarelo do primeiro sem�foro piscar
            LEDA_Amarelo ^= 1; // Alterna o estado do LED amarelo
            MCU_Delayms(300); // Delay de 0,3 segundos
        }
        LEDB_Vermelho = DESLIGAR; // Desliga o LED vermelho do sem�foro 2
        
        if (BOTAO == LIGAR) break;
        
        LEDB_Verde = LIGAR; // Liga o LED verde do sem�foro 2
        LEDA_Vermelho = LIGAR; // Liga o LED vermelho do sem�foro 1
        MCU_Delayms(9000); // Delay de 9 segundos
        LEDB_Verde = DESLIGAR; // Desliga o LED verde do sem�foro 2
        // Faz o LED amarelo do sem�foro 2 piscar
        for(count = 0; count < 10; count++) { // Faz o LED amarelo do segundo sem�foro piscar
            LEDB_Amarelo ^= 1; // Alterna o estado do LED amarelo
            MCU_Delayms(300); // Delay de 0,3 segundos
        }
        LEDA_Vermelho = DESLIGAR; // Desliga o LED vermelho do sem�foro 1    
    } // Fim da sequ�ncia do sem�foro.
    // A sequ�ncia se repete indefinidamente
}

// Fun��o para gerar delays em milissegundos
void MCU_Delayms(unsigned int t) {
    unsigned int acc;
    // Repetir enquanto acc for menor que t
    for(acc = 0; acc < t; acc++) {
        __delay_ms(1); // Delay de 1 milissegundo
    }
}
