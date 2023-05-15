#include <bits/stdc++.h>
using namespace std;

typedef struct aresta
{
    int orig, dest, peso;
} aresta;

typedef struct grafo
{
    int V, E;           // V = numero de vertices, E = numero de arestas
    aresta *arestaList; // Lista de arestas
} graph;

grafo *cria_grafo(int V, int E)
{
    grafo *g = new grafo;
    g->V = V;
    g->E = E;
    g->arestaList = new aresta[E];
    return g;
}

typedef struct subset
{ // subconjunto
    int parent, rank;
} subset;

int find(subset subsets[], int i)
{
    // encontra o conjunto ao qual o i pertence

    if (subsets[i].parent != i)
    {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void Union(subset subsets[], int x, int y)
{
    /* Função que une dois conjuntos */

    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
    {
        subsets[xroot].parent = yroot;
    }
    else if (subsets[xroot].rank > subsets[yroot].rank)
    {
        subsets[yroot].parent = xroot;
    }
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int compara(const void *a, const void *b)
{
    /* Função que compara dois elementos de uma lista de arestas */

    aresta *a1 = (aresta *)a;
    aresta *b1 = (aresta *)b;
    return a1->peso > b1->peso;
}

void KruskalMST(grafo *graph)
{
    /* Função que calcula o MST de um grafo */

    int V = graph->V, E = graph->E;
    aresta result[V];
    int e = 0; // e = numero de arestas do MST
    int i = 0; //

    // realiza a ordenação
    qsort(graph->arestaList, graph->E, sizeof(graph->arestaList[0]), compara);

    subset *subsets = new subset[V * sizeof(subset)];

    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1)
    {
        aresta next_aresta = graph->arestaList[i++];

        int x = find(subsets, next_aresta.orig);
        int y = find(subsets, next_aresta.dest);

        if (x != y)
        {
            result[e++] = next_aresta;
            Union(subsets, x, y);
        }
    }

    long long sum = 0;
    for (i = 0; i < e; ++i)
    {
        sum += result[i].peso;
    }
    cout << sum << endl;
}

int main()
{
    int m, n;

    cin >> m >> n;

    while (m != 0 && n != 0)
    {
        grafo *g = cria_grafo(m, n);

        for (int i = 0; i < n; ++i)
        {
            int a, b, w;
            cin >> a >> b >> w;
            g->arestaList[i].orig = a;
            g->arestaList[i].dest = b;
            g->arestaList[i].peso = w;
        }

        KruskalMST(g);
        cin >> m >> n;
        delete g;
    }
}