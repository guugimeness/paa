// Gustavo de Olivera Gimenes
// Engenharia de Computação
// 820759

#include <stdio.h>
#include <stdlib.h>

// função que intercala os valores e conta as trocas necessárias
long long intercalaEcontaTrocas(int *v, int *temp, int left, int pivo, int right) {
    long long trocas = 0;
    int i = left;    // sub-vetor da esquerda
    int j = pivo + 1; // sub-vetor da direita
    int k = left;

    while (i <= pivo && j <= right) {
        if (v[i] <= v[j]) {
            temp[k++] = v[i++];
        } else {
            temp[k++] = v[j++];
            trocas += (pivo - i + 1); // contando trocas
        }
    }

    // copiando os elementos que sobraram
    while (i <= pivo) {
        temp[k++] = v[i++];
    }
    while (j <= right) {
        temp[k++] = v[j++];
    }

    // copiando os elementos de volta para o vetor original
    for (i = left; i <= right; i++) {
        v[i] = temp[i];
    }

    return trocas;
}

// função que conta as trocas usando D&C
long long contaTrocas(int *v, int *temp, int left, int right) {
    if (left >= right)   // caso-base -> retorna 0 trocas
        return 0;

    long long trocas = 0;
    int pivo = (left + right) / 2;

    // dividindo o problema em dois sub-problemas
    trocas += contaTrocas(v, temp, left, pivo);
    trocas += contaTrocas(v, temp, pivo + 1, right);
    trocas += intercalaEcontaTrocas(v, temp, left, pivo, right);

    return trocas;
}

long long distanciaGenomica(int *A, int *B, int n) {
    int temp[n];    // vetor auxiliar
    int map[n];     // mapa de posições
    int posB[n];    // mapa direto para índices de B

    // mapeando os índices de B para acesso em O(1)
    for (int i = 0; i < n; i++) {
        posB[B[i]] = i;     // valor em B[i] está na posição i
    }

    // mapeando as posições de B em relação à A
    for (int i = 0; i < n; i++) {
        map[i] = posB[A[i]];
    }

    // contar as trocas adjacentes para que B seja igual à A
    return contaTrocas(map, temp, 0, n - 1);
}

int main() {

    // tamanho do vetor
    int n;
    scanf("%d", &n);

    // genômas A e B
    int A[n], B[n];
    for (int i = 0; i < n; i++) 
        scanf("%d", &A[i]);

    for (int i = 0; i < n; i++)
        scanf("%d", &B[i]);

    printf("%lld\n", distanciaGenomica(A, B, n));

    return 0;
}
