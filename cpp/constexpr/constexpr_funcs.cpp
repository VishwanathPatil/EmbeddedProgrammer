#include <iostream>

using namespace std;

constexpr int compute_compile_and_runtime(int x) {
	return x * x;
}

int main() {
	constexpr auto x = compute_compile_and_runtime(3);
	auto y = x - 2;
	const auto z = compute_compile_and_runtime(3); // executed runtime
	// x-=2; // x can't be modified since it is constant
//	static_assert(y==10, "Assert Y not 10"); non constant can't be used in constant expression
	static_assert(x==9, "Assert X not equal to 9"); // function will assert at compile time
	static_assert(x!=9, "Assert X equal to 9"); // function will assert at compile time

}
