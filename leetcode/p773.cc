#include "common.h"

class Solution {
public:
  enum Direction {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
  };
    
  int slidingPuzzle(vector<vector<int>>& board) {
    State goal({{1,2,3},{4,5,0}}, 0);
      
    // BFS for shortest path
    State* start = new State(board, 0);
    std::queue<State*> q;
    std::set<int> visited;  // NOTE: avoid duplicated search states
    q.push(start);
    visited.insert(start->Fingerprint());
    while(!q.empty()) {
      State* top = q.front(); q.pop();
      if (top->Fingerprint() == goal.Fingerprint()) {
        return top->Depth();
      }
      
      for (auto direction : {UP, DOWN, LEFT, RIGHT}) {
        if (top->Movable(direction)) {
          State* next = top->Move(direction);
          if (const auto it = visited.find(next->Fingerprint()); it == visited.end()) {
            q.push(next);
            visited.insert(next->Fingerprint());
          }
        }
      }
      delete top;
    }
    return -1;
  }
  
private:
  class State {
    public:
      State(const vector<vector<int>>& board, const int depth) : board_(board), depth_(depth) {
        // assert board_.size() == 2
        // assert board_[0].size() == 3
        // assert 0 exists in board_
        for (int i = 0; i < 2; i++) {
          for (int j = 0; j < 3; j++) {
            if (board_[i][j] == 0) {
              x_ = i; y_ = j;
              break;
            }
          }
        }
      }
       
      int Fingerprint() const {
        int fp = 0;
        for (int i = 0; i < 2; i++) {
          for (int j = 0; j < 3; j++) {
            fp = fp * 10 + board_[i][j];
          }
        }
        return fp;
      }
      
      int Depth() const {
        return depth_;    
      }
    
      bool Movable(Direction direction) const {
        if (direction == UP) {
          if (x_ == 0) return false;
        } else if (direction == DOWN) {
          if (x_ == 1) return false;
        } else if (direction == LEFT) {
          if (y_ == 0) return false;
        } else {  // RIGHT
          if (y_ == 2) return false;
        }
        return true;
      }
    
      State* Move(Direction direction) const {
        State* nextState = new State(board_, depth_+1);
        if (direction == UP) {
          int tmp = nextState->board_[x_-1][y_];
          nextState->board_[x_-1][y_] = nextState->board_[x_][y_];
          nextState->board_[x_][y_] = tmp;
          nextState->x_--;
        } else if (direction == DOWN) {
          int tmp = nextState->board_[x_+1][y_];
          nextState->board_[x_+1][y_] = nextState->board_[x_][y_];
          nextState->board_[x_][y_] = tmp;
          nextState->x_++;
        } else if (direction == LEFT) {
          int tmp = nextState->board_[x_][y_-1];
          nextState->board_[x_][y_-1] = nextState->board_[x_][y_];
          nextState->board_[x_][y_] = tmp;
          nextState->y_--;
        } else {  // RIGHT
          int tmp = board_[x_][y_+1];
          nextState->board_[x_][y_+1] = nextState->board_[x_][y_];
          nextState->board_[x_][y_] = tmp;  
          nextState->y_++;
        }
        return nextState;
      }
    
    private:
      vector<vector<int>> board_;
      const int depth_; // depth in the search tree
      int x_;  // x-coordinate of 0  (first dimension of vector 2D)
      int y_;  // y-coordinate of 0  (second dimension of vector 2D)
  };  
};