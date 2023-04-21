#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
using namespace std;

int bfs(vector<vector<int>>& rGraph, int vertexesNumber, int s, int t, vector<int>& parent) {
    vector<bool> used(vertexesNumber, 0); 
    queue <int> q;
    q.push(s);
    used[s] = 1;
    parent[s] = -1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < vertexesNumber; v++) {
            if (!used[v] && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                used[v] = 1;
            }
        }
    }
    return (used[t] == true);
}

void dfs(vector<vector<int>> rGraph, int vertexesNumber, int s, vector<bool>& used) {
    used[s] = 1;
    for (int i = 0; i < vertexesNumber; i++)
       if (rGraph[s][i] && !used[i])
           dfs(rGraph, vertexesNumber, i, used);
}

void minCut(vector<vector<int>> & graph, int vertexesNumber, int s, int t) {
    vector<vector<int>> rGraph;
    for (int i = 0; i < vertexesNumber; i++) {
        for (int j = 0; j < vertexesNumber; j++) {
            rGraph[i][j] = graph[i][j];
        }
    }
    vector<int> parent(vertexesNumber);
    while (bfs(rGraph, vertexesNumber, s, t, parent)) {
        int pathFlow = INT_MAX;
        for(int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }
    }
    vector<bool> used(vertexesNumber, 0);
    dfs(rGraph, vertexesNumber, s, used);

    for (int i = 0; i < vertexesNumber; i++) {
        for (int j = 0; j < vertexesNumber; j++) {
            if (used[i] && !used[j] && graph[i][j])
                cout << i << " - " << j << '\n';
        }
    }
}

int main() {
    int vertexesNumber = 6;
    vector<vector<int>> graph = { 
        {0, 6, 9, 0, 0, 0},
        {0, 0, 16, 11, 0, 0},
        {0, 6, 0, 0, 19, 0},
        {0, 0, 3, 0, 0, 25},
        {0, 0, 0, 17, 0, 8},
        {0, 0, 0, 0, 0, 0}
    };

    minCut(graph, vertexesNumber, 0, 5);
}
