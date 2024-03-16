#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
#include <unistd.h>
using namespace std;

#define MAX_DIFF 2
#define MAX_PROFIT 1
#define MIN_WEIGHT 0

//Η υλοποίηση της Union Find βρεθηκε στο internet
//δεν είναι δική μου 

struct result {
    int sum_of_weights = 0;
    int sum_of_profits = 0;
    int gcd;
};

int gcd(int a, int b) 
{ 
    int result = min(a, b); 
    while (result > 0) { 
        if (a % result == 0 && b % result == 0) { 
            break; 
        } 
        result--; 
    } 
  
    return result; 
}

bool max_profitComparator(const std::vector<double>& a, const std::vector<double>& b) {
        return a[1] > b[1];
}

bool differentialComparator(const std::vector<double>& a, const std::vector<double>& b) {
        return a[4] > b[4];
}

class DSU { 
    vector<long long> parent;
    vector<long long> rank;
  
public: 
    DSU(int n) 
    { 
  
        for (int i = 0; i < n; i++) { 
            parent[i] = -1; 
            rank[i] = 1; 
        } 
    } 
  
    // Find function 
    int find(int i) 
    { 
        if (parent[i] == -1) 
            return i; 
  
        return parent[i] = find(parent[i]); 
    } 
  
    // Union function 
    void unite(int x, int y) 
    { 
        int s1 = find(x); 
        int s2 = find(y); 
  
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

struct result MST(int vertices, int edges, vector<vector<double>> edgelist, int MACRO) { 
    DSU tree(vertices);
    struct result res;

    if (MACRO == MIN_WEIGHT){ 
        sort(edgelist.begin(), edgelist.end());
    }

    if (MACRO == MAX_PROFIT) {
        sort(edgelist.begin(), edgelist.end(), max_profitComparator);
    }

    if (MACRO == MAX_DIFF) {
        sort(edgelist.begin(), edgelist.end(), differentialComparator);
    }

    for(int i=0; i<edges; i++){ 
        if (tree.find(edgelist[i][2]) != tree.find(edgelist[i][3])) { 
            tree.unite(edgelist[i][2], edgelist[i][3]);
            res.sum_of_weights += edgelist[i][0];
            res.sum_of_profits += edgelist[i][1];
        }
    }

    int fr = gcd((int)res.sum_of_profits, (int)res.sum_of_weights);
    res.gcd = fr;

    return res;
}

int main(int argc, char **argv){ 
    // int iteration = atoi(argv[1]);
    int vertices,edges;
    int sum_of_weights = 0;
    int sum_of_profits = 0;
    
    std::cin >> vertices;
    std::cin >> edges;

    double source, destination;
    double profit, weight;
    double differential;
 
    vector<vector<double> > edgelist;

    //Input
    for (int i=0; i<edges; i++){ 
        std::cin >> source;
        std::cin >> destination;
        std::cin >> profit;
        std::cin >> weight;
        source -= 1;
        destination -= 1;
        differential = 0;
        edgelist.push_back({ weight, profit, source, destination, differential});
    }

    //Solution
    //----------------------------------------------------

    struct result min_weight = MST(vertices, edges, edgelist, MIN_WEIGHT);
    struct result max_profit = MST(vertices, edges, edgelist, MAX_PROFIT);
    vector<struct result> answer;
    
    double left = 1;
    double right = ((double)max_profit.sum_of_profits/min_weight.sum_of_weights);
    double c = (left + right)/2;

    struct result res;
    vector<struct result> answers;


    while (right - left >= 0.01) { 
        for (int i = 0; i < edges; i++) { 
            edgelist[i][4] = edgelist[i][1] - c*edgelist[i][0];
        }

        res = MST(vertices, edges, edgelist, MAX_DIFF);
        answers.push_back(res);

        if (res.sum_of_profits - res.sum_of_weights*c >= 0) {
            left = c;
        } else { 
            right = c;
        }

        c = (left + right)/2;
    }
    // printf("Iteration %d\n", iteration);
    //
    // for (auto item : answers) {
    //     printf("%d %d\n", item.sum_of_profits/item.gcd, item.sum_of_weights/item.gcd);
    // }
    //
    // printf("\n");

    
    printf("%d %d\n", res.sum_of_profits/res.gcd, res.sum_of_weights/res.gcd);
    //----------------------------------------------------

    return 0;

}

