#pragma once
#include <vector>
#include <string>

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
	int test_111(TreeNode* root);
	bool test_112(TreeNode* root, int targetSum);
	std::vector<int> test_145(TreeNode* root);
}

namespace test94 {
	std::vector<int> test_94(testtreenode::TreeNode* root);
	void inorder(testtreenode::TreeNode* root, std::vector<int>& result);
}

namespace test101 {
	bool twosymmetric(testtreenode::TreeNode* left, testtreenode::TreeNode* right);
	bool test_101(testtreenode::TreeNode* root);
}

namespace test104 {
	int findmax(testtreenode::TreeNode* root, int cur);
	int test_104(testtreenode::TreeNode* root);
}

namespace test108 {
	testtreenode::TreeNode* test_108(std::vector<int>& nums);
	void split(std::vector<int>& nums, int beginvalue, int endvalue, bool left, testtreenode::TreeNode* root);
}

namespace test110 {
	int height(testtreenode::TreeNode* root, int cur);
	bool test_110(testtreenode::TreeNode* root);
}

namespace test144 {
	void preorder(testtreenode::TreeNode* root, std::vector<int>& result);
	std::vector<int> test_144(testtreenode::TreeNode* root);
}

namespace test226 {
	void changelr(testtreenode::TreeNode* node);
	testtreenode::TreeNode* test_226(testtreenode::TreeNode* root);
}

namespace test257 {
	void road(testtreenode::TreeNode* node, std::vector<std::string>& result, std::string& str);
	std::vector<std::string> test_257(testtreenode::TreeNode* root);
}
