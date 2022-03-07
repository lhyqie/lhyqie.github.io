#include "common.h"
class Solution {
public:  
  string findSmallestRegion(vector<vector<string>>& regions, const string& region1, const string& region2) {
    InvertedTree itree = BuildInvertedTree(regions);
    Node* n1 = itree.valueNodeMap[region1];  // TODO: if region1 does not exit
    Node* n2 = itree.valueNodeMap[region2];  // TODO: if region2 does not exit
    int len1 = 0, len2 = 0;
    for(Node* p1 = n1; p1; p1=p1->parent) {
      len1++;
    }
    for(Node* p2 = n2; p2; p2=p2->parent) {
      len2++;
    }
    Node* lca = nullptr;
    if (len1 < len2) {
      lca = LowestCommonAncestor(n1, n2, len1, len2);
    } else {
      lca = LowestCommonAncestor(n2, n1, len2, len1);
    }
    
    return lca ? lca->v : "N/A";
  }
  
private:
  struct Node {
    string v;
    Node* parent;
  };
  
  struct InvertedTree {
    void RecordEdge(const string& child, const string& parent) {
      if (const auto it = valueNodeMap.find(parent); it == valueNodeMap.end()) {
        valueNodeMap[parent] = new Node{.v = parent, .parent = nullptr};
      }
      if (const auto it = valueNodeMap.find(child); it == valueNodeMap.end()) {
        valueNodeMap[child] = new Node{.v = child, .parent = valueNodeMap[parent]};
      }
    }
    std::map<string, Node*> valueNodeMap;
  };
  
  InvertedTree BuildInvertedTree(vector<vector<string>>& regions) {
    InvertedTree tree;
    for (const auto& row : regions) {
      // assert row.size() > 1
      for (int j = 1; j < row.size(); ++j) {
        tree.RecordEdge(row[j], row[0]);
      }
    }
    return tree;
  } 
  
  Node* LowestCommonAncestor(Node* n1, Node* n2, int len1, int len2) {
    // assert 0 < len1 < len2;
    while(len2-- > len1) {
      n2 = n2->parent;
    }
    while(n1 && n1 != n2) {
      n1 = n1->parent;
      n2 = n2->parent;
    }
    if (n1) return n1;
    return nullptr;
  }
};