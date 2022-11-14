#include "test_listnode.h"

// 20ms 69.4mb
// middle
testlistnode::ListNode* testlistnode::test_2(ListNode* l1, ListNode* l2) {
	ListNode* h1 = l1;
	ListNode* h2 = l2;
	ListNode* result = new ListNode();
	ListNode* r = result;

	int temp = 0;
	while (h1 != nullptr || h2 != nullptr) {
		if (h1 != nullptr) {
			temp += h1->val;
			h1 = h1->next;
		}
		if (h2 != nullptr) {
			temp += h2->val;
			h2 = h2->next;
		}
		if (temp <= 9) {
			r->val = temp;
			temp = 0;
		}
		else {
			r->val = temp % 10;
			temp = temp / 10;
		}
		if (h1 != nullptr || h2 != nullptr) {
			r->next = new ListNode();
			r = r->next;
		}
	}
	if (temp != 0) {
		r->next = new ListNode();
		r = r->next;
		r->val = temp;
	}
	r->next = nullptr;
	return result;
}

// 0ms 10.4mb
// improve storage
testlistnode::ListNode* testlistnode::test_19(ListNode* head, int n) {
	ListNode* last = nullptr;
	ListNode* cur = head;
	size_t count = 0;
	while (cur != nullptr) {
		++count;
		cur = cur->next;
	}
	if (count > 0) {
		last = nullptr;
		cur = head;
		--count;
	}
	while (count > n) {
		--count;
		last = cur;
		cur = cur->next;
	}
	if (last != nullptr) {
		last->next = cur->next;
		cur->next = nullptr;
	}
	else if (cur != nullptr) {
		head = cur->next;
	}
	return head;
}

// 0ms 14.3mb
// aha
testlistnode::ListNode* testlistnode::test_21(ListNode* list1, ListNode* list2) {
	ListNode* temp = nullptr;
	ListNode* result = nullptr;
	while (list1 != nullptr || list2 != nullptr) {
		if (list1 != nullptr && list2 != nullptr) {
			if (list1->val <= list2->val) {
				if (temp == nullptr) {
					temp = list1;
					result = list1;
				}
				else {
					temp->next = list1;
					temp = list1;
				}
				list1 = list1->next;
			}
			else {
				if (temp == nullptr) {
					temp = list2;
					result = list2;
				}
				else {
					temp->next = list2;
					temp = list2;
				}
				list2 = list2->next;
			}
		}
		else if (list1 != nullptr) {
			if (temp == nullptr) {
				temp = list1;
				result = list1;
			}
			else {
				temp->next = list1;
				temp = list1;
			}
			list1 = list1->next;
		}
		else if (list2 != nullptr) {
			if (temp == nullptr) {
				temp = list2;
				result = list2;
			}
			else {
				temp->next = list2;
				temp = list2;
			}
			list2 = list2->next;
		}
	}
	return result;
}

// 24ms 12.6mb
// middle
testlistnode::ListNode* testlistnode::test_23(std::vector<ListNode*>& lists) {
	if (lists.empty()) return nullptr;
	ListNode* result = nullptr;
	ListNode* cur = nullptr;
	ListNode* temp = nullptr;
	int turnMin = 0;
	int i = 0;
	int count = 0;
	for (auto& l : lists) {
		if (cur == nullptr) {
			if (l != nullptr) {
				turnMin = l->val;
				cur = l;
				result = l;
				i = count;
			}
		}
		if (l != nullptr && l->val < turnMin) {
			turnMin = l->val;
			cur = l;
			result = l;
			i = count;
		}
		++count;
	}
	if (lists[i] != nullptr) {
		lists[i] = lists[i]->next;
	}
	bool newTurn = true;
	while (cur != nullptr) {
		newTurn = true;
		count = 0;	// ¼Ç¿Õ
		for (auto& l : lists) {
			if (l != nullptr) {
				if (l->val == turnMin) {
					newTurn = false;
					cur->next = l;
					cur = l;
					l = l->next;
				}
			}
			else {
				++count;
			}
		}
		if (count == lists.size()) {
			break;
		}
		if (newTurn) {
			i = 0;
			count = 0;
			temp = nullptr;
			for (auto& l : lists) {
				if (temp == nullptr) {
					if (l != nullptr) {
						turnMin = l->val;
						temp = l;
						i = count;
					}
				}
				if (l != nullptr && l->val < turnMin) {
					turnMin = l->val;
					i = count;
				}
				++count;
			}
			if (lists[i] != nullptr) {
				cur->next = lists[i];
				cur = lists[i];
				lists[i] = lists[i]->next;
			}
		}
	}
	return result;
}

// 0ms 7.2mb
// ~
testlistnode::ListNode* testlistnode::test_24(ListNode* head) {
	ListNode* cur = head;
	ListNode* temp = nullptr;
	if (cur != nullptr) {
		if (cur->next != nullptr) {
			head = cur->next;
			cur->next = head->next;
			head->next = cur;
			temp = cur;
			cur = cur->next;
		}
		else {
			return cur;
		}
	}
	while (cur != nullptr) {
		if (cur->next != nullptr) {
			temp->next = cur->next;
			cur->next = cur->next->next;
			temp->next->next = cur;
			temp = cur;
			cur = cur->next;
		}
		else {
			break;
		}
	}
	return head;
}

// 12ms 11.2mb
// improve storage
testlistnode::ListNode* testlistnode::test_25(ListNode* head, int k) {
	ListNode* cur = head;
	ListNode* temp = head;
	ListNode* last = nullptr;
	ListNode* segTail = nullptr;
	ListNode* lastSegHead = nullptr;
	int count = 0;
	if (cur != nullptr) {
		while (temp != nullptr) {
			++count;
			temp = temp->next;
			if (count == k) {
				segTail = temp;
				break;
			}
		}
		if (count == k) {
			lastSegHead = cur;
			temp = cur->next;
			cur->next = segTail;
			last = cur;
			cur = temp;
			while (count > 1) {
				--count;
				temp = cur->next;
				cur->next = last;
				last = cur;
				cur = temp;
			}
			head = last;
		}
		else {
			return head;
		}
	}
	while (cur != nullptr) {
		count = 0;
		segTail = nullptr;
		temp = cur;
		while (temp != nullptr) {
			++count;
			if (count == k) {
				segTail = temp;
				break;
			}
			temp = temp->next;
		}
		if (count == k) {
			temp = cur->next;
			lastSegHead->next = segTail;
			lastSegHead = cur;
			cur->next = segTail->next;
			last = cur;
			cur = temp;
			while (count > 1 && cur != nullptr) {
				--count;
				temp = cur->next;
				cur->next = last;
				last = cur;
				cur = temp;
			}
		}
		else {
			break;
		}
	}
	return head;
}
