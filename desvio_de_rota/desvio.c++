#include <bits/stdc++.h>

#define infinito INT_MAX

using namespace std;

int n, m, c, k;
int grafo[1010][1010];
int custo[1010];

// declara uma fila
queue<int> fila;

int dijkstra(int ori, int dest)
{
    custo[ori] = 0;
    fila.push(ori);

    while (!fila.empty())
    {
        int i = fila.front();
        fila.pop();
        for (int j = 0; j < n; j++)
        {
            if (grafo[i][j] != infinito && custo[j] > custo[i] + grafo[i][j])
            {
                custo[j] = custo[i] + grafo[i][j];
                fila.push(j);
            }
        }
    }

    return custo[dest];
}

int main()
{
    while ((cin >> n >> m >> c >> k), (n | m | c | k))
    {

        // infinita o grafo e o vetor custo

        for (int i = 0; i <= n; i++)
        {
            custo[i] = infinito;
            for (int j = 0; j <= n; j++)
                grafo[i][j] = infinito;
        }

        for (int i = 1; i <= m; i++)
        { // para cada estrada

            // le os valores da estrada (vertice) e o pedagio (peso) entre eles
            int u, v, p;
            scanf("%d %d %d", &u, &v, &p);

            if (u >= c && v >= c)
            { // se as duas cidades estiverem fora da rota

                // adicione a estrada (vertices) e o peso
                // adciona o peso indo e voltando na estrada
                grafo[u][v] = p;
                grafo[v][u] = p;
            }
            // se v pertencer à rota
            if (u >= c && v < c)
                grafo[u][v] = p; // adicione apenas a estrada que chega em v

            // se u pertencer à rota
            if (u < c && v >= c)
                grafo[v][u] = p; // adicione apenas a estrada que chega em u

            // se as duas cidades forem cidades consecutivas da rota
            if (u < c && v < c && abs(u - v) == 1)
            {
                // adiciono a estrada normalmente
                grafo[u][v] = p;
                grafo[v][u] = p;
            }
        }

        cout << dijkstra(k, c - 1) << "\n"; // imprime o menor caminho usando dijkstra
    }

    return 0;
}