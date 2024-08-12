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
        printf("escreva no formato val1 op val2, onde val sao numeros e op um operador entre (+, -, X, /)");
        return 0;
    }        

    char* val1 = argv[1];
    char op = argv[2][0]; 
    char* val2 = argv[3];

    ieee754 ie;
    ie.value = atof(val1);
    printf("valor 1: ");
    printaIeee754(ie);

    ieee754 ie2;
    ie2.value = atof(val2);
    printf("valor 2: ");
    printaIeee754(ie2);

    float res = resolvedorMagico(op, ie, ie2);
    ieee754 ie3;
    ie3.value = res;
    printf("res: ");
    printaIeee754(ie3);
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
    printf(" = %f\n", ie.value);
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
    case 'X':
        return num1 * num2;
    case '-':
        return num1 - num2;
    case '/':
        return num1 / num2;
    case '+':
        return num1 + num2;
    default:
        //caso por algum diabo de motivo o usuário passe parametros nao utilizaveis
        printf("Erro: Operador inválido.\n");
        return 0.0;
    }
}

void checaExcecao() {

    printf("Excecao FE_DIVBYZERO %d\n", fetestexcept(FE_DIVBYZERO));
    printf("Excecao FE_OVERFLOW %d\n", fetestexcept(FE_OVERFLOW));        
    printf("Excecao FE_UNDERFLOW %d\n", fetestexcept(FE_UNDERFLOW));    
    printf("Excecao FE_INVALID %d\n", fetestexcept(FE_INVALID));        
    printf("Excecao FE_INEXACT %d\n", fetestexcept(FE_INEXACT));
    
    //limpa exceções dnv, pq might aswell
    feclearexcept(FE_ALL_EXCEPT);
}