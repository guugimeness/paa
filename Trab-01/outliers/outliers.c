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

// função que conta os outliers usando D&C
int outliers(double **matriz, int floor, int top, int k, double l, int n)
{
    if (floor == top){      // caso-base -> matriz "tem" uma linha -> vejo se é outlier

        double *temp = (double *)malloc(n * sizeof(double));    // vetor temporário

        // copiar os valores da matriz para o vetor
        for (int i = 0; i < n; i++) {
            temp[i] = matriz[floor][i];
        }

        qsort(temp, n, sizeof(double), compara);   // Ordena o vetor temporário

        for(int i=1; i<k+2; i++){
            if(temp[i] > l)     // checando se é outlier
                return 1;
        }

        free(temp);
        return 0;
    }

    int out = 0;    
    int pivo = (floor + top) / 2;   // Dividindo a matriz pela metade verticalmente

    out += outliers(matriz, floor, pivo, k, l, n);
    out += outliers(matriz, pivo + 1, top, k, l, n);

    return out;
}

int main() 
{
    int n, s, k;
    double l;

    scanf("%d", &n);
    scanf("%d", &s);
    scanf("%d", &k);
    scanf("%lf", &l); 

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

    printf("%d\n", outliers(matriz, 0, s-1, k, l, n));

    for (int i = 0; i < s; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}
