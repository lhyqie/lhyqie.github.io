#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution {
 public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        map<int, int> m;
        for (size_t i = 0; i < nums.size(); ++i) {
          if (m.find(target - nums[i]) != m.end()) {
            result.push_back(i);
            result.push_back(m[target - nums[i]]);
          } else {
            m[nums[i]] = i; 
          }
        }
        return result;  // Should not reach here.
    }
          
    // Assume the vector is sorted, but it's not the case for this problem.
    /*
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        int l = 0, r = nums.size() - 1;
        while (l < r) {
          if (nums[l] + nums[r] == target) {
            result.push_back(l);
            result.push_back(r);
            return result;
          } else if (nums[l] + nums[r] < target) {
            l++;
          } else {
            r--;
          }
        }
        return result;  // Should not reach here.
    }
    */
};

int main() {
    vector<int> nums = {3, 2, 4};
    int target = 6;
    const auto& res = Solution().twoSum(nums, target);
    for (const auto& e : res) {
        std::cout << e << " ";    
    }
    return 0;
}