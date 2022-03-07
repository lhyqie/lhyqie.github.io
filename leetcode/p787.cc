#include "common.h"

class Solution {
public:
    // Bellman-ford algorithm
    // https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm
    // NOTE: predecessor is no needed for this problem but useful for backtracing shortest path.
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
      // Step 1. Init (with no knowledge from edge)
      vector<int> distance(n, INT_MAX); // store the shortest distance from `src` to array-index `i`.
      // vector<int> predecessor(n, -1);   // store the predecessor in the shortest path.
      distance[src] = 0;
      
      // Step 2: relax edges repeatedly for `k+1` times
      while ( k-- >= 0) {   
        // create temp for synchronous update.
        vector<int> tempDistance(distance.begin(), distance.end());
        
        for(const vector<int>& flight: flights) {
          const int from = flight[0];
          const int to = flight[1];
          const int price = flight[2];
          if (distance[from] < INT_MAX && tempDistance[to] > distance[from] + price) {
            tempDistance[to] = distance[from] + price;
            // predecessor[to] = from;
          }
        }
        
        distance = tempDistance;
      }
      
      // Step 3. Check for negative-weight cycles.
      // But In this problem, this is not negative flight cost (edge weight)
      
      return distance[dst] == INT_MAX ? -1 : distance[dst];
    }
};

/*
// my solution times out. 
struct SearchState {
  int id;
  int depth;
  int cost;
};
  
class Solution {
public:
  int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    if (n <= 0 || k < 0) return -1;
    if (src == dst) return 0;
    
    vector<vector<int>> costMap(n, vector<int>(n, INT_MAX));
    for (const auto& flight : flights) {
      const int from = flight[0];
      const int to = flight[1];
      const int price = flight[2];
      costMap[from][to] = price;
    }
    
    std::queue<SearchState> queue;
    // initialize queue.
    for (int j = 0; j < costMap[src].size(); ++j) {
      if (costMap[src][j] < INT_MAX) {
        queue.push({.id = j, .depth = 1, .cost=costMap[src][j]});
      }      
    }

    int res = INT_MAX;
    
    while(!queue.empty()) {
      auto top = queue.front(); queue.pop();
      if (top.id == dst) {
        res = min(res, top.cost);
      }
      if (top.depth <= k  ) {
        for (int j = 0; j < costMap[top.id].size(); ++j) {
          if (costMap[top.id][j] < INT_MAX) {
            queue.push({.id = j, .depth = top.depth+1, .cost=top.cost+costMap[top.id][j]});
          }      
        }
      } 
    }
    
    return res == INT_MAX ? -1 : res;
  }
  
};
*/