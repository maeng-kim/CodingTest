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
        ListNode* dummy = new ListNode(0);
        ListNode* curr = dummy;
        int carry = 0;

        ListNode* p1 = l1;
        ListNode* p2 = l2;

        while (p1 != nullptr || p2 != nullptr) {
            int d1 = (p1 != nullptr) ? p1 -> val : 0;
            int d2 = (p2 != nullptr) ? p2 -> val : 0;

            int sum = d1 + d2 + carry;
            int d3 = sum % 10;
            carry = sum / 10;

            curr -> next = new ListNode(d3);
            curr = curr->next;
            
            if (p1 != nullptr) p1 = p1->next;
            if (p2 != nullptr) p2 = p2->next;
        }
        if (carry == 1) {
            curr -> next = new ListNode(1);
        }
        return dummy -> next;
    }
};