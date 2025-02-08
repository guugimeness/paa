// Gustavo de Oliveira Gimenes
// Engenharia de Computação
// 820759

#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) (((a)>(b))?(a):(b))    // função max

// função que encontra um subconjunto com max_valor/2
int bauFelicidade(int n, int moedas[], int max_valor){

    int half_valor = max_valor/2;

    int A[n+1][half_valor+1];   // inicializando tabela
    for(int x=0; x<=half_valor; x++){
        A[0][x] = 0;
    }

    for(int i=1; i<=n; i++){
        for(int x=0; x<=half_valor; x++){
            if (moedas[i-1] <= x) {
                A[i][x] = MAX(A[i-1][x], A[i-1][x - moedas[i-1]] + moedas[i-1]);
            } 
            else {
                A[i][x] = A[i-1][x];
            }
        }
    }

    return A[n][half_valor];
}

int main(){

    int n;  // número de moedas
    while(scanf("%d", &n) == 1 && n != 0){

        int moedas[n];  // vetor com os valores de cada moeda
        int total = 0;
        for(int i=0; i<n; i++){
            scanf("%d", &moedas[i]);
            total += moedas[i];
        }

        // valor do subconjunto 1
        int sub1 = bauFelicidade(n, moedas, total);

        // valor do subconjunto 2
        int sub2 = total - sub1;

        // retorna o valor da diferença entre os dois subconjuntos
        printf("%d\n", abs(sub2 - sub1));
    }

    return 0;
}