#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
    int source;
    int destination;
    int distance;
    int load;
    int speed;
    int total_distance;
    int total_time;
};


bool compare(struct Edge e1, struct Edge e2){
    return (e1.source < e2.source);
}

int main () {
    int N;
    std::cin >> N;
    std::vector<struct Edge> edges;


    for (int i=0; i<N-1; i++) { 
        int source;
        int destination;
        int distance;
        int load=0;
        int speed=0;
        int total_distance=0;
        int total_time=0;

        std::cin >> source;
        std::cin >> destination;
        std::cin >> distance;

        if (source < destination){ 
            edges.push_back({destination,source,distance,load,speed,total_distance,total_time});
        }
        else { 
            edges.push_back({source,destination,distance,load,speed,total_distance,total_time});
        }
    }
    sort(edges.begin(),edges.end(),compare);

    for (int i=0; i<N-1; i++) { 
        int p;
        int s;
        std::cin >> p;
        std::cin >> s;
        edges[i].load = p;
        edges[i].speed = s;
    }

    for (auto edge:edges) {
        std::cout << "SOURCE:" << edge.source << " "
                    << "DESTINATION:" << edge.destination << " "
                    << "DISTANCE:" << edge.distance << " " 
                    << "LOAD:" << edge.load << " "
                    << "SPEED:" << edge.speed << std::endl;

    }

    return 0;
}
