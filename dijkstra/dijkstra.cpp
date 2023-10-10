#include <iostream>
#include <bits/stdc++.h>
#include "../utils.h"

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


/*
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
*/

//Dijkstra with Priority Queue
pair<vector<int>, vector<int>> dijkstraPQ(Graph G, int iN)
{
    int N = G.getNodeCount();
    //Adjacency, parents and condition list (open or closed)
    vector<int> d(N), p(N), open(N);
    fill_n(d.begin(), N, INT_MAX);
    fill_n(p.begin(), N, -1);
    fill_n(open.begin(), N, 1);
    //Initial node distance = 0
    d[iN] = 0;
    // Priority Queue
    PQueue fila;
    //Add initial node and distance to queue
    fila.add({iN, 0});
    //While the queue is not empty
    while (!fila.isEmpty()){
        //Remove the node distance pair from queue
        pair<int, int> vertcost = fila.poll();
        //Split
        int vert = vertcost.first, minValue = vertcost.second;
        //Set node to closed
        open[vert] = 0;
        //If the distance to the node is already less than the distance from the pair, ignore
        if (!(d[vert]<minValue)) 
        {  
            //Run through the edges
            for (auto adj: G.getAdjList()[vert])
            {
                //If it is open
                if(open[adj.first])
                {
                    //Calculate the new distance to the node
                    int newDist = d[vert] + adj.second;
                    //If its better than the actual distance
                    if (newDist < d[adj.first])
                    {
                        //Update path
                        p[adj.first] = vert;
                        //Update distance
                        d[adj.first] = newDist;
                        //Add to the queue
                        fila.add({adj.first, newDist});
                    }
                }
            }
        }        
    }
    //Return a pair of vectors, distance and parents
    return {d, p};
}

int main(int argc, char *argv[]){
    string input_file = "";
    string output_file = "";
    int startVertex = 0;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-s: mostra a solução (em ordem crescente)" << endl;
            return 0;
        }
        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1)
        {
            output_file = argv[++i];
        }
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1)
        {
            input_file = argv[++i];
        }
        else if (strcmp(argv[i], "-i") == 0 && i < argc - 1)
        {
            startVertex = atoi(argv[++i]);
        }
    }

    if (input_file == "")
    {
        cerr << "No input file specified. Use the -f parameter." << endl;
        return 1;
    }
    
    ifstream fin(input_file);
    if (!fin)
    {
        cerr << "Could not open input file: " << input_file << endl;
        return 1;
    }

    int N, E;
    fin >> N >> E;
    Graph G(N, E);
    int a, b, wt;
    for (int e = 0; e < E; e++)
    {
        fin >> a >> b >> wt;
        G.insertEdge(a, b, wt);
    }
    fin.close();
    pair<vector<int>,vector<int>> res = dijkstraPQ(G, startVertex);
    vector<int> dist = res.first;
    vector<int> parent = res.second;

    if (!(output_file==""))
    {
        ofstream fout(output_file);
        if (!fout)
        {
            cerr << "Could not open output file:" << output_file << endl;
            return 1;
        }
        for (int i = 0; i < N; i++) {
            fout << i+1 << ":" << dist[i] << " ";
        }
        fout << endl;
        fout.close();
    }
    
    for (int i = 0; i < N; i++) {
        cout << i+1 << ":" << dist[i] << " ";
    }
    cout << endl;


    return 0;
}