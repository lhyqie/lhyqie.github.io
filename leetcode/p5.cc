#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
  string longestPalindrome(string s) {
    int start = 0, len = 1;
    for(int i = 0; i < s.size(); i++){
      int len1 = expandAroundCenter(s, i, i);
      int len2 = expandAroundCenter(s, i, i+1);
      if(std::max(len1, len2) > len){
          // when len is odd     e.g.  ...abcba...    len = 5   center is i    =>  start = i - (len-1)/2 = i - 2
          // when len is even    e.g.  ...abba...     len = 4   center is i    =>  start = i - (len-1)/2 = i - 1
          start = i - (len-1)/2;  
          len = std::max(len1, len2);
      }
    }
    return s.substr(start, len);
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
  Solution().longestPalindrome("babbc");
  return 0;
}

// class Solution {
// public:
//   string longestPalindrome(string s) {
//     const int n = s.size();
//     int L[n];

//     for (size_t i = 0; i < n; ++i) {
//       L[i] = 1;
//     }

//     for (int w = 1; w <= (n - 1) / 2; ++w) {
//       for (int i = 1; i <= n - w - 1; ++i) {
//         if (L[i] == 2 * (w - 1) + 1) {
//           L[i] += s[i - w] == s[i + w] ? 2 : 0;
//         }
//       }
//     }
//     // printArray(L, n);

//     int max_index = std::max_element(L, L + n) - L;
//     std::cout << max_index;
//     return s.substr(max_index - L[max_index], 2 * L[max_index] + 1);
//   }

//   void printArray(int arr[], int n) {
//     for (size_t i = 0; i < n; i++) {
//       std::cout << arr[i] << ' ';
//     }
//     std::cout << std::endl;
//   }
// };

