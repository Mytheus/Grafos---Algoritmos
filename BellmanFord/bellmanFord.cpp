#include <iostream>
#include <bits/stdc++.h>
#include "../utils.h"

using namespace std;

const int INIT_NODE  = 0;





//BF Algorithm
vector<int> bellmanFord(Graph G, int iN)
{
    int N = G.getNodeCount();
    vector<int> d(N);
    fill(d.begin(), d.end(), (INT_MAX/2));
    d[iN] = 0;
    for (int i = 0; i < N-1; i++)
    {
        for (auto e: G.getEdgesList())
        {
            //Se a distância até u + peso da aresta uv < distancia até v
            //Então distancia até v = distancia até u + peso da aresta uv
            if (d[e.node1]!=(INT_MAX/2) && d[e.node1] + e.weight < d[e.node2]) d[e.node2] = d[e.node1] + e.weight;
            // for (int i = 0; i < N; i++)
            // {
            //     cout << d[i] << " ";
            // }
            // cout << endl;
        }
    }
    for (int i = 0; i < N-1; i++)
    {
        for (auto e: G.getEdgesList())
        {
            //Se a distância até u + peso da aresta uv < distancia até v
            //Então distancia até v = distancia até u + peso da aresta uv
            if (d[e.node1]!=(INT_MAX/2) && d[e.node1] + e.weight < d[e.node2])
            {
                d[e.node2] = -(INT_MAX/2);
                return {};
            }
        }
    }

    return d;
}

int main(int argc, char *argv[]){
    string input_file = "";
    string output_file = "";
    int startVertex = 1;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
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
    Graph G(N, E, true);
    int a, b, wt;
    for (int e = 0; e < E; e++)
    {
        fin >> a >> b >> wt;
        G.insertEdge(a, b, wt);
    }
    fin.close();
    vector<int> dist = bellmanFord(G, startVertex-1);
    if (dist.size()>0){
        if (!(output_file==""))
        {
            ofstream fout(output_file);
            if (!fout)
            {
                cerr << "Could not open output file:" << output_file << endl;
                return 1;
            }
            fout << "I = Inaccessible" << endl;
            for (int i = 0; i < N; i++) {
                fout << i+1 << ":" << dist[i] << " ";
            }
            fout << endl;
            fout.close();
        }
        cout << "I = Inaccessible" << endl;
        for (int i = 0; i < N; i++) {
            if (dist[i] == (INT_MAX)/2) cout << i+1 << ":" << "I" << " ";
            else cout << i+1 << ":" << dist[i] << " ";
        }
        cout << endl;
        }
        else
        {
            if (!(output_file==""))
            {
                ofstream fout(output_file);
                if (!fout)
                {
                    cerr << "Could not open output file:" << output_file << endl;
                    return 1;
                }
                for (int i = 0; i < N; i++) {
                    fout << "The graph has a negative cycle!";
                }
                fout << endl;
                fout.close();
            }
            else{
                cout << "The graph has a negative cycle!" << endl;
            }
        }

    return 0;
}