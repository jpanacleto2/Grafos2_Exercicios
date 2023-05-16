class Grafo:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = []
        self.gasto = 0

    def add_edge(self, u, v, w):
        self.graph.append([u, v, w])


    def find(self, parent, i):
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])

    def apply_union(self, parent, rank, x, y):
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)
        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot
        else:
            parent[yroot] = xroot
            rank[xroot] += 1

    def kruskal_algo(self):
        result = []
        i, e = 0, 0
        self.graph = sorted(self.graph, key=lambda item: item[2]) #ordena arestas pelo peso
        parent = []
        rank = []
        for node in range(self.V):
            parent.append(node)
            rank.append(0)
        while e < self.V - 1:
            u, v, w = self.graph[i]
            i = i + 1
            x = self.find(parent, u)
            y = self.find(parent, v)
            if x != y:
                e = e + 1
                result.append([u, v, w])
                self.apply_union(parent, rank, x, y)
        for u, v, weight in result:
            self.gasto = self.gasto + weight


def main():
    m, n = list(map(lambda x: int(x), input().split())) #recebe numero de vertices e conexoes grafo
    gastoTotal = 0
    g = Grafo(m)

    for i in range(n):
        x, y, distancia = list(map(lambda x: int(x), input().split())) #recebe os vertices a serem conectados e o peso aresta
        if x == 0 and y == 0:
            break
        g.add_edge(x, y, distancia)
        gastoTotal += distancia

    g.kruskal_algo()
    print(gastoTotal-g.gasto) #printa o total economizado

main()
