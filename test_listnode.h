#pragma once
#include <vector>
#include <stack>

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
	bool test_141(ListNode* head);
	ListNode* test_160(ListNode* headA, ListNode* headB);
	ListNode* test_203(ListNode* head, int val);
	bool test_234(ListNode* head);
}

namespace test206 {
	void reverse(testlistnode::ListNode*& cur, testlistnode::ListNode* last);
	testlistnode::ListNode* test_206(testlistnode::ListNode* head);
}