#include "test_treenode.h"

using namespace testtreenode;
using namespace std;

void test94::inorder(TreeNode* root, std::vector<int>& result) {
	if (root != nullptr) {
		inorder(root->left, result);
		result.push_back(root->val);
		inorder(root->right, result);
	}
}

// 0ms 8.2mb
// improve storage
std::vector<int> test94::test_94(TreeNode* root) {
	std::vector<int> result = {};
	inorder(root, result);
	return result;
}

// 0ms 9.6mb
// ~
bool testtreenode::test_100(TreeNode* p, TreeNode* q) {
	if (p != nullptr && q != nullptr) return p->val == q->val && test_100(p->left, q->left) && test_100(p->right, q->right);
	if (p == nullptr && q == nullptr) return true;
	return false;
}

bool test101::twosymmetric(TreeNode* left, TreeNode* right) {
	if (left != nullptr && right != nullptr) {
		return left->val == right->val && twosymmetric(left->left, right->right) && twosymmetric(left->right, right->left);
	}
	if (left == nullptr && right == nullptr) return true;
	return false;
}

// 0ms 15.8mb
// ~
bool test101::test_101(TreeNode* root) {
	if (root == nullptr)return true;
	return twosymmetric(root->left, root->right);
}

int test104::findmax(TreeNode* root, int cur) {
	if (root == nullptr) return cur;
	int leftlen = findmax(root->left, cur + 1);
	int rightlen = findmax(root->right, cur + 1);
	return leftlen > rightlen ? leftlen : rightlen;
}

// 8ms 18.3mb
// another resolution?
int test104::test_104(TreeNode* root) {
	return findmax(root, 0);
}

void test108::split(vector<int>& nums, int beginvalue, int endvalue, bool left, TreeNode* root) {
	int middle = (beginvalue + endvalue) / 2;
	TreeNode* a = new TreeNode(nums[middle]);
	if (left) {
		root->left = a;
	}
	else {
		root->right = a;
	}
	if (middle - 1 >= beginvalue) {
		split(nums, beginvalue, middle - 1, true, a);
	}
	if (middle + 1 <= endvalue) {
		split(nums, middle + 1, endvalue, false, a);
	}
}

// 12ms 20mb
// another resolution?
TreeNode* test108::test_108(vector<int>& nums) {
	int middle = nums.size() / 2;
	TreeNode* result = new TreeNode(nums[middle]);
	if (0 <= middle - 1)
		split(nums, 0, middle - 1, true, result);
	if (middle + 1 <= nums.size() - 1)
		split(nums, middle + 1, nums.size() - 1, false, result);
	return result;
}

int test110::height(TreeNode* root, int cur) {
	if (root == nullptr) return cur;
	int leftl = height(root->left, cur + 1);
	int rightl = height(root->right, cur + 1);
	return leftl > rightl ? leftl : rightl;
}

// 12ms 20.4mb
// another resolution?
bool test110::test_110(TreeNode* root) {
	if (root == nullptr) return true;
	return abs(height(root->left, 1) - height(root->right, 1)) <= 1 && test_110(root->left) && test_110(root->right);
}

// 192ms 141.1mb
// ~
int testtreenode::test_111(TreeNode* root) {
	if (root == nullptr) return 0;
	int result = 1;
	vector<TreeNode*> temp;
	temp.push_back(root);
	int index = 0;
	while (!temp.empty()) {
		index = temp.size();
		for (int i = 0; i < index; i++) {
			if (temp[i]->left == nullptr && temp[i]->right == nullptr) return result;
			if (temp[i]->left != nullptr) temp.push_back(temp[i]->left);
			if (temp[i]->right != nullptr) temp.push_back(temp[i]->right);
		}
		++result;
		temp.erase(temp.begin(), temp.begin() + index);
	}
	return result;
}

// 8ms 20.6mb
// middle
bool testtreenode::test_112(TreeNode* root, int targetSum) {
	if (root == nullptr) return false;
	int add = root->val;
	vector<TreeNode*> temp;
	temp.push_back(root);
	TreeNode* p = root;
	while (!temp.empty()) {
		if (temp[temp.size() - 1]->left != nullptr) {
			temp.push_back(temp[temp.size() - 1]->left);
			add += temp[temp.size() - 1]->val;
		}
		else if (temp[temp.size() - 1]->right != nullptr) {
			temp.push_back(temp[temp.size() - 1]->right);
			add += temp[temp.size() - 1]->val;
		}
		else {
			if (add == targetSum) return true;
			add -= temp[temp.size() - 1]->val;
			p = temp[temp.size() - 1];
			temp.erase(temp.end() - 1);
			while (!temp.empty()) {
				if (p == temp[temp.size() - 1]->left && temp[temp.size() - 1]->right != nullptr) {
					temp.push_back(temp[temp.size() - 1]->right);
					add += temp[temp.size() - 1]->val;
					break;
				}
				else {
					p = temp[temp.size() - 1];
					add -= temp[temp.size() - 1]->val;
					temp.erase(temp.end() - 1);
				}
			}
		}
	}
	return false;
}

void test144::preorder(TreeNode* root, vector<int>& result) {
	if (root == nullptr) return;
	result.push_back(root->val);
	preorder(root->left, result);
	preorder(root->right, result);
}

// 0ms 8.1mb
// another resolution?
vector<int> test144::test_144(TreeNode* root) {
	vector<int> result;
	preorder(root, result);
	return result;
}

// 4ms 8.1mb
// middle
vector<int> testtreenode::test_145(TreeNode* root) {
	if (root == nullptr) return {};
	vector<int> result;
	vector<TreeNode*> tree;
	tree.push_back(root);
	TreeNode* temp = tree[tree.size() - 1];
	while (!tree.empty()) {
		if (tree[tree.size() - 1]->left != nullptr && tree[tree.size() - 1]->left != temp && tree[tree.size() - 1]->right != temp)
		{
			temp = tree[tree.size() - 1];
			tree.push_back(tree[tree.size() - 1]->left);
		}
		else if (tree[tree.size() - 1]->right != nullptr && tree[tree.size() - 1]->right != temp)
		{
			temp = tree[tree.size() - 1];
			tree.push_back(tree[tree.size() - 1]->right);
		}
		else
		{
			temp = tree[tree.size() - 1];
			result.push_back(tree[tree.size() - 1]->val);
			tree.erase(tree.end() - 1);
		}
	}
	return result;
}

void test226::changelr(TreeNode* node) {
	if (node == nullptr) return;
	TreeNode* temp = node->left;
	node->left = node->right;
	node->right = temp;
	changelr(node->left);
	changelr(node->right);
}

// 4ms 9.3mb
// improve time
TreeNode* test226::test_226(TreeNode* root) {
	changelr(root);
	return root;
}

void test257::road(TreeNode* node, vector<string>& result, string& str) {
	string temp = str;
	if (node->left != nullptr) {
		temp += ("->" + to_string(node->val));
		road(node->left, result, temp);
	}
	if (node->right != nullptr) {
		temp = str;
		temp += ("->" + to_string(node->val));
		road(node->right, result, temp);
	}
	else if (node->left == nullptr) {
		str += ("->" + to_string(node->val));
		result.push_back(str);
	}
}

// 4ms 12.5mb
// middle
vector<string> test257::test_257(TreeNode* root) {
	vector<string> result;
	if (root != nullptr) {
		string str = to_string(root->val);
		if (root->left != nullptr) {
			road(root->left, result, str);
		}
		if (root->right != nullptr) {
			str = to_string(root->val);
			road(root->right, result, str);
		}
		else if (root->left == nullptr) {
			result.push_back(str);
		}
	}
	return result;
}

vector<string> MorrisInOrder(TreeNode* root) {
	vector<string> result;
	return result;
}
