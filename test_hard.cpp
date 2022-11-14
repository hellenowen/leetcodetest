#include "test_hard.h"

// 8ms 7.3mb
// 55555 reference
bool test_hard::test_10(std::string s, std::string p) {
	size_t slen = s.size();
	size_t plen = p.size();
	std::vector<std::vector<bool>> result;
	for (size_t i = 0; i < slen + 1; i++) {
		std::vector<bool> temp;
		for (size_t j = 0; j < plen + 1; j++) {
			temp.push_back(false);
		}
		result.push_back(temp);
	}
	result[0][0] = true;
	for (size_t j = 1; j < plen + 1; j++) {
		if (p[j - 1] == '*') {
			result[0][j] = result[0][j - 2];
		}
	}
	for (size_t i = 1; i < slen + 1; i++) {
		for (size_t j = 1; j < plen + 1; j++) {
			if (s[i - 1] == p[j - 1] || p[j - 1] == '.') {
				result[i][j] = result[i - 1][j - 1];
			}
			else if (p[j - 1] == '*') {
				if (s[i - 1] == p[j - 2] || p[j - 2] == '.') {
					result[i][j] = result[i][j - 2] || result[i - 1][j - 2] || result[i - 1][j];
				}
				else {
					result[i][j] = result[i][j - 2];
				}
			}
		}
	}
	return result[slen][plen];
}

// 1568ms 25mb
// T.T
std::vector<std::vector<int>> test_hard::test_15(std::vector<int>& nums) {
	std::vector<std::vector<int>> result;
	std::map<std::vector<int>, bool> delrepeat;
	std::sort(nums.begin(), nums.end());
	int i = 0;
	int j = nums.size() - 1;
	std::vector<int> temp;
	for (size_t k = 0; k < nums.size(); k++) {
		i = 0;
		j = nums.size() - 1;
		while (i < j) {
			if (i == k) {
				++i;
			}
			if (j == k) {
				--j;
			}
			if (i >= j)
			{
				break;
			}
			if (nums[i] + nums[j] + nums[k] == 0) {
				// elimination rearrangement
				temp = { nums[i],nums[j],nums[k] };
				std::sort(temp.begin(), temp.end());
				if (delrepeat.find(temp) == delrepeat.end()) {
					delrepeat.insert({ temp,true });
					result.push_back(temp);
				}
				++i;
				--j;
			}
			else if (nums[i] + nums[j] + nums[k] < 0) {
				++i;
			}
			else if (nums[i] + nums[j] + nums[k] > 0) {
				--j;
			}
		}
	}
	return result;
}
