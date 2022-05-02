// https://www.dropbox.com/home/Books/Algorithm?preview=01UnionFind.pdf
#include "common.h"

class UnionFind {
 public:
  UnionFind() {};

  virtual bool Find(const int a, const int b) const = 0;

  virtual void Union(const int a, const int b) = 0;
};

class QuickFind: public UnionFind {
 public:
  QuickFind(int n) : id(n, 0) {
    for (int i = 0; i < n; ++i) {
      id[i] = i;
    }
  }
 
  bool Find(const int a, const int b) const {
    return id[a] == id[b];
  }

  void Union(const int a, const int b) {
    const int pa = id[a];   // store id[a] between the loop below may change it.
    for (int i = 0; i < id.size(); ++i) {
      if (id[i] == pa) {
        id[i] = id[b];
      }
    }
  }

  void Print() {
    for (int i = 0; i < id.size(); ++i) {
      std::cout << "i = " << i << ":" << " id[i] = " << id[i] << std::endl;
    }
    std::cout << std::endl;
  }

private:
  vector<int> id;
};

class QuickUnion: public UnionFind {
public:
  QuickUnion(int n) : id(n, 0) {
    for (int i = 0; i < n; ++i) {
      id[i] = i;
    }
  }
 
  bool Find(const int a, const int b) const {
    return root(a) == root(b);
  }

  void Union(const int a, const int b) {
    const int i = root(a);
    const int j = root(b);
    id[i] = j;
  }

  void Print() {
    for (int i = 0; i < id.size(); ++i) {
      std::cout << "i = " << i << ":" << " id[i] = " << id[i] << std::endl;
    }
    std::cout << std::endl;
  }

 private:
  vector<int> id;

  int root(int i) const {
    while(i != id[i]) { i = id[i];}
    return i;
  }
};

int main() {
  int n = 10;
  vector<pair<int, int>> edges = {
    {3,4},
    {4,9},
    {8,0},
    {2,3},
    {5,6},
    {5,9},
    {7,3},
    {4,8},
    {6,1},
  };
  
  {
    QuickFind qf(n);
    for (const auto& edge : edges) {
      qf.Union(edge.first, edge.second);
    }
    qf.Print();
  }

  {
    QuickUnion qu(n);
    for (const auto& edge : edges) {
      qu.Union(edge.first, edge.second);
    }
    qu.Print();
  }
  
  return 0;
}