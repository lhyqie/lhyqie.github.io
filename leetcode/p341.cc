#include "common.h"

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList): nestedList_(nestedList) {
      if (nestedList_.empty()) {
        i_ = -1;
      }
      i_ = 0;
      for (int j = 0; j < nestedList_.size(); ++j) {
        iterList_.push_back(NestedIterator(nestedList_[j].getList()));
      }
      next_ = INT_MAX;
    }
    
    int next() {
      int ret = next_;
      next_ = INT_MAX;
      return ret;
    }
    
    bool hasNext() {
      if (i_ < 0 || i_ == nestedList_.size()) return false;
      // search for next integer
      while (i_ < nestedList_.size()) {
        if (nestedList_[i_].isInteger()) {
          next_ = nestedList_[i_].getInteger();
          i_++;
          return true;
        }
        if (iterList_[i_].hasNext()) {
          next_ = iterList_[i_].next();
          return true;
        } else {
          i_++;
        }
      }
      return false;  // now i_ == nestedList_.size(), we exhausted all NestedInteger
    }
  
private:
  vector<NestedInteger>& nestedList_;
  vector<NestedIterator> iterList_;
  int i_;
  int next_;
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */