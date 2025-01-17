#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUE 1000000        // 10^6

void limpaFila(int n, int *fila, int *final_fila, int *m){
    int *partial = (int *)malloc(n * sizeof(int));      // vetor parcial
    int *visitado = (int *)calloc(MAX_VALUE, sizeof(int));  // vetor para marcar duplicados
    if(!visitado){
        exit(1); // encerra o programa se falhar na alocação
    }

    // inicializa o vetor de visitados
    for(int i=0; i<MAX_VALUE; i++){
        visitado[i] = -1;
    }

    for(int i=0; i<n; i++){      // percorre todos os elementos da fila inicial
        int valor = fila[i];
        visitado[valor] = i;        // atualiza a última posição em que o valor apareceu
    }

    // preenche o parcial pela posição marcada no vetor visitados
    for(int i=0; i<MAX_VALUE; i++){
        if(visitado[i] != -1) {
            partial[visitado[i]] = i;
        }
    }

    int k = 0;
    // preenche a fila final
    for(int i=0; i<n; i++){
        if(partial[i] != 0) {
            final_fila[k++] = partial[i];
        }
    }

    *m = k;  // atualiza o tamanho do vetor final
    // desalocando
    free(visitado);  
    free(partial);
}

int main() {

    // tamanho da fila
    int n;
    scanf("%d", &n);

    // alocando fila e verificando erro de alocação
    int *fila = (int *)malloc(n * sizeof(int));
    if (!fila) {
        return 1;
    }

    // preenchendo a fila
    for(int i = 0; i < n; i++) 
        scanf("%d", &fila[i]);

    // alocando fila final e verificando erro de alocação
    int *final_fila = (int *)malloc(n * sizeof(int));
    if (!final_fila) {
        free(fila);
        return 1;
    }

    int m = 0;

    limpaFila(n, fila, final_fila, &m);

    // resultado final
    for(int i = 0; i < m; i++)
        if (i == m - 1)
            printf("%d\n", final_fila[i]);
        else
            printf("%d ", final_fila[i]);

    // desalocando
    free(fila);
    free(final_fila);

    return 0;
}
