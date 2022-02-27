#include "common.h"

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
      long a = numerator, b = denominator;
      if (b == 0) return "";
      if (a == 0) return "0";
      string ans = "";
      if (a > 0 && b < 0)  ans = "-";
      else if (a < 0 && b > 0)  ans = "-";
      
      a = abs(a);
      b = abs(b);
      
      ans += std::to_string(a/b);
      if (a % b == 0) {
        return ans;
      } else {
        ans += ".";
      }
      
      a %= b;
      
      std::map<long, int> n2idx;
      int i = ans.size();
      while (a > 0) {
        if (const auto it = n2idx.find(a); it != n2idx.end()) {
          return ans.substr(0, it->second) + "(" + ans.substr(it->second) +")";
        }
        n2idx[a] = i++;
        a *= 10;
        ans += std::to_string(a/b);
        a %= b;
      }
      return ans;
    }
};
