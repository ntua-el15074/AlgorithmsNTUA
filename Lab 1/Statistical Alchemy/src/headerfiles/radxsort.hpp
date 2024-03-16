#ifndef __RADXSORT_HPP__
#define __RADXSORT_HPP__
#include <iostream>
#include <deque>

void countingSort(std::deque<int> &dq, int n, int pos) 
{  
    int result[n + 1];  
    int count[10] = {0};    

    // count howmany numbers are present with digit 0-9 at given position 
    for (int i = 0; i < n; i++)  
        count[(dq[i] / pos) % 10]++;  

    // now do prefix sum of the count array 
    for (int i = 1; i < 10; i++)  
        count[i] += count[i - 1];  

    // Place the elements in sorted order  
    for (int i = n - 1; i >= 0; i--) {  
        result[count[(dq[i] / pos) % 10] - 1] = dq[i];  
        count[(dq[i] / pos) % 10]--;  
    }  

    for (int i = 0; i < n; i++)  
        dq[i] = result[i];  
}  

int find_max(std::deque<int> &dq, int n) {  
    int max_element = dq[0];  
    for(int i = 1; i<n; i++) {  
        if(dq[i] > max_element)  
            max_element = dq[i];  
    }  
    return max_element; 
}  

void radxsort(std::deque<int> &dq, int &n) {  

    int max_element = find_max(dq, n);  

    // counting sort from the least significant digit to the most significant digit  
    for (int pos = 1; max_element / pos > 0; pos *= 10)  
        countingSort(dq, n, pos);  
}

#endif 
