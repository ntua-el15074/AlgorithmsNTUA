#include <algorithm>
#include <deque>
#include <iostream>
#include "headerfiles/radxsort.hpp"

int main(int argc, char **argv){ 
    
    //Initialize all items
    int iteration = atoi(argv[1]);
    int K,N;
    int s[200000];
    int global_max = 0;
    int median;

    double time_spent = 0.0;

    std::cin >> N;
    std::cin >> K;

    for (int i=0; i<N; i++){ 
        std::cin >> s[i];
    }

    //Begin Clock
    clock_t begin = clock();

    //Solution
    //----------------------------------------------------
    
    std::deque<int> dq;
    std::deque<int> temp;
    std::deque<int> output;
    
    for(int j=0; j<K; j++){ 
        dq.push_back(s[j]);
    }

    temp = dq;

    radxsort(temp, K);

    if (K%2 == 1){ 
        median = temp[(K+1)/2-1];
    }
    else { 
        // median = ((temp[K/2-1]+temp[K/2])/2);
        // median = temp[(K+1)/2-1];
        // median = ((temp[K/2+1]+temp[K/2])/2);
        // median = temp[(K+1)/2];
        median = temp[(K+1)/2+1];
        // std::cout << "{" << median << " " << median1 << " " << median2 << " ";
        // std::cout << median3 << " " << median4 << "}" << std::endl;
    }

    output.push_back(median);

    for (int i=0; i<N-K; i++){

        dq.pop_front();

        dq.push_back(s[i+K]);

        temp = dq;

        radxsort(temp, K);

        // median = temp[w];
        if (K%2 == 1){ 
            median = temp[(K+1)/2-1];
        }
        else { 
            // median = ((temp[K/2-1]+temp[K/2])/2);
            median = temp[(K+1)/2-1];
            // median4 = ((temp[K/2+1]+temp[K/2])/2);
            // median = temp[(K+1)/2];
            // median = temp[(K+1)/2+1];
            // std::cout << "{" << median << " " << median1 << " " << median2 << " ";
            // std::cout << median3 << " " << median4 << "}" << std::endl;
        }

        output.push_back(median);

    }

    global_max = find_max(output, N-K+1);
    //----------------------------------------------------
    
    //End Clock
    clock_t end = clock();
    time_spent += (double)(end-begin)/ CLOCKS_PER_SEC;

    //Output the result
    printf("Iteration %d: %d\n", iteration, global_max);
    printf("Elapsed time is %f seconds\n", time_spent);

    //Write to file
    FILE *fptr;

    fptr = fopen("outputs.txt", "a");

    if(fptr == NULL){
        printf("Error\n");
        return 1;
    }

    fprintf(fptr, "iteration %d: %d\n", iteration, global_max);
    fclose(fptr);

    return 0;

}
