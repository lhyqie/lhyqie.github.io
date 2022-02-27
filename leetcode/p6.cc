#include "common.h"

class Solution {
public:
  string longestPalindrome(string s) {
    int start = 0, max_len = 1;
    for(int i = 0; i < s.size(); i++){
      int len1 = expandAroundCenter(s, i, i);
      int len2 = expandAroundCenter(s, i, i+1);
      int len = std::max(len1, len2);
      if(std::max(len1, len2) > max_len){
          // when len is odd     e.g.  ...abcba...    len = 5   center is i    =>  start = i - (len-1)/2 = i - 2
          // when len is even    e.g.  ...abba...     len = 4   center is i    =>  start = i - (len-1)/2 = i - 1
          start = i - (len-1)/2;  
          max_len = len;
      }
      // std::cout << "i=" << i << " len1=" << len1 << " len2=" << len2 << " start=" << start << "\n" ; 
    }
    return s.substr(start, max_len);
  }
private:
  int expandAroundCenter(const string& s, int left, int right){
    while(left >= 0 && right< s.size() && s[left] == s[right]){
        left --; right ++;
    }
    return right - left - 1;    // right - left + 1 - 2
  }
};

int main()
{
  std::cout << Solution().longestPalindrome("babbc");
  return 0;
}

