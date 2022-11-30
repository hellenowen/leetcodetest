#include "test_treenode.h"

void test94::inorder(testtreenode::TreeNode* root, std::vector<int>& result) {
	if (root != nullptr) {
		inorder(root->left, result);
		result.push_back(root->val);
		inorder(root->right, result);
	}
}

// 0ms 8.2mb
// improve storage
std::vector<int> test94::test_94(testtreenode::TreeNode* root) {
	std::vector<int> result = {};
	inorder(root, result);
	return result;
}

// 0ms 9.6mb
// ~
bool testtreenode::test_100(testtreenode::TreeNode* p, testtreenode::TreeNode* q) {
	if (p != nullptr && q != nullptr) return p->val == q->val && test_100(p->left, q->left) && test_100(p->right, q->right);
	if (p == nullptr && q == nullptr) return true;
	return false;
}
