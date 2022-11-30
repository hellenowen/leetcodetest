#pragma once
#include <vector>

namespace testtreenode {
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() :val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) :val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) :val(x), left(left), right(right) {}
	};
	bool test_100(TreeNode* p, TreeNode* q);
}

namespace test94 {
	std::vector<int> test_94(testtreenode::TreeNode* root);
	void inorder(testtreenode::TreeNode* root, std::vector<int>& result);
}