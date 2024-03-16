#include <iostream>
#include <map>
#include <vector>
#include <limits>
#include <algorithm>
#include <deque>
using namespace std;

typedef long long ll;

struct CHT {

    struct Line {

        ll slope;
        ll yIntercept;

        Line(double slope, ll yIntercept) : slope(slope), yIntercept(yIntercept) {}

        ll val(ll x) {
            return slope * x + yIntercept;
        }
        
        long double intersect(Line y) {
            return (long double)(y.yIntercept - yIntercept) / (slope - y.slope);
        }

        // ll intersect(Line y) {
        //     return (y.yIntercept - yIntercept + slope - y.slope - 1) / (slope - y.slope);
        // }
    };

    deque<pair<Line, ll>> dq;

    void insert(ll slope, ll yIntercept) {
        Line newLine(slope, yIntercept);

        while (!dq.empty() && dq.back().second >= dq.back().first.intersect(newLine))
            dq.pop_back();

        if (dq.empty()) {
            dq.emplace_back(newLine, 0);
            return;
        }

        dq.emplace_back(newLine, dq.back().first.intersect(newLine));
    }

    ll query(ll x) {
        ll value;

        if (x >= dq.back().second) {
            return dq.back().first.val(x);
        }

        for (auto item: dq) {
            if (x > item.second) {
                value = item.first.val(x);
            }
        }

        return value;
    }

};


struct City { 
    vector<int> neighbors;
    map<int,int> distance;
    int load;
    int speed;
};

void printSolution(std::vector<ll> &OPT, int &N) {
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

    vector<ll> OPT(N+1,0);
    vector<City> nodes(N+1);

    for (int i = 2; i <= N; i++) {
        int v1, v2, distance;
        std::cin >> v1 >> v2 >> distance;

        nodes[v1].neighbors.push_back(v2);
        nodes[v2].neighbors.push_back(v1);
        nodes[v1].distance[v2] = distance;
        nodes[v2].distance[v1] = distance;
    }

    for (int i = 2; i <= N; i++) {
        int load, speed;
        std::cin >> load >> speed;
        nodes[i].load = load;
        nodes[i].speed = speed;
    }

    for (auto neighbor : nodes[1].neighbors) {

        int previous = 1;
        int current = neighbor;
        ll total_distance = 0;
        int next_to_go;

        CHT cht;
        cht.insert(0,0);

        while (nodes[current].neighbors.size() == 2) {

            for (auto next: nodes[current].neighbors) {
                if (next != previous) { 
                    OPT[current] = cht.query(nodes[current].speed) +
                        nodes[current].load +
                        nodes[current].speed*(total_distance+nodes[current].distance[previous]);
                    cht.insert(-(total_distance + nodes[current].distance[previous]),OPT[current]);
                    total_distance += nodes[current].distance[previous];
                    next_to_go = next;
                }
            }

            previous = current;
            current = next_to_go;
        }

        // cht.insert(total_distance,OPT[previous]);
        OPT[current] = cht.query(nodes[current].speed) + nodes[current].load +
            nodes[current].speed*(total_distance + nodes[current].distance[previous]);
    }


    printSolution(OPT, N);

    return 0;
}

