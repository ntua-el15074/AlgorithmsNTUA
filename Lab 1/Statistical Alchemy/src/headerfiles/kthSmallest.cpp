#include <iostream>
#include <deque>

int partition(std::deque<int> &dq, int l, int r){
    int x = dq[r], i = l;
    for (int j = l; j <= r - 1; j++) {
        if (dq[j] <= x) {
            std::swap(dq[i], dq[j]);
            i++;
        }
    }
    std::swap(dq[i], dq[r]);
    return i;
}
  
int kthSmallest(std::deque<int> &dq, int l, int r, int w){
    if (w > 0 && w <= r - l + 1) {
        int index = partition(dq, l, r);
        if (index - l == w - 1)
            return dq[index];
        if (index - l > w - 1) 
            return kthSmallest(dq, l, index - 1, w);
        return kthSmallest(dq, index + 1, r, 
                            w - index + l - 1);
    }
    return INT_MAX;
}
