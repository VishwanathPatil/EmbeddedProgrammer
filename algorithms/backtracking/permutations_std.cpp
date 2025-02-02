#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Permutation {
	private:
		vector<string> perms;
		void Perms(string &s, int startIndex);
		void swapZeroIndex(string &s,int startIndex, int index);
	public:
		vector<string> generatePerm(string &s);
		void printPerms();
};

vector<string> Permutation::generatePerm(string &s) {
	Perms(s,0);
	return perms;
}

void Permutation::swapZeroIndex(string &s, int startIndex, int index) {
	char c = s[index];
	s[index] = s[startIndex];
	s[startIndex] = c;
}

void Permutation::Perms(string &s, int startIndex) {
	if(startIndex == s.size()) {
		perms.push_back(s);
	}
	for(int i=startIndex; i < s.size(); i++) {
		swapZeroIndex(s,startIndex,i);
		Perms(s,startIndex+1);
		// Everybody down the order will revert to what it was when they got it 
		// eventually everything is reverted, ur iteration ur responsibility to revert
		swapZeroIndex(s,i,startIndex);
	}
}
void Permutation::printPerms() {
	for(auto s:perms)
		cout << s << endl;
}
int main() {
	Permutation P;
	string s("123");
	auto rv = P.generatePerm(s);
	P.printPerms();
}
