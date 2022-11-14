#include "test_middle.h"

// 8ms 10.7mb
// middle
std::vector<int> test_middle::test_1(std::vector<int> nums, int target) {
	std::map<int, int> rtemp;
	int preIndex = 0;
	bool findZero = false;
	if (nums[0] == target) {
		findZero = true;
	}
	for (size_t i = 0; i < nums.size(); i++) {
		if (findZero) {
			if (nums[i] == 0 && i != 0) {
				return { 0, int(i) };
			}
		}
		if (rtemp.find(nums[i]) != rtemp.end()) {
			return { rtemp[nums[i]], int(i) };
		}
		rtemp.insert({ target - nums[i], i });
	}
	return { -1, -1 };
}

// 32ms 86.8mb
// middle
double test_middle::test_4(std::vector<int>& nums1, std::vector<int>& nums2) {
	int m = nums1.size();
	int n = nums2.size();
	int maxIndex = m + n;// m > n ? m : n;
	int i = 0;
	int j = 0;
	double midbit = 0;
	int midcount = (m + n) / 2;
	bool findTwo = (m + n) % 2 == 0; // midcount-1 midcount
	int temp = 0;
	while (maxIndex > 0) {
		maxIndex--;
		if (i >= m) {
			temp = nums2[j];
			j++;
		}
		else if (j >= n)
		{
			temp = nums1[i];
			i++;
		}
		else if (nums1[i] >= nums2[j]) {
			temp = nums2[j];
			j++;
		}
		else if (nums1[i] < nums2[j]) {
			temp = nums1[i];
			i++;
		}
		if ((i + j) == midcount + 1) {
			if (findTwo) {
				midbit = (midbit + temp) / 2.0;
			}
			else {
				midbit = temp;
			}
			break;
		}
		midbit = temp;
	}
	return midbit;
}

// 16ms 6.7mb
// aha
std::string test_middle::test_5(std::string s) {
	int maxl = 0;
	int maxlbeginindex = -1;
	char b;
	char a;
	int lnum = 0;
	int up = 0;
	int down = 0;
	int totallen = s.size();
	for (size_t i = 0; i < s.size(); i++) {
		up = i;
		down = i + 1;
		a = '\0';
		b = s[up];
		if (down < totallen) {
			a = s[down];
		}
		lnum = 0;
		while (b == a && a != '\0') {
			up--;
			down++;
			lnum += 2;
			if (up >= 0) {
				b = s[up];
			}
			else {
				b = '\0';
			}
			if (down < totallen) {
				a = s[down];
			}
			else {
				a = '\0';
			}
		}
		if (lnum > maxl) {
			maxl = lnum;
			maxlbeginindex = up + 1;
		}
		maxl = lnum > maxl ? lnum : maxl;
		up = i - 1;
		down = i + 1;
		if (up >= 0) {
			b = s[up];
		}
		else {
			b = '\0';
		}
		if (down < totallen) {
			a = s[down];
		}
		else {
			a = '\0';
		}
		lnum = 1;
		while (a == b && a != '\0') {
			up--;
			down++;
			lnum += 2;
			if (up >= 0) {
				b = s[up];
			}
			else {
				b = '\0';
			}
			if (down < totallen) {
				a = s[down];
			}
			else {
				a = '\0';
			}
		}
		if (lnum > maxl) {
			maxl = lnum;
			maxlbeginindex = up + 1;
		}
	}
	if (maxlbeginindex == -1) {
		return std::string(&s[0]);
	}
	return s.substr(maxlbeginindex, maxl);
}

// 0ms 6.5mb
// improve storage
int test_middle::test_7(int x) {
	if (x == -pow(2, 31)) {
		return 0;
	}
	std::vector<int> maxnum = { 2,1,4,7,4,8,3,6,4,8 };
	std::vector<int> num;
	bool begin = true;
	int temp = 0;
	int absx = x < 0 ? -x : x;
	for (int i = 9; i >= 0; i--) {
		temp = (absx / int(pow(10, i))) % 10;
		if (begin) {
			if (temp != 0) {
				begin = false;
				num.push_back(temp);
			}
		}
		else {
			num.push_back(temp);
		}
	}
	int result = 0;
	size_t numsize = num.size();
	if (numsize == maxnum.size()) {
		for (size_t i = 0; i < numsize; i++) {
			if (num[numsize - i - 1] < maxnum[i]) {
				break;
			}
			else if (num[numsize - i - 1] > maxnum[i]) {
				return 0;
			}
		}
	}
	for (size_t i = 0; i < numsize; i++) {
		result += num[i] * int(pow(10, i));
	}
	return result * (x < 0 ? -1 : 1);
}

// 0ms 6.2mb
// improve storage
bool test_middle::test_9(int x) {
	if (x < 0) {
		return false;
	}
	int8_t temp = 0;
	int8_t l = -1;
	for (int i = 9; i >= 0; i--) {
		temp = (x / int(pow(10, i))) % 10;
		if (l == -1) {
			if (temp != 0) {
				l = i;
			}
		}
		else {
			if (temp != (x / int(pow(10, (l - i)))) % 10) {
				return false;
			}
		}
		if (l / 2 > i) {
			break;
		}
	}
	return true;
}

// 4ms 5.8mb
// en
std::string test_middle::test_12(int num) {
	int left = num;
	int temp = 0;
	std::string result = "";
	int threshold1 = 1000;
	int threshold2 = 500;
	int curChar = ' ';
	while (left > 0) {
		temp = left / threshold1;
		switch (threshold1)
		{
		case 1:curChar = 'I'; break;
		case 10:curChar = 'X'; break;
		case 100:curChar = 'C'; break;
		case 1000:curChar = 'M'; break;
		default:temp = 0; break;
		}
		for (int i = 0; i < temp; i++) {
			result += curChar;
		}
		left -= temp * threshold1;
		threshold1 /= 10;
		if (threshold1 > 0) {
			temp = left / threshold1;
			switch (temp * threshold1)
			{
			case 4:result += 'I'; result += 'V'; break;
			case 9:result += 'I'; result += 'X'; break;
			case 40:result += 'X'; result += 'L'; break;
			case 90:result += 'X'; result += 'C'; break;
			case 400:result += 'C'; result += 'D'; break;
			case 900:result += 'C'; result += 'M'; break;
			default:left += temp * threshold1; break;	// 不是以上特殊情况就把待减值加回来
			}
			left -= temp * threshold1;
		}
		if (threshold2 > 0) {
			temp = left / threshold2;
			switch (threshold2)
			{
			case 5:curChar = 'V'; break;
			case 50:curChar = 'L'; break;
			case 500:curChar = 'D'; break;
			default:temp = 0; break;
			}
			for (int i = 0; i < temp; i++) {
				result += curChar;
			}
			left -= temp * threshold2;
			threshold2 /= 10;
		}
	}
	return result;
}

// 8ms 8.8mb
// improve time
std::string test_middle::test_14(std::vector<std::string>& strs) {
	std::string maxPre = strs[0];
	int tempminstrlen = maxPre.size();
	for (size_t i = 1; i < strs.size(); i++) {
		if (maxPre.empty()) break;
		if (maxPre.size() > strs[i].size()) {
			tempminstrlen = strs[i].size();
			maxPre.erase(tempminstrlen);
		}
		else {
			tempminstrlen = maxPre.size();
		}
		for (size_t j = 0; j < tempminstrlen; j++) {
			if (maxPre[j] != strs[i][j]) {
				maxPre.erase(j);
				break;
			}
		}
	}
	return maxPre;
}

// 0ms? 6.4mb
// improve graphy
std::vector<std::string> test_middle::test_17(std::string digits) {
	char a = 'a';	// 1
	std::vector<std::string> result;
	int up = 0;
	int down = 0;
	std::string emptystr = "";
	std::vector<std::string>  temp;
	for (auto& d : digits) {
		if (d == '8' || d == '9') {
			up = (d - '1') * 3 - 2;
		}
		else {
			up = (d - '1') * 3 - 3;
		}
		if (d == '9' || d == '7') {
			down = up + 4;
		}
		else {
			down = up + 3;
		}
		temp.clear();
		for (int j = up; j < down; j++) {
			if (result.empty()) {
				temp.push_back(emptystr + char(a + j));
			}
			else {
				for (auto& r : result) {
					temp.push_back(r + char(a + j));
				}
			}
		}
		result = temp;
	}
	return result;
}

// 156ms 9.8mb
// can you do not using sort?
int test_middle::test_16(std::vector<int>& nums, int target) {
	int result = nums[0] + nums[1] + nums[2];
	std::sort(nums.begin(), nums.end());
	int i = 0;
	int j = nums.size() - 1;
	int minDelta = abs(target - result);
	for (size_t k = 0; k < nums.size(); k++) {
		i = 0;
		j = nums.size() - 1;
		while (i < j) {
			if (k == j) {
				--j;
				continue;
			}
			if (k == i) {
				++i;
				continue;
			}
			if (abs(target - (nums[i] + nums[j] + nums[k])) < minDelta) {
				minDelta = abs(target - (nums[i] + nums[j] + nums[k]));
				result = nums[i] + nums[j] + nums[k];
			}
			if (nums[i] + nums[j] + nums[k] > target) {
				--j;
			}
			else if (nums[i] + nums[j] + nums[k] < target) {
				++i;
			}
			else {
				return nums[i] + nums[j] + nums[k];
			}
		}
	}
	return result;
}

// 0ms 6.1mb
// aha
bool test_middle::test_20(std::string s) {
	std::string exception = "";
	for (auto& c : s) {
		if (c == '(') {
			exception += ')';
		}
		else if (c == '[') {
			exception += ']';
		}
		else if (c == '{') {
			exception += '}';
		}
		else {
			if (exception.size() <= 0 || exception[exception.size() - 1] != c) {
				return false;
			}
			exception.erase(exception.end() - 1);
		}
	}
	return exception.empty();
}

void test22::combat(std::vector<std::string>& result, int count, std::string cur, bool left, int& n, int countnum) {
	if (left) {
		if (count < n) {
			cur += "(";
			++count;
			++countnum;
		}
		combat(result, count, cur, false, n, countnum);
		if (count < n) {
			combat(result, count, cur, true, n, countnum);
		}
	}
	else {
		if (countnum > 0) {
			cur += ")";
			--countnum;
		}
		if (count == n && countnum == 0) {
			result.push_back(cur);
		}
		else {
			if (countnum > 0) {
				combat(result, count, cur, false, n, countnum);
			}
			if (count < n) {
				combat(result, count, cur, true, n, countnum);
			}
		}
	}
}

// 4ms 13.3mb
// another resolution?
std::vector<std::string> test22::test_22(int n) {
	std::vector<std::string> result;
	combat(result, 0, "", true, n, 0);
	return result;
}

// 0ms 5.8mb
// middle
int test_middle::test_29(int dividend, int divisor) {
	if (divisor == -1)
		if (dividend == (1 << 31))
		{
			return ((1 << 30) - 1) << 1 | 1;
		}
		else {
			return -dividend;
		}
	if (divisor == 1) return dividend;
	int q = 0;
	int count = 0;
	int result = 0;
	bool negative = (dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0);
	dividend = dividend > 0 ? -dividend : dividend;
	divisor = divisor > 0 ? -divisor : divisor;
	if (dividend > divisor) {
		return 0;
	}
	else if (dividend == divisor) {
		return negative ? -1 : 1;
	}
	while (dividend <= divisor) {
		q = dividend;
		count = 0;
		while ((q >> 1) < divisor) {
			q >>= 1;
			++count;
		}
		q = -divisor;
		result += negative ? -(1 << count) : (1 << count);
		while (count > 0) {
			--count;
			q <<= 1;
		}
		dividend += q;
	}
	return result;
}

// 0ms 8.4mb
// ~
int test_middle::test_27(std::vector<int>& nums, int val) {
	int count = 0;
	int temp = 0;
	int len = nums.size();
	for (size_t i = 0; i < len; i++) {
		if (nums[i] == val) {
			temp = nums[i];
			while (count < (len - i) && nums[len - count - 1] == val) {
				++count;
			}
			if (count >= (len - i)) {
				break;
			}
			nums[i] = nums[len - count - 1];
			nums[len - count - 1] = temp;
		}
	}
	return len - count;
}

// 4ms 17.9mb
// improve storage
int test_middle::test_26(std::vector<int>& nums) {
	int temp = 0;
	int cur = nums[0];
	int count = 1;
	for (int i = 0; i < nums.size(); i++) {
		if (nums[i] != cur) {
			cur = nums[i];
			if (count != i) {
				temp = nums[i];
				nums[i] = nums[count];
				nums[count] = temp;
			}
			++count;
		}
	}
	return count;
}

// 0ms 6.1mb
// improve storage
int test_middle::test_28(std::string haystack, std::string needle) {
	int a = haystack.length();
	int b = needle.length();
	for (int i = 0; i <= a - b; i++) {
		for (int j = 0; j < b; j++) {
			if (haystack[i + j] != needle[j]) break;
			if (haystack[i + j] == needle[j] && j == b - 1) {
				return i;
			}
		}
	}
	return -1;
}

// 4ms 10.7mb
// aha
int test_middle::test_33(std::vector<int>& nums, int target) {
	int down = 0;
	int up = nums.size() - 1;
	while (down <= up) {
		if (nums[down] == target) return down;
		if (nums[up] == target) return up;
		if (nums[(down + up) / 2] == target) return (down + up) / 2;
		if (nums[down] < target && nums[(down + up) / 2] > target) {
			up = (down + up) / 2;
			++down;
		}
		else if (nums[(down + up) / 2] < target && nums[up] > target) {
			down = (down + up) / 2;
			--up;
		}
		else if (nums[down] > nums[up]) {
			if (nums[(down + up) / 2] < nums[down]) {
				up = (down + up) / 2;
				++down;
			}
			else if (nums[(down + up) / 2] > nums[up]) {
				down = (down + up) / 2;
				--up;
			}
		}
		else {
			return nums[down] == target ? down : -1;
		}
	}
	return -1;
}

// 4ms 13.2mb
// middle
std::vector<int> test_middle::test_34(std::vector<int>& nums, int target) {
	int begin = 0;
	int endd = 0;
	int down = 0;
	int l = nums.size();
	int up = l - 1;
	int i = 0;
	while (down <= up) {
		if (target > nums[down] && target < nums[(down + up) / 2]) {
			up = (down + up) / 2;
			++down;
		}
		else if (target > nums[(down + up) / 2] && target < nums[up]) {
			down = (down + up) / 2;
			--up;
		}
		else {
			if (nums[down] == target) i = down;
			if (nums[(down + up) / 2] == target) i = (down + up) / 2;
			if (nums[up] == target) i = up;
			begin = 0;
			while (i - begin >= 0 && nums[i - begin] == target) {
				++begin;
			}
			endd = 0;
			while (i + endd < l && nums[i + endd] == target) {
				++endd;
			}
			if (begin != 0 || endd != 0)return { i - begin + 1,i + endd - 1 };
			++down;
			--up;
		}
	}
	return { -1,-1 };
}

// 4ms 11.7mb
// middle
void test_middle::test_31(std::vector<int>& nums) {
	int temp = 0;
	int len = nums.size();
	int k = len - 1;
	for (int i = len - 1; i > 0; i--) {
		if (nums[i] > nums[i - 1]) {
			while (k < len && nums[k] <= nums[i - 1]) {
				--k;
			}
			temp = nums[i - 1];
			nums[i - 1] = nums[k];
			nums[k] = temp;
			if (i != len - 1) {
				for (int j = i; j <= (i + len - 1) / 2; j++) {
					temp = nums[j];
					nums[j] = nums[nums.size() - 1 - j + i];
					nums[nums.size() - 1 - j + i] = temp;
				}
			}
			return;
		}
	}
	// max -> min
	for (int j = 0; j < len / 2; j++) {
		temp = nums[j];
		nums[j] = nums[nums.size() - j - 1];
		nums[nums.size() - j - 1] = temp;
	}
}

// 0ms 6.2mb
// middle
std::string test_middle::test_38(int n) {
	int num = 1;
	std::string last = "1";
	std::string result = last;
	int count = 0;
	while (num < n) {
		result = "";
		count = 1;
		for (size_t i = 1; i < last.length(); i++) {
			if (last[i] == last[i - 1]) ++count;
			else
			{
				result += (count + '0');
				result += last[i - 1];
				count = 1;
			}
		}
		result += (count + '0');
		result += last[last.length() - 1];
		last = result;
		++num;
	}
	return result;
}

// 0ms 9.3mb
// ~
int test_middle::test_35(std::vector<int>& nums, int target) {
	int result = 0;
	int i = 0;
	int j = nums.size() - 1;
	if (target < nums[i]) return i;
	if (target > nums[j])return j + 1;
	while (i < j) {
		if (nums[i] == target) return i;
		if (nums[j] == target)return j;
		if (nums[(i + j) / 2] == target) return (i + j) / 2;
		if (i == j - 1 && nums[i] < target && target < nums[j]) {
			return j;
		}
		if (nums[(i + j) / 2] < target) {
			i = (i + j) / 2;
		}
		else {
			j = (i + j) / 2;
		}
	}
	if (target <= nums[i]) return i;
	else return i + 1;
}

// 0ms 7mb
// improve storage
void test_middle::test_48(std::vector< std::vector<int>>&matrix) {
	int len = matrix.size();
	int i = len - 1;
	std::vector<int> temp;
	int j;
	while (i >= len / 2) {
		// up->temp
		temp.clear();
		for (j = len - 1 - i; j < i; j++) {
			temp.push_back(matrix[len - 1 - i][j]);
		}
		// left->up
		for (j = len - 1 - i; j < i; j++) {
			matrix[len - 1 - i][j] = matrix[len - 1 - j][len - 1 - i];
		}
		// down->left
		for (j = i; j > len - 1 - i; j--) {
			matrix[j][len - 1 - i] = matrix[i][j];
		}
		// right->down
		for (j = i; j > len - 1 - i; j--) {
			matrix[i][j] = matrix[len - 1 - j][i];
		}
		// temp(up)->right
		for (j = 0; j < temp.size(); j++) {
			matrix[len - 1 - i + j][i] = temp[j];
		}
		--i;
	}
}

// 8ms 16.1mb
// middle
int test_middle::test_45(std::vector<int>& nums) {
	int j = 0;
	int result = 0;
	int len = nums.size();
	int max = 0;
	int index = 0;
	int i = 0;
	while (i < len - 1) {
		j = 1;
		max = nums[i] + i;
		index = nums[i] + i;
		while (i < len && j <= nums[i]) {
			if (i + j < len && nums[i + j] + i + j >= max) {
				max = nums[i + j] + i + j;
				index = i + j;
			}
			if (i + j >= len - 1) {
				index = i + j;
				break;
			}
			++j;
		}
		++result;
		i = index;
	}
	return result;
}

// 12ms 7.7mb
// middle
std::string test_middle::test_43(std::string num1, std::string num2) {
	std::string result = "0";
	if (num1 == "0" || num2 == "0") return result;
	int temp = result.length();
	int k = 1;
	for (int i = num1.length() - 1; i >= 0; i--) {
		while (result.length() < (num1.length() - 1 - i) + num2.length()) {
			result = '0' + result;
		}
		for (int j = num2.length() - 1; j >= 0; j--) {
			temp = (num1[i] - '0') * (num2[j] - '0') + (result[j] - '0');
			result[j] = temp % 10 + '0';
			k = 1;
			while (temp / 10 > 0) {
				if (j - k >= 0) {
					result[j - k] = (result[j - k] - '0') + temp / 10 + '0';
					temp = temp - 10 * (temp / 10);
				}
				else {
					result = '0' + result;
					--k;
					continue;
				}
				++k;
			}
		}
	}
	return result;
}
