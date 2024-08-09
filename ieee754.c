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


float resolvedorMagico(char sinal, const char* valor1, const char* valor2);
void printaBin(int valor);
int main(int argc, char *argv[]){
    feclearexcept(FE_ALL_EXCEPT);

    // printf("Number of arguments: %d\n", argc);

    // if(argc > 4){
    //     printf("escreve os bagulho direito mano, ta trollando?");
    //     return 0;
    // }        

    // for (int i = 0; i < argc; i++) {
    //     printf("Argument %d: %s\n", i, argv[i]);
    // }

    // char arr[argc - 1];

    // for(int i = 1; i < argc; i++)
    //     arr[i - 1] = *argv[i];

    // for(int i = 0; i < sizeof(arr); i++)
    //     printf("%c", arr[i]);

    printaBin(23);

    return 0;
}

void printaBin(int valor){

    //divide, pega mod, e divide o resultado

    // 23/2 = 11 1
    // 11 / 2 = 5 1
    // 5 / 2 = 2  1
    // 2 / 2 = 1 0

    // 1, 1, 1, 0, 1

    int bin[32];
    int i = 0;
    while(valor){       
        bin[i] = valor % 2;      
        valor = valor / 2;
        i++;
    }

    while (i)
    {
        i--;
        printf("%d", bin[i]);
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





