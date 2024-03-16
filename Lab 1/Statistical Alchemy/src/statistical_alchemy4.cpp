#include <iostream>
using namespace std;
 
int check_for_proper_median(int arr[], int& N, int& K, int& median)
{
    int prefix_sums[N];
    int maximum;
    int minimum = 0;

    for (int i = 0; i < N; i++) {

        if (arr[i] >= median) { 
            prefix_sums[i] = 1;
        } else { 
            prefix_sums[i] = -1;
        }

        if (i > 0) {
            prefix_sums[i] += prefix_sums[i - 1];
        }

    }
 
    maximum = prefix_sums[K - 1];
 
    for (int i = K; i < N; i++) {
        minimum = min(minimum, prefix_sums[i - K]);
        maximum = max(maximum, prefix_sums[i] - minimum);
    }
    if (maximum > 0) { 
        return 0;
    }

    return 1;
}
 
int max_median(int arr[], int N, int K)
{
    int left = 1; 
    int right = N + 1;
 
    int median = -1;
 
    while (left <= right) {
        int middle = (left + right) / 2;
        if (check_for_proper_median(arr, N, K, middle) == 0) {
            median = middle;
            left = middle + 1;
        }
        else
            right = middle - 1;
    }
    return median;
}
 

int main(int argc, char **argv){ 
    
    int iteration = atoi(argv[1]);
    int K,N;
    int s[200000];

    double time_spent = 0.0;

    cin >> N;
    cin >> K;

    for (int i=0; i<N; i++){ 
        cin >> s[i];
    }

    //Begin Clock
   clock_t begin = clock();

    //Solution
    //----------------------------------------------------

    int global_max = max_median(s, N, K);
    
    //----------------------------------------------------

    cout << global_max;
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
