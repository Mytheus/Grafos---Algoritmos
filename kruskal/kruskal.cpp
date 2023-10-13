#include <iostream>
#include <bits/stdc++.h>
#include "../utils.h"

using namespace std;

//Returns the Minimum Spanning Tree
vector<edge> kruskal(Graph G)
{
    
    vector<edge> MST;
    //UnionFind, size based on nodes count
    UnionFind UF(G.getNodeCount());
    //Creating a set for each node
    for (int i = 0; i < G.getNodeCount(); i++) UF.makeSet(i);
    //Getting the list of edges [{node1, node2, weight}]
    vector<edge> edges = G.getEdgesList();
    //Sorting ascending
    sort(edges.begin(), edges.end(), [](edge a, edge b)->bool{ return a.weight < b.weight; });
    //Through the edges
    for (auto e: edges)
    {  
        //If they belong to different connected components
        if (UF.Find(e.node1)!=UF.Find(e.node2))
        {
            //Add them to the MST
            MST.push_back(e);
            //Unite the nodes in a connected component
            UF.Union(UF.Find(e.node1), UF.Find(e.node2));
        }
    }
    return MST;
}

int main(int argc, char *argv[])
{
    
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
    vector<edge> MST = kruskal(G);
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
    else{
        if(ans){
            cout << res << endl;
        }
        else{
            cout << MSTCost << endl;
        }
    }
    return 0;
}
