#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
    long int destination;
    long int distance;
    long int load;
    long int speed;
};

long int costAt(struct Node &node) {
    return node.load + node.speed * node.distance;
}

void printSolution(std::vector<long int> OPT, int N) {
    for (int i = 2; i <= N; i++) {
        if (i == N) {
            std::cout << OPT[i] << std::endl;
        } else {
            std::cout << OPT[i] << " ";
        }
    }
}

int main() {
    int N;
    std::cin >> N;
    std::vector<Node> nodes(N + 1);
    std::vector<long int> OPT(N + 1, 0);

    for (int i = 2; i <= N; i++) {
        long int source, destination, distance;
        std::cin >> source >> destination >> distance;

        if (source < destination) {
            nodes[destination].destination = source;
            nodes[destination].distance = distance;
        } else {
            nodes[source].destination = destination;
            nodes[source].distance = distance;
        }
    }

    for (int i = 2; i <= N; i++) {
        long int load, speed;
        std::cin >> load >> speed;

        nodes[i].load = load;
        nodes[i].speed = speed;
    }

    for (int i = 2; i <= N; i++) {
        int next = nodes[i].destination;
        int current_speed = nodes[i].speed;

        OPT[i] = costAt(nodes[i]);

        while (next != 1) {
            if (current_speed*nodes[next].distance < nodes[next].load + nodes[next].speed*nodes[next].distance) { 
                OPT[i] += current_speed*nodes[next].distance;
            }
            else { 
                OPT[i] += nodes[next].load + nodes[next].speed*nodes[next].distance;
                current_speed = nodes[next].speed;
            }
            next = nodes[next].destination;

        }
    }

    printSolution(OPT, N);

    return 0;
}

