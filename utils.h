#ifndef UTILS_H
#define UTILS_H


#include <bits/stdc++.h>



struct edge
{
    int node1;
    int node2;
    int weight;

    bool equals(struct edge b)
    {
        if (this->node1 == b.node1 && this->node2 == b.node2 && this->weight==b.weight) return true;
        return false;
    }
};

struct Graph
{
private:
    //Nº de vértices e arestas
    int N, E;
    //Vetor de adjacências [[{V, Peso}]]
    std::vector<std::pair<int, int>>* adj;
    //Vetor de arestas [{{Vi, Vf}, Peso}]
    std::vector<edge> edges;
    //Flag de grafo direcionado
    bool Dgraf;

public:
    //Construtor (Número de vértices, arestas e flag de Digrafo (default = false))
    Graph(int N, int E, bool Dgraf=false)
    {
        this->N = N;
        this->E = E;
        this->Dgraf=Dgraf;
        this->adj = new std::vector<std::pair<int, int>>[N];
    }


    //Insere arestas no grafo
    void insertEdge(int a, int b, int wt)
    {
        //Insere a ida, se não for digrafo insere a volta
        adj[a-1].push_back(std::make_pair(b-1, wt));
        if (!Dgraf) adj[b-1].push_back(std::make_pair(a-1, wt));
        edges.push_back({a-1, b-1, wt});
        if (!Dgraf) edges.push_back({b-1, a-1, wt});
    }

    int getNodeCount()
    {
        return N;
    }

    int getEdgeCount()
    {
        return E;
    }

    std::vector<edge> getEdgesList()
    {
        return edges;
    }

    std::vector<std::pair<int, int>>* getAdjList()
    {
        return adj;
    }


};

struct UnionFind
{
    int size;
    int* parent;
    int* rank;

    UnionFind(int size)
    {
        this->size = size;
        this->parent = new int[size];
        this->rank = new int[size];
    }

    ~UnionFind()
    {
        delete[] parent;
        delete[] rank;
    }

    void makeSet(int x)
    {
        parent[x] = x;
        rank[x] = 0;
    }

    void Union(int x, int y)
    {
        if (rank[x] >= rank[y])
        {
            parent[y] = x;
            if (rank[x] == rank[y]) rank[x]+=1;
        }
        else parent[x] = y;
    }

    int Find(int x)
    {
        if(parent[x]!=x) parent[x] = this->Find(parent[x]);
        return parent[x];
    }


};

#endif