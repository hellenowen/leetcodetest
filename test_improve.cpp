#include "test_improve.h"

// 36ms 11.2mb
// defeat 5.9% - -|||
int test_improve::test_13(std::string s) {
	std::map<char, int> valueType;
	valueType['I'] = 1;
	valueType['V'] = 5;
	valueType['X'] = 10;
	valueType['L'] = 50;
	valueType['C'] = 100;
	valueType['D'] = 500;
	valueType['M'] = 1000;
	std::map<std::string, int> smallType;
	smallType["IV"] = 4;
	smallType["IX"] = 9;
	smallType["XL"] = 40;
	smallType["XC"] = 90;
	smallType["CD"] = 400;
	smallType["CM"] = 900;
	char curC = s[0];
	int result = 0;
	int sameCount = 1;
	std::string tempSub = "";
	for (size_t i = 1; i < s.size(); i++) {
		if (!tempSub.empty()) {
			tempSub += curC;
			if (smallType.find(tempSub) != smallType.end()) {
				result += smallType[tempSub];
				tempSub.clear();
			}
		}
		else {
			if (valueType[curC] == valueType[s[i]]) {
				sameCount++;
			}
			else if (valueType[curC] > valueType[s[i]]) {
				result += (valueType[curC] * sameCount);
				sameCount = 1;
			}
			else {
				sameCount = 1;
				tempSub += curC;
			}
		}
		curC = s[i];
	}
	if (!tempSub.empty()) {
		tempSub += curC;
		if (smallType.find(tempSub) != smallType.end()) {
			result += smallType[tempSub];
			tempSub.clear();
		}
		sameCount = 0;
	}
	result += (valueType[curC] * sameCount);
	return result;
}

// 164ms 11mb
// defeat 7.9% - -|||
int test_improve::test_3(std::string s) {
	int count = 0;
	int maxl = 0;
	int length = 0;
	std::map<char, int> temp;
	for (auto& c : s) {
		if (temp.find(c) == temp.end()) {
			temp.insert({ c, count });
			length++;
		}
		else {
			std::vector<char> t;
			if (length > maxl) {
				maxl = length;
			}
			for (auto& kv : temp) {
				if (kv.second < temp[c]) {
					t.push_back(kv.first);
				}
			}
			for (auto& r : t) {
				temp.erase(r);
			}
			temp[c] = count;
			length -= t.size();
		}
		count++;
	}
	if (length > maxl) {
		maxl = length;
	}
	return maxl;
}

// 68ms 16.5mb
// defeat 9.8%
std::string test_improve::test_6(std::string s, int numRows) {
	std::vector<std::vector<char>> zimg;
	std::vector<int> indexList;
	int i = 0;
	int temp = -1;
	int total = s.size();
	if (numRows == 1) {
		return s;
	}
	for (int j = 0; j < numRows; j++) {
		zimg.push_back(std::vector<char>());
	}
	while (i < total) {
		for (int j = 0; j < numRows; j++) {
			if (j >= 1 && j <= numRows - 2) {
				temp = (2 * numRows - 2) * i - j;
				if (temp < total && temp >= 0) {
					zimg[j].push_back(s[temp]);
				}
			}
			temp = (2 * numRows - 2) * i + j;
			if (temp < total && temp >= 0) {
				zimg[j].push_back(s[temp]);
			}
		}
		i++;
	}
	std::string result = "";
	for (auto& line : zimg) {
		for (auto& c : line) {
			result += c;
		}
	}
	return result;
}

// 8ms 8.2mb
// - -|||
int test_improve::test_8(std::string s) {
	std::map<char, int> ctoi = {
		{'0',0},
		{'1',1},
		{'2',2},
		{'3',3},
		{'4',4},
		{'5',5},
		{'6',6},
		{'7',7},
		{'8',8},
		{'9',9}
	};
	std::vector<int> num;
	bool positive = true;
	bool beginfindnum = false;
	bool nozero = true;
	for (auto& c : s) {
		if (beginfindnum) {
			if (c < '0' || c > '9') {
				break;
			}
			else {
				if (c == '0') {
					if (nozero) {
						continue;
					}
				}
				else {
					nozero = false;
				}
				num.push_back(ctoi[c]);
			}
		}
		else {
			if (c == ' ') {
				continue;
			}
			else if (c == '-') {
				positive = false;
				beginfindnum = true;
			}
			else if (c == '+') {
				beginfindnum = true;
			}
			else if (c >= '0' && c <= '9') {
				beginfindnum = true;
				if (c != '0') {
					num.push_back(ctoi[c]);
					nozero = false;
				}
			}
			else {
				break;
			}
		}
	}
	std::vector<int> maxnum = { 2,1,4,7,4,8,3,6,4,8 };
	if (num.size() > maxnum.size()) {
		return positive ? int(pow(2, 30)) - 1 + int(pow(2, 30)) : int(pow(-2, 31));
	}
	else if (num.size() == maxnum.size()) {
		for (size_t i = 0; i < num.size(); i++) {
			if (num[i] < maxnum[i]) {
				break;
			}
			else {
				if (i == (num.size() - 1) && positive) {
					maxnum[i] -= 1;
				}
				if (num[i] > maxnum[i]) {
					return positive ? int(pow(2, 30)) - 1 + int(pow(2, 30)) : int(pow(-2, 31));
				}
			}
		}
	}
	int result = 0;
	for (size_t i = 0; i < num.size(); i++) {
		if (positive) {
			result += num[i] * int(pow(10, num.size() - i - 1));
		}
		else {
			result -= num[i] * int(pow(10, num.size() - i - 1));
		}
	}
	return result;
}

// 700ms 57.6mb
// confusing ?^?
int test_improve::test_11(std::vector<int>& height) {
	int result = 0;
	int temp = 0;
	size_t j = height.size() - 1;
	int beforemaxheight = 0;
	for (size_t i = 0; i < height.size(); i++) {
		if (height[i] < beforemaxheight) {
			continue;
		}
		beforemaxheight = height[i];
		while (height[i] > height[j]) {
			temp = (j - i) * (height[i] > height[j] ? height[j] : height[i]);
			if (result < temp) result = temp;
			--j;
		}
		temp = (j - i) * height[i];
		if (result < temp) result = temp;
		j = height.size() - 1;
	}
	return result;
}

// 688ms 151.8mb
// improve
std::vector<int> test_improve::test_30(std::string s, std::vector<std::string>& words) {
	std::vector<int> result;
	std::map<std::string, int> countMap;
	std::map<std::string, int> tempcountMap;
	// words.len>0
	int onelen = words[0].length();
	int substrlen = words.size() * onelen;
	if (s.length() < substrlen) return result;
	for (auto& c : words) {
		if (countMap.find(c) != countMap.end()) {
			++countMap[c];
		}
		else {
			countMap.insert({ c,1 });
		}
	}
	std::string temp;
	std::string temptemp;
	int count = 0;
	bool ok = false;
	for (size_t i = 0; i <= s.length() - substrlen; i++) {
		tempcountMap = countMap;
		count = 0;
		temp = s.substr(i, substrlen);
		ok = true;
		while (count < substrlen) {
			temptemp = temp.substr(count, onelen);
			if (tempcountMap.find(temptemp) != tempcountMap.end() && tempcountMap[temptemp] > 0) {
				--tempcountMap[temptemp];
			}
			else {
				ok = false;
				break;
			}
			count += onelen;
		}
		if (ok) {
			result.push_back(i);
		}
	}
	return result;
}

// 24ms 19.3mb
// improve & another resolution?
bool test_improve::test_36(std::vector<std::vector<char>>& board) {
	std::map<char, bool> repeatornot;
	for (size_t j = 1; j <= 3; j++) {
		for (size_t k = 0; k < 3; k++) {
			repeatornot.clear();
			for (size_t i = k * 3; i < k * 3 + 3; i++) {
				if (board[i][3 * j - 1] != '.' && (repeatornot.find(board[i][3 * j - 1]) != repeatornot.end()))
					return false;
				else repeatornot.insert({ board[i][3 * j - 1] , true });
				if (board[i][3 * j - 2] != '.' && (repeatornot.find(board[i][3 * j - 2]) != repeatornot.end()))
					return false;
				else repeatornot.insert({ board[i][3 * j - 2] , true });
				if (board[i][3 * j - 3] != '.' && (repeatornot.find(board[i][3 * j - 3]) != repeatornot.end()))
					return false;
				else repeatornot.insert({ board[i][3 * j - 3] , true });
			}
		}
	}
	for (size_t i = 0; i < board.size(); i++) {
		repeatornot.clear();
		for (size_t j = 0; j < board[i].size(); j++) {
			if (board[i][j] != '.' && (repeatornot.find(board[i][j]) != repeatornot.end()))
				return false;
			else repeatornot.insert({ board[i][j] , true });
		}
	}
	for (size_t i = 0; i < board.size(); i++) {
		repeatornot.clear();
		for (size_t j = 0; j < board[i].size(); j++) {
			if (board[j][i] != '.' && (repeatornot.find(board[j][i]) != repeatornot.end()))
				return false;
			else repeatornot.insert({ board[j][i] , true });
		}
	}
	return true;
}

// 4ms 7.1mb
// improve brain
int test_improve::test_32(std::string s) {
	int maxCount = 0;
	std::vector<int> process;
	int temp = 0;
	for (auto& c : s) {
		if (c == '(') {
			process.push_back(1);
		}
		else if (c == ')') {
			if (process.empty()) {
				process.push_back(-1);
			}
			else {
				if (process[process.size() - 1] == 1) {
					process.pop_back();
					if (process.empty()) {
						process.push_back(2);
					}
					else {
						temp = 0;
						while (!process.empty() && process[process.size() - 1] > 1) {
							temp += process[process.size() - 1];
							process.pop_back();
						}
						temp += 2;
						process.push_back(temp);
					}
				}
				else {
					temp = 0;
					while (!process.empty() && process[process.size() - 1] > 1) {
						temp += process[process.size() - 1];
						process.pop_back();
					}
					if (process.empty()) {
						process.push_back(temp);
						process.push_back(-1);
					}
					else {
						if (process[process.size() - 1] == 1) {	// '('
							process.pop_back();
							temp += 2;
							process.push_back(temp);
						}
						else {	// ')'
							if (temp != 0) {
								process.push_back(temp);
							}
							process.push_back(-1);
						}
					}
				}
			}
		}
	}
	temp = 0;
	for (auto& d : process) {
		if (d <= 1) temp = 0;
		if (d > 1) temp += d;
		if (temp > maxCount) {
			maxCount = temp;
		}
	}
	return maxCount;
}

// 1244ms 13.3mb
// defeat 5%
std::vector<std::vector<int>> test_improve::test_18(std::vector<int>& nums, int target) {
	std::vector<std::vector<int>> result;
	std::map<std::vector<int>, bool> norepeat;
	int i = 0;
	long tempvalue = 0;
	std::vector<int> temp;
	std::sort(nums.begin(), nums.end());
	int len = nums.size();
	int j = len - 1;
	for (int a = 0; a < len; a++) {
		for (int b = 0; b < len; b++) {
			if (a == b) continue;
			i = 0;
			j = len - 1;
			while (i < j) {
				if (a == i || b == i) {
					++i;
					continue;
				}
				if (a == j || b == j) {
					--j;
					continue;
				}
				tempvalue = 0;
				tempvalue += nums[a];
				tempvalue += nums[b];
				tempvalue += nums[i];
				tempvalue += nums[j];
				if (tempvalue == target) {
					temp = { nums[a], nums[b], nums[i],nums[j] };
					std::sort(temp.begin(), temp.end());
					if (norepeat.find(temp) == norepeat.end()) {
						result.push_back(temp);
						norepeat.insert({ temp,true });
					}
					++i;
					--j;
				}
				else if (tempvalue < target) {
					++i;
				}
				else {
					--j;
				}
			}
		}
	}
	return result;
}

// 1040ms 19.2mb
// edge of timeout
int test_improve::test_42(std::vector<int>& height) {
	int result = 0;
	int i = 0;
	int j = 0;
	int max = 0;
	int len = height.size();
	while (i < len - 1) {
		j = i + 1;
		max = i;
		while (j < len) {
			if (height[j] >= height[max]) {
				for (int k = i + 1; k < j; k++) {
					result += (height[max] - height[k]);
				}
				i = j;
				break;
			}
			++j;
			if (j == len) {
				max = i + 1;
				--j;
				while (j > i) {
					if (height[j] >= height[max]) {
						max = j;
					}
					--j;
				}
				j = i + 1;
			}
		}
	}
	return result;
}
