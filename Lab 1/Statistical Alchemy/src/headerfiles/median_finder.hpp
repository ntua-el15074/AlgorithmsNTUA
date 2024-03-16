#include <queue>

class MedianFinder {
std::priority_queue<int> maxHeap;
std::priority_queue<int> minHeap;
int n;
public:
    
    MedianFinder() {
        n = 0;
    }
    
    void addNum(int num) {
        if(n %2 == 0) {
            if(n == 0){
                insertInMaxHeap(num);
            } else {
                int topOfMinHeap = getMinHeapTop();
                if (num >= topOfMinHeap) {
                    insertInMaxHeap(topOfMinHeap);
                    minHeap.pop();
                    insertInMinHeap(num);
                } else {
                    insertInMaxHeap(num);
                }
            }
        } else {
            int topOfMaxHeap = getMaxHeapTop();
            if(topOfMaxHeap < num) {
                insertInMinHeap(num);            
            } else {
                maxHeap.pop();
                insertInMaxHeap(num);
                insertInMinHeap(topOfMaxHeap);
            }
        }
        n++;
    }
    
    int findMedian() {
        if(n%2 == 1)
            return maxHeap.top();
        return (getMaxHeapTop() + getMinHeapTop())/2;
    }
    
private:
    void insertInMaxHeap(int val) {
        maxHeap.push(val);
    }
    
    void insertInMinHeap(int val) {
        minHeap.push(-val);
    }
    
    int getMinHeapTop() {
        return -minHeap.top();
    }
    
    int getMaxHeapTop() {
        return maxHeap.top();
    }
};
