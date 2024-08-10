/*
    Nome: Leonardo T. Rubert
 */
#include <stdio.h>
#include <string.h>
#include <fenv.h>
#include <stdlib.h>
// Ele recebe pela linha de comando uma expressão no formato val1 op val2 
// onde op é uma operação (+,−, ∗,/) e val1 e val2 são dois valores em ponto flutuante, NaN ou ±∞. 
// (Use os símbolos x, X ou . para a multipliação. Não use o asteriso. )

typedef union {
    float value;
    struct {
        unsigned int mantissa : 23;
        unsigned int expoente : 8;
        unsigned int sinal : 1;
    } parts;
} ieee754;

float resolvedorMagico(char sinal, ieee754 valor1, ieee754 valor2);
void printaBin(int valor, int bits);
void printaIeee754(ieee754 valor);
void checaExcecao();

int main(int argc, char *argv[]){
    feclearexcept(FE_ALL_EXCEPT);

    if(argc > 4){
        printf("escreve os bagulho direito mano, ta trollando?");
        return 0;
    }        

    char* val1 = argv[1];
    char op = argv[2][0]; 
    char* val2 = argv[3];

    ieee754 ie;
    ie.value = atof(val1);
    printaIeee754(ie);

    ieee754 ie2;
    ie2.value = atof(val2);
    printaIeee754(ie2);

    printf("%f \n", resolvedorMagico(op, ie, ie2));

    checaExcecao();

    return 0;
}

void printaIeee754(ieee754 ie){
    int value = ie.value;
    printaBin(ie.parts.sinal, 1);
    printf(" ");
    printaBin(ie.parts.expoente, 8);
    printf(" ");
    printaBin(ie.parts.mantissa, 24);
    printf(" = %d", value);
    printf("\n");

}

void printaBin(int valor, int bits){

    for (int i = bits - 1; i >= 0; i--) {
        printf("%u", (valor >> i) & 1);
    }
}

float resolvedorMagico(char sinal, ieee754 valor1, ieee754 valor2) {
    float num1 = valor1.value;
    float num2 = valor2.value;
    
    switch (sinal) {
    case 'x':
        return num1 * num2;
    case '-':
        return num1 - num2;
    case '/':
        return num1 / num2;
    case '+':
        return num1 + num2;
    default:
        printf("Erro: Operador inválido.\n");
        return 0.0;
    }
}

void checaExcecao() {

    printf("Exception: Division by zero %d\n", fetestexcept(FE_DIVBYZERO));

    printf("Exception: Overflow %d\n", fetestexcept(FE_OVERFLOW));    
    
    printf("Exception: Underflow %d\n", fetestexcept(FE_UNDERFLOW));
    
    printf("Exception: Invalid operation %d\n", fetestexcept(FE_INVALID));
        
    printf("Exception: Inexact result %d\n", fetestexcept(FE_INEXACT));
    

    feclearexcept(FE_ALL_EXCEPT);
}