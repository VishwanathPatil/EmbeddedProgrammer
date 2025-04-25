#include <iostream>

using namespace std;

int main() {
	constexpr auto x = 3 * 2;
	auto y = x - 2;
	// x-=2; // x can't be modified since it is constant
//	static_assert(y==10, "Assert Y not 10"); non constant can't be used in constant expression
	static_assert(x==12, "Assert X not 12"); // function will assert at compile time

}
