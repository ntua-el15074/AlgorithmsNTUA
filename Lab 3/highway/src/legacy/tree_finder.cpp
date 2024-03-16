#include <iostream>
#include <vector>
using namespace std;

struct Adjacent {
    int v2,t;
};

struct Edge {
    int v1,v2,t;
};

struct Tree {
    vector<Edge> edges;
};

struct Forest { 
    vector<Tree> trees;
};

void dfs(int v, vector<vector<Adjacent>>& adj, vector<bool>& visited, Tree& tree) {
    visited[v] = true;

    for (const Adjacent& adjNode : adj[v]) {
        tree.edges.push_back({v,adjNode.v2,adjNode.t});
        if (!visited[adjNode.v2]) {
            dfs(adjNode.v2, adj, visited, tree);
        }
    }
}

int main(int argc, char **argv) {
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<Adjacent>> adj(N + 1);
    vector<bool> visited(N + 1, false);
    Forest forest;

    for (int i = 0; i < M; i++) {
        int v1, v2, t;
        cin >> v1 >> v2 >> t;
        adj[v1].push_back({v2, t});
        adj[v2].push_back({v1, t});
    }

    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            Tree tree;
            dfs(i, adj, visited, tree);
            forest.trees.push_back(tree);
        }
    }


    return 0;
}

