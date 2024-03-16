#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

struct Edge {
    long int v1,v2;
    long long t;
};

bool customcomparator (const Edge& e1, const Edge& e2) {
    return e1.t > e2.t;
}

class DSU {
    vector<int> parent;
    vector<int> rank;
 
public:
    DSU(long long n)
    {
        parent.resize(n + 1);
        rank.resize(n + 1);
 
        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            rank[i] = 1;
        }
    }
 
    int find(long long i) {
        if (parent[i] == -1) {
            return i;
        }
       
        return parent[i] = find(parent[i]);
    }
 
    void unite(int x, int y) {
        long int s1 = find(x);
        long int s2 = find(y);
 
        if (s1 != s2) {
            if (rank[s1] < rank[s2]) {
                parent[s1] = s2;
            }
            else if (rank[s1] > rank[s2]) {
                parent[s2] = s1;
            }
            else {
                parent[s2] = s1;
                rank[s1] += 1;
            }
        }
    }
};

long long kruskal(long long K, long long vertices, long long edges, vector<Edge> edgelist){
    DSU s(vertices);
    vector<Edge> new_edgelist;
    for (auto edge: edgelist) {
        long long t = edge.t;
        long int x = edge.v1;
        long int y = edge.v2;


        if (s.find(x) != s.find(y)) {
            s.unite(x, y);
            new_edgelist.push_back({x,y,t});
        }
    }

    if (K >= new_edgelist.size()) {
        return 0;
    }

    return new_edgelist[new_edgelist.size() - K - 1].t;
}

int main() {
    long long N, M, K;
    cin >> N >> M >> K;
    vector<Edge> edges;

    if (K >= M) {
        cout << "infinity" << endl;
        return 0;
    }

    for (int i = 0; i < M; i++) {
        long int v1, v2;
        long long t;
        cin >> v1 >> v2 >> t;
        edges.push_back({v1,v2,t});
    }

    std::sort(edges.begin(), edges.end(), customcomparator);

    long long res = kruskal(K,N,M,edges);
    if (res == 0){
        cout << "infinity" << endl;
        return 0;
    }

    cout << res << endl;

    return 0;
}

