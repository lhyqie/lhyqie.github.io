#include "common.h"

class Vector2D {
  public:
    Vector2D(vector<vector<int>>& vec):vec_(vec), i(0), j(0) {
      if(vec_.empty()) {
        i = -1;
      }
    }
    
    int next() {
      if (!hasNext()) {return INT_MAX;} // exception
      int ret = vec_[i][j];
      if (j == vec_[i].size() - 1) {
        ++i;
        j = 0;
      } else {
        j++;
      }
      return ret;
    }
    
    bool hasNext() {
      if (i < 0) return false;
      while (i < vec_.size()) {
        if (j < vec_[i].size()) {
          return true;
        } else {
          i++;
          j = 0;
        }
      }
      return false;
    }
  
private:
  const vector<vector<int>>& vec_; // not owned;
  int i;
  int j;
  
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D* obj = new Vector2D(vec);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
