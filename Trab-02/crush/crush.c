// Gustavo de Olivera Gimenes
// Engenharia de Computação
// 820759

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF 99999999999

// aresta
typedef struct Aresta{
    long long destino;    
    long long peso;      
    struct Aresta* prox;
} Aresta;

// grafo
typedef struct{
    Aresta** lista_adj;
    long long V; 
} Grafo;

// heap
typedef struct{
    long long vertice;      
    long long distancia;    
} FilaPrioridade;

// funções auxiliares
Aresta* criaAresta(long long destino, long long peso){
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->prox = NULL;
    return novaAresta;
}

Grafo* criaGrafo(long long V){
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->V = V;
    grafo->lista_adj = (Aresta**)malloc(V * sizeof(Aresta*));
    for(long long i = 0; i < V; i++){
        grafo->lista_adj[i] = NULL;
    }
    return grafo;
}

void addAresta(Grafo* grafo, long long origem, long long destino, long long peso){
    Aresta* novaAresta = criaAresta(destino, peso);
    novaAresta->prox = grafo->lista_adj[origem];
    grafo->lista_adj[origem] = novaAresta;
}

// funções para manipulação do min-heap
void trocar(FilaPrioridade* a, FilaPrioridade* b){
    FilaPrioridade temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(FilaPrioridade* fila, long long n, long long index){
    long long esquerda = 2 * index + 1;
    long long direita = 2 * index + 2;
    long long menor = index;
    
    if(esquerda < n && fila[esquerda].distancia < fila[menor].distancia){
        menor = esquerda;
    }
    
    if(direita < n && fila[direita].distancia < fila[menor].distancia){
        menor = direita;
    }
    
    if(menor != index){
        trocar(&fila[index], &fila[menor]);
        heapify(fila, n, menor);
    }
}

void inserirHeap(FilaPrioridade* fila, long long* n, long long vertice, long long distancia){
    fila[*n].vertice = vertice;
    fila[*n].distancia = distancia;
    long long i = (*n)++;
    
    while(i && fila[i].distancia < fila[(i - 1) / 2].distancia){
        trocar(&fila[i], &fila[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

FilaPrioridade popMinimo(FilaPrioridade* fila, long long* n){
    FilaPrioridade min = fila[0];
    fila[0] = fila[--(*n)];
    heapify(fila, *n, 0);
    return min;
}

void atualizarPrioridade(FilaPrioridade* fila, long long n, long long vertice, long long novaPrioridade){
    for(long long i = 0; i < n; i++){
        if(fila[i].vertice == vertice){
            fila[i].distancia = novaPrioridade;
            while(i && fila[i].distancia < fila[(i - 1) / 2].distancia){
                trocar(&fila[i], &fila[(i - 1) / 2]);
                i = (i - 1) / 2;
            }
            break;
        }
    }
}

// função para achar caminho mínimo
void dijkstra(Grafo* grafo, long long raiz){
    long long V = grafo->V;
    long long dist[V];  
    long long pred[V];
    int visitado[V];  
    FilaPrioridade fila[V];
    long long n = 0;

    // inicializando as distancias como infinito e sem predecessores
    for(long long i = 0; i < V; i++){
        dist[i] = INF;
        pred[i] = -1;
        visitado[i] = 0;
    }
    dist[raiz] = 0;

    // inserir todos os vértices na fila de prioridade
    for(long long i = 0; i < V; i++){
        inserirHeap(fila, &n, i, dist[i]);
    }

    while(n > 0){
        FilaPrioridade u = popMinimo(fila, &n);     // extrair vértice com maior prioridade
        long long u_vertice = u.vertice;

        if(visitado[u_vertice]){        // checa se o vértice já foi visitado
            continue;
        }
        visitado[u_vertice] = 1;
        
        Aresta* adj = grafo->lista_adj[u_vertice];
        while(adj){     // para cada vizinho de u:
            long long v = adj->destino;
            long long peso = adj->peso;

            if(dist[u_vertice] + peso < dist[v]){     // verifica se é melhor chegar em v por u
                dist[v] = dist[u_vertice] + peso;
                pred[v] = u_vertice;
                atualizarPrioridade(fila, n, v, dist[v]);       // se sim, atualiza a prioridade
            }
            adj = adj->prox;
        }
    }

    // resultados para o vértice destino (V-1)
    printf("%lld\n", dist[V-1]);
}

int main(){

    // número de vertices e de arcos
    long long V, E;
    scanf("%lld %lld", &V, &E); 
    Grafo* grafo = criaGrafo(V);   // criando um grafo com V vértices

    // ligando os vértices com seus respectivos pesos W
    long long A, B, W;  
    for(long long i = 0; i < E; i++){
        scanf("%lld %lld %lld", &A, &B, &W);  
        addAresta(grafo, A, B, W);
    }

    // encontrando o caminho mínimo
    dijkstra(grafo, 0);

    return 0;
}