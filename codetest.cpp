#include <iostream>
using namespace std;

//#include "test_listnode.h"
#include "test_compilations.h"
//#include "test_improve.h"
//#include "test_hard.h"

void test_37(std::vector<std::vector<char>>& board) {

}

std::vector<std::vector<int>> test_39(std::vector<int>& candidates, int target) {
	std::vector<std::vector<int>> result;
	std::sort(candidates.begin(), candidates.end());
	return result;
}

std::vector<std::vector<int>> test_40(std::vector<int>& candidates, int target) {
	return {};
}

int test_41(std::vector<int>& nums) {
	int min = nums[0];
	for (auto& d : nums) {
		if (d > 0) {
			if (min < 0) min = d;
			if (d < min) min = d;
		}
	}
	if (min != 1) {
		return 1;
	}
	else {

	}
	return -1;
}

int climbStairs(int n) {
	if (n == 3) {
		return 3;
	}
	if (n == 2) {
		return 2;
	}
	if (n == 1) {
		return 1;
	}
	return climbStairs(n - 1) + climbStairs(n - 2);
}

int test_70(int n) {
	if (n == 3) {
		return 3;
	}
	if (n == 2) {
		return 2;
	}
	if (n == 1) {
		return 1;
	}
	return climbStairs(n - 1) + climbStairs(n - 2);
}

int main() {
	std::vector<int> a = { 0,0,0 };
	for (auto& p : test_39(a, 0)) {
		for (auto& q : p) {
			std::cout << q << " ";
		}
		std::cout << std::endl;
	}
	cout << test_70(45);
	return 0;
}
