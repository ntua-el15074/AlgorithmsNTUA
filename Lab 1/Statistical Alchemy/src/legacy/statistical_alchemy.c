#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}


int find_max(int arr[], int n) {  
    int max_element = arr[0];  
    for(int i = 1; i<n; i++) {  
        if(arr[i] > max_element)  
            max_element = arr[i];  
    }  
    return max_element; 
}  

void countingSort(int arr[], int n, int pos) 
{  
    int result[n + 1];  
    int count[10] = {0};    

    // count howmany numbers are present with digit 0-9 at given position 
    for (int i = 0; i < n; i++)  
        count[(arr[i] / pos) % 10]++;  

    // now do prefix sum of the count array 
    for (int i = 1; i < 10; i++)  
        count[i] += count[i - 1];  

    // Place the elements in sorted order  
    for (int i = n - 1; i >= 0; i--) {  
        result[count[(arr[i] / pos) % 10] - 1] = arr[i];  
        count[(arr[i] / pos) % 10]--;  
    }  

    for (int i = 0; i < n; i++)  
        arr[i] = result[i];  
}  

void radxsort(int arr[], int n) {  

    int max_element = find_max(arr, n);  

    // counting sort from the least significant digit to the most significant digit  
    for (int pos = 1; max_element / pos > 0; pos *= 10)  
        countingSort(arr, n, pos);  
}
// function to swap elements
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// function to find the partition position
int partition(int array[], int low, int high) {

    // select the rightmost element as pivot
    int pivot = array[high];

    // pointer for greater element
    int i = (low - 1);

    // traverse each element of the array
    // compare them with the pivot
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {

            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;

            // swap element at i with element at j
            swap(&array[i], &array[j]);
        }
    }

    // swap the pivot element with the greater element at i
    swap(&array[i + 1], &array[high]);

    // return the partition point
    return (i + 1);
}

void quickSort(int array[], int low, int high) {
    if (low < high) {

        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        int pi = partition(array, low, high);

        // recursive call on the left of pivot
        quickSort(array, low, pi - 1);

        // recursive call on the right of pivot
        quickSort(array, pi + 1, high);
    }
}

void bubbleSort(int array[], int size) {

    // loop to access each array element
    for (int step = 0; step < size - 1; ++step) {

        // loop to compare array elements
        for (int i = 0; i < size - step - 1; ++i) {

            // compare two adjacent elements
            // change > to < to sort in descending order
            if (array[i] > array[i + 1]) {

                // swapping occurs if elements
                // are not in the intended order
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }
}

void opt_bubbleSort(int array[], int size) {

    // loop to access each array element
    for (int step = 0; step < size - 1; ++step) {

        // check if swapping occurs  
        int swapped = 0;

        // loop to compare array elements
        for (int i = 0; i < size - step - 1; ++i) {

            // compare two array elements
            // change > to < to sort in descending order
            if (array[i] > array[i + 1]) {

                // swapping occurs if elements
                // are not in the intended order
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;

                swapped = 1;
            }
        }

        // no swapping means the array is already sorted
        // so no need for further comparison
        if (swapped == 0) {
            break;
        }

    }
}

int main(int argc, char **argv){ 

    int iteration = atoi(argv[1]);
    int max_object = 0;

    int N;
    scanf("%d", &N);

    int K;
    scanf("%d", &K);

    int array[N];
    for (int i = 0; i<N; i++){ 
        scanf("%d", &array[i]);
    }
    int counter = 0;
    int temp_array[K];
    double time_spent = 0.0;

    clock_t begin = clock();

    //Iterate through all items in the array
    for(int w=K-1; w<N; w++){

        //Grab K consecutive numbers in the array
        for(int i=0; i<K; i++){ 
            temp_array[i] = array[w-K+1+i];
        }

        //sort them for from smallest to largest
        // radxsort(temp_array, K);
        qsort(temp_array, K, sizeof(int), compare);
        int median;

        if (K % 2 == 0) { 
            median = (temp_array[(K/2)-1]+temp_array[(K/2)])/2;
        }
        else { 
            median = temp_array[((K+1)/2)-1];
        }


        //Grab the object at position (K+1)/2 - 1 
        //Check for Max
        if(median >= max_object) max_object = median;
    }

    clock_t end = clock();
    time_spent += (double)(end-begin)/ CLOCKS_PER_SEC;

    printf("iteration %d: %d\n", iteration, max_object);
    printf("Elapsed time is %f seconds\n", time_spent);

    FILE *fptr;

    fptr = fopen("outputs.txt", "a");

    if(fptr == NULL){
        printf("Error\n");
        return 1;
    }
    fprintf(fptr, "iteration %d: %d\n", iteration, max_object);
    fclose(fptr);

    return 0;
}
