#include "common.h"

class FileSystem {
public:
    FileSystem() {
      folder_value[""] = INT_MAX;
      folder_value["/"] = INT_MAX;
    }
    
    bool createPath(string path, int value) {
      if (path.empty() || path == "/" || path[0] != '/') return false;
      
      string parent = parentFolder(path);
      if (parent.empty()) return false;
      
      if (folder_value.find(parent) == folder_value.end()) {
        return false;
      }
      if (folder_value.find(path) != folder_value.end()) {
        return false;  
      }
      folder_value[path] = value;
      return true;
    }
    
    int get(string path) {
      if (folder_value.find(path) != folder_value.end()) {
        return folder_value[path];
      }
      return -1;
    }

private:  
    string parentFolder(string path) {
      if (std::size_t p = path.rfind("/"); p != string::npos) {
        if (p == 0) return "/";
        else return path.substr(0, p);
      }
      return "";
    }
  
    std::map<string, int> folder_value;
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * bool param_1 = obj->createPath(path,value);
 * int param_2 = obj->get(path);
 */