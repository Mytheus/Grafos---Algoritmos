#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int INIT_NODE  = 0;




class PQueue
{
    // Número de elementos dentro da heap
private:
    int heapSize = 0;

    // Lista para os elementos na heap
    vector<pair<int, int>> heap;

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
        pair<int, int> aux = heap[j];
        heap[j] = heap[i];
        heap[i] = aux;
    }
    pair<int, int> removeAt(int i)
    {
        if (isEmpty()) return {-1,-1};
        heapSize--;
        pair<int, int> removido = heap[i];
        this->swap(i, heapSize);
        heap.pop_back();

        if (i == heapSize) return removido;

        pair<int, int> elem = heap[i];

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

    pair<int, int> peek(){
        if (isEmpty()) return {-1, -1};
        return heap.at(0);
    }

    pair<int, int> poll()
    {
        return removeAt(0);
    }

    //Linear
    int contains(pair<int, int> elem)
    {
        for (int i = 0; i < heapSize; i++)
        {
            if (heap.at(i)==elem) return 1;
        }
        return 0;
    }

    void add(pair<int, int> elem)
    {
        heap.push_back(elem);
        swim(heapSize);
        heapSize++;
    }



    int remove (pair<int, int> elem)
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
    int N, E;
    vector<pair<int, int>>* edges;
    bool Dgraf;

    Graph(int N, int E, bool Dgraf=false){
        this->N = N;
        this->E = E;
        this->Dgraf=Dgraf;
        this->edges = new vector<pair<int, int>>[N];
    }

    void insertEdge(int a, int b, int wt)
    {
        edges[a-1].push_back(make_pair(b-1, wt));
        if (!Dgraf) edges[b-1].push_back(make_pair(a-1, wt));
    }

};

int isOpen(int open[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (open[i]) return 1;
    }
    return 0;
}

int min(int array[], int open[], int n)
{
    int m = INT_MAX;
    int pos = -1;
    for (int i = 0; i < n; i++)
    {
        if (open[i] && array[i] < m)
        {
            m = array[i];
            pos = i;
        } 
    }
    return pos;
}

void initializeInt(int* array, int init,  int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = init;
    }
}

void dijkstra(Graph G, int iN)
{
    int d[G.N];
    int p[G.N];
    int open[G.N];
    initializeInt(d, INT_MAX/2, G.N);
    initializeInt(p, -1, G.N);
    initializeInt(open, 1, G.N);
    d[iN] = 0;
    while (isOpen(open, G.N))
    {
        int u = min(d, open, G.N);
        open[u] = 0;
        for (auto adj: G.edges[u])
        {
            if(open[adj.first])
            {
                if (d[u] + adj.second < d[adj.first])
                {
                    d[adj.first] = d[u] + adj.second;
                    p[adj.first] = u;
                }
            }
        }
    }
    for (int i = 0; i < G.N; i++)
    {
        cout << i << ":" << d[i] << " ";
    }
    cout << endl;
}

//Dijkstra com Priority Queue
pair<vector<int>, vector<int>> dijkstraPQ(Graph G, int iN)
{
    //Lista de distâncias, pais e condição (aberto ou fechado)
    vector<int> d(G.N), p(G.N), open(G.N);
    fill_n(d.begin(), G.N, INT_MAX);
    fill_n(p.begin(), G.N, -1);
    fill_n(open.begin(), G.N, 1);
    //Distância do vértice inicial = 0
    d[iN] = 0;
    // Fila de prioridade
    PQueue fila;
    //Adiciona na fila o vértice inicial e a distância
    fila.add({iN, 0});
    //Enquanto houver itens na fila
    while (!fila.isEmpty()){
        //Tira o par vértice e distancia menores da fila
        pair<int, int> vertcost = fila.poll();
        //Separa
        int vert = vertcost.first, minValue = vertcost.second;
        //Seta o vértice como fechado
        open[vert] = 0;
        // Se já temos a melhor distância até o vértice, ignora
        if (!(d[vert]<minValue)) 
        {  
            //Percorre as adjacências
            for (auto adj: G.edges[vert])
            {
                //se tiver aberto
                if(open[adj.first])
                {
                    //Calcula a nova distância até ele
                    int newDist = d[vert] + adj.second;
                    //Se for melhor que a atual
                    if (newDist < d[adj.first])
                    {
                        //Adiciona o pai
                        p[adj.first] = vert;
                        //Atualiza a distância
                        d[adj.first] = newDist;
                        //Adiciona na fila
                        fila.add({adj.first, newDist});
                    }
                }
            }
        }        
    }
    //Retorna a lista de distâncias e o caminho
    return {d, p};
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

    dijkstraPQ(G, INIT_NODE);


    return 0;
}