#include "common.h"

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int high = *std::max_element(piles.begin(), piles.end());
        int low = 1;
        while (low < high) {
          int mid = low + (high - low) / 2;
          if (can_eat(piles, h, mid)) {
            high = mid;    // `mid` is a solution and `mid` is the largest possible solution  (therefore set high = mid + 1)
          } else {
            low = mid + 1; // `mid` is not a solution and `mid` + 1 can be smallest possible solution (therefore set low = mid + 1)
          }
        }
        return low;  // now low == high and high is the optimal solution
    }
  
    bool can_eat(const vector<int>& piles, const int h, const int speed) {
      int hours = 0;
      for (int pile : piles) {
        hours += (pile - 1)/ speed + 1;
        if (hours> h) break;
      }
      return hours <= h;
    }
};