#include <iostream>
using namespace std;

//#include "test_listnode.h"
#include "test_compilations.h"
//#include "test_improve.h"
//#include "test_hard.h"
//#include "test_treenode.h"

void test_37(std::vector<std::vector<char>>& board) {

}

std::vector<std::vector<int>> test_39(std::vector<int>& candidates, int target) {
	std::vector<std::vector<int>> result;
	return result;
}

std::vector<std::vector<int>> test_40(std::vector<int>& candidates, int target) {
	return {};
}

bool test_290(string pattern, string s) {
	unordered_map<char, string> match;
	string tempstr = "";
	int i = 0;
	for (auto& c : pattern) {
		if (i >= s.size()) return false;
		tempstr = "";
		while (s[i] == ' ' && i<s.size()) ++i;
		while (s[i] != ' ' && i < s.size()) {
			tempstr += s[i];
			++i;
		}
		if (match.find(c) == match.end()) {
			match.insert({ c, tempstr });
		}
		else {
			if (match[c] != tempstr) return false;
		}
	}
	return true;
}

int main() {
	std::vector<int> a = { 0,0,0 };
	for (auto& p : test_39(a, 0)) {
		for (auto& q : p) {
			std::cout << q << " ";
		}
		std::cout << std::endl;
	}
	vector<int>b = { 0,1,0,3,12,1 };
	return 0;
}
