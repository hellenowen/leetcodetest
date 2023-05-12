#include "test_compilations.h"

std::string testexample::testFunc()
{
	return "please coding test function";
}

// other resolution
void testexample::quicksort(std::vector<int>& nums) {
	std::vector<int> before;
	std::vector<int> behind;
	std::vector<int> middle;
	for (auto& d : nums) {
		if (d > nums[nums.size() - 1]) behind.push_back(d);
		if (d < nums[nums.size() - 1]) before.push_back(d);
		if (d == nums[nums.size() - 1]) middle.push_back(d);
	}
	if (!before.empty()) quicksort(before);
	if (!behind.empty()) quicksort(behind);
	int i = 0;
	while (i < before.size()) {
		nums[i] = before[i];
		++i;
	}
	for (int j = 0; j < middle.size(); j++) {
		nums[i + j] = middle[j];
	}
	i += middle.size();
	for (int j = 0; j < behind.size(); j++) {
		nums[i + j] = behind[j];
	}
}
