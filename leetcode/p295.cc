#include "common.h"

class MedianFinder {
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
      // looping invariant: max_q.size() == min_q.size() or max_q.size() == min_q.size() + 1
      if (max_q.empty() || max_q.top() >= num) {
        max_q.push(num);
        if (max_q.size() > min_q.size() + 1) {
          int tmp = max_q.top(); max_q.pop();
          min_q.push(tmp);
        }
      } else {
        min_q.push(num);
        if (max_q.size() < min_q.size() ) {
          int tmp = min_q.top(); min_q.pop();
          max_q.push(tmp);
        }
      }
    }
    
    double findMedian() {
      if (max_q.size() == min_q.size()) {
        return (double)(max_q.top() + min_q.top()) / 2;
      } else {
        return max_q.top();
      }
    }
private:
  std::priority_queue<int, vector<int>> max_q;
  std::priority_queue<int, vector<int>, greater<int>> min_q;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */