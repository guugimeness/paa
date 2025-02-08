// Gustavo de Oliveira Gimenes
// Engenharia de Computação
// 820759

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000  
#define MAX_D 1000  

// função para contar o número de subconjuntos cuja soma é divisível por D
long long contarSubConj(int N, int D) {

    long long A[N+1][D];    // inicializando tabela
    for(int i=0; i<=N; i++){
        for (int j=0; j<D; j++){
            A[i][j] = 0;
        }
    }

    // caso-base: há um subconjunto vazio com soma 0
    A[0][0] = 1;

    for(int i=1; i<=N; i++){
        for(int j=0; j<D; j++){
            // opção 1: não incluir o elemento i
            A[i][j] += A[i-1][j];

            // opção 2: incluir o elemento i
            A[i][(j + i) % D] += A[i-1][j];
        }
    }

    return A[N][0];
}

int main(){
    int N, D;

    // Loop para ler múltiplos casos de teste até que N seja 0
    while(1){
        // tamanho do conjunto
        scanf("%d", &N);
        if (N == 0) break;

        // divisor
        scanf("%d", &D);

        // função para contar os subconjuntos
        long long result = contarSubConj(N, D);
        printf("%lld\n", result);
    }

    return 0;
}