#include "common.h"

struct FileNode {
  string path;
  string content;
  // ordered map. if map is empty, implies the FileNode is a file not directory
  std::map<string, FileNode*> childMap; 
};

class FileSystem {
public:
  FileSystem() {
    // Don't initialize "/"
    // root.childMap["/"] = new FileNode({.path="/"});
  }

  vector<string> ls(string path) {    
    FileNode* parent = parentNode(path);
    if(!parent) return {};
    if (parent->childMap.find(path) == parent->childMap.end()) {
      return {};
    }
    
    FileNode* node = parent->childMap[path];
    if (node->childMap.empty()) {
      // path is an existing empty dir
      if (node->content.empty()) return {};
      // path is an existing file
      else return {relativePath(path)};
    }
    
    // path is an existing dir with files.
    vector<string> res;
    for (const auto& it : node->childMap) {
      res.push_back(relativePath(it.second->path));
    }
    return res;
  }

  void mkdir(string path) {
    FileNode* parent = parentNodeOrCreate(path);
    // path already exists
    if (parent->childMap.find(path) != parent->childMap.end()) {
      return;
    }
    parent->childMap[path] = new FileNode({.path=path});
  }

  void addContentToFile(string filePath, string content) {
    FileNode* parent = parentNodeOrCreate(filePath);
    if (parent->childMap.find(filePath) == parent->childMap.end()) {
      parent->childMap[filePath] = new FileNode({.path=filePath});
    }
    parent->childMap[filePath]->content += content;
  }

  string readContentFromFile(string filePath) {
    FileNode* parent = parentNode(filePath);
    if(!parent) return "";
    if (parent->childMap.find(filePath) == parent->childMap.end()) {
      return "";
    }
    return parent->childMap[filePath]->content;
  }
  
  ~FileSystem() {
    // recursively release `FileNode root`
    // prefer std::unique_ptr over pointer.
  }

private:
  FileNode root;
    
  // "#" means invalid path
  string parentPath(string path) const {
    if (path.empty() || path[0] != '/') return "#";
    if (size_t p = path.rfind('/'); p != string::npos) {
      return path.substr(0, p);
    }
    return "";  // should not reach this line;
  }
  
  // "#" means invalid path
  string relativePath(string path) const {
    if (path.empty() || path[0] != '/') return "#";
    if (size_t p = path.rfind('/'); p != string::npos) {
      return path.substr(p+1);
    }
    return "";  // should not reach this line;
  }
  
  deque<string> parentChain(string path) const {
    string parent = parentPath(path);
    if (parent == "#") return {};
        
    deque<string> parentChain;
    while(parent != "") {
      parentChain.push_front(parent);
      parent = parentPath(parent);
    }
    parentChain.push_front("/");
    return parentChain;
  }
  
  FileNode* parentNode(string path) {
    if (path == "/") return &root;
    deque<string> chain = parentChain(path);
    if (chain.empty()) return nullptr;
    
    FileNode* node = &root;
    for (const string& par : chain) {
      if (node->childMap.find(par) != node->childMap.end()) {
        node = node->childMap[par];
      } else {
        return nullptr;
      }
    }
    return node;
  }
  
  FileNode* parentNodeOrCreate(string path) {
    if (path == "/") return &root;
    deque<string> chain = parentChain(path);
    FileNode* node = &root;
    for (const string& par : chain) {
      if (node->childMap.find(par) != node->childMap.end()) {
        node = node->childMap[par];
      } else {
        FileNode* newNode = new FileNode({.path=par});
        node->childMap[par] = newNode;
        node = newNode;
      }
    }
    return node;
  }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * vector<string> param_1 = obj->ls(path);
 * obj->mkdir(path);
 * obj->addContentToFile(filePath,content);
 * string param_4 = obj->readContentFromFile(filePath);
 */