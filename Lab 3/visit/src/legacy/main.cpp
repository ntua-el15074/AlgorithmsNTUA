// #include <algorithm> 
#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <queue>
using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    long int v,d;
};

struct Block {
    long int startTime;
    long int endTime;
};

ostream& operator << (ostream& o, Block &b) {
    o << "Block start at: " << b.startTime << ", and ends at: " << b.endTime << endl;
    return o;
}

long int findTime(map<int,vector<Edge>> &graph, long int &v, long int &u){ 
    for (auto &next: graph[v]) {
        if (next.v == u) return next.d;
    }
    return 0;
}

int main() { 
    long int N,M;
    long int A,B,T,K;
    cin >> N >> M >> A >> B >> T >> K;

    map<int,vector<Edge>> graph;
    map<pair<int,int>,Block> blocked;
    vector<long int> c(K);

    for (int i=0; i<K; i++) {
        cin >> c[i];
    }

    for (int i=0; i<M; i++) {
        long int v1,v2,d;
        cin >> v1 >> v2 >> d;
        graph[v1].push_back({v2,d});
        graph[v2].push_back({v1,d});
    }

    int presidential_t = 0;
    long int extra_time,u,v;
    for (int i=0; i<K-1; i++) { 
        u = c[i];
        v = c[i+1];
        extra_time = findTime(graph,u,v);
        blocked[{u,v}] = {presidential_t, presidential_t+extra_time};
        blocked[{v,u}] = {presidential_t, presidential_t+extra_time};
        cout << blocked[{u,v}];
        presidential_t += extra_time;
    }

    return 0;
}
