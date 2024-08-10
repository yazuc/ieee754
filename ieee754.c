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
        int mantissa : 24;
        int expoente : 8;
        int sinal : 1;
    } parts;
} ieee754;

float resolvedorMagico(char sinal, const char* valor1, const char* valor2);
void printaBin(int valor, int bits);
void printaIeee754(ieee754 valor);

int main(int argc, char *argv[]){
    feclearexcept(FE_ALL_EXCEPT);

    // printf("Number of arguments: %d\n", argc);

    if(argc > 4){
        printf("escreve os bagulho direito mano, ta trollando?");
        return 0;
    }        

    ieee754 ie;
    ie.value = -235;
    printaIeee754(ie);

    // for (int i = 0; i < argc; i++) {
    //     printf("Argument %d: %s\n", i, argv[i]);
    // }

    // char arr[argc - 1];

    // for(int i = 1; i < argc; i++)
    //     arr[i - 1] = *argv[i];

    // for(int i = 0; i < sizeof(arr); i++)
    //     printf("%c", arr[i]);

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
        printf("%d", (valor >> i) & 1);
    }
}

float resolvedorMagico(char sinal, const char* valor1, const char* valor2) {
    float num1 = atof(valor1);
    float num2 = atof(valor2);
    
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





