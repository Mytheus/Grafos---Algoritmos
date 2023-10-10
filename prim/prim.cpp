#include <iostream>
#include <bits/stdc++.h>

using namespace std;

//Nó inicial
const int INIT_NODE = 0;

class PQueue
{
    // Número de elementos dentro da heap
private:
    int heapSize = 0;

    // Lista para os elementos na heap
    vector<pair<pair<int, int>, int>> heap;

    int less(int i, int j)
    {
        return heap.at(i).second<=heap.at(j).second;
    }
    //UP
    void swim(int k)
    {
        int parent = (k-1) / 2;

        while (k>0 && less(k, parent))
        {
            this->swap(parent, k);
            k = parent;

            parent = (k-1)/2;
        }
    }
    //DOWN
    void sink(int k)
    {
        while (1)
        {
            int left = 2 * k + 1;
            int right = 2 * k + 2;
            int smallest = left;
            
            if (right < heapSize && less(right, left)) smallest = right;

            if (left >= heapSize || less(k, smallest)) break;

            this->swap(smallest, k);
            k = smallest;
        }
    }

    void swap(int i, int j)
    {
        pair<pair<int, int>, int> aux = heap[j];
        heap[j] = heap[i];
        heap[i] = aux;
    }
    pair<pair<int, int>, int> removeAt(int i)
    {
        if (isEmpty()) return {{-1,-1}, -1};
        heapSize--;
        pair<pair<int, int>, int> removido = heap[i];
        this->swap(i, heapSize);
        heap.pop_back();

        if (i == heapSize) return removido;

        pair<pair<int, int>, int> elem = heap[i];

        sink(i);

        if (heap[i]==elem) swim(i);

        return removido;

    }
public:
    int isEmpty()
    {
        return heapSize == 0;
    }


    int size(){
        return heapSize;
    }

    pair<pair<int, int>, int> peek(){
        if (isEmpty()) return {{-1,-1}, -1};
        return heap.at(0);
    }

    pair<pair<int, int>, int> poll()
    {
        return removeAt(0);
    }

    //Linear
    int contains(pair<pair<int, int>, int> elem)
    {
        for (int i = 0; i < heapSize; i++)
        {
            if (heap.at(i)==elem) return 1;
        }
        return 0;
    }

    void add(pair<pair<int, int>, int> elem)
    {
        heap.push_back(elem);
        swim(heapSize);
        heapSize++;
    }



    int remove (pair<pair<int, int>, int> elem)
    {
        for (int i = 0; i < heapSize; i++)
        {
            if (elem == heap[i])
            {
                removeAt(i);
                return 1;
            }
        }
        return 0;
    }


    int isMinHeap(int k)
    {
        if (k >= heapSize) return true;

        int left = 2 * k+1;
        int right = 2 * k+2;

        if (left < heapSize && !less(k, left)) return false;
        if (right < heapSize && !less(k, right)) return false;

        return isMinHeap(left) && isMinHeap(right);
    }

};

struct Graph{
    //Nº de vértices e arestas
    int N, E;
    //Vetor de adjacências [[{V, Peso}]]
    vector<pair<int, int>>* edges;
    //Flag de grafo direcionado
    bool Dgraf;
    //Construtor (Número de vértices, arestas e flag de Digrafo (default = false))
    Graph(int N, int E, bool Dgraf=false){
        this->N = N;
        this->E = E;
        this->Dgraf=Dgraf;
        this->edges = new vector<pair<int, int>>[N];
    }
    //Insere arestas no grafo
    void insertEdge(int a, int b, int wt)
    {
        //Insere a ida, se não for digrafo insere a volta
        edges[a-1].push_back(make_pair(b-1, wt));
        if (!Dgraf) edges[b-1].push_back(make_pair(a-1, wt));
    }

};

//Adiciona as arestas adjacêntes ao vértice index à fila de prioridade e marca-o como visitado
void addEdges(int index, vector<int>& visited, PQueue* fila, Graph G)
{
    visited[index] = 1;
    for (auto adj: G.edges[index])
    if (!visited[adj.first]) fila->add({{index, adj.first},adj.second});
}

vector<pair<pair<int, int>, int>> prim(Graph G, int iN)
{
    //Visitados
    vector<int> visited(G.N); fill(visited.begin(), visited.end(), 0);
    //Arestas da AGM {{Vi, Vf}, Peso}
    vector<pair<pair<int, int>, int>> MSTEdges;
    // Fila de prioridade
    PQueue fila;
    // Contador de arestas e quantidade de arestas da AGM
    int edgesC = 0, edgesMST = G.N-1;
    
    //Adiciona as arestas do vértice inicial
    addEdges(iN, visited, &fila, G);
    
    //Enquanto a fila não estiver vazia e não tiver todas as arestas da AGM
    while (!fila.isEmpty() && edgesC != edgesMST)
    {
        //Pega a melhor aresta na fila
        pair<pair<int,int>,int> edge = fila.poll();
        //Guarda a informação do vértice alvo
        int index = edge.first.second;
        //Se não tiver sido visitado
        if (!visited[index])
        {
            //Adiciona nas arestas da AGM
            MSTEdges.push_back(edge);
            //Incrementa contador
            edgesC++;
            //Adiciona as arestas adjacêntes ao vértice alvo na fila de p.
            addEdges(index, visited, &fila, G);
        }
    }
    //Caso não exista AGM
    if (edgesC!=edgesMST) return {};
    //Retorna arestas da AGM (Trios {{Vi, Vf},Peso})
    return MSTEdges;
}

int main(){
    int N, E;
    cin >> N >> E;
    Graph G(N, E);
    int a, b, wt;
    for (int e = 0; e < E; e++)
    {
        cin >> a >> b >> wt;
        G.insertEdge(a, b, wt);
    }
/*
    for (int i = 0; i < N; i++)
    {
        for (auto adj: G.edges[i])
        {
            cout << "(" << i << ", " << adj.first << ", " << adj.second << ")" << endl; 
        }
    }
*/
    int MSTCost = 0;
    vector<pair<pair<int, int>, int>> MST = prim(G, INIT_NODE);
    for (auto edge: MST)
    {
        cout << "(" << edge.first.first << "," << edge.first.second << ") ";
        MSTCost += edge.second;
    }
    cout << endl;
    cout << MSTCost << endl;



    return 0;
}