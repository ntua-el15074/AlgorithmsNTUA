#include <iostream>
#include <queue>
#include <climits>
#include <vector>
#include <algorithm>

struct Edge {
    long int source;
    long int destination;
    long int distance;
    long int load;
    long int speed;
    long int total_distance;
    long int cost;
};

bool compare(struct Edge e1, struct Edge e2){
    return (e1.source < e2.source);
}

struct Node {
    long int index;
    long int distance;
};

struct CompareNode {
    bool operator()(const Node& n1, const Node& n2) {
        return n1.distance > n2.distance;
    }
};

void Dijkstra(long int V, std::vector<Edge>& edges) {
    std::vector<long int> distance(V + 1, INT_MAX);
    distance[1] = 0; // Source node is 1

    std::priority_queue<Node, std::vector<Node>, CompareNode> pq;
    pq.push({1, 0});

    while (!pq.empty()) {
        int current = pq.top().index;
        int dist = pq.top().distance;
        pq.pop();

        if (dist > distance[current]) {
            continue;
        }

        for (auto edge : edges) {
            if (edge.destination == current) {
                long int next = edge.source;
                long int cost = edge.cost;

                if (distance[next] > distance[current] + cost) {
                    distance[next] = distance[current] + cost;
                    pq.push({next, distance[next]});
                }
            }
        }
    }

    // Print shortest paths
    for (int i = 2; i <= V; ++i) {
        if (distance[i] == INT_MAX) {
            continue;
        } else {
            if (i == V) {
                std::cout << distance[i] << std::endl;
            } else {
                std::cout << distance[i] << " ";
            }
        }
    }
}

int main () {
    long int N;
    std::cin >> N;
    std::vector<struct Edge> edges;


    for (long int i=0; i<N-1; i++) { 
        long int source;
        long int destination;
        long int distance;
        long int load=0;
        long int speed=0;
        long int total_distance = 0;

        std::cin >> source;
        std::cin >> destination;
        std::cin >> distance;

        if (source < destination){ 
            edges.push_back({destination,source,distance,load,speed,total_distance});
        }
        else { 
            edges.push_back({source,destination,distance,load,speed,total_distance});
        }
    }

    sort(edges.begin(),edges.end(),compare);

    for (long int i=0; i<N-1; i++) { 
        long int p;
        long int s;
        std::cin >> p;
        std::cin >> s;
        edges[i].load = p;
        edges[i].speed = s;
        edges[i].cost = p + s*edges[i].distance;
    }

    for (long int i=N-2; i>=0; i--){ 
        struct Edge current = edges[i];
        long int total_distance = current.distance;
        while (current.destination != 1) { 
            total_distance += edges[current.destination-2].distance;
            current = edges[current.destination-2];
            edges.push_back({edges[i].source,current.destination,
                            0,0,0,0,
                            total_distance*edges[i].speed+edges[i].load});
        }
    }

    Dijkstra(N,edges);


    return 0;
}
