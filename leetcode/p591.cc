#include "common.h"

class Solution {
public:
    bool isValid(string code) {
      std::stack<string> stack;
      for (int i = 0; i < code.size();) {
        if (i > 0 && stack.empty()) return false;  // no starting <TAG_NAME>.
        if (code.find("<![CDATA[", i) == i) {
          int j = i + 9;
          i = code.find("]]>", j);
          if (i == std::string::npos) return false;  // no match CDATA end-tag.
          i += 3;
        } else if (code.find("</", i) == i) {
          int j = i + 2;
          i = code.find(">", j);
          if (i == std::string::npos) return false;  // no ending > for </
          string end_tag = code.substr(j, i-j);
          if (!validTag(end_tag)) return false;       // invalid ending <TAG_NAME>
          if (stack.empty()) return false;            // no starting <TAG_NAME>.
          string start_tag = stack.top(); stack.pop();
          if (start_tag != end_tag) return false;     // start <TAG_NAME>, end <TAG_NAME> not match
          i++;
        } else if (code.find("<", i) == i) {
          int j = i + 1;
          i = code.find(">", j);
          if (i == std::string::npos) return false;  // no ending > for <
          string start_tag = code.substr(j, i-j);
          if (!validTag(start_tag)) return false;     // invalid starting <TAG_NAME>
          stack.push(start_tag);
          i++;
        } else {
          i++;
        }
      }
      return stack.empty();    // all match.
    }

private:
    bool validTag(const string& tag) {
      if (tag.empty() || tag.size() > 9) return false;
      for (char ch : tag) {
        if (ch < 'A' || ch > 'Z') return false;
      }
      return true;
    }
};