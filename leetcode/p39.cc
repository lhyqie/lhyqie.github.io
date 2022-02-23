#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <limits.h>
#include <stdio.h>

using namespace std;

class Solution {
  public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        std::sort(candidates.begin(), candidates.end());
        std::vector<int> choices;
        search(res, choices, candidates, target, 0);
        return res;
    }
  
    void search(vector<vector<int>>& res, std::vector<int>& choices, const vector<int>& candidates, 
                const int target, const int start) {
      if (target < 0) {
        return;
      }
      if (target == 0) {
        res.push_back(choices);
        return;
      }
      for (int i = start; i < candidates.size(); ++i) {
        // skip duplicates.
        if (i > start && candidates[i] == candidates[i-1]) {
          continue;
        }
        // Branch option 1: pick candidates[i], stay current position (note line#27: the `i` passed to arg `start`)
        choices.push_back(candidates[i]);
        search(res, choices, candidates, target - candidates[i], i);
        // Branch option 2: pick candidates[i], move to next position (in the next iteration `++i`)
        choices.pop_back();
      }
    }
};