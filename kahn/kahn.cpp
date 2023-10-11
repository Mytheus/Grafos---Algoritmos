#include <iostream>
#include <bits/stdc++.h>
#include "../utils.h"

using namespace std;

vector<int> kahnTO(Graph G)
{

    int N = G.getNodeCount();
    vector<int> inDegree(N), order;
    for (int i = 0; i < N; i++)
    {
        for (auto adj: G.getAdjList()[i]) inDegree[adj.first]++;
    }
    queue<int> q;
    for (int i =0; i < N; i++) if (inDegree[i] == 0) q.push(i);
    int index;
    while(!q.empty())
    {
        index = q.front();
        q.pop();
        order.push_back(index);
        for (auto adj: G.getAdjList()[index])
        {
            if (--inDegree[adj.first] == 0)
            {
                q.push(adj.first);
            }
        }
    }
    
    return order;

}


int main(int argc, char *argv[]){
    int N, E;
    cin >> N >> E;
    Graph G(N, E, true);
    int a, b, wt;
    for (int e = 0; e < E; e++)
    {
        cin >> a >> b >> wt;
        G.insertEdge(a, b, wt);
    }
    vector<int> order = kahnTO(G);
    for (auto i: order) cout << i << " ";
    cout << endl;
    

    return 0;
}