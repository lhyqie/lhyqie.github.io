// Dup of https://leetcode.com/problems/koko-eating-bananas/ (875)

#include "common.h"

class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
      int low = 1;
      int high = *std::max_element(nums.begin(), nums.end()); // note the constraint nums.length <= threshold
      
      while (low < high) {
        int mid = low + (high - low) / 2;
        if (satisfy(nums, threshold, mid)) {
          high = mid;
        } else {
          low = mid + 1;
        }
      }
      // now low == high
      return low;
    }
  
    bool satisfy(const vector<int>& nums, int threshold, int divisor) {
      int sum = 0;
      for (const int num : nums) {
        sum += (num - 1) / divisor + 1;
        if (sum > threshold) break;
      }
      return sum <= threshold;
    }
};