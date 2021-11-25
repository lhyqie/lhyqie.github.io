/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
 public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
      ListNode* head = nullptr;
      ListNode** p = &head;
      int c = 0;  // carry bit
      while (l1 != nullptr && l2 != nullptr) {
        ListNode* node = new ListNode(0);
        *p = node;
        p = &(node->next);

        node->val = l1->val + l2->val + c;
        if (node->val >= 10 ) {
          node->val -= 10;
          c = 1;
        } else {
          c = 0;
        }
        l1 = l1->next;
        l2 = l2->next;
      }
      while (l1 != nullptr) {
        ListNode* node = new ListNode(0);
        *p = node;
        p = &(node->next);

        node->val = l1->val + c;
        if (node->val >= 10 ) {
          node->val -= 10;
          c = 1;
        } else {
          c = 0;
        }
        l1 = l1->next;
      }
      while (l2 != nullptr) {
        ListNode* node = new ListNode(0);
        *p = node;
        p = &(node->next);

        node->val = l2->val + c;
        if (node->val >= 10 ) {
          node->val -= 10;
          c = 1;
        } else {
          c = 0;
        }
        l2 = l2->next;
      }
      if (c == 1) {
        *p = new ListNode(c);
      }
      return head;
    }
};


// class Solution {
//  public:
//     ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
//       ListNode* res = new ListNode(-1);  // dummy head.
//       ListNode* l3 = res;
//       int c = 0;  // carry
//       while (l1 != nullptr && l2 != nullptr) {
//         l3->next = new ListNode(0);
//         l3 = l3->next;
//         l3->val = l1->val + l2->val + c;
//         if (l3->val >= 10 ) {
//           l3->val -= 10;
//           c = 1;
//         } else {
//           c = 0;
//         }
//         l1 = l1->next;
//         l2 = l2->next;
//       }
//       while (l1 != nullptr) {
//         l3->next = new ListNode(0);
//         l3 = l3->next;
//         l3->val = l1->val + c;
//         if (l3->val >= 10 ) {
//           l3->val -= 10;
//           c = 1;
//         } else {
//           c = 0;
//         }
//         l1 = l1->next;
//       }
//       while (l2 != nullptr) {
//         l3->next = new ListNode(0);
//         l3 = l3->next;
//         l3->val = l2->val + c;
//         if (l3->val >= 10 ) {
//           l3->val -= 10;
//           c = 1;
//         } else {
//           c = 0;
//         }
//         l2 = l2->next;
//       }
//       if (c == 1) {
//         l3->next = new ListNode(c);
//       }
//       ListNode* dummy = res;
//       if (dummy->next != nullptr) {
//         // has valid result
//         res = res->next;
//         delete dummy;
//         return res;
//       } else {
//         // invalid result
//         return nullptr;
//       }      
//     }
// };