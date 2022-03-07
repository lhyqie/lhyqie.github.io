#include "common.h"

struct Interval {
  int start;
  int end;
  int profit; 
}; 

class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
      // assert same size of three vector
      vector<Interval> ivs;
      for (int i = 0; i < startTime.size(); ++i) {
        ivs.push_back({startTime[i], endTime[i], profit[i]});
      }
      // sort by end time and then by start time
      std::sort(ivs.begin(), ivs.end(), [](const auto& lhs, const auto& rhs)->bool{
        if (lhs.end == rhs.end) return lhs.start < rhs.start;
        return lhs.end < rhs.end;
      });
      
      return maxProfit(ivs);
    }

private:
  
  int maxProfit(const vector<Interval>& ivs) {
    vector<int> dp(ivs.size(), 0);
    dp[0] = ivs[0].profit;
    
    for (int i = 1; i < dp.size(); ++i) {
      dp[i] = max(dp[i-1], ivs[i].profit);   // base case, pick interval[i] or use previous optimal profit without interval i
      for (int j = i - 1; j >= 0; --j) {
        if (ivs[j].end <= ivs[i].start) {    // pick any optimal profit from dp[0...i-1] + use interval i
          dp[i] = max(dp[i], ivs[i].profit + dp[j]);
          break;  // without this, it will time out
        }
      }
    }
    
    return *std::max_element(dp.begin(), dp.end());
  }
  
};



/*  My Solution below times out
struct Interval {
  int start;
  int end;
  int profit; 
}; 

class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
      // assert same size of three vector
      vector<Interval> ivs;
      for (int i = 0; i < startTime.size(); ++i) {
        ivs.push_back({startTime[i], endTime[i], profit[i]});
      }
      std::sort(ivs.begin(), ivs.end(), [](const auto& lhs, const auto& rhs)->bool{
        if (lhs.start == rhs.start) return lhs.end < rhs.end;
        return lhs.start < rhs.start;
      });
      
      return maxProfit(ivs);
    }

private:
    
    int maxProfit(const vector<Interval>& ivs) {
      int max_p = 0;
      vector<Interval> stack;
      search(ivs, 0, stack, max_p);
      return max_p;
    }
    
    void search(const vector<Interval>& ivs, int k, vector<Interval>& stack, int& max_p) {
      // search completed.
      if (k == ivs.size()) {
        int profit = 0;
        for (const Interval& iv : stack) {
          profit += iv.profit;
        }
        max_p = max(max_p, profit);
        return;
      }
      
      Interval cur = stack.empty() ? Interval({0,0,0}) : stack.back();
      const Interval& next = ivs[k];
      
      if (cur.end <= next.start) {
        // pick 
        stack.push_back(next);
        search(ivs, k+1, stack, max_p);
        stack.pop_back();
        
      } 
      // skip
      search(ivs, k+1, stack, max_p); 
    }
};
*/