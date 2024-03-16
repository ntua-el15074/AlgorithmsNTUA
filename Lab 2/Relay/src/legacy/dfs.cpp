#include <iostream>
#include <vector>
#include <algorithm>

struct Next {
    long int distance_to_child;
    long int child;
};

struct Node {
    long int load;
    long int speed;
    long int parent;
    long int distance_to_parent;
    long int total_distance = 0;
    std::vector<Next> next;
};

void computeTotalDistanceAndOptimalCost(std::vector<bool> &visited,
                                        long int current, std::vector<Node> &nodes,
                                        std::vector<long int> &OPT, long int traversed) {
    visited[current] = true;
    long int total_cost = (current == 1) ? 0 : nodes[current].load;

    if (current != 1) {
        long int current_speed = nodes[current].speed;
        total_cost += current_speed * nodes[current].total_distance;

        long int current_cost = nodes[current].distance_to_parent;
        long int parent_node = nodes[current].parent;

        while (parent_node != -1) {
            long int temp = nodes[current].load + current_cost * current_speed + OPT[parent_node];
            current_cost += nodes[parent_node].distance_to_parent;

            if (temp < total_cost) {
                total_cost = temp;
            }

            parent_node = nodes[parent_node].parent;
        }
    }

    OPT[current] = total_cost;

    for (auto &next : nodes[current].next) {
        if (!visited[next.child]) {
            nodes[next.child].total_distance = traversed + next.distance_to_child;
            computeTotalDistanceAndOptimalCost(visited, next.child, nodes, OPT,
                                                traversed + next.distance_to_child);
        }
    }
}

void printSolution(std::vector<long int> &OPT, int &N) {
    for (int i = 2; i <= N; i++) {
        std::cout << OPT[i];
        if (i != N) {
            std::cout << " ";
        } else {
            std::cout << std::endl;
        }
    }
}

int main() {
    int N;
    std::cin >> N;
    std::vector<Node> nodes(N + 1);
    std::vector<long int> OPT(N + 1, 0);
    std::vector<bool> visited(N + 1, false);

    nodes[1].parent = -1;

    for (int i = 2; i <= N; i++) {
        long int source, destination, distance;
        std::cin >> source >> destination >> distance;

        if (source < destination) {
            nodes[source].next.push_back({ distance, destination });
            nodes[destination].parent = source;
            nodes[destination].distance_to_parent = distance;
        } else {
            nodes[destination].next.push_back({ distance, source });
            nodes[source].parent = destination;
            nodes[source].distance_to_parent = distance;
        }
    }

    for (int i = 2; i <= N; i++) {
        long int load, speed;
        std::cin >> load >> speed;
        nodes[i].load = load;
        nodes[i].speed = speed;
    }

    computeTotalDistanceAndOptimalCost(visited, 1, nodes, OPT, 0);
    printSolution(OPT, N);

    return 0;
}

