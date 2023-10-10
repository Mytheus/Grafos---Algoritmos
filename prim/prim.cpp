#include <iostream>
#include <bits/stdc++.h>
#include "../utils.h"

using namespace std;

//Nó inicial
const int INIT_NODE = 0;

class PQueue
{
    // Número de elementos dentro da heap
private:
    int heapSize = 0;

    // Lista para os elementos na heap
    vector<edge> heap;

    int less(int i, int j)
    {
        return heap.at(i).weight<=heap.at(j).weight;
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
        edge aux = heap[j];
        heap[j] = heap[i];
        heap[i] = aux;
    }
    edge removeAt(int i)
    {
        if (isEmpty()) return {-1, -1, -1};
        heapSize--;
        edge removido = heap[i];
        this->swap(i, heapSize);
        heap.pop_back();

        if (i == heapSize) return removido;

        edge elem = heap[i];

        sink(i);

        if (heap[i].equals(elem)) swim(i);

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

    edge peek(){
        if (isEmpty()) return {-1, -1, -1};
        return heap.at(0);
    }

    edge poll()
    {
        return removeAt(0);
    }

    //Linear
    int contains(edge elem)
    {
        for (int i = 0; i < heapSize; i++)
        {
            if (heap[i].equals(elem)) return 1;
        }
        return 0;
    }

    void add(edge elem)
    {
        heap.push_back(elem);
        swim(heapSize);
        heapSize++;
    }



    int remove (edge elem)
    {
        for (int i = 0; i < heapSize; i++)
        {
            if (heap[i].equals(elem))
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

//Adiciona as arestas adjacêntes ao vértice index à fila de prioridade e marca-o como visitado
void addEdges(int index, vector<int>& visited, PQueue* fila, Graph G)
{
    visited[index] = 1;
    for (auto adj: G.getAdjList()[index])
    if (!visited[adj.first]) fila->add({index, adj.first, adj.second});
}

vector<edge> prim(Graph G, int iN)
{
    //Visitados
    vector<int> visited(G.getNodeCount()); fill(visited.begin(), visited.end(), 0);
    //Arestas da AGM {{Vi, Vf}, Peso}
    vector<edge> MSTEdges;
    // Fila de prioridade
    PQueue fila;
    // Contador de arestas e quantidade de arestas da AGM
    int edgesC = 0, edgesMST = G.getNodeCount()-1;
    
    //Adiciona as arestas do vértice inicial
    addEdges(iN, visited, &fila, G);
    
    //Enquanto a fila não estiver vazia e não tiver todas as arestas da AGM
    while (!fila.isEmpty() && edgesC != edgesMST)
    {
        //Pega a melhor aresta na fila
        edge e = fila.poll();
        //Guarda a informação do vértice alvo
        int index = e.node2;
        //Se não tiver sido visitado
        if (!visited[index])
        {
            //Adiciona nas arestas da AGM
            MSTEdges.push_back(e);
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

int main(int argc, char *argv[]){
    string input_file = "";
    string output_file = "";
    bool ans = false;
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
        else if (strcmp(argv[i], "-s") == 0)
        {
            ans = true;
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
    vector<edge> MST = prim(G, startVertex);
    int MSTCost = 0;
    string res;
    for (auto e: MST)
    {
        res += "(" + to_string(e.node1+1) + "," + to_string(e.node2+1) + ") ";
        MSTCost += e.weight;
    }
    if (!(output_file==""))
    {
        ofstream fout(output_file);
        if (!fout)
        {
            cerr << "Could not open output file:" << output_file << endl;
            return 1;
        }
        if(ans)
        {
            fout << res << endl;
        }
        else
        {
            fout << MSTCost << endl;
        }
    }
    if(ans){
        cout << res << endl;
    }
    else{
        cout << MSTCost << endl;
    }


    return 0;
}