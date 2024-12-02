// Gustavo de Olivera Gimenes
// Engenharia de Computação
// 820759

#include <stdio.h>
#include <stdlib.h>

// função de comparação para qsort
int compara(const void *a, const void *b) {
    if (*(double*)a > *(double*)b) return 1;
    if (*(double*)a < *(double*)b) return -1;
    return 0;
}

// função que acumula as distâncias de cada elemento S para o k-ésimo mais próximo usando D&C
double acumulaDist(double **matriz, int floor, int top, int k, int n)
{
    double dist = 0;

    if (floor == top){      // caso-base -> matriz "tem" uma linha -> distância para o k-ésimo

        double *temp = (double *)malloc(n * sizeof(double));    // vetor temporário
        
        // copiar os valores da matriz para o vetor
        for (int i = 0; i < n; i++) {
            temp[i] = matriz[floor][i];
        }

        qsort(temp, n, sizeof(double), compara);   // ordena o vetor temporário

        dist += temp[k+1];

        free(temp);
        return dist;
    }

    int pivo = (floor + top) / 2;   // dividindo a matriz pela metade verticalmente

    dist += acumulaDist(matriz, floor, pivo, k, n);
    dist += acumulaDist(matriz, pivo + 1, top, k, n);

    return dist;
}

int main() 
{
    int n, s, k;

    scanf("%d", &n);
    scanf("%d", &s);
    scanf("%d", &k);

    double **matriz = (double **)malloc(s * sizeof(double *));
    for (int i = 0; i < s; i++) {
        matriz[i] = (double *)malloc(n * sizeof(double));
    }
    
    // lendo os valores da matriz
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &matriz[i][j]);
        }
    }

    printf("%.2lf\n", acumulaDist(matriz, 0, s-1, k, n)/s);

    for (int i = 0; i < s; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}
