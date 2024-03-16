#include <algorithm>
#include <deque>
#include <iostream>

using namespace std;

// Merge two sorted deques into one sorted deque
void merge(deque<int>& left, deque<int>& right, deque<int>& result) {
    while (!left.empty() && !right.empty()) {
        if (left.front() <= right.front()) {
            result.push_back(left.front());
            left.pop_front();
        } else {
            result.push_back(right.front());
            right.pop_front();
        }
    }

    // Copy any remaining elements
    while (!left.empty()) {
        result.push_back(left.front());
        left.pop_front();
    }

    while (!right.empty()) {
        result.push_back(right.front());
        right.pop_front();
    }
}

// Merge Sort function for deque
void mergeSort(std::deque<int>& arr) {
    if (arr.size() <= 1) {
        return; // Base case: the deque is already sorted or empty
    }

    int middle = arr.size() / 2;

    deque<int> left;
    deque<int> right;

    // Split the deque into two halves
    for (int i = 0; i < middle; ++i) {
        left.push_back(arr[i]);
    }

    for (int i = middle; i < arr.size(); ++i) {
        right.push_back(arr[i]);
    }

    // Recursively sort the two halves
    mergeSort(left);
    mergeSort(right);

    // Merge the sorted halves
    arr.clear();
    merge(left, right, arr);
}

int main(int argc, char **argv){ 
    
    //Initialize all items
    int iteration = atoi(argv[1]);
    int K,N;
    int s[200000];

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

    std::deque<int> d;
    std::deque<int> c;
    int global_max = 0;
    int next;
    int median;

    //Initialize Deque
    for (int j=0; j<K; j++){ 
        c.push_back(s[j]);
    }

    d = c;

    // Sort the deque in ascending order
    mergeSort(c);

    median = c[(K+1)/2-1];
    global_max = median;

    for (int i=K; i<N; i++){

        c = d;

        c.pop_front();
        
        next = s[i];

        c.push_back(next);

        d = c;

        mergeSort(c);

        if (K % 2 == 0) median = (c[K/2-1]+c[K/2])/2;
        else median = c[(K+1)/2-1];

        if (median > global_max) global_max = median;
    }

    //----------------------------------------------------
    
    //End Clock
    clock_t end = clock();
    time_spent += (double)(end-begin)/ CLOCKS_PER_SEC;

    //Output the result
    printf("%d\n", K);
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
