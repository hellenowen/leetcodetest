#include <iostream>

//#include "test_listnode.h"
#include "test_compilations.h"
//#include "test_improve.h"
//#include "test_hard.h"

void test_37(std::vector<std::vector<char>>& board) {

}

std::vector<std::vector<int>> test_39(std::vector<int>& candidates, int target) {
	std::vector<std::vector<int>> result;
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

int test_42(std::vector<int>& height) {
	return -1;
}

int main() {
	std::vector<int> a = { 0,0,0 };
	for (auto& p : test_39(a, 0)) {
		for (auto& q : p) {
			std::cout << q << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
