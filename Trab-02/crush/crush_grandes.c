// Gustavo de Olivera Gimenes
// Engenharia de Computação
// 820759

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

// aresta
typedef struct Aresta {
    int vertice; 
    int peso; 
    struct Aresta *prox; 
} Aresta;

// grafo
typedef struct {
    Aresta **lista_adj; 
    int V; 
} Grafo;

typedef struct {
    int vertice; 
    int distancia; 
} FilaPrioridade;

// min-heap
typedef struct {
    FilaPrioridade *dados; 
    int *posicao; 
    int tamanho; 
    int capacidade; 
} MinHeap;

// funções auxiliares
void criaAresta(Grafo *grafo, int origem, int destino, int peso) {
    Aresta *novoNo = (Aresta *)malloc(sizeof(Aresta));
    novoNo->vertice = destino;
    novoNo->peso = peso;
    novoNo->prox = grafo->lista_adj[origem];
    grafo->lista_adj[origem] = novoNo;
}

Grafo *criaGrafo(int vertices) {
    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    grafo->V = vertices;
    grafo->lista_adj = (Aresta **)malloc(vertices * sizeof(Aresta *));
    
    // inicializa as listas de adjacência como NULL
    for (int i = 0; i < vertices; i++) {
        grafo->lista_adj[i] = NULL;
    }
    return grafo;
}

// funções para manipulação do min-heap
MinHeap *criarMinHeap(int capacidade) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->dados = (FilaPrioridade *)malloc(capacidade * sizeof(FilaPrioridade));
    heap->posicao = (int *)malloc(capacidade * sizeof(int));
    heap->tamanho = 0;
    heap->capacidade = capacidade;
    return heap;
}

void trocarNosHeap(FilaPrioridade *a, FilaPrioridade *b) {
    FilaPrioridade temp = *a;
    *a = *b;
    *b = temp;
}

// ajusta a posição de um nó para cima na heap
void heapifyCima(MinHeap *heap, int indice) {
    while(indice > 0){
        int pai = (indice - 1) / 2;
        if (heap->dados[indice].distancia >= heap->dados[pai].distancia) break;
        heap->posicao[heap->dados[indice].vertice] = pai;
        heap->posicao[heap->dados[pai].vertice] = indice;
        trocarNosHeap(&heap->dados[indice], &heap->dados[pai]);
        indice = pai;
    }
}

// ajusta a posição de um nó para baixo na heap
void heapifyBaixo(MinHeap *heap, int indice) {
    while(2 * indice + 1 < heap->tamanho){
        int esquerda = 2 * indice + 1;
        int direita = 2 * indice + 2;
        int menor = esquerda;

        // verifica qual filho tem a menor distância
        if(direita < heap->tamanho && heap->dados[direita].distancia < heap->dados[esquerda].distancia)
            menor = direita;

        // se o nó já está na posição correta, não é necessário continuar
        if(heap->dados[indice].distancia <= heap->dados[menor].distancia) break;

        // atualiza as posições dos vértices na heap
        heap->posicao[heap->dados[indice].vertice] = menor;
        heap->posicao[heap->dados[menor].vertice] = indice;
        trocarNosHeap(&heap->dados[indice], &heap->dados[menor]);
        indice = menor;
    }
}

FilaPrioridade popMinimo(MinHeap *heap){
    FilaPrioridade raiz = heap->dados[0];
    FilaPrioridade ultimoNo = heap->dados[--heap->tamanho];
    heap->dados[0] = ultimoNo;
    heap->posicao[raiz.vertice] = -1;
    heap->posicao[ultimoNo.vertice] = 0;
    heapifyBaixo(heap, 0);
    return raiz;
}

void atualizarPrioridade(MinHeap *heap, int vertice, int distancia){
    int indice = heap->posicao[vertice];
    heap->dados[indice].distancia = distancia;
    heapifyCima(heap, indice);
}

int estaNoMinHeap(MinHeap *heap, int vertice){
    return heap->posicao[vertice] >= 0;
}

// função para achar caminho mínimo
void dijkstra(Grafo *grafo, int origem, int destino){
    int V = grafo->V;
    int *distancia = (int *)malloc(V * sizeof(int));
    MinHeap *heap = criarMinHeap(V);

    // inicializa as distâncias e a heap
    for(int v=0; v<V; v++){
        distancia[v] = INF;
        heap->dados[v].vertice = v;
        heap->dados[v].distancia = INF;
        heap->posicao[v] = v;
    }

    // define a distância do vértice de origem como 0
    distancia[origem] = 0;
    heap->dados[origem].distancia = 0;
    heapifyCima(heap, origem);
    heap->tamanho = V;

    // começa a busca pelo menor caminho
    while(heap->tamanho > 0){
        FilaPrioridade noMinimo = popMinimo(heap);
        int u = noMinimo.vertice;

        Aresta *crawl = grafo->lista_adj[u];
        while(crawl != NULL){
            int v = crawl->vertice;

            // verifica se a distância pode ser atualizada
            if(estaNoMinHeap(heap, v) && distancia[u] != INF && distancia[u] + crawl->peso < distancia[v]){
                distancia[v] = distancia[u] + crawl->peso;
                atualizarPrioridade(heap, v, distancia[v]);
            }
            crawl = crawl->prox;
        }
    }

    // resultados para o vértice destino (V-1)
    printf("%d\n", distancia[destino]);

    // libera a memória alocada
    free(distancia);
    free(heap->dados);
    free(heap->posicao);
    free(heap);
}

int main(){

    // número de vertices e de arcos
    int V, E;
    scanf("%d %d", &V, &E);
    Grafo *grafo = criaGrafo(V);     // criando um grafo com V vértices

    /// ligando os vértices com seus respectivos pesos W
    for(int i=0; i<E; i++){
        int A, B, W;
        scanf("%d %d %d", &A, &B, &W);
        criaAresta(grafo, A, B, W);
    }

    // encontrando o caminho mínimo
    dijkstra(grafo, 0, V - 1);

    // libera a memória do grafo
    for(int i=0; i<V; i++){
        Aresta *crawl = grafo->lista_adj[i];
        while(crawl != NULL){
            Aresta *temp = crawl;
            crawl = crawl->prox;
            free(temp);
        }
    }
    free(grafo->lista_adj);
    free(grafo);

    return 0;
}
