#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
      int max_len = 0;
      
      // maintains the the index of each char's last appearance index.
      map<char, int> last_index_map; 
      // last_repeat_index stores the last repeating char's index for s[:i)
      int last_repeat_index = -1;
      
      for (int i = 0; i < s.size(); ++i) {
        if (last_index_map.find(s[i]) != last_index_map.end()) {
          last_repeat_index =  std::max(last_repeat_index, last_index_map[s[i]]);
        } 
        last_index_map[s[i]] = i;
        max_len = std::max(max_len, i - last_repeat_index);
      }
      return max_len;
    }
};