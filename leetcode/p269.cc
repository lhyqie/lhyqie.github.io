#include "common.h"

class Solution {
 public:
  string alienOrder(vector<string>& words) {
    string res = "";
    
    std::map<char, std::vector<char>> adjListMap;
    std::map<char, int> parentCounter;
    if (!initialize(words, adjListMap, parentCounter)) {return "";}
    
    std::queue<char> q;
    for(const auto& pair : parentCounter) {
      if (pair.second == 0) {
        q.push(pair.first);
      }
    }
    while (!q.empty()) {
      char top = q.front(); q.pop();
      res.append(1, top);
      for (const char ch : adjListMap[top]) {
        parentCounter[ch]--;
        if (parentCounter[ch] == 0) {
          q.push(ch);
        }
      }
    }
    
    if (res.length() != parentCounter.size()) return ""; // NOTE: corner case, cycle ["a", "b", "a"]
    return res; 
  }
  
  bool initialize(const vector<string>& words, 
                  std::map<char, std::vector<char>>& adjListMap,
                  std::map<char, int>& parentCounter) {
    for (int i = 1; i < words.size(); ++i) {
      const auto& w1 = words[i-1];
      const auto& w2 = words[i];
      int j = 0;
      for (; j < w1.length() && j < w2.length(); ++j) {
        if (w1[j] != w2[j]) {
          adjListMap[w1[j]].push_back(w2[j]);
          break;  // NOTE: don't forget to break. eg ["ab", "cd", "bb"] will cause b->d->b
        }
      }
      if (w1.length() > w2.length() && w2.length() == j) { // NOTE: corn case ["abc", "ab"] is invalid
        return false;
      }
    }
    
    // NOTE: Don't forget to initialize each char's parent count to 0.
    for (const string& word : words) {
      for (const char ch: word) {
        parentCounter[ch] = 0;
      }
    }
    
    for (const auto& pair : adjListMap) {
      for (const char elem : pair.second) {
         parentCounter[elem] ++;
      }
    }
    
    return true;
  }
};