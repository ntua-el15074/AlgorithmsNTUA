#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <climits>
#include <utility>
using namespace std;

struct Connection {
    long int u,v;
    bool operator<(const Connection& other) const {
        if (u == other.u) {
            return v < other.v;
        }
        return u < other.u;
    }
};

struct Interval {
    long int start,end;
};

struct Edge {
    long int v, d;
    Edge(long int dest, long int w) : v(dest), d(w) {}  
};

struct Node {
    long int city, time;
    Node(long int c, long int t) : city(c), time(t) {}  
    bool operator>(const Node& other) const {  
        return time > other.time;  
    }
};

long int findTime(map<long int, vector<Edge>> &graph,
                             long int &fromCity, long int &toCity) {

    for (const Edge& edge : graph[fromCity]) {
        if (edge.v == toCity) {
            return edge.d;
        }
    }

    return -1;
}

long int dijkstra(long int &start, long int &end, long int &T,
                  long int &N, map<long int, vector<Edge>> &graph,
                  map<Connection, Interval> &blockedRoads) {

    vector<long int> min(N + 1, INT_MAX);
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.emplace(start, T);
    min[start] = T;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.city == end) {
            return current.time - T;
        }

        for (const Edge& edge : graph[current.city]) {
            long int next = edge.v;
            long int travelTime = edge.d;
            long int waitTime = 0;

            auto roadBlock = blockedRoads.find({current.city, next});

            if (roadBlock != blockedRoads.end()) {
                long int blockStart = roadBlock->second.start;
                long int blockEnd = roadBlock->second.end;
                if (current.time >= blockStart && current.time < blockEnd) {
                    waitTime = blockEnd - current.time;
                }
            }

            long int arrivalTime = current.time + waitTime + travelTime;
            if (arrivalTime < min[next]) {
                min[next] = arrivalTime;
                pq.emplace(next, arrivalTime);
            }
        }
    }

    return INT_MAX;
}


int main() {

    long int N, M, A, B, T, K;

    cin >> N >> M 
        >> A >> B
        >> T >> K;

    vector<long int> c(K);
    map<long int, vector<Edge>> graph;
    map<Connection, Interval> blockedRoads;

    for (long int i = 0; i < K; ++i) {
        cin >> c[i];
    }

    for (long int i = 0; i < M; ++i) {
        long int u, v, d;
        cin >> u >> v >> d;
        graph[u].emplace_back(v, d);
        graph[v].emplace_back(u, d);
    }

    long int ct = 0;
    for (long int i = 0; i < K - 1; ++i) {
        long int u = c[i], v = c[i + 1];
        long int t = findTime(graph, u, v);
        blockedRoads[{u, v}] = {ct, ct + t};
        blockedRoads[{v, u}] = {ct, ct + t};
        ct += t;
    }

    long int travelTime = dijkstra(A, B, T,
                                   N, graph, blockedRoads);

    cout << travelTime << endl;

    return 0;
}

