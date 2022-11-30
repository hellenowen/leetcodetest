#pragma once
#include <vector>

namespace testlistnode {
	struct ListNode {
		int val;
		ListNode* next;
		ListNode() :val(0), next(nullptr) {}
		ListNode(int x) :val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) :val(x), next(next) {}
	};
	ListNode* test_2(ListNode*, ListNode*);
	ListNode* test_19(ListNode* head, int n);
	ListNode* test_21(ListNode* list1, ListNode* list2);
	ListNode* test_23(std::vector<ListNode*>& lists);
	ListNode* test_24(ListNode* head);
	ListNode* test_25(ListNode* head, int k);
	ListNode* test_83(ListNode* head);
}