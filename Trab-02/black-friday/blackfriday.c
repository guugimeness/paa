// Gustavo de Olivera Gimenes
// Engenharia de Computação
// 820759

#include <stdio.h>
#include <stdlib.h>

// função para ordenar os preços decrescente
int comparar(const void *a, const void *b) {
    return (*(long long*)b - *(long long*)a);
}

long long BlackFriday(int n, long long *precos){
    qsort(precos, n, sizeof(long long), comparar);  // ordenando decrescente  
    long long desconto = 0;
    
    int i=0, j = n-1;
    
    // forma grupos para maximizar o intermediário
    while(i+1 < j){
        desconto += precos[i+1];      // desconto = intermediário
        i += 2;     // avança os dois maiores
        j--;        // usa o menor restante
    }

    return desconto;
}

int main(){

    long long desconto = 0;   // desconto total

    // número de itens comprados
    int n;
    scanf("%d", &n);
    
    // alocando vetor dos preços dos itens
    long long *precos = (long long*)malloc(n * sizeof(long long));
    for(int i=0; i<n; i++){
        scanf("%lld", &precos[i]);
    }
    
    desconto = BlackFriday(n, precos);
    printf("%lld\n", desconto);
    
    // desalocando
    free(precos);
    return 0;
}