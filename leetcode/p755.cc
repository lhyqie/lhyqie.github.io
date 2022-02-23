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

void PrintWall(const vector<int>& arr) {
  // assert: each element in arr is  >= 0.
  const int max = *std::max_element(arr.begin(), arr.end());
  for (int level = max; level > 0 ;  --level) {
    for (int i = 0; i < arr.size(); ++i) {
      cout << ((level <= arr[i]) ? "X" : " ");
    }
    cout << endl;
  }
  cout << endl;
        
}

int leftCandidate(const vector<int>& arr, int k) {
    int index = k;
    for (int i = k - 1; i >= 0; --i) {
        if (arr[i] < arr[index]) {
            index = i; 
        } else if (arr[i] > arr[index]) {
            break;  // block, can't go left
        }
    }
    return index;
}

int rightCandidate(const vector<int>& arr, int k) {
    int index = k;
    for (int i = k + 1; i < arr.size(); ++i) {
        if (arr[i] < arr[index]) {
            index = i;
        } else if (arr[i] > arr[index]) {
            break;  // block, can't go left
        }
    }
    return index;
}

vector<int> PourWater(const vector<int>& terrain, int volume, const int k) {
    if (k < 0 || k >= terrain.size()) {
        return {-1}; // indicate error.
    }
    
    std::vector<int> res(terrain.begin(), terrain.end());
    for (int i = 0; i < volume; ++i) {
      const int l = leftCandidate(res, k);
      if (l != k) {
          res[l] ++;
      } else {
          const int r = rightCandidate(res, k);
          res[r] ++;
      }
    }
    return res;
}


int main()
{
    
    // std::vector<int> terrain = {2,1,1,2,1,2,2};
    // int volume = 4;
    // int k = 3;
    // std::vector<int> expected = {2,2,2,3,2,2,2};
    
    // std::vector<int> terrain = {1,2,3,4,3,2,1,2,3,4,3,2,1};
    // int volume = 2;
    // int k = 2;
    // std::vector<int> expected = {2,3,3,4,3,2,1,2,3,4,3,2,1};
    
    std::vector<int> terrain =  {2,3,4,4,3,2,1,2,3,4,3,2,1};
    // {1,2,3,4,3,2,1,2,3,4,3,2,1};
    int volume = 7;
    int k = 2;
    std::vector<int> expected =  {4,4,4,4,3,3,3,3,3,4,3,2,1};
    
    PrintWall(terrain);
    PrintWall(PourWater(terrain, volume, k));
    
    // --------------------
    PrintWall(expected);
    return 0;
}
