#include "common.h"

class Solution {
public:
  // There is one test-case timeout, to improve use trie. ( see java solution)
  vector<vector<int>> palindromePairs(vector<string>& words) {
    vector<vector<int>> res;
    // reverse_map stores {word, i} implies the reverse of word is words[i];
    std::unordered_map<string, int> mirror_map;
    for (int i = 0; i < words.size(); ++i) {
      string word = words[i];
      std::reverse(word.begin(), word.end());
      mirror_map[word] = i;
    }
     
    // Corner case, empty string ""   ["a", ""]
    if (mirror_map.find("") != mirror_map.end()) {
      for (int i = 0; i < words.size(); ++i) {
        if (isPalindrome(words[i]) && mirror_map[""] != i) {
          res.push_back({mirror_map[""], i});
        }
      } 
    }
    
    for (int i = 0; i < words.size(); ++i) {
      for (int j = 0; j < words[i].size(); ++j) {
        string left = words[i].substr(0, j);
        string right = words[i].substr(j, words[i].size()- j);
        
        // reverse word of `right` preappends left part to construct palindrome
        if (mirror_map.find(right) != mirror_map.end() && isPalindrome(left) && mirror_map[right] != i) {
          res.push_back({mirror_map[right], i});
        }
        
        // reverse word of `left` appends right part to construct palindrome
        if (mirror_map.find(left) != mirror_map.end() && isPalindrome(right) && mirror_map[left] != i) {
          res.push_back({i, mirror_map[left]});
        }
      }
    }
    return res;
  }
  
private:
  bool isPalindrome(const string word) {
    int left = 0, right = word.size() - 1;
    while (left < right) {
      if (word[left++] != word[right--]) return false;
    }
    return true;
  }
};

/*
class TrieNode {
  public int wordEnding = -1;
  public Map<Character, TrieNode> next = new HashMap();
  public List<Integer> palindromePrefixRemaining = new ArrayList();
}

class Solution {
  public List<List<Integer>> palindromePairs(String[] words) {
    TrieNode trie = new TrieNode();

    // 1. build the Trie with reversed words
    for (int wordId = 0; wordId < words.length; wordId++) {
      String word = words[wordId];
      String reversedWord = new StringBuilder(word).reverse().toString();
      TrieNode currentTrieLevel = trie;
      for (int j = 0; j < reversedWord.length(); j++) {
        if (hasPalindromeRemaining(reversedWord, j)) {
          currentTrieLevel.palindromePrefixRemaining.add(wordId);
        }
        Character c = reversedWord.charAt(j);
        if (!currentTrieLevel.next.containsKey(c)) {
          currentTrieLevel.next.put(c, new TrieNode());
        }
        currentTrieLevel = currentTrieLevel.next.get(c);
      }
      currentTrieLevel.wordEnding = wordId;
    }

    // 2. Find Pairs
    List<List<Integer>> pairs = new ArrayList<>();
    for (int wordId = 0; wordId < words.length; wordId++) {
      String word = words[wordId];
      TrieNode currentTrieLevel = trie;
      for (int j = 0; j < word.length(); j++) {
        // case #3:  word:(xxx + Palindrome), trie: xxx
        if (currentTrieLevel.wordEnding != -1
           && hasPalindromeRemaining(word, j)) {
          pairs.add(Arrays.asList(wordId, currentTrieLevel.wordEnding));
        }

        Character c = word.charAt(j);
        currentTrieLevel = currentTrieLevel.next.get(c);
        if (currentTrieLevel == null)        break;
      }

      if (currentTrieLevel == null) continue;

      // case #1
      if (currentTrieLevel.wordEnding != -1 
          && currentTrieLevel.wordEnding != wordId) {
        pairs.add(Arrays.asList(wordId, currentTrieLevel.wordEnding));
      }

      // case #2: Trie:(Palindrome + xxx) , word:xxx
      for (int other: currentTrieLevel.palindromePrefixRemaining) {
        pairs.add(Arrays.asList(wordId, other));
      }
    }

    return pairs;
  }

  private boolean hasPalindromeRemaining(String s, int i) {
    int p1 = i;
    int p2 = s.length() - 1;
    while (p1 < p2) {
      if (s.charAt(p1) != s.charAt(p2))        return false;
      p1++;
      p2--;
    }
    return true;
  }
}

*/
