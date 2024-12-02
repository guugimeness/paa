// Gustavo de Oliveira Gimenes
// Engenharia de Computação
// 820759

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double exponencial(double B, unsigned int N)
{
    double aux;     // variável auxiliar
    if(N==0)        // caso base: expoente == 0
        return 1;

    aux = exponencial(B, floor(N/2));  // divisão
    aux = aux*aux;

    if(N%2 == 1)    // se o expoente for ímpar, vai sobrar um B na divisão
        aux = B*aux;

    return aux;
}

void imprimeDigitoOrdem(double num)
{
    int i = 0;
    while (num >= 10)
    {
        num = num / 10;
        i++;
    }
    printf("%d %d\n", (int)num, i);
}

int main()
{
    double B, resp;
    unsigned int N;
    scanf("%lf %u", &B, &N);
    resp = exponencial(B, N);
    // printf("%.2lf\n", resp);
    // printf("%.5e\n", resp);
    imprimeDigitoOrdem(resp);
    return 0;
}
