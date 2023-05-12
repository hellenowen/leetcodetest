#pragma once

#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

namespace test_middle {
	std::vector<int> test_1(std::vector<int> nums, int target);
	double test_4(std::vector<int>& nums1, std::vector<int>& nums2);
	std::string test_5(std::string s);
	int test_7(int x);
	bool test_9(int x);
	std::string test_12(int num);
	std::string test_14(std::vector<std::string>& strs);
	int test_16(std::vector<int>& nums, int target);
	std::vector<std::string> test_17(std::string digits);
	bool test_20(std::string s);
	int test_26(std::vector<int>& nums);
	int test_27(std::vector<int>& nums, int val);
	int test_28(std::string haystack, std::string needle);
	int test_29(int dividend, int divisor);
	void test_31(std::vector<int>& nums);
	int test_33(std::vector<int>& nums, int target);
	std::vector<int> test_34(std::vector<int>& nums, int target);
	int test_35(std::vector<int>& nums, int target);
	std::string test_38(int n);
	int test_41(std::vector<int>& nums);
	std::string test_43(std::string num1, std::string num2);
	int test_45(std::vector<int>& nums);
	vector<vector<int>> test_46(vector<int>& nums);
	void test_48(std::vector< std::vector<int>>& matrix);
	int test_58(string s);
	vector<int> test_66(vector<int>& digits);
	string test_67(string a, string b);
	int test_69(int x);
	int test_70(int n);
	void test_88(vector<int>& nums1, int m, vector<int>& nums2, int n);
	vector<vector<int>> test_118(int numRows);
	vector<int> test_119(int rowIndex);
	int test_121(vector<int>& prices);
	bool test_125(string s);
	int test_136(vector<int>& nums);
	string test_168(int columnNumber);
	uint32_t test_190(uint32_t n);
	bool test_202(int n);
	bool test_205(string s, string t);
	bool test_217(vector<int>& nums);
	bool test_219(vector<int>& nums, int k);
	vector<string> test_228(vector<int>& nums);
	bool test_231(int n);
	bool test_242(string s, string t);
	bool test_263(int n);
	int test_268(vector<int> nums);
	int test_278(int n);
	void test_283(vector<int>& nums);
}

namespace test22 {
	void combat(std::vector<std::string>& result, int count, std::string cur, bool left, int& n, int countnum);
	std::vector<std::string> test_22(int n);
}

namespace test225 {
	// 0ms 6.6mb
	// en
	class MyStack {
	private:
		queue<int> q1;
		queue<int> q2;
	public:
		MyStack() {

		}
		void push(int x) {
			q1.push(x);
		}
		int pop() {
			while (q1.size() > 1) {
				q2.push(q1.front());
				q1.pop();
			}
			int result = q1.front();
			q1.pop();
			while (!q2.empty()) {
				q1.push(q2.front());
				q2.pop();
			}
			return result;
		}
		int top() {
			while (q1.size() > 1) {
				q2.push(q1.front());
				q1.pop();
			}
			return q1.front();
		}
		bool empty() {
			return q1.empty() && q2.empty();
		}
	};
}

namespace test232 {
	// 4ms 6.8mb
	// en
	class MyQueue {
	private:
		stack<int> s1;
		stack<int> s2;
	public:
		MyQueue() {

		}
		void push(int x) {
			while (!s2.empty()) {
				s1.push(s2.top());
				s2.pop();
			}
			s1.push(x);
		}
		int pop() {
			while (!s1.empty()) {
				s2.push(s1.top());
				s1.pop();
			}
			int result = s2.top();
			s2.pop();
			return result;
		}
		int peek() {
			while (!s1.empty()) {
				s2.push(s1.top());
				s1.pop();
			}
			return s2.top();
		}
		bool empty() {
			return s1.empty() && s2.empty();
		}
	};
}
